
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef OD_0_0_H
#define OD_0_0_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 OD_0_0_valueRangeTest (UNS8 typeValue, void * value);
const indextable * OD_0_0_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks);

/* Master node data struct */
extern CO_Data OD_0_0_Data;
extern UNS8 OD_0_0_trashvariables_TRASH1;		/* Mapped at index 0x2000, subindex 0x01 */
extern UNS8 OD_0_0_trashvariables_TRASH8;		/* Mapped at index 0x2000, subindex 0x02 */
extern UNS16 OD_0_0_trashvariables_TRASH16;		/* Mapped at index 0x2000, subindex 0x03 */
extern UNS32 OD_0_0_trashvariables_TRASH32;		/* Mapped at index 0x2000, subindex 0x04 */
extern UNS64 OD_0_0_trashvariables_TRASH64;		/* Mapped at index 0x2000, subindex 0x05 */
extern UNS8 beremiz__IB0_0_8_24576_1;		/* Mapped at index 0x2208, subindex 0x01 */
extern UNS8 Can_Bitrate;		/* Mapped at index 0x4000, subindex 0x00*/
extern UNS8 SYS_TICK_PERIOD_MS;		/* Mapped at index 0x4001, subindex 0x00*/
extern UNS8 Axis_Number;		/* Mapped at index 0x4002, subindex 0x00*/
extern UNS8 Axis_Types[4];		/* Mapped at index 0x4003, subindex 0x01 - 0x04 */
extern UNS8 Axis_Mods[4];		/* Mapped at index 0x4004, subindex 0x01 - 0x04 */
extern INTEGER8 Homing_methods[4];		/* Mapped at index 0x4005, subindex 0x01 - 0x04 */
extern UNS32 Homing_Speeds_during_search_for_switch[4];		/* Mapped at index 0x4006, subindex 0x01 - 0x04 */
extern UNS32 Homing_Speeds_during_search_for_zero[4];		/* Mapped at index 0x4007, subindex 0x01 - 0x04 */
extern UNS32 Homing_Accelerations[4];		/* Mapped at index 0x4008, subindex 0x01 - 0x04 */
extern INTEGER32 Homing_Position_offset[4];		/* Mapped at index 0x4009, subindex 0x01 - 0x04 */
extern UNS8 CAM_0[10];		/* Mapped at index 0x400A, subindex 0x01 - 0x0A */
extern UNS8 CAM_1[10];		/* Mapped at index 0x400B, subindex 0x01 - 0x0A */
extern UNS16 Interpolation_data_records_low[4];		/* Mapped at index 0x4010, subindex 0x01 - 0x04 */
extern UNS16 Interpolation_data_records_high[4];		/* Mapped at index 0x4011, subindex 0x01 - 0x04 */
extern UNS16 ControlWords[4];		/* Mapped at index 0x4012, subindex 0x01 - 0x04 */
extern UNS32 Max_accelerations[4];		/* Mapped at index 0x4020, subindex 0x01 - 0x04 */
extern UNS32 Max_Decelerations[4];		/* Mapped at index 0x4021, subindex 0x01 - 0x04 */
extern UNS32 Max_Velocitys[4];		/* Mapped at index 0x4022, subindex 0x01 - 0x04 */
extern UNS32 Position_Factor_Numerators[4];		/* Mapped at index 0x4030, subindex 0x01 - 0x04 */
extern UNS32 Position_Factor_Feed_Constants[4];		/* Mapped at index 0x4031, subindex 0x01 - 0x04 */
extern UNS32 Pulse_Per_Rotate[4];		/* Mapped at index 0x4032, subindex 0x01 - 0x04 */
extern UNS32 interrupt_register[4];		/* Mapped at index 0x4033, subindex 0x01 - 0x04 */
extern UNS8 finish_flag_register[4];		/* Mapped at index 0x4034, subindex 0x01 - 0x04 */
extern UNS8 Execute_flag_register[4];		/* Mapped at index 0x4035, subindex 0x01 - 0x04 */
extern UNS8 command_to_request_type[4];		/* Mapped at index 0x4036, subindex 0x01 - 0x04 */
extern REAL32 Pulse_Equivalent[4];		/* Mapped at index 0x4037, subindex 0x01 - 0x04 */
extern UNS32 Soft_Limits_Low[4];		/* Mapped at index 0x4040, subindex 0x01 - 0x04 */
extern UNS32 Soft_Limits_High[4];		/* Mapped at index 0x4041, subindex 0x01 - 0x04 */
extern UNS8 Gear_Inputs[4];		/* Mapped at index 0x4050, subindex 0x01 - 0x04 */
extern UNS8 Gear_Outputs[4];		/* Mapped at index 0x4051, subindex 0x01 - 0x04 */
extern UNS32 Gear_Leads[4];		/* Mapped at index 0x4053, subindex 0x01 - 0x04 */
extern UNS8 Modbus_Bitrate;		/* Mapped at index 0x4100, subindex 0x00*/
extern UNS8 Modbus_RTU_or_ASCII;		/* Mapped at index 0x4101, subindex 0x00*/
extern UNS8 Modbus_Slave_Id;		/* Mapped at index 0x4102, subindex 0x00*/
extern UNS8 Modbus_Parity;		/* Mapped at index 0x4103, subindex 0x00*/
extern UNS16 Modbus_Coils[4];		/* Mapped at index 0x4110, subindex 0x01 - 0x04 */
extern UNS16 Modbus_Holdings[100];		/* Mapped at index 0x4111, subindex 0x01 - 0x64 */
extern UNS8 Debug_COM_Port_Birtrate;		/* Mapped at index 0x4120, subindex 0x00*/
extern UNS8 Leds[4];		/* Mapped at index 0x4200, subindex 0x01 - 0x04 */
extern UNS8 Keys[4];		/* Mapped at index 0x4201, subindex 0x01 - 0x04 */
extern UNS8 beremiz__QB0_0_8_25088_1;		/* Mapped at index 0x4208, subindex 0x01 */

#endif // OD_0_0_H
