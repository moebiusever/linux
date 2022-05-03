/*
*   Lora test
*   bkxr@outlook.com v202101
*/

#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <signal.h>

#define msleep(n) usleep(n*1000)

volatile	int fd;
char* dev   = NULL;
char* baudrate   = NULL;

pthread_mutex_t mut;
fd_set rd;
int nread,retval;
unsigned char cmd[12];
unsigned char buffer[12];
struct timeval timeout={0,100};


static speed_t getBaudrate(int baudrate)
{
	switch(baudrate) {
	case 0: return B0;
	case 50: return B50;
	case 75: return B75;
	case 110: return B110;
	case 134: return B134;
	case 150: return B150;
	case 200: return B200;
	case 300: return B300;
	case 600: return B600;
	case 1200: return B1200;
	case 1800: return B1800;
	case 2400: return B2400;
	case 4800: return B4800;
	case 9600: return B9600;
	case 19200: return B19200;
	case 38400: return B38400;
	case 57600: return B57600;
	case 115200: return B115200;
	case 230400: return B230400;
	case 460800: return B460800;
	case 500000: return B500000;
	case 576000: return B576000;
	case 921600: return B921600;
	case 1000000: return B1000000;
	case 1152000: return B1152000;
	case 1500000: return B1500000;
	case 2000000: return B2000000;
	case 2500000: return B2500000;
	case 3000000: return B3000000;
	case 3500000: return B3500000;
	case 4000000: return B4000000;
	default: return -1;
	}
}



int OpenDev(char *Dev)
{
	speed_t speed;

    int i=0;
    int fdt,c=0,num;
    struct termios oldtio,newtio;
	
    speed = B9600;
    fdt=open(Dev,O_RDWR | O_NONBLOCK| O_NOCTTY | O_NDELAY);
    if(fdt<0)
    {
        perror(Dev);
        exit(1);
    }
    tcgetattr(fdt,&oldtio);
    bzero(&newtio,sizeof(newtio));
    newtio.c_cflag = speed|CS8|CLOCAL|CREAD;
    newtio.c_cflag &= ~CSTOPB;
    newtio.c_cflag &= ~PARENB;
    newtio.c_iflag = IGNPAR;  
    newtio.c_oflag = 0;
    tcflush(fdt,TCIFLUSH);  
    tcsetattr(fdt,TCSANOW,&newtio);  
    tcgetattr(fdt,&oldtio);
    return fdt;
}

void read_port(void)
{  
		int i=0,num_read;
		int ret,nread = 0;
		memset(buffer,'\0',sizeof(buffer));
	/*	while(1){ */
				if((nread = read(fd, buffer, 6)) > 0){
						printf("Rec(%d bytes)", nread);				
				} 


		for(i = 0; i< strlen(buffer); i++)
		{
				printf("%.2x",buffer[i]);
		}
		printf("\n");

}
static void print_usage()
{
	 printf("\n"
	        " Test Application for lora driver\n"
	        "\n"
            "Example: \n"       
	        "fltest_lorar /dev/ttymxc5 0x01 0x02 0x03\n");
}


int main(int argc, char **argv)
{
	int fd;
	int val;
	int nread;
	char buffer[512];
	int n=0 ,i=0;
	struct timeval timeout={0,100};	

	if(argc < 2)
	{
		print_usage();
		return 1;
	}	

	dev = argv[1];
	for(i=0;i<(argc-2);i++)
		cmd[i] = strtol(argv[2+i], NULL,16);

	fd = OpenDev(dev);
	if (fd>0) {}
	else
	{
		printf("Can't Open Serial Port %s \n",dev);
		exit(0);
	}
	printf("Forlinx LoRa test.\n");

	memset(buffer,0,sizeof(buffer));

	printf("\nPress Ctrl + 'C' to stop.\n\n");
	/* SEND CMD */
	if (argc>2)
	{
	printf("Sending CMD.\n");
	write(fd,cmd, (argc-2));
	printf("Sent successfully.\n\n");
	}


	fd_set rd;
	while(1)
	{
		int ret;
		FD_ZERO(&rd);
		FD_SET(fd,&rd);
	    ret = select(fd+1,&rd,NULL,NULL,NULL);
		nread = read(fd, &buffer[n], 1);
		for(i = 0;i<nread; i++)
		{
			printf("Read byte[%d]: 0x%x\n", n, buffer[n]); 
			n += 1;
		}	
	}

	close(fd);
}
	







