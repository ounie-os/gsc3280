/*******************************************/
/*     FILE GENERATED BY iec2c             */
/* Editing this file is not recommended... */
/*******************************************/

#include "iec_std_lib.h"

// RESOURCE SDS

extern unsigned long long common_ticktime__;

#include "accessor.h"
#include "cff.h"
#include "POUS.h"

#include "POUS.c"

BOOL SD;
HHH SDS__REF;
#define REF SDS__REF

void SDS_init__(void) {
  BOOL retain;
  retain = 0;

  SD = __BOOL_LITERAL(FALSE);
  HHH_init__(&REF,retain);
}

void SDS_run__(unsigned long tick) {
  SD = !(tick % 1);
  HHH_body__(&REF);
}

