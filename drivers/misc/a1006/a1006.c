/* Copyright (C) 2020-2020
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
/*
 *  This is Linux kernel modules for a1006
 *  Revision History
 *  2021-1-27:    Ver. 1.0    New release 
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <asm/mach/map.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <asm/io.h>
#include <linux/device.h>
#include <linux/platform_device.h>

#include <linux/workqueue.h>

#include "a1006.h"
#include "app.h"
#include "a100x_host.h" 
#include "a100x_crypto.h"
#include "a100x_root.h"
#include "md5.h"


#define DEV_NAME "a1006"
#define DEV_CNT (1)
#define _DEBUG_A1006

static dev_t a1006_dev;
static struct cdev a1006_chr_dev;
struct class *class_a1006;
struct device *device_a1006;
struct device_node *a1006_device_node;

struct i2c_client *a1006_client = NULL;
                 
/* Private variables */
static a1006_dev_t a1006dev;
static a1006_dev_t *a1006dev_p = &a1006dev;

/*  Interface */
uint32_t a100x_interface_sendrecv(a1006_dev_t *dev,
		uint8_t *sendbuf,
		const uint32_t sendsize,
		uint8_t *recvbuf,
		const uint32_t recvsize)
{
	struct i2c_msg msg[2];
	uint32_t ret;
	int msg_count=1;
	u8 byte[256] = {0};
	struct i2c_client *client = (struct i2c_client*)dev->private_data;
	msg[0].addr = client->addr; /*!< a1006地址 */
	msg[0].flags = 0; /*!< 标记为写数据 */
	msg[0].buf = sendbuf;
	msg[0].len = sendsize;/*!< 要写入数据的长度 */	
	if(recvsize > 0)
	{
		msg_count = 2;
		/* msg[1]为要读取数据 */
		msg[1].addr = client->addr;	/*!< a1006地址 */
		msg[1].flags = I2C_M_RD;	/*!< 标记为读取数据 */
		msg[1].buf = recvbuf;	/*!< 读取数据的缓冲区 */
		msg[1].len = recvsize;		/*!< 读取数据的长度 */
	}
	
	ret = i2c_transfer(client->adapter, msg, msg_count);
	if (ret == msg_count)	ret = 0;
	else ret = -EREMOTEIO;
	return ret;
}

/* A1006 */
int user_check_a1006(a1006_dev_t *dev)
{
	uint8_t ifBuf[IFBUF_DLCERT_SIZE];
	uint8_t cert[CERT_SIZE];
	const uint32_t *rootPub;
	int ret,i;
	memset(ifBuf, 0, IFBUF_DLCERT_SIZE);
	
	a100x_host_init(ifBuf, ENTROPY_SIZE);
	if (a100x_host_uid(dev, 1, ifBuf) != 0)
	{
		printk("a100x_host_uid failed\n");
		return -1;
	}
	dbgprint_hexDump("uid", ifBuf, 18);	
		
	ret = a100x_host_status(dev);
	if (ret != 0){
		a1006_debug("a100x_host_status failed, %x\n", ret);
		return -1;
	}
	
	rootPub = prodRootPub;

	ret = a100x_host_cert(dev, CERT_SLOT, rootPub, ifBuf, cert, NULL);
	if (ret != 0 ){
		a1006_debug("a100x_host_cert failed, %x\n", ret);
		return -1;
	}
	ret = a100x_host_auth(dev, hostUID, hostUIDsize, (cert + CERT_PUBKEY_OFF), ifBuf, NULL);
	if (ret != 0){
		a1006_debug("a100x_host_auth failed, %x\n", ret);
		return -1;
	}

	if (a100x_host_cipher_check(dev) != 0){
		a1006_debug("a100x_host_cipher_check failed\n");
		return -1;
	}
		
	return 0;
}

int user_write_a1006(a1006_dev_t *dev)
{
	int ret;
	ret = a100x_host_write_cipher(dev); //写入用户自定义鉴权信息
	if (ret == 0)
	{
		printk("Warning: User permission authentication succeeded!\n");
		return 0;
	}
	return -1;
}
/* sys */
static ssize_t att_store(struct device *dev,   
                    struct device_attribute *attr,   
                    const char *buf, size_t count)   
{  
	unsigned long val;
    	int result = 0;

    	result = kstrtoul(buf, 10, &val);
    	if (result)
        return result;
    	if (val == 1)
    	{
    		user_write_a1006(a1006dev_p);
    	}
    	
    return count;  
}  

static ssize_t state_show(struct device *dev,
                        struct device_attribute *attr, char *buf)
{
	static  char sbuf[10]="ok";
	int ret;
	//struct a1006_dev_t *a1006d = dev_get_drvdata(dev);

	ret = user_check_a1006(a1006dev_p);
	if (ret == 0)
	{
		strcpy(sbuf,"ok");
	}
	else
	{
		strcpy(sbuf,"fail");
	}
    return sprintf(buf, "%s\n", sbuf);
}
static DEVICE_ATTR(auth, 0660, state_show, att_store);

/* sys end */

static int a1006_open(struct inode *inode, struct file *filp)
{
	filp->private_data = &a1006dev;
    return 0;
}
static ssize_t a1006_read(struct file *filp, char __user *buf, size_t cnt, loff_t *off)
{
	long err = 0;
	int ret;
	static char sbuf[10]="ok";

	ret = user_check_a1006(&a1006dev);
	if (ret == 0)
	{
		strcpy(sbuf,"ok");
	}
	else
	{
		strcpy(sbuf,"fail");
	}

	err = copy_to_user(buf, sbuf, sizeof(sbuf));
    return 0;
}
static int a1006_release(struct inode *inode, struct file *filp)
{
    return 0;
}
static struct file_operations a1006_chr_dev_fops =
{
    .owner = THIS_MODULE,
    .open = a1006_open,
    .read = a1006_read,
    .release = a1006_release,
};

static int a1006_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	pr_info("a1006: probed\n");
	int ret = -1;
	ret = alloc_chrdev_region(&a1006dev.devid, 0, DEV_CNT, DEV_NAME);
	if (ret < 0)
	{
		printk("fail to alloc a1006\n");
		goto alloc_err;
	}

//	a1006_chr_dev.owner = THIS_MODULE;
	cdev_init(&a1006dev.cdev, &a1006_chr_dev_fops);

	ret = cdev_add(&a1006dev.cdev, a1006dev.devid, DEV_CNT);
	if (ret < 0)
	{
		printk("fail to add cdev\n");
		goto add_err;
	}
	a1006dev.class = class_create(THIS_MODULE, DEV_NAME);
	a1006dev.device = device_create(a1006dev.class, NULL, a1006dev.devid, NULL, DEV_NAME);
	a1006dev.private_data = client;

	if(device_create_file(a1006dev.device, &dev_attr_auth)) {
		printk(KERN_ERR "device_add_groups() failed\n");
		goto add_err;
	}
	return 0;

add_err:
	unregister_chrdev_region(a1006dev.devid, DEV_CNT);
	printk("\n add_err error! \n");
alloc_err:

	return -1;
}

static int a1006_remove(struct i2c_client *client)
{
	device_destroy(a1006dev.class, a1006dev.devid);	  
	class_destroy(a1006dev.class);	
	cdev_del(&a1006dev.cdev);
	unregister_chrdev_region(a1006dev.devid, DEV_CNT);
	return 0;
}

static const struct i2c_device_id a1006_device_id[] = {
    {"forlinx,a1006", 0},
    { }
};

/*定义设备树匹配表*/
static const struct of_device_id a1006_match_table[] = {
    {.compatible = "forlinx,a1006", },
    { },
};

/*定义i2c设备结构体*/
struct i2c_driver a1006_driver = {
    .probe = a1006_probe,
    .remove = a1006_remove,
    .id_table = a1006_device_id,
    .driver = {
            .name = "forlinx,a1006",
            .owner = THIS_MODULE,
            .of_match_table = a1006_match_table,
    },
};


static int __init a1006_driver_init(void)
{
    return i2c_add_driver(&a1006_driver);
}
static void __exit a1006_driver_exit(void)
{
    i2c_del_driver(&a1006_driver);
}
module_init(a1006_driver_init);
module_exit(a1006_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bkxr@outlook.com");
MODULE_DESCRIPTION("a1006 sensor driver");

