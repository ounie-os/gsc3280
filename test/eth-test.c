#include <stdio.h>
#include <def.h>
#include "can_gsc3280.h"
#include "timer_gsc3280.h"
#include "gpio_gsc3280.h"
#include "gsc3280_mac.h"
#include "canfestival.h"
#include "OD_0_0.h"
#include "net.h"
#include "lwip/tcp.h"
#include "lwip/ip_addr.h"

#include "httpd.h"

const static u8_t http_html_hdr[] =  HTTP_HEAD;   	//http文件头
const static u8_t login[]= LOGIN;	 		//要显示的网页
const static u8_t led_ctrl_on[] =LED_CTRL_ON;
const static u8_t led_ctrl_off[] =LED_CTRL_OFF;


static int gpio_flag = 0;

static unsigned char FrameBuf[1500]=    
{        
    0x12,0x12,0x12,0x12,0x12,0x12,        
    0x22,0x22,0x22,0x22,0x22,0x22,        
    0x88,0xa4,0x0e,0x10    
};

void eth_send_test(void)
{
	int i;
	
	gsc3280_eth_init();

    for(i=0;i<1000;i++)
        gsc3280_mac_eth_tx(FrameBuf, 150);
}





/*
 * 函数名：http_recv
 * 描述  ：http接收到数据后的回调函数
 * 输入  ：tcp_arg设置的参数、tcp_pcb、pcb、err
 * 输出  ：err
 * 调用  ：内部调用 
 */

static err_t http_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
	{  
  	char * data = NULL;
	char *UserName =NULL;
	char *PassWord =NULL;
	char *LED_CMD  =NULL;
	char *ch =NULL;

	data = p->payload;	//把接收到的数据指针交给data

	 if (err == ERR_OK && p != NULL)	//判断是否非空
	 {	    	 	 			
		if(strncmp(data,"GET",3)==0) 
			{	
						
				/*第一次与服务器连接，打开登录页面，未输入登录信息*/
		  			tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* 发送http协议头部信息 */
	  				tcp_write(pcb,login,sizeof(login),0);              			/* 发送登录网页信息 */
			}
				  	   		
		else if(strncmp(data,"POST",4)==0)		
		  {
				LED_CMD	= strstr(data,"LED_CTRL=");					
				UserName = strstr(data,"UserName="); 		//截取UserName=
				PassWord = strstr(UserName,"PassWord=");	//截取PassWord=						

					if(UserName!=NULL && PassWord!=NULL)	 /*输入了用户名和密码*/
					{	
						ch = strchr(UserName,'&'); 				//把&替换为‘\0’
						*ch = '\0';
		
						UserName +=sizeof("UserName=")-1; 		//提取用户名。sizeof字符串包括终止符‘\0’ 
						PassWord += sizeof("PassWord=")-1;		//提取密码
						
						if(strcmp(UserName,"wildfire")==0 && strncmp(PassWord,"123456",6)==0)	/*输入的用户名和密码正确*/
						{	
							//LED1(ON);
						//	printf("\r\n提取出的用户名 =%s\r\n提取出的密码 =%s",UserName,PassWord);				 
						 	tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* 发送http协议头部信息 */
							tcp_write(pcb,led_ctrl_on,sizeof(led_ctrl_on),0);          /* 发送led控制网页信息 */
								
						 }
						 else /*输入的用户名和密码错误*/
						 {
						   	tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* 发送http协议头部信息 */
	  						tcp_write(pcb,login,sizeof(login),0);              			/* 发送登录网页信息 */
						 }
					}
					else if(LED_CMD !=NULL)	  /*接收到LED控制命令*/
					{
						if(strstr(LED_CMD,"LED_CTRL=ON"))	 /*检测是哪个命令：开\关*/
						{
							//LED1(ON);
							tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* 发送http协议头部信息 */
							tcp_write(pcb,led_ctrl_on,sizeof(led_ctrl_on),0);         /* 发送led控制网页信息 */
						}
						else if(strstr(LED_CMD,"LED_CTRL=OFF"))
						{
							//LED1(OFF);
						   	tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* 发送http协议头部信息 */
							tcp_write(pcb,led_ctrl_off,sizeof(led_ctrl_off),0);        /* 发送led控制网页信息 */
						} 								
					}			
		   	 }
		
    		pbuf_free(p);  /* 释放该pbuf段 */
	 }	  
  tcp_close(pcb);                                              			/* 关闭这个连接 */
  err = ERR_OK;
  
  return err;
}



/*
 * 函数名：http_accept
 * 描述  ：http web server的回调函数，建立连接后调用
 * 输入  ：tcp_arg设置的参数、pcb、err
 * 输出  ：err
 * 调用  ：内部调用 
 */
static err_t http_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{
  tcp_setprio(pcb, TCP_PRIO_MIN);     /* 设置回调函数优先级，当存在几个连接时特别重要，此函数必须调用*/
								
  tcp_recv(pcb,http_recv);            /* 设置TCP段到时的回调函数 */
     
  return ERR_OK;
}


/*
 * 函数名：httpd_init
 * 描述  ：初始化web server，初始化后才能显示网页
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用 
 */
void httpd_init(void)
{
  struct tcp_pcb *pcb;
  
  pcb = tcp_new();                           /* 建立通信的TCP控制块(pcb) */
  
  tcp_bind(pcb,IP_ADDR_ANY,80);             /* 绑定本地IP地址和端口号 */
 
  pcb = tcp_listen(pcb);                    /* 进入监听状态 */
  
  tcp_accept(pcb,http_accept);             /* 设置有连接请求时的回调函数 */

} 



static void timer3_handle(void)
{
    tcp_tmr();
    if (gpio_flag)
    {
        gpio_flag = 0;
        GPIOA_Set_Value(31, 0);
    }
    else
    {
        gpio_flag = 1;
        GPIOA_Set_Value(31, 1);
    }    
}

int main_loop(void)
{
    init_irq();

    GPIO_Enable();

    GPIOA_Set_Dir(31, GPIO_OUTPUT);

    lwip_stack_init();

    printf("lwip_stack_init done\n");

    gsc3280_eth_irq_init();

    printf("eth irq init done\n");

    generic_timer_init(TIMER3, (void *)timer3_handle);    /* 定时器中断中，调用systick_task函数 */

    timer_setup_by_ms(250, TIMER3);

#if 0
    stack_init();
#endif /* if 0 end*/

    httpd_init();

    while (1)
    {

    }
	
	return 0;
}
