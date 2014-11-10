#include     <stdio.h>      /*��׼�����������*/
#include     <stdlib.h>     /*��׼�����ⶨ��*/
#include     <unistd.h>     /*Unix ��׼��������*/
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      /*�ļ����ƶ���*/
#include     <termios.h>    /*PPSIX �ն˿��ƶ���*/
#include     <errno.h>      /*����Ŷ���*/
#include	"App.h"

//#define FALSE                   -1
//#define TRUE                     0

//int speed_arr11[] = { B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300};
//int name_arr11[] = {115200, 38400,  19200,  9600,  4800,  2400,  1200,  300 };
int PRT_STATE = 0;
char PRTBUF[1024];

int fd;


/*******************************************************************************************
��������	:	PRT_PaperState
��������	:	��ȡ��ӡ���Ƿ�ȱֽ
��ڲ���	:	��
���ڲ���	:	��
��������	:	��ֽ��TRUE����ֽ��ʧ�ܣ�FASLE��
����˵��	:	��
*******************************************************************************************/
int PRT_PaperState(void)
{
	unsigned char buffer[] = {0x10,0x04,0x04};
	unsigned char recv[16];
	int recvlen;
	int ret;
	memset(recv,0,16);
	write(fd,buffer,3);
	usleep(1000*50);
	if ((PRT_STATE) && (PRTBUF[0] == 0x00)) 
		return TRUE; 
		else return FALSE;
}

/*******************************************************************************************
��������	:	PRT_Black
��������	:	��ָ��ɸ��ݲ�ͬ�ĵ�Դ���������ӡ�ڶ�
��ڲ���	:	n�ĵ�����Χ��0x08~0x40;ȱʡֵ�� n=0x08
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_Black(char n)
{
	unsigned char buffer[]={0x10,0x05,0x05,n};
	write(fd,buffer,4);
	return TRUE;
}
/*******************************************************************************************
��������	:	PRT_Empty
��������	:	ִ��n �ַ��пհ״�ӡ
��ڲ���	:	n��������
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_Empty(int fd,char n)
{
	unsigned char buffer[]={0x1B,0x66,0x01,n};
	write(fd,buffer,4);
	return TRUE;
}

/*******************************************************************************************
��������	:	PRT_HZoom
��������	:	�������ͬʱ�����ַ��Ŀ��ȷŴ����͸߶ȷŴ�����
					�������������ַ����Ի������ȵ�n ���ͻ����߶ȵ� ����ӡ
��ڲ���	:	n���Ŵ���� ȡֵ��1~6
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_WHZoom(char n)
{
	if (n>6) return FALSE;
	unsigned char buffer[]={0x1B,0x57,n};
	write(fd,buffer,3);
	return TRUE;
}

/*******************************************************************************************
��������	:	PRT_HZoom
��������	:	�������������ַ����Ի����߶ȵ�n ����ӡ
��ڲ���	:	n���Ŵ���� ȡֵ��1~6
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_HZoom(char n)
{
	if (n>6) return FALSE;
	unsigned char buffer[]={0x1B,0x56,n};
	write(fd,buffer,3);
	return TRUE;
}

/*******************************************************************************************
��������	:	PRT_WZoom
��������	:	�������������ַ����Ի������ȵ�n ����ӡ
��ڲ���	:	n���Ŵ���� ȡֵ��1~6
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_WZoom(char n)
{
	if (n>6) return FALSE;
	unsigned char buffer[]={0x1B,0x55,n};
	write(fd,buffer,3);
	return TRUE;
}

/*******************************************************************************************
��������	:	PRT_LineSpace
��������	:	Ϊ����Ļ�����������n ���м�࣬��ֵ��ʾ�����ַ���֮��Ŀհ׵�����
��ڲ���	:	n�����е�����Ĭ��Ϊ0x03
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_LineSpace(char n)
{
	unsigned char buffer[]={0x1B,0x31,n};
	write(fd,buffer,3);
	return TRUE;
}

/*******************************************************************************************
��������	:	PRT_UnderLine
��������	:	�Ƿ��ӡ�»���
��ڲ���	:	state��ΪTRUEʱ��ӡ�»��ߣ�FASLE�ǲ���ӡ
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_UnderLine(char state)
{
	unsigned char buffer[]={0x1B,0x2B,state};
	
	write(fd,buffer,3);
	return TRUE;
}


/*******************************************************************************************
��������	:	PRT_PaperGo
��������	:	��ӡ��ֽN��
��ڲ���	:	n:��ֽ����; 
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_PaperGo(char n)
{
	unsigned char buffer[]={0x1B,0x4B,n};
	write(fd,buffer,3);
	return TRUE;
}

/*******************************************************************************************
��������	:	PRT_text
��������	:	��ӡ�ַ�
��ڲ���	:	cnt:���ݸ���,�ֽ�Ϊ��Ϊ,str:��ӡ������ָ��
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_text(unsigned char * str, int cnt)
{
	write(fd,str,cnt);
	return TRUE;
}

/*******************************************************************************************
��������	:	PRT_SetTextDouble
��������	:	���ô�ӡ���ַ����������뱶��
��ڲ���	:	
	WH�ַ�����, 16���Ʊ�ʾ,ǰһλΪ����,��һλΪ�߶� 
	EG:0x00 ��������,0x01:������0x02:���ߣ�0x03:��������
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_SetTextDouble(unsigned char WH)
{
	int i;
	unsigned char buffer[3] = {0x1c, 0x21, 0x00};
	switch (WH)
	{
	case 0: WH = 0x00; break;
	case 1: WH = 0x04; break;
	case 2: WH = 0x08; break;
	case 3: WH = 0x0c; break;
	}
	buffer[2] = WH;
	write(fd,buffer,3);
	return 0;
}

/*******************************************************************************************
��������	:	PRT_SetTextWH
��������	:	���ô�ӡ���ַ�����
��ڲ���	:	WH�ַ�����, 16���Ʊ�ʾ,ǰһλΪ����,��һλΪ�߶� EG:0x00 ��������,0x11:�Ŵ�һ��
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	height ��Ĭ�ϵ������Ϊ30
*******************************************************************************************/
int PRT_SetTextWH(unsigned char WH)
{
	unsigned char buffer[3] = {0x1d, 0x21, 0x00};	
	buffer[2] = WH;
	write(fd,buffer,3);
	return 0;
}

/*******************************************************************************************
��������	:	PRT_SetLineHeight
��������	:	���ô�ӡ���о�
��ڲ���	:	height�о�,ȡֵ0~255,��ȡֵΪ0ʱʹ�ô�ӡĬ�ϵ��и�
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	height ��Ĭ�ϵ������Ϊ30
*******************************************************************************************/
int PRT_SetLineHeight(unsigned char height)
{
	unsigned char buffer[3] = {0x1b, 0x33, 0x00};
	
	if (height == 0)
	{
		buffer[1] = 0x32;
		write(fd,buffer,2);
	} else
	{
		buffer[2] = height;
		write(fd,buffer,3);
	}
	return 0;
}


/*******************************************************************************************
��������	:	PRT_SetSpaceBetween
��������	:	���ô�ӡ���ַ����
��ڲ���	:	width���,ȡֵ0~255
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_SetSpaceBetween(unsigned char width)
{
	unsigned char buffer[3] = {0x1b, 0x20, 0x00};
	
	buffer[2] = width;
	write(fd,buffer,3);
	return 0;
}

/*******************************************************************************************
��������	:	PRT_Alignment
��������	:	���ö��뷽ʽ
��ڲ���	:	type ���뷽ʽ, 0x00 �����; 0x01 ����; 0x02 �Ҷ���
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_Alignment(unsigned char type)
{
	unsigned char buffer[3] = {0x1B, 0x61, 0x00};
	buffer[2] = type;
	write(fd,buffer,3);
	return 0;
}

/*******************************************************************************************
��������	:	PRT_SetInit
��������	:	���ô�ӡ��Ϊ����״̬
��ڲ���	:	��
���ڲ���	:	��
��������	:	�ɹ�:TRUE; ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/
int PRT_SetInit(void)
{
	unsigned char buffer[2] = {0x0B, 0x40};
	write(fd,buffer,2);
	return 0;
}


/*
void printer_write(int fd,char *buf,int len)
{
    int i=0;
    if(PRT_STATE==0)
    {
        memset(PRTBUF,0,1024);
        tcflush(fd,TCIFLUSH);
        write(fd,buf,len); 
        memset(PRTBUF,0,1024);
        read_datas_tty(fd,PRTBUF,0,1024);
  //      read_datas_tty(fd,PRTBUF,0,1024);

        if(strlen(PRTBUF)!=0&&PRTBUF[0]>' '&&PRTBUF[0]<'z') 
        {
            if(strstr(PRTBUF,"NO PAPER")!=0)
            {
                printf("stinrg=%s\n",PRTBUF);
                lcd_clear();
                text_out(0,0," ��ӡȱֽ");
                sleep(2);
                set_gpio(PRINTTER_PORT,PRINTER_PORT_NUM0,LOW);
                set_gpio(PRINTTER_PORT,PRINTER_PORT_NUM1,LOW);
                close(fd); 
                PRT_STATE=1; 
                return;
            }
        }
        PRT_STATE=0;
    }
}
*/

/*******************************************************************************************
��������	:	pritner_test
��������	:	��ӡ����
��ڲ���	:	��
���ڲ���	:	��
��������	:	�ɹ�:TRUE ʧ��:FALSE
����˵��	:	��
*******************************************************************************************/

int printer_test(int language)
{
    time_t tim;
    struct tm *ptm;
    tim=time(NULL);
    ptm=localtime(&tim);
    
    unsigned char time[1024];
    sprintf(time,"%d-%d-%d,%d-%d-%d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,
			ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
    
    unsigned char string[1024];
    int i=0;
    int count=0;
    int buf[3]={0};
    int num[7];

    unsigned char buf1[100]="  storm         pos��Ʊ��\r";
    unsigned char prtmsg[100]="..............................\r";
    unsigned char buf10[100]="Ticket No : 000510707400455\r";
    unsigned char buf3[100]="Price:";
    unsigned char buf4[100]="Date :";
    unsigned char buf5[100]="Conductor :0056\r";
    unsigned char buf6[100]="                 \r";
    unsigned char buf7[100]="��ע(REMARK):                 \r";
    unsigned char buf8[100]="ллʹ��                 \r";
    unsigned char buf9[100]="ǩ��(SIGNATURE) :                \r";
	lcd_clear();
    text_out(0,0,"�������");
    draw_rect(16,30,100,12,1);
    while(1)
    {
        buf[0]=0;
        buf[1]=99;
        read(Drivers[KEY].fd,(char *)buf,2);
		if(buf[0]==1)
		{
			ioctl(Drivers[KEY].fd,0,0);

			count++;
            printf("buf[1]:%d\n",buf[1]);
			switch(buf[1])
			{
			case 19:{
						printf("conut=%d\n",count);
						num[count-1]=1;
						text_out(25+11*count,32,"1");
						strcat(buf3,"1");
						break;
					}
			case 17:{
						printf("conut=%d\n",count);
						num[count-1]=2;
						text_out(25+11*count,32,"2");
						strcat(buf3,"2");
						break;
					}
			case 16:{
						num[count-1]=3;
						printf("conut=%d\n",count);
						text_out(25+11*count,32,"3");
						strcat(buf3,"3");
						break;
					}
			case 14:{
						printf("conut=%d\n",count);
						num[count-1]=4;
						text_out(25+11*count,32,"4");
						strcat(buf3,"4");
						break;
					}
			case 13:{
						printf("conut=%d\n",count);
						num[count-1]=5;
						text_out(25+11*count,32,"5");
						strcat(buf3,"5");
						break;
					}
			case 11:{
						printf("conut=%d\n",count);
						num[count-1]=6;
						text_out(25+11*count,32,"6");
						strcat(buf3,"6");
						break;
					}
			case  8:{
						printf("conut=%d\n",count);
						num[count-1]=7;
						text_out(25+11*count,32,"7");
						strcat(buf3,"7");
						break;
					}
			case  9:{
						printf("conut=%d\n",count);
						num[count-1]=8;
						text_out(25+11*count,32,"8");
						strcat(buf3,"8");
						break;
					}
			case  7:{
						printf("conut=%d\n",count);
						num[count-1]=9;
						text_out(25+11*count,32,"9");
						strcat(buf3,"9");
						break;
					}
			case  3:{
						printf("conut=%d\n",count);
						num[count-1]=0;
						text_out(25+11*count,32,"0");
						strcat(buf3,"0");
						break;
					}
			case  1:
					{
						printf("conut=%d\n",count);
						num[count-1]=23;
						break;
					}
			}
			if(count==6||num[count-1]==23)
			{
				break;
			}
		}
	}
    strcat(buf3,"\r");
	strcat(buf4,time);
	strcat(buf4,"\r");
    /*
    unsigned char buf1[]="           POSǩ����\r";
    unsigned char buf2[]="�ͻ������           �����Ʊ���\r";
    unsigned char buf3[]="��Ʒ����(Name) ��       \r";
    unsigned char buf4[]="                 \r";
    unsigned char buf5[]="�̻���MER NO.��       \r";
    unsigned char buf6[]="�ն˺ţ�                 00008\r";
    unsigned char buf7[]="����Ա�ţ�                  06\r";
    unsigned char buf9[]="����(card NO.) :         \r";
    unsigned char buf10[]="            622848785698748\r";
    unsigned char buf11[]="���� /ʱ��(TIME DATE)��       \r";
    unsigned char buf12[]="           2011/12/20 08:12:55\r";
    unsigned char buf13[]="�������ͣ�TYPE����     ��ֵ����\r";
    unsigned char buf14[]="��¼���ͣ�TYPE����     �������� \r";
    unsigned char buf15[]="���κ�(BATCH NO.)           0 \r";
    unsigned char buf16[]="��ˮ��(VOUCHER NO.)         0 \r";
    unsigned char buf17[]="��Ч��(EXP.DATE)    2011-12-30 \r";
    unsigned char buf18[]="�ο���REFER NO.           100 \r";
    unsigned char buf19[]="���(AMOUNT):             800\r";
    unsigned char buf20[]="                 \r";
    unsigned char buf21[]="��ע(REMARK):                 \r";
    unsigned char buf22[]="ллʹ��                 \r";
    unsigned char buf23[]="ǩ��(SIGNATURE) :                \r";
    
*/

    if(language == 0)
	  pos_menu3=pos_chnedit;
    else if(language == 1)
	  pos_menu3=pos_ukedit;

    struct timeval begintime, endtime;

    fd = open("/dev/ttyS2", O_RDWR );         
    if (fd == -1)	
    { 			
        perror("Can't Open Serial Port\n");
        exit(-1);	
    }	
    set_speed(fd,115200);
    set_Parity (fd, 8,1,'n'); 
	
	set_gpio(PRINTTER_PORT,PRINTER_PORT_NUM0,HIGH);
	set_gpio(PRINTTER_PORT,PRINTER_PORT_NUM1,HIGH);
    sleep(1);

    PRT_STATE=0;

    tcflush(fd,TCIFLUSH);
    write(fd,buf1,strlen(buf1)); 
    
    write(fd,prtmsg,strlen(prtmsg)); 
    write(fd,buf10,strlen(buf10)); 
    
    write(fd,buf3,strlen(buf3)); 
    write(fd,buf4,strlen(buf4)); 
    write(fd,buf5,strlen(buf5));
    write(fd,buf6,strlen(buf6)); 
    write(fd,buf7,strlen(buf7));

    write(fd,buf8,strlen(buf8));
    write(fd,buf9,strlen(buf9)); 
  /*  write(fd,buf10,strlen(buf10)); 
    write(fd,buf11,strlen(buf11)); 
    write(fd,buf12,strlen(buf12)); 
    write(fd,buf13,strlen(buf13)); 
    write(fd,buf14,strlen(buf14));
    write(fd,buf15,strlen(buf15));
    write(fd,buf16,strlen(buf16));
    write(fd,buf17,strlen(buf17));
    write(fd,buf18,strlen(buf18));
    write(fd,buf19,strlen(buf19));
    write(fd,buf20,strlen(buf20));
    write(fd,buf21,strlen(buf21));
    write(fd,buf22,strlen(buf22));
    write(fd,buf23,strlen(buf23));
*/
    gettimeofday(&begintime, NULL );//��ȡϵͳʱ�� 
    while(1)
    {
        memset(string,0,1024);
        read_datas_tty(fd,string,0,1024);
		gettimeofday(&endtime,NULL);
		sleep(4);PRT_STATE=1;
		break;
     /* if(strstr(string,"OK")!=0)break;
		else if(strstr(string,"NO PAPER")!=0){
            lcd_clear();
            text_out(0,0,pos_menu3[32]);
            sleep(2);
            PRT_STATE=1; 
            break;
        } else if((endtime.tv_sec-begintime.tv_sec)>10)
			{
				lcd_clear();
				text_out(0,0,"TIME OUT");
				sleep(1);
				PRT_STATE=1;
				break;
			}
	*/
    
    }
	set_gpio(PRINTTER_PORT,PRINTER_PORT_NUM0,LOW);
	set_gpio(PRINTTER_PORT,PRINTER_PORT_NUM1,LOW);
    close(fd); 
    return PRT_STATE; 
}