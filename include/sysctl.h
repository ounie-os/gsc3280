#ifndef __SYSCTL_H
#define __SYSCTL_H

#define SYSCTL_BASE             0xbc04a000
#define SYSCTL_PLL_FREQ         (0x00 + SYSCTL_BASE)
#define SYSCTL_PLL_CSR          (0x04 + SYSCTL_BASE)
#define SYSCTL_MOD_CTL0         (0x08 + SYSCTL_BASE)
#define SYSCTL_MOD_CTL1         (0x0C + SYSCTL_BASE)
#define SYSCTL_MOD_SRST0        (0x10 + SYSCTL_BASE)
#define SYSCTL_MOD_SRST1        (0x14 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_AHB       (0x18 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_APB       (0x1C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_SDIO      (0x20 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_LCDC      (0x24 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_I2C       (0x28 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_I2S       (0x2C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_CAN       (0x30 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_SPI0      (0x34 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_SPI1      (0x38 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_KEYPAD    (0x3C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_SCI0      (0x40 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_SCI1      (0x44 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_PWM0      (0x48 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_PWM1      (0x4C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_PWM2      (0x50 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_PWMR      (0x54 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_PS2_0     (0x58 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_PS2_1     (0x5C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART0     (0x60 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART1     (0x64 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART2     (0x68 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART3     (0x6C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART4     (0x70 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART5     (0x74 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART6     (0x78 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_UART7     (0x7C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_TIMER0    (0x80 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_TIMER1    (0x84 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_TIMER2    (0x88 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_TIMER3    (0x8C + SYSCTL_BASE)
#define SYSCTL_CLKDIV_GPIODB    (0x90 + SYSCTL_BASE)
#define SYSCTL_CLKDIV_CLKOUT    (0x94 + SYSCTL_BASE)
#define SYSCTL_WDT_CFG          (0x98 + SYSCTL_BASE)
#define SYSCTL_NFC_CFG          (0x9C + SYSCTL_BASE)
#define SYSCTL_DDR2_CFG         (0xA0 + SYSCTL_BASE)
#define SYSCTL_UART7_CFG        (0xA4 + SYSCTL_BASE)
#define SYSCTL_MAC_CFG          (0xA8 + SYSCTL_BASE)
#define SYSCTL_TSC_CFG          (0xAC + SYSCTL_BASE)
#define SYSCTL_IOMUX_CFG0       (0xB0 + SYSCTL_BASE)
#define SYSCTL_IOMUX_CFG1       (0xB4 + SYSCTL_BASE)
#define SYSCTL_USB_CFG          (0xB8 + SYSCTL_BASE)
#define SYSCTL_CLKPOL_CFG       (0xBC + SYSCTL_BASE)
#define SYSCTL_BOOTMODE_STATUS  (0xC0 + SYSCTL_BASE)
#define SYSCTL_BUSERR_STATUS    (0xC4 + SYSCTL_BASE)

#define DLL 0x0
#define DLH 0x1
#define IER 0x1
#define IIR 0x2
#define FCR 0x2
#define LCR 0x3
#define LSR 0x5
#define USR 0x1f

#define SYSCTL_MOD_APB    39
#define SYSCTL_MOD_CLKOUT 38
#define SYSCTL_MOD_EMI    37
#define SYSCTL_MOD_SYSCTL 36
#define SYSCTL_MOD_DDR2   35
#define SYSCTL_MOD_USB    34
#define SYSCTL_MOD_LCDC   33
#define SYSCTL_MOD_MAC    32
#define SYSCTL_MOD_SDIO   31
#define SYSCTL_MOD_NFC    30
#define SYSCTL_MOD_DMA    29
#define SYSCTL_MOD_ICTL   28
#define SYSCTL_MOD_GPIO   27
#define SYSCTL_MOD_WDT    26
#define SYSCTL_MOD_TIMER3 25
#define SYSCTL_MOD_TIMER2 24
#define SYSCTL_MOD_TIMER1 23
#define SYSCTL_MOD_TIMER0 22
#define SYSCTL_MOD_UART7  21
#define SYSCTL_MOD_UART6  20
#define SYSCTL_MOD_UART5  19
#define SYSCTL_MOD_UART4  18
#define SYSCTL_MOD_UART3  17
#define SYSCTL_MOD_UART2  16
#define SYSCTL_MOD_UART1  15
#define SYSCTL_MOD_UART0  14
#define SYSCTL_MOD_PS2_1   13
#define SYSCTL_MOD_PS2_0   12
#define SYSCTL_MOD_PWMR   11
#define SYSCTL_MOD_PWM2   10
#define SYSCTL_MOD_PWM1   9
#define SYSCTL_MOD_PWM0   8
#define SYSCTL_MOD_SCI1   7
#define SYSCTL_MOD_SCI0   6
#define SYSCTL_MOD_KPD    5
#define SYSCTL_MOD_SPI1   4
#define SYSCTL_MOD_SPI0   3
#define SYSCTL_MOD_CAN    2
#define SYSCTL_MOD_I2S    1
#define SYSCTL_MOD_I2C    0


static inline void sysctl_mod_disable(unsigned int module)
{
        volatile unsigned int addr =  SYSCTL_MOD_CTL0 + (((module & ~0x1fUL) >> 5) << 2);

        *(volatile unsigned int *)addr = *(volatile unsigned int *)addr & (~(1<<(module & 0x1fUL)));

}
static inline void sysctl_mod_enable(unsigned int module)
{
        volatile unsigned int addr =  SYSCTL_MOD_CTL0 + (((module & ~0x1fUL) >> 5) << 2);

        *(volatile unsigned int *)addr = *(volatile unsigned int *)addr | (1 << (module & 0x1fUL));

}

static inline unsigned int sysctl_mod_is_enabled(unsigned int module)
{
        volatile unsigned int addr = SYSCTL_MOD_CTL0 + (((module & ~0x1fUL) >> 5) << 2);
        return !!((*(volatile unsigned int *)addr) & (1 << (module & 0x1fUL)));
}

#define SYSCTL_IOMUX_UART6_FULL       49
#define SYSCTL_IOMUX_UART6_4W         48
#define SYSCTL_IOMUX_PWM_OUT45        47
#define SYSCTL_IOMUX_PWM_OUT23        46
#define SYSCTL_IOMUX_PWM_CAP2         45
#define SYSCTL_IOMUX_PWM_CAP1         44
#define SYSCTL_IOMUX_PWM_ABCAP0       43
#define SYSCTL_IOMUX_EMI_A1519        42
#define SYSCTL_IOMUX_EMI_A1214        41
#define SYSCTL_IOMUX_EMI_A11          40
#define SYSCTL_IOMUX_EMI_A10          39
#define SYSCTL_IOMUX_EMI_A39          38
#define SYSCTL_IOMUX_EMI_A02          37
#define SYSCTL_IOMUX_EMI_CSN2         36
#define SYSCTL_IOMUX_EMI_CSN1         35
#define SYSCTL_IOMUX_EMI_CSN0         34                
#define SYSCTL_IOMUX_USB              33
#define SYSCTL_IOMUX_JTAG             32
#define SYSCTL_IOMUX_EMI_WRD          31
#define SYSCTL_IOMUX_SPI1             30
#define SYSCTL_IOMUX_SPI0             29
#define SYSCTL_IOMUX_PWM_OUT01        28
#define SYSCTL_IOMUX_PS2_1            27
#define SYSCTL_IOMUX_PS2_0            26
#define SYSCTL_IOMUX_I2S              25
#define SYSCTL_IOMUX_I2C              24
#define SYSCTL_IOMUX_KEYPAD           23
#define SYSCTL_IOMUX_MAC_RMII         22
#define SYSCTL_IOMUX_MAC_MII          21
#define SYSCTL_IOMUX_LCDC             20
#define SYSCTL_IOMUX_SCI1_1           19
#define SYSCTL_IOMUX_SCI1_0           18
#define SYSCTL_IOMUX_SCI0             17
#define SYSCTL_IOMUX_CAN_1            16
#define SYSCTL_IOMUX_CAN_0            15
#define SYSCTL_IOMUX_UART7            14
#define SYSCTL_IOMUX_UART6            13
#define SYSCTL_IOMUX_UART5_TXE1       12
#define SYSCTL_IOMUX_UART5_TXE0       11
#define SYSCTL_IOMUX_UART5            10
#define SYSCTL_IOMUX_UART4_1          9
#define SYSCTL_IOMUX_UART4_0          8
#define SYSCTL_IOMUX_UART3_1          7
#define SYSCTL_IOMUX_UART3_0          6
#define SYSCTL_IOMUX_UART2            5
#define SYSCTL_IOMUX_UART1            4
#define SYSCTL_IOMUX_UART0            3
#define SYSCTL_IOMUX_NFC              2
#define SYSCTL_IOMUX_SDIO             1
#define SYSCTL_IOMUX_CLKOUT           0

static char iomux_tab[][16] = {
        {SYSCTL_IOMUX_CLKOUT,
         -1,
         -1,
         -1,
        },
	{SYSCTL_IOMUX_SDIO,
         -1,
         -1,
         SYSCTL_IOMUX_UART6/*WPROT,DTETECN(txd,rxd)*/,
         SYSCTL_IOMUX_UART3_0/*CLK,WPROT,DTETECTN(txe_0,txd_0,rxd_0)*/,
         SYSCTL_IOMUX_UART4_0/*DAT0,1,CMD(txd_0,txe_0,rxd_0*/,
         SYSCTL_IOMUX_CAN_0/*DAT2,3(rx_in_0,tx_out_0)*/,
         SYSCTL_IOMUX_PWM_OUT01/*PWREN(out_0)*/,
         SYSCTL_IOMUX_UART6_4W/*CLK,CMD(rstn,ctsn)*/,
         SYSCTL_IOMUX_UART6_FULL/*DAT0~3(dtrn,dcdn,ri,dsrn)*/,
         -1,
        },
	 {SYSCTL_IOMUX_NFC,
         -1,
         -1,
         SYSCTL_IOMUX_EMI_WRD/*NFDAT0~7,RNB,WEN,REN(d0~7,rdy,wen,oen)*/,
         -1,
        },
        {SYSCTL_IOMUX_UART0,
         -1,
         -1,
         SYSCTL_IOMUX_CAN_1/*TXD,RXD(tx_out_1,rx_in_1)*/,
         SYSCTL_IOMUX_UART5_TXE0/*RXD(txe_0)*/,
         SYSCTL_IOMUX_SCI1_0/*TXD(rstn_0)*/,
         -1,
        },
	{SYSCTL_IOMUX_UART1,
         -1,
         -1,
         SYSCTL_IOMUX_PWM_CAP1/*RXD*/,
         SYSCTL_IOMUX_JTAG/*TXD,RXD(jtdo,jtdi)*/,
         SYSCTL_IOMUX_PWM_OUT23/*TXD(out2)*/,
         -1,
        },
        {SYSCTL_IOMUX_UART2,
         -1,
         -1,
         SYSCTL_IOMUX_LCDC/*TXD,RXD(hsync,vclk)*/,
         -1,
        },
        {SYSCTL_IOMUX_UART3_0,
         -1,
         -1,
         SYSCTL_IOMUX_SDIO/*TXE_0,RXD_0,TXD_0(clk,detectn,wprot)*/,
         SYSCTL_IOMUX_UART6_4W/*TXE_0(rts_n)*/,
         SYSCTL_IOMUX_UART6/*RXD_0,TXD_0(rxd,txd)*/,
         -1,
        },
	{SYSCTL_IOMUX_UART3_1,
         -1,
         -1,
         SYSCTL_IOMUX_SCI0/*TXE_1(clk)*/,
         SYSCTL_IOMUX_LCDC/*TXD,RXD_1(vm,vsync)*/,
         SYSCTL_IOMUX_KEYPAD/*TXE_1(row3)*/,
         -1,
        },
        {SYSCTL_IOMUX_UART4_0,
         -1,
         -1,
         SYSCTL_IOMUX_UART6_FULL/*TXE_0,TXD_0(dcd_n,dtr_n)*/,
         SYSCTL_IOMUX_UART6_4W/*RXD_0(cts_n)*/,
         SYSCTL_IOMUX_SDIO/*TXE_0,TXD_0,RXD_0(dat1,dat0,cmd)*/,
         -1,
        },
	{SYSCTL_IOMUX_UART4_1,
         -1,
         -1,
         SYSCTL_IOMUX_SCI0/*TXE_1(io)*/,
         SYSCTL_IOMUX_LCDC/*TXD_1,RXD_1(rgb1,rgb0)*/,
         SYSCTL_IOMUX_KEYPAD/*TXE_1(col3)*/,
         -1,
        },
        {-1,/*SYSCTL_IOMUX_UART5*/
        },
        {SYSCTL_IOMUX_UART5_TXE0,
         SYSCTL_IOMUX_UART5,
         -1,
         SYSCTL_IOMUX_CAN_1/*TXE_0(rx_in_1)*/,
         SYSCTL_IOMUX_UART0/*TXE_0(rxd)*/,
         SYSCTL_IOMUX_SCI1_0/*TXD,RXD(io_0,clk_0)*/,
         -1,
        },
	{SYSCTL_IOMUX_UART5_TXE1,
         SYSCTL_IOMUX_UART5,
         -1,
         SYSCTL_IOMUX_EMI_CSN2/*TXE_1*/,
         SYSCTL_IOMUX_SCI1_0/*TXD,RXD(io_0,clk_0)*/,
         -1,
        },
        {SYSCTL_IOMUX_UART6,
         -1,
         -1,
         SYSCTL_IOMUX_SDIO/*RXD,TXD(detectn,wprot)*/,
         SYSCTL_IOMUX_UART3_0/*RXD,TXD(rxd,txd)*/,
         -1,
        },
        {SYSCTL_IOMUX_UART7,
         -1,
         -1,
         SYSCTL_IOMUX_LCDC/*RXD,TXD(rgb2,rgb3)*/
         -1,
        },
	{SYSCTL_IOMUX_CAN_0,
         -1,
         -1,
         SYSCTL_IOMUX_SDIO/*RX_IN_0,TX_OUT_0(dat2,dat3)*/,
         SYSCTL_IOMUX_UART6_FULL/*RX_IN_0,TX_OUT_0(ri,dsr_n)*/,
         -1,
        },
        {SYSCTL_IOMUX_CAN_1,
         -1,
         -1,
         SYSCTL_IOMUX_UART0/*RX_IN_1,TX_OUT_1(rxd,txd)*/,
         SYSCTL_IOMUX_UART5_TXE0/*RX_IN_1(txe_0)*/,
         SYSCTL_IOMUX_SCI1_0/*TX_OUT_1(rstn_0)*/,
         -1,
        },
	{SYSCTL_IOMUX_SCI0,
         -1,
         -1,
         SYSCTL_IOMUX_KEYPAD/*VCCEN,CLK,IO(row0,row3,col3)*/,
         SYSCTL_IOMUX_EMI_A02/*VCCEN(a1)*/,
         SYSCTL_IOMUX_UART4_1/*IO(txe_1)*/,
         SYSCTL_IOMUX_UART3_1/*CLK(txe_1)*/,
#ifdef SCI_USE_JTMS_AS_HOTPLUG
         SYSCTL_IOMUX_JTAG/*HOT_PLUG(jtms)*/,
         SYSCTL_IOMUX_PWM_CAP2/*HOT_PLUG*/,
#endif
         -1,
        },
	{SYSCTL_IOMUX_SCI1_0,
         -1,
         -1,
         SYSCTL_IOMUX_CAN_1/*RSTN_0(tx_out_1)*/,
         SYSCTL_IOMUX_UART0/*RSTN_0(txd)*/,
         SYSCTL_IOMUX_UART5/*IO_0,CLK_0(txd,rxd)*/,
         SYSCTL_IOMUX_I2S/*VCCEN(sdo)*/,
#ifdef SCI_USE_JTMS_AS_HOTPLUG
         SYSCTL_IOMUX_JTAG/*HOT_PLUG(jtms)*/,
         SYSCTL_IOMUX_PWM_CAP2/*HOT_PLUG*/,
#endif
         -1,
        },
        {SYSCTL_IOMUX_SCI1_1,
         -1,
         -1,
         SYSCTL_IOMUX_LCDC/*RSTN_1,CLK_1,IO_1(rgb4~6)*/,
         SYSCTL_IOMUX_I2S/*VCCEN(sdo)*/,
#ifdef SCI_USE_JTMS_AS_HOTPLUG
         SYSCTL_IOMUX_JTAG/*HOT_PLUG(jtms)*/,
         SYSCTL_IOMUX_PWM_CAP2/*HOT_PLUG*/,
#endif
         -1,
        },
	{SYSCTL_IOMUX_LCDC,
         -1,
         -1,
         SYSCTL_IOMUX_UART2/*HSYNC,VCLK(txd,rxd)*/,
         SYSCTL_IOMUX_UART3_1/*VM,VSYNC(txd,rxd)*/,
         SYSCTL_IOMUX_UART4_1/*RGB0,1(rxd,txd)*/,
         SYSCTL_IOMUX_UART7/*RGB2,3(rxd,txd)*/,
         SYSCTL_IOMUX_SCI1_1/*RGB4,5,6(rstn_1,clk_1,io_1)*/,
         SYSCTL_IOMUX_EMI_A39/*RGB8~14(a3~9)*/,
         SYSCTL_IOMUX_MAC_MII/*RGB7~14(mcoll,mcrs,mtxd2,mtxd3,mrxclk,mrxerr,mrxd2,mrxd3)*/,
         -1,
        },
        {SYSCTL_IOMUX_MAC_MII,
         -1,
         -1,
         SYSCTL_IOMUX_LCDC,
         SYSCTL_IOMUX_EMI_A39,
         SYSCTL_IOMUX_MAC_RMII,
         -1,
        },
	{SYSCTL_IOMUX_MAC_RMII,
         -1,
         -1,
         SYSCTL_IOMUX_MAC_MII,
         -1,
        },
        {SYSCTL_IOMUX_KEYPAD,
         -1,
         -1,
         SYSCTL_IOMUX_SPI0/*COL0,COL1,ROW1(sck,miso,mosi)*/,
         SYSCTL_IOMUX_EMI_A02/*COL0,ROW0(a0,a1)*/,
         SYSCTL_IOMUX_EMI_A1519/*COL1,ROW1(a18,a19)*/,
         SYSCTL_IOMUX_UART4_1/*COL3(txe_1)*/,
         SYSCTL_IOMUX_UART3_1/*ROW3(tx3_1)*/,
         SYSCTL_IOMUX_SCI0/*COL3,ROW0,ROW3(io,vccen,clk)*/,
         -1,
        },
	{SYSCTL_IOMUX_I2C,
         -1,
         -1,
         -1,
        },
        {SYSCTL_IOMUX_I2S,
         -1,
         -1,
         SYSCTL_IOMUX_EMI_CSN0/*WS*/,
         SYSCTL_IOMUX_EMI_CSN1/*SDI*/,
         SYSCTL_IOMUX_EMI_A11/*CLK*/,
         SYSCTL_IOMUX_PWM_OUT45/*CLK(out5)*/,
         SYSCTL_IOMUX_PWM_OUT01/*SDI(out1)*/,
         SYSCTL_IOMUX_SCI1_0/*SDO(vccen)*/,
         SYSCTL_IOMUX_SCI1_1/*SDO(vccen)*/,
         -1,
        },
	{SYSCTL_IOMUX_PS2_0,
         -1,
         -1,
         SYSCTL_IOMUX_PWM_OUT45/*DAT(out4)*/,
         SYSCTL_IOMUX_PWM_OUT23/*CLK(out3)*/,
         SYSCTL_IOMUX_EMI_A10/*DAT*/,
         SYSCTL_IOMUX_EMI_A1519/*DAT(a17)*/,
         -1,
        },
        {SYSCTL_IOMUX_PS2_1,
         -1,
         -1,
         SYSCTL_IOMUX_PWM_ABCAP0/*CLK,DAT*/,
         SYSCTL_IOMUX_EMI_A1519/*DAT,CLK(a15,a16)*/,
         -1,
        },
	{SYSCTL_IOMUX_PWM_OUT01,
         -1,
         -1,
         SYSCTL_IOMUX_I2S/*OUT1(sdi)*/,
         SYSCTL_IOMUX_EMI_CSN1/*OUT1*/,
         SYSCTL_IOMUX_SDIO/*OUT0(pwren)*/,
         -1,
        },
        {SYSCTL_IOMUX_SPI0,
         -1,
         -1,
         SYSCTL_IOMUX_KEYPAD/*MISO,MOSI,SCK(col1,row1,col0)*/,
         SYSCTL_IOMUX_EMI_A1519/*MISO,MOSI(a18,a19)*/,
         SYSCTL_IOMUX_EMI_A02/*SCK(a0)*/,
         -1,
        },
	{SYSCTL_IOMUX_SPI1,
         -1,
         -1,
         SYSCTL_IOMUX_EMI_A1214,
         -1,
        },
        {SYSCTL_IOMUX_EMI_WRD,
         -1,
         -1,
         SYSCTL_IOMUX_NFC,
         -1,
        },
	{SYSCTL_IOMUX_JTAG,
         -1,
         -1,
         SYSCTL_IOMUX_UART1/*JTDI,JTDO(rxd,txd)*/,
         SYSCTL_IOMUX_PWM_OUT23/*JTDO(out2)*/,
         SYSCTL_IOMUX_PWM_CAP1/*JTDI*/,
         SYSCTL_IOMUX_PWM_CAP2/*JTMS*/,
#ifdef SCI_USE_JTMS_AS_HOTPLUG
         SYSCTL_IOMUX_SCI0/*JTMS*/,
         SYSCTL_IOMUX_SCI1_0/*JTMS*/,
         SYSCTL_IOMUX_SCI1_1/*JTMS*/,
#endif
         -1,
        },
        {SYSCTL_IOMUX_USB,
         -1,
         -1,
         -1,
        },
	{SYSCTL_IOMUX_EMI_CSN0,
         -1,
         -1,
         SYSCTL_IOMUX_I2S/*ws*/,
         -1,
        },
        {SYSCTL_IOMUX_EMI_CSN1,
         -1,
         -1,
         SYSCTL_IOMUX_I2S/*sdi*/,
         SYSCTL_IOMUX_PWM_OUT01/*OUT1*/,
         -1,
        },
        {SYSCTL_IOMUX_EMI_CSN2,
         -1,
         -1,
         SYSCTL_IOMUX_UART5_TXE1,
         -1,
        },
	{SYSCTL_IOMUX_EMI_A02,
         -1,
         -1,
         SYSCTL_IOMUX_SCI0/*A1(sim0,vccen)*/,
         SYSCTL_IOMUX_SPI0/*A0(miso)*/,
         SYSCTL_IOMUX_KEYPAD/*A1,A0(row0,col0)*/,
         -1,
        },
        {SYSCTL_IOMUX_EMI_A39,
         -1,
         -1,
         SYSCTL_IOMUX_LCDC/*rgb8~14*/,
         SYSCTL_IOMUX_MAC_MII,
         -1,
        },
        {SYSCTL_IOMUX_EMI_A10,
         -1,
         -1,
         SYSCTL_IOMUX_PWM_OUT45/*OUT4*/,
         SYSCTL_IOMUX_PS2_0/*DAT_0*/,
         -1,
        },
	{SYSCTL_IOMUX_EMI_A11,
         -1,
         -1,
         SYSCTL_IOMUX_PWM_OUT45/*OUT5*/,
         SYSCTL_IOMUX_I2S/*clk*/,
         -1,
        },
        {SYSCTL_IOMUX_EMI_A1214,
         -1,
         -1,
         SYSCTL_IOMUX_SPI1/*miso,sck,mosi*/,
         -1,
        },
	{SYSCTL_IOMUX_EMI_A1519,
         -1,
         -1,
         SYSCTL_IOMUX_PS2_1 /*A15,A16(dat,clk)*/,
         SYSCTL_IOMUX_PS2_0 /*A17,a10(clk,dat)*/,
         SYSCTL_IOMUX_PWM_ABCAP0 /*A15,16(cap0,abort)*/,
         SYSCTL_IOMUX_PWM_OUT23 /*A17(out3)*/,
         SYSCTL_IOMUX_SPI0 /*A18,A19(miso,mosi)*/,
         SYSCTL_IOMUX_KEYPAD/*A18,A19(col1,row1)*/,
         -1,
        },
        {SYSCTL_IOMUX_PWM_ABCAP0,
         -1,
         -1,
         SYSCTL_IOMUX_PS2_1/*CAP0,ABORT(dat,clk)*/,
         SYSCTL_IOMUX_EMI_A1519/*CAP0,ABORT(a15,a16)*/,
         -1,
        },
	{SYSCTL_IOMUX_PWM_CAP1,
         -1,
         -1,
         SYSCTL_IOMUX_JTAG/*jtdi*/,
         SYSCTL_IOMUX_UART1/*rxd*/,
         -1,
        },
        {SYSCTL_IOMUX_PWM_CAP2,
         -1
         -1,
         SYSCTL_IOMUX_JTAG/*jtms*/,
#ifdef SCI_USE_JTMS_AS_HOTPLUG
         SYSCTL_IOMUX_SCI0/*JTMS*/,
         SYSCTL_IOMUX_SCI1_0/*JTMS*/,
         SYSCTL_IOMUX_SCI1_1/*JTMS*/,
#endif
         -1,
        },
	 {SYSCTL_IOMUX_PWM_OUT23,
         -1,
         -1,
         SYSCTL_IOMUX_UART1/*OUT2(txd)*/,
         SYSCTL_IOMUX_JTAG/*OUT2(jtdo)*/,
         SYSCTL_IOMUX_EMI_A1519/*OUT3(a17)*/,
         SYSCTL_IOMUX_PS2_0/*OUT3(clk)*/,
         -1,
        },
        {SYSCTL_IOMUX_PWM_OUT45,
         -1,
         -1,
         SYSCTL_IOMUX_PS2_0/*OUT4(dat)*/,
         SYSCTL_IOMUX_I2S/*OUT5(clk)*/,
         SYSCTL_IOMUX_EMI_A10/*OUT4*/,
         SYSCTL_IOMUX_EMI_A11/*OUT5*/,
         -1,
        },
	 {SYSCTL_IOMUX_UART6_4W,
         SYSCTL_IOMUX_UART6,
         -1,
         SYSCTL_IOMUX_SDIO/*CTS,RTS(cmd,clk)*/,
         SYSCTL_IOMUX_UART3_0/*RTS(txe_0)*/,
         SYSCTL_IOMUX_UART4_0/*CTS(rxd)*/,
        },
        {SYSCTL_IOMUX_UART6_FULL,
         SYSCTL_IOMUX_UART6_4W,
         SYSCTL_IOMUX_UART6,
         SYSCTL_IOMUX_SDIO/*DTR,DCD,RI,DSR(dat0~3)*/,
         SYSCTL_IOMUX_UART4_0/*TXD,TXE(dtr,dcd)*/,
         SYSCTL_IOMUX_UART3_0/*RTS(txe_0)*/,
         SYSCTL_IOMUX_CAN_0/*RI,dsr(rx_in,tx_out)*/,
        },
};

static inline int sysctl_iomux_is_enabled(unsigned int module)
{
        volatile unsigned int addr = SYSCTL_IOMUX_CFG0 + (((module & ~0x1fUL) >> 5) << 2);


        return !!(*(volatile unsigned int *)addr & (1 << (module & 0x1fUL)));

}
static inline void sysctl_iomux_disable(unsigned int module)
{
        volatile unsigned int addr = SYSCTL_IOMUX_CFG0 + (((module & ~0x1fUL) >> 5) << 2);

        *(volatile unsigned int *)addr = *(volatile unsigned int *)addr & (~(1<<(module & 0x1fUL)));
        if (iomux_tab[module][1] >=0) {
                 volatile unsigned int addr1 = SYSCTL_IOMUX_CFG0 + (((iomux_tab[module][1] & ~0x1fUL)>>5)<<2);
                *(volatile unsigned int *)addr1 = *(volatile unsigned int *)addr1 & (~(1 << (iomux_tab[module][1] & 0x1fUL)));
                 if (iomux_tab[module][2] >=0) {
                        addr1 = SYSCTL_IOMUX_CFG0 + (((iomux_tab[module][2] & ~0x1fUL)>>5)<<2);
                        *(volatile unsigned int *)addr1 = *(volatile unsigned int *)addr1 & (~(1 << (iomux_tab[module][2] & 0x1fUL)));
                }
        }

}

static inline int sysctl_iomux_enable(unsigned int module)
{
        int i;
        volatile unsigned int addr = SYSCTL_IOMUX_CFG0 + (((module & ~0x1fUL) >> 5) << 2);

        for (i=3;i<16;i++) {
                if(iomux_tab[module][i]>=0) {

                        if (sysctl_iomux_is_enabled(iomux_tab[module][i]))
                                return -1;//EACCES;
//                        sysctl_iomux_disable(iomux_tab[module][i]);
                }
                else
                        break;
        }

        if (iomux_tab[module][1] >=0) {
                volatile unsigned int addr1 = SYSCTL_IOMUX_CFG0 + (((iomux_tab[module][1] & ~0x1fUL)>>5)<<2);
                *(volatile unsigned int *)addr1 = *(volatile unsigned int *)addr1 | (1 << (iomux_tab[module][1] & 0x1fUL));
                if (iomux_tab[module][2] >=0) {
                        addr1 = SYSCTL_IOMUX_CFG0 + (((iomux_tab[module][2] & ~0x1fUL)>>5)<<2);
                        *(volatile unsigned int *)addr1 = *(volatile unsigned int *)addr1 | (1 << (iomux_tab[module][2] & 0x1fUL));
                }
        }

        *(volatile unsigned int *)addr = *(volatile unsigned int *)addr | (1 << (module & 0x1fUL));
        return 0;

}

#endif
