#include "App.h"

#define MODE_INITAUTHENTICA 0x05

#define MODE_GETNUM 0x0b

#define MI_OK 0x00

char cardnum1[30] = { 0, };

char cardnum2[30] = { 0, };

char cardnum3[30] = { 0, };

typedef struct
{
	unsigned char key[6];
	unsigned char mode;
	unsigned char* rtValue;
	unsigned char* buf;
	unsigned int keymode;
	unsigned char* cardid;
}key_buf;

typedef struct 
{
	unsigned int show;		//对应show_n显示的位置
	unsigned int count;		//对应n字符总位数
	unsigned int real;		//对应real_n和指针对应指向的位置
	unsigned char buf[100];
	unsigned int xPos;		//对应x坐标指向的位置
}rf_buf;

unsigned char buf2[16];
unsigned char buffer[16];
unsigned char rtValue2;
unsigned int j;
unsigned long tmp=0;
unsigned char mifare_buf[20];
unsigned int Timeout= 10;
int IO_flag = 1;
//int buf[3] = { 0 };
struct timeval begintime, currenttime;
int fd_mifare;

key_buf keyBuf2;


void Rc531_test()
{
	memset(keyBuf2.key, 0xff, 6);

	keyBuf2.buf = buf2;
	keyBuf2.rtValue = &rtValue2;

	keyBuf2.mode = MODE_GETNUM;	//设置模式为获取射频卡卡号
	gettimeofday(&begintime, NULL);	//获取开始刷卡的时间

	gettimeofday(&begintime, NULL);										//获取开始刷卡的时间

	while (1) 
	{
		IO_flag = ioctl(Drivers[RC531].fd, 0, 0);										//初始化RC531

		memset(&keyBuf2,0,6);
		tmp=0;
		if(read(Drivers[RC531].fd, &keyBuf2, 6)!=-1)
		{
			memset(mifare_buf, 0, 20);

			for (j = 0; j < 4; j++)										//将16进制卡号转换成十进制数
			{
				tmp += *((keyBuf2.buf) + 3 - j) << j * 8;
			}

			sprintf(mifare_buf, "%u", (unsigned long) tmp);
			printf("card num is %s\n",mifare_buf);
			return;
		} 
		else 
		{
			gettimeofday(&currenttime, NULL);	//获取当前的时间
			if ((currenttime.tv_sec - begintime.tv_sec) > Timeout)	//刷卡超时
			{
				printf("time out\n");
				return;
			}
		}
	}
}

int write_card(int key_fd)
{
	unsigned char buf2[32] = {0, };
	int ret = 1;

	memset(keyBuf2.key, 0xff, 6);
	buf2[0]=100;
	printf("%d\n",buf2[0]);

	keyBuf2.buf = buf2;
	keyBuf2.rtValue = &rtValue2;

	keyBuf2.mode = MODE_GETNUM;
	keyBuf2.keymode = 1;

	gettimeofday(&begintime, NULL);	//获取开始刷卡的时间

	while (1) 
	{
		int buf[2];
		buf[0] = 0;
		buf[1] = 99;
		read(key_fd, (char *) buf, 2);
		if (buf[1]==KEY_CANCEL) //退出键
		{
			ioctl(Drivers[KEY].fd,0,0);
			show_function(1);
			buf[1]=99;
			return 1;
		}

		ret = read(Drivers[RC531].fd,&keyBuf2,6);
		if (ret == 0) 
		{
			keyBuf2.buf[0] = 100;
			rtValue2=write(Drivers[RC531].fd, &keyBuf2, 6 );	//读取射频卡卡号

			if (rtValue2 == MI_OK) {					
				printf("write card suceed\n");	
				return 0;
			} else {
				printf("write card error\n");
			}
			break;
		} else {
			gettimeofday(&currenttime, NULL);	//获取当前的时间
			if ((currenttime.tv_sec - begintime.tv_sec) > 5)	//刷卡超时
			{
				printf("time out\n");
				return -1;
			}
		}
	}
}

void read_card()
{
	key_buf keyBuf1;
	unsigned char rtValue1;
	unsigned char buf1[16] = {0,};
	int ret = -1;
	int j;
	char temp[4] = {0,};

	memset(keyBuf1.key, 0xff, 6);

	keyBuf1.buf = buf1;
	keyBuf1.rtValue = &rtValue1;

	keyBuf1.mode = MODE_GETNUM;
	keyBuf1.keymode = 1;

	gettimeofday(&begintime, NULL);												//获取开始刷卡的时间
	while (1) 
	{
		ret = read(Drivers[RC531].fd, &keyBuf1, 6);												//读取射频卡卡号
		if (ret == 0) 
		{
			lseek (Drivers[RC531].fd, 5, SEEK_SET);
			read(Drivers[RC531].fd, &keyBuf1, 6);												//读取射频卡卡号
			printf("cardnum=%d\n",keyBuf1.buf[0]);
			if (rtValue1 == MI_OK)
			{		
				for (j = 0; j < 16; j++)
				{
					if(j < 6)
					{
						sprintf(temp, "%x ", *((keyBuf1.buf) + j));
						strcat(cardnum1, temp);
					}
					else
					{
						if (j < 12)
						{
							sprintf(temp, "%x ", *((keyBuf1.buf) + j));
							strcat(cardnum2, temp);
						}
						else
						{
							sprintf(temp, "%x ", *((keyBuf1.buf) + j));
							strcat(cardnum3, temp);
						}
					}
				}						
				//			printf("%s	%s	%s\n",cardnum1,cardnum2,cardnum3);
			}
			else
			{
				printf("read card error\n");		
			}
			break;
		} 
		else 
		{
			gettimeofday(&currenttime, NULL);							//获取当前的时间
			if ((currenttime.tv_sec - begintime.tv_sec) > Timeout)	//刷卡超时
			{
				printf("time out\n");
				break;
			}
		}
	}
}
