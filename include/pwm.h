#ifndef __PWM_H_
#define __PWM_H_

#define PWM_BASE	0xBC105000

#define PWMODE	 	(PWM_BASE + 0x0)
#define PWMCTRL		(PWM_BASE + 0x4)
#define MCPWMCTRL	(PWM_BASE + 0x8)
#define PWMCAPCTRL 	(PWM_BASE + 0xc)
#define PWMCNTCTRL	(PWM_BASE + 0x10)
#define PWMIR		(PWM_BASE + 0x14)
#define PWMIER		(PWM_BASE + 0x18)
#define PWMTC0		(PWM_BASE + 0x1c)
#define PWMTC1		(PWM_BASE + 0x20)
#define PWMTC2		(PWM_BASE + 0x24)
#define PWMLIM0		(PWM_BASE + 0x28)
#define PWMLIM1		(PWM_BASE + 0x2C)
#define PWMLIM2		(PWM_BASE + 0x30)
#define PWMMR0_1	(PWM_BASE + 0x34)
#define PWMMR0_2	(PWM_BASE + 0x38)
#define PWMMR1_1	(PWM_BASE + 0x3c)
#define PWMMR1_2	(PWM_BASE + 0x40)
#define PWMMR2_1	(PWM_BASE + 0x44)
#define PWMMR2_2	(PWM_BASE + 0x48)
#define PWMCAP0		(PWM_BASE + 0x4c)
#define PWMCAP1		(PWM_BASE + 0x50)
#define PWMCAP2		(PWM_BASE + 0x54)
#define PWMMCR		(PWM_BASE + 0x58)
#define PWMDT		(PWM_BASE + 0x5c)
#define PWMCPR		(PWM_BASE + 0x60)
#define PWMLER		(PWM_BASE + 0x64)

#define MODE_PWM	0
#define MODE_MCPWM	1

#define SINGLE	15
#define POLA5	14
#define POLA4	13
#define POLA3	12
#define POLA2	11
#define POLA1	10
#define POLA0	9
#define PWMSEL2	8
#define PWMSEL1	7
#define PWMSEL0	6
#define PWMEN5	5
#define PWMEN4	4
#define PWMEN3	3
#define PWMEN2	2
#define PWMEN1	1
#define PWMEN0	0

#define DCMODE 	14
#define ACMODE 	13
#define INVBDC 	12
#define DTE2 	11
#define MC_POLA2 	10
#define CENTER2	9
#define MC_PWMEN2	8
#define DTE1	7
#define MC_POLA1	6
#define CENTER1 5
#define MC_PWMEN1	4
#define DTE0	3
#define MC_POLA0	2
#define CENTER0 1
#define MC_PWMEN0	0

#define HNFCAP2	14
#define HNFCAP1	13
#define HNFCAP0	12
#define RT2	11
#define RT1	10
#define RT0	9
#define CAP_IN2 6
#define CAP_IN1 3
#define CAP_IN0 0



#define TC2_DEGE 13
#define TC2_IN_N 11
#define TC1_DEGE 9
#define TC1_IN_N 7
#define TC0_DEGE 5
#define TC0_IN_N 3
#define CNTR2	 2
#define CNTR1	 1
#define CNTR0	 0

#define IRABORT	 12
#define IRCAP2	 11
#define IRCAP1	 10
#define IRCAP0	 9
#define IRLIM2	 8
#define IRLIM1	 7
#define IRLIM0	 6
#define IRMAT2_2 5
#define IRMAT2_1 4
#define IRMAT1_2 3
#define IRMAT1_1 2
#define IRMAT0_2 1
#define IRMAT0_1 0

#define IERABORT 12
#define IERCAP2  11
#define IERCAP1  10
#define IERCAP0  9
#define IERLIM2	 8
#define IERLIM1	 7
#define IERLIM0	 6
#define IERMAT2_2 5
#define IERMAT2_1 4
#define IERMAT1_2 3
#define IERMAT1_1 2
#define IERMAT0_2 1
#define IERMAT0_1 0

#define MR2_2STOP 5
#define MR2_1STOP 4
#define MR1_2STOP 3
#define MR1_1STOP 2
#define MR0_2STOP 1
#define MR0_1STOP 0

#define DT2	20
#define DT1	10
#define DT0	0

#define	CPB2	5
#define	CPA2	4
#define	CPB1	3
#define	CPA1	2
#define	CPB0	1
#define CPA0	0

#define LOAD_11 11
#define LOAD_10 10
#define LOAD_9 	9
#define LOAD_8 	8
#define LOAD_7 	7
#define LOAD_6 	6
#define LOAD_5 	5
#define LOAD_4 	4
#define LOAD_3 	3
#define LOAD_2 	2
#define LOAD_1 	1
#define LOAD_0 	0


#define REG(x) (1 << x)
#define REGS(x,v) (v << x)


#if 0
int pwm_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int pwm_single(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int pwm_stop(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
void test_pwm_input(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
void test_pwm_cap(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
int set_input(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
#endif
int test_pwm(int channel, int edge, int valid, int mr1, int mr2, int lim);
#endif
