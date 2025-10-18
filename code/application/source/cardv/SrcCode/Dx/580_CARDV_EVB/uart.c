
#include "uart.h"
///////////////////////////////////////////////////////////////////////////////
#define __MODULE__          Uart
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>
///////////////////////////////////////////////////////////////////////////////
//ttyS1---是UART2
const char uart2_pach[] = "/dev/ttyS1";
int uart2_fd;
ER uart2_open(void)
{
    uart2_fd = open(uart2_pach,O_RDWR | O_NOCTTY);
	if (uart2_fd < 0) {
		perror("open");
		return 0;
	}
    return E_OK;
}

void uart2_init(void)
{
	/*****
	termios 函数族提供了一个常规的终端接口，用于控制非同步通信端口。 这个结构包含了至少下列成员：
	tcflag_t c_iflag;      //输入模式 
	tcflag_t c_oflag;      // 输出模式 
	tcflag_t c_cflag;      // 控制模式 
	tcflag_t c_lflag;      // 本地模式 
	cc_t c_cc[NCCS];       // 控制字符 

	struct termios
	{unsigned short c_iflag; //输入模式标志
	unsigned short c_oflag;  //输出模式标志
	unsigned short c_cflag;  //控制模式标志
	unsigned short c_lflag;  //区域模式标志或本地模式标志或局部模式
	unsigned char c_line;    //行控制line discipline 
	unsigned char c_cc[NCC]; //控制字符特性
	};

	struct termios tty_std_termios = {
	 .c_iflag = ICRNL | IXON,
	 .c_oflag = OPOST | ONLCR,
	 .c_cflag = B38400 | CS8 | CREAD | HUPCL,
	 .c_lflag = ISIG | ICANON | ECHO | ECHOE | ECHOK |
	 ECHOCTL | ECHOKE | IEXTEN,
	 .c_cc = INIT_C_CC
	};
	******/
	struct termios opt;
	//获取串口参数opt
	tcgetattr(uart2_fd,&opt);
	//设置串口输出波特率
	//cfsetospeed(&opt,B9600);
	//设置串口输入波特率
	//cfsetispeed(&opt,B9600);
	 if (0 > cfsetspeed(&opt, B9600)) { //B9600 //B115200
	 	DBG_DUMP("cfsetspeed error\n");
	 }
	//设置为原始模式
	//cfmakeraw(&opt);
	//接收使能
	opt.c_cflag |= CREAD;
	//设置数据位数
	opt.c_cflag &= ~CSIZE;
	opt.c_cflag |= CS8;
	//
	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	//无校验位
	opt.c_cflag &= ~PARENB;
	opt.c_iflag &= ~INPCK;
	//opt.c_cflag &= ~INPCK;
	//设置停止位
	opt.c_cflag &= ~CSTOPB;
	//read为非阻塞状态,非规范模式
	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN] = 0;
	//更新配置
	tcsetattr(uart2_fd,TCSANOW,&opt);
	//清空串口缓冲区
	tcflush(uart2_fd, TCIOFLUSH);
	//printf("Device %s is set to 9600bps,8N1\n",uart2_pach);
	//DBG_DUMP("Device %s is set to 9600bps,8N1\n",uart2_pach);
}

ER uart2_getString(CHAR *pcString, UINT32 *pcBufferLen)
{
	unsigned int res = 0;
	char buf[800] = {0};
	//memset(buf,0,sizeof(buf));
	//tcflush(uart2_fd, TCIOFLUSH);
	//usleep(100000);
	res = read(uart2_fd,buf, sizeof(buf)-1);
	*pcBufferLen = res;
	//printf("===res=%u==%u==\r\n",res,*pcBufferLen);
	if (res > 0) {
		//给接受到的字符串加结束符
		buf[res] = '\0';
		// printf("Receive res = %d buf: %s\n",res, buf);
		// printf("%s\n",buf);
		// printf("-------------------------------------\n");
		memcpy(pcString, buf, sizeof(buf));
		// printf("%s\n",pcString);
		// printf("-------------------------------------\n");
	}
	else {
		return E_TMOUT;
	}
	return E_OK;
}

ER uart2_close(void)
{
	close(uart2_fd);
	return E_OK;
}
