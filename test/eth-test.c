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
#include "netif/etharp.h"

#include "httpd.h"

const static u8_t http_html_hdr[] =  HTTP_HEAD;   	//http�ļ�ͷ
const static u8_t login[]= LOGIN;	 		//Ҫ��ʾ����ҳ
const static u8_t led_ctrl_on[] =LED_CTRL_ON;
const static u8_t led_ctrl_off[] =LED_CTRL_OFF;


static int gpio_flag = 0;
static u8 time_count = 0;

static unsigned char FrameBuf[1500]=    
{        
    0x12,0x12,0x12,0x12,0x12,0x12,        
    0x22,0x22,0x22,0x22,0x22,0x22,        
    0x88,0xa4,0x0e,0x10    
};

void eth_send_test(void)
{
	int i;
	
	//gsc3280_eth_init();

    for(i=0;i<10;i++)
        gsc3280_mac_eth_tx(FrameBuf, 150);
}





/*
 * ��������http_recv
 * ����  ��http���յ����ݺ�Ļص�����
 * ����  ��tcp_arg���õĲ�����tcp_pcb��pcb��err
 * ���  ��err
 * ����  ���ڲ����� 
 */

static err_t http_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
	{  
  	char * data = NULL;
	char *UserName =NULL;
	char *PassWord =NULL;
	char *LED_CMD  =NULL;
	char *ch =NULL;

	data = p->payload;	//�ѽ��յ�������ָ�뽻��data

	 if (err == ERR_OK && p != NULL)	//�ж��Ƿ�ǿ�
	 {	    	 	 			
		if(strncmp(data,"GET",3)==0) 
			{	
						
				/*��һ������������ӣ��򿪵�¼ҳ�棬δ�����¼��Ϣ*/
		  			tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
	  				tcp_write(pcb,login,sizeof(login),0);              			/* ���͵�¼��ҳ��Ϣ */
			}
				  	   		
		else if(strncmp(data,"POST",4)==0)		
		  {
				LED_CMD	= strstr(data,"LED_CTRL=");					
				UserName = strstr(data,"UserName="); 		//��ȡUserName=
				PassWord = strstr(UserName,"PassWord=");	//��ȡPassWord=						

					if(UserName!=NULL && PassWord!=NULL)	 /*�������û���������*/
					{	
						ch = strchr(UserName,'&'); 				//��&�滻Ϊ��\0��
						*ch = '\0';
		
						UserName +=sizeof("UserName=")-1; 		//��ȡ�û�����sizeof�ַ���������ֹ����\0�� 
						PassWord += sizeof("PassWord=")-1;		//��ȡ����
						
						if(strcmp(UserName,"wildfire")==0 && strncmp(PassWord,"123456",6)==0)	/*������û�����������ȷ*/
						{	
							//LED1(ON);
						//	printf("\r\n��ȡ�����û��� =%s\r\n��ȡ�������� =%s",UserName,PassWord);				 
						 	tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
							tcp_write(pcb,led_ctrl_on,sizeof(led_ctrl_on),0);          /* ����led������ҳ��Ϣ */
								
						 }
						 else /*������û������������*/
						 {
						   	tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
	  						tcp_write(pcb,login,sizeof(login),0);              			/* ���͵�¼��ҳ��Ϣ */
						 }
					}
					else if(LED_CMD !=NULL)	  /*���յ�LED��������*/
					{
						if(strstr(LED_CMD,"LED_CTRL=ON"))	 /*������ĸ������\��*/
						{
							//LED1(ON);
							tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
							tcp_write(pcb,led_ctrl_on,sizeof(led_ctrl_on),0);         /* ����led������ҳ��Ϣ */
						}
						else if(strstr(LED_CMD,"LED_CTRL=OFF"))
						{
							//LED1(OFF);
						   	tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
							tcp_write(pcb,led_ctrl_off,sizeof(led_ctrl_off),0);        /* ����led������ҳ��Ϣ */
						} 								
					}			
		   	 }
		
    		pbuf_free(p);  /* �ͷŸ�pbuf�� */
	 }	  
  tcp_close(pcb);                                              			/* �ر�������� */
  err = ERR_OK;
  
  return err;
}



/*
 * ��������http_accept
 * ����  ��http web server�Ļص��������������Ӻ����
 * ����  ��tcp_arg���õĲ�����pcb��err
 * ���  ��err
 * ����  ���ڲ����� 
 */
static err_t http_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{
  tcp_setprio(pcb, TCP_PRIO_MIN);     /* ���ûص��������ȼ��������ڼ�������ʱ�ر���Ҫ���˺����������*/
								
  tcp_recv(pcb,http_recv);            /* ����TCP�ε�ʱ�Ļص����� */
     
  return ERR_OK;
}


/*
 * ��������httpd_init
 * ����  ����ʼ��web server����ʼ���������ʾ��ҳ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ���� 
 */
void httpd_init(void)
{
  struct tcp_pcb *pcb;
  
  pcb = tcp_new();                           /* ����ͨ�ŵ�TCP���ƿ�(pcb) */
  
  tcp_bind(pcb,IP_ADDR_ANY,80);             /* �󶨱���IP��ַ�Ͷ˿ں� */
 
  pcb = tcp_listen(pcb);                    /* �������״̬ */
  
  tcp_accept(pcb,http_accept);             /* ��������������ʱ�Ļص����� */

} 



static void timer0_handle(void)
{
    time_count++;
    tcp_tmr();

    if (time_count >= 20)
    {
        etharp_tmr();
        time_count = 0;
    }
    
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
    GPIOC_Set_Value(23, 0);
}

void buserr_irq_handler(void)
{
    printf("bus err\n");
}

int main_loop(void)
{
    init_irq();

    request_irq(30, buserr_irq_handler, (void *)0);

    GPIO_Enable();

    GPIOA_Set_Dir(31, GPIO_OUTPUT);
    GPIOC_Set_Dir(23, GPIO_OUTPUT);

    lwip_stack_init();

    printf("lwip_stack_init done\n");

    gsc3280_eth_irq_init();

    printf("eth irq init done\n");

    generic_timer_init(TIMER0, (void *)timer0_handle);

    timer_setup_by_ms(250, TIMER0);

#if 0
    stack_init();
#endif /* if 0 end*/

#if 0
    httpd_init();
#endif /* if 0 end*/

    while (1)
    {

    }
	
	return 0;
}
