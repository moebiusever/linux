#ifndef _A1006_H_
#define _A1006_H_

/*#define _DEBUG_A1006*/

#define A1006_CHIP_ADDR 	0x50
/*#define A1006_CIPHER_WRITE*/


#ifdef _DEBUG_A1006
#define a1006_debug(format, ...) printk(format, ##__VA_ARGS__)
#else
#define a1006_debug(format, ...)
#endif
#include "common.h"
#include <linux/cdev.h>

/* Private typedef -----------------------------------------------------------*/
/* a1006设备结构体 */
typedef struct {
	dev_t devid;			/*!< 设备号 */
	struct cdev cdev;		/*!< cdev */
	struct class *class;	/*!< 类 */
	struct device *device;	/*!< 设备 */
	struct device_node *nd; /*!< 设备节点 */
	int major;				/*!< 主设备号 */
	void *private_data;		/*!< 私有数据 */
	unsigned short ir, als, ps;	/*!< 光传感数据 */
}a1006_dev_t;



static inline void dbgprint_hexDump(char *text, uint8_t *buf, int len) 
{
#if 0
	int i;
	printk("\n%s:hexdump\n", text);
	for (i = 0; i < len; i++)
	{
		printk("%02x", *(buf + i));
		if ((i + 1) % 16 == 0)
			printk("\n");
	}
	printk("\nhexdup end \n\n");
#endif
}


#endif
