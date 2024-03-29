#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"

// FUNCTION_BLOCK R_TRIG
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CLK)
  __DECLARE_VAR(BOOL,Q)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,M)

} R_TRIG;

// FUNCTION_BLOCK F_TRIG
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CLK)
  __DECLARE_VAR(BOOL,Q)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,M)

} F_TRIG;

// FUNCTION_BLOCK SR
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,S1)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(BOOL,Q1)

  // FB private variables - TEMP, private and located variables

} SR;

// FUNCTION_BLOCK RS
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,S)
  __DECLARE_VAR(BOOL,R1)
  __DECLARE_VAR(BOOL,Q1)

  // FB private variables - TEMP, private and located variables

} RS;

// FUNCTION_BLOCK CTU
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(INT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(INT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CU_T;

} CTU;

// FUNCTION_BLOCK CTU_DINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(DINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(DINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CU_T;

} CTU_DINT;

// FUNCTION_BLOCK CTU_LINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(LINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(LINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CU_T;

} CTU_LINT;

// FUNCTION_BLOCK CTU_UDINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(UDINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(UDINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CU_T;

} CTU_UDINT;

// FUNCTION_BLOCK CTU_ULINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(ULINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(ULINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CU_T;

} CTU_ULINT;

// FUNCTION_BLOCK CTD
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(INT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(INT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;

} CTD;

// FUNCTION_BLOCK CTD_DINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(DINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(DINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;

} CTD_DINT;

// FUNCTION_BLOCK CTD_LINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(LINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(LINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;

} CTD_LINT;

// FUNCTION_BLOCK CTD_UDINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(UDINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(UDINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;

} CTD_UDINT;

// FUNCTION_BLOCK CTD_ULINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(ULINT,PV)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(ULINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;

} CTD_ULINT;

// FUNCTION_BLOCK CTUD
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(INT,PV)
  __DECLARE_VAR(BOOL,QU)
  __DECLARE_VAR(BOOL,QD)
  __DECLARE_VAR(INT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;
  R_TRIG CU_T;

} CTUD;

// FUNCTION_BLOCK CTUD_DINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(DINT,PV)
  __DECLARE_VAR(BOOL,QU)
  __DECLARE_VAR(BOOL,QD)
  __DECLARE_VAR(DINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;
  R_TRIG CU_T;

} CTUD_DINT;

// FUNCTION_BLOCK CTUD_LINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(LINT,PV)
  __DECLARE_VAR(BOOL,QU)
  __DECLARE_VAR(BOOL,QD)
  __DECLARE_VAR(LINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;
  R_TRIG CU_T;

} CTUD_LINT;

// FUNCTION_BLOCK CTUD_UDINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(UDINT,PV)
  __DECLARE_VAR(BOOL,QU)
  __DECLARE_VAR(BOOL,QD)
  __DECLARE_VAR(UDINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;
  R_TRIG CU_T;

} CTUD_UDINT;

// FUNCTION_BLOCK CTUD_ULINT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CU)
  __DECLARE_VAR(BOOL,CD)
  __DECLARE_VAR(BOOL,R)
  __DECLARE_VAR(BOOL,LD)
  __DECLARE_VAR(ULINT,PV)
  __DECLARE_VAR(BOOL,QU)
  __DECLARE_VAR(BOOL,QD)
  __DECLARE_VAR(ULINT,CV)

  // FB private variables - TEMP, private and located variables
  R_TRIG CD_T;
  R_TRIG CU_T;

} CTUD_ULINT;

// FUNCTION_BLOCK TP
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,IN)
  __DECLARE_VAR(TIME,PT)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(TIME,ET)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(SINT,STATE)
  __DECLARE_VAR(BOOL,PREV_IN)
  __DECLARE_VAR(TIME,CURRENT_TIME)
  __DECLARE_VAR(TIME,START_TIME)

} TP;

// FUNCTION_BLOCK TON
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,IN)
  __DECLARE_VAR(TIME,PT)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(TIME,ET)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(SINT,STATE)
  __DECLARE_VAR(BOOL,PREV_IN)
  __DECLARE_VAR(TIME,CURRENT_TIME)
  __DECLARE_VAR(TIME,START_TIME)

} TON;

// FUNCTION_BLOCK TOF
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,IN)
  __DECLARE_VAR(TIME,PT)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(TIME,ET)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(SINT,STATE)
  __DECLARE_VAR(BOOL,PREV_IN)
  __DECLARE_VAR(TIME,CURRENT_TIME)
  __DECLARE_VAR(TIME,START_TIME)

} TOF;

// FUNCTION_BLOCK DERIVATIVE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,RUN)
  __DECLARE_VAR(REAL,XIN)
  __DECLARE_VAR(TIME,CYCLE)
  __DECLARE_VAR(REAL,XOUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,X1)
  __DECLARE_VAR(REAL,X2)
  __DECLARE_VAR(REAL,X3)

} DERIVATIVE;

// FUNCTION_BLOCK HYSTERESIS
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(REAL,XIN1)
  __DECLARE_VAR(REAL,XIN2)
  __DECLARE_VAR(REAL,EPS)
  __DECLARE_VAR(BOOL,Q)

  // FB private variables - TEMP, private and located variables

} HYSTERESIS;

// FUNCTION_BLOCK INTEGRAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,RUN)
  __DECLARE_VAR(BOOL,R1)
  __DECLARE_VAR(REAL,XIN)
  __DECLARE_VAR(REAL,X0)
  __DECLARE_VAR(TIME,CYCLE)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(REAL,XOUT)

  // FB private variables - TEMP, private and located variables

} INTEGRAL;

// FUNCTION_BLOCK PID
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,AUTO)
  __DECLARE_VAR(REAL,PV)
  __DECLARE_VAR(REAL,SP)
  __DECLARE_VAR(REAL,X0)
  __DECLARE_VAR(REAL,KP)
  __DECLARE_VAR(REAL,TR)
  __DECLARE_VAR(REAL,TD)
  __DECLARE_VAR(TIME,CYCLE)
  __DECLARE_VAR(REAL,XOUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,ERROR)
  INTEGRAL ITERM;
  DERIVATIVE DTERM;

} PID;

// FUNCTION_BLOCK RAMP
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,RUN)
  __DECLARE_VAR(REAL,X0)
  __DECLARE_VAR(REAL,X1)
  __DECLARE_VAR(TIME,TR)
  __DECLARE_VAR(TIME,CYCLE)
  __DECLARE_VAR(BOOL,BUSY)
  __DECLARE_VAR(REAL,XOUT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,XI)
  __DECLARE_VAR(TIME,T)

} RAMP;

// FUNCTION_BLOCK SEMA
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,CLAIM)
  __DECLARE_VAR(BOOL,RELEASE)
  __DECLARE_VAR(BOOL,BUSY)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,Q_INTERNAL)

} SEMA;

// FUNCTION_BLOCK H8WT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,YGB)
  __DECLARE_VAR(INT,IDX)
  __DECLARE_VAR(INT,BIT)
  __DECLARE_VAR(BOOL,INB)
  __DECLARE_VAR(INT,INU8)

  // FB private variables - TEMP, private and located variables

} H8WT;

// FUNCTION_BLOCK H8RD
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(INT,XFP)
  __DECLARE_VAR(INT,IDX)
  __DECLARE_VAR(INT,BIT)
  __DECLARE_VAR(BOOL,OUTB)
  __DECLARE_VAR(INT,OUTU8)

  // FB private variables - TEMP, private and located variables

} H8RD;

// PROGRAM HHH
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,AAA)
  H8RD HRD;
  H8WT HWT;

} HHH;

#endif //__POUS_H
