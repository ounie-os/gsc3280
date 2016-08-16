#include <def.h>
#include <sysctl.h>
#include "emi_gsc3280.h"

typedef struct
{
    u8 sm_read_pipe;
    u8 ready_mode;
    u8 page_size;
    u8 page_mode;
    u8 t_prc;    /* ҳģʽ������ʱ�� */
    u8 t_bta;    /* ����д��д�����Ƭѡ�ı䡢���������֮��ļ�����ڿ��� */
    u8 t_wp;    /* д�������� */
    u8 t_wr;    /* д��ַ/���ݱ���ʱ�� */
    u8 t_as;    /* д��ַ����ʱ�� */
    u8 t_rc;    /* ������ʱ�� */
}EMI_SMTMGR;

void emi_enable(void)
{
    sysctl_mod_enable(SYSCTL_MOD_EMI);
    writel(readl(SYSCTL_MOD_CTL1) | 0x20, SYSCTL_MOD_CTL1);
}

void emi_disable(void)
{
    sysctl_mod_disable(SYSCTL_MOD_EMI);
}

void emi_iomux_init(void)
{
    writel(readl(SYSCTL_IOMUX_CFG0) | (0x1<<31), SYSCTL_IOMUX_CFG0);     /* we oe rdy d0-d7 */
    writel(readl(SYSCTL_IOMUX_CFG1) | (0x1<<5),  SYSCTL_IOMUX_CFG1);    /* a0-a2 */
    writel(readl(SYSCTL_IOMUX_CFG1) | (0x1<<6),  SYSCTL_IOMUX_CFG1);    /* a3-a9 */
    writel(readl(SYSCTL_IOMUX_CFG1) | (0x1<<3),  SYSCTL_IOMUX_CFG1);    /* cs1 */
}

void emi_write(u32 base, u32 offset, u8 value)
{
    *((volatile u8 *)(base + offset)) = value;
}

u8 emi_read(u32 base, u32 offset)
{
    u8 value = 0;
    value = *((volatile u8 *)(base + offset));
    return value;
}

void emi_write_array(u32 base, u32 offset, u8* value, u16 count)
{
    u16 i=0;
    for (i=0;i<count;i++)
    {
        *((volatile u8 *)(base + offset + i)) = value[i];
    }
}

void emi_read_array(u32 base, u32 offset, u8* value, u16 count)
{
    u16 i=0;
    for (i=0;i<count;i++)
    {
        value[i] = *((volatile u8 *)(base + offset + i));
    }
}

static void emi_time_setup(u32 reg, u32 value)
{
    writel(value, reg);
}

void emi_init(void)
{
    EMI_SMTMGR timing;
    u32 value = 0;

    memset(&timing, 0, sizeof(EMI_SMTMGR));

    timing.t_prc = 1;    /* ҳģʽ������ʱ�� */
    timing.t_bta = 0;    /* ������� */
    timing.t_wp = 10;    /* д�������� */
    timing.t_wr = 2;    /* д��ַ/���ݱ���ʱ�� */
    timing.t_as = 1;    /* д��ַ����ʱ�� */
    timing.t_rc = 0;    /* ������ʱ�� */

    timing.page_mode = 1;    /* ����ҳģʽ������ */

    value = T_PRC(timing.t_prc) | T_BTA(timing.t_bta) | T_WP(timing.t_wp) | T_WR(timing.t_wr) | T_AS(timing.t_as) | T_RC(timing.t_rc);
    printf("EMI_SMTMGR = 0x%08x\n", value);
    emi_enable();
    emi_iomux_init();
    emi_time_setup(EMI_BASE_ADDR + EMI_SMTMGR_SET1, value);
}

