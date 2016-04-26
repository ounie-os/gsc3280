void R_TRIG_init__(R_TRIG *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CLK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->M,__BOOL_LITERAL(FALSE),1)
}

// Code part
void R_TRIG_body__(R_TRIG *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,Q,(__GET_VAR(data__->CLK) && !(__GET_VAR(data__->M))));
  __SET_VAR(data__->,M,__GET_VAR(data__->CLK));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // R_TRIG_body__() 





void F_TRIG_init__(F_TRIG *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CLK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->M,__BOOL_LITERAL(FALSE),1)
}

// Code part
void F_TRIG_body__(F_TRIG *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,Q,(!(__GET_VAR(data__->CLK)) && !(__GET_VAR(data__->M))));
  __SET_VAR(data__->,M,!(__GET_VAR(data__->CLK)));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // F_TRIG_body__() 





void SR_init__(SR *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->S1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q1,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void SR_body__(SR *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,Q1,(__GET_VAR(data__->S1) || (!(__GET_VAR(data__->R)) && __GET_VAR(data__->Q1))));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // SR_body__() 





void RS_init__(RS *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->S,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q1,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void RS_body__(RS *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,Q1,(!(__GET_VAR(data__->R1)) && (__GET_VAR(data__->S) || __GET_VAR(data__->Q1))));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // RS_body__() 





void CTU_init__(CTU *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTU_body__(CTU *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTU_body__() 





void CTU_DINT_init__(CTU_DINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTU_DINT_body__(CTU_DINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTU_DINT_body__() 





void CTU_LINT_init__(CTU_LINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTU_LINT_body__(CTU_LINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTU_LINT_body__() 





void CTU_UDINT_init__(CTU_UDINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTU_UDINT_body__(CTU_UDINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTU_UDINT_body__() 





void CTU_ULINT_init__(CTU_ULINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTU_ULINT_body__(CTU_ULINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTU_ULINT_body__() 





void CTD_init__(CTD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

// Code part
void CTD_body__(CTD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTD_body__() 





void CTD_DINT_init__(CTD_DINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

// Code part
void CTD_DINT_body__(CTD_DINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTD_DINT_body__() 





void CTD_LINT_init__(CTD_LINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

// Code part
void CTD_LINT_body__(CTD_LINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTD_LINT_body__() 





void CTD_UDINT_init__(CTD_UDINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

// Code part
void CTD_UDINT_body__(CTD_UDINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTD_UDINT_body__() 





void CTD_ULINT_init__(CTD_ULINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
}

// Code part
void CTD_ULINT_body__(CTD_ULINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
    __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTD_ULINT_body__() 





void CTUD_init__(CTUD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTUD_body__(CTUD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q) && __GET_VAR(data__->CD_T.Q)))) {
      if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));
  __SET_VAR(data__->,QD,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTUD_body__() 





void CTUD_DINT_init__(CTUD_DINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTUD_DINT_body__(CTUD_DINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q) && __GET_VAR(data__->CD_T.Q)))) {
      if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));
  __SET_VAR(data__->,QD,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTUD_DINT_body__() 





void CTUD_LINT_init__(CTUD_LINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTUD_LINT_body__(CTUD_LINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q) && __GET_VAR(data__->CD_T.Q)))) {
      if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));
  __SET_VAR(data__->,QD,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTUD_LINT_body__() 





void CTUD_UDINT_init__(CTUD_UDINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTUD_UDINT_body__(CTUD_UDINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q) && __GET_VAR(data__->CD_T.Q)))) {
      if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));
  __SET_VAR(data__->,QD,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTUD_UDINT_body__() 





void CTUD_ULINT_init__(CTUD_ULINT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->QU,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->QD,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CV,0,retain)
  R_TRIG_init__(&data__->CD_T,retain);
  R_TRIG_init__(&data__->CU_T,retain);
}

// Code part
void CTUD_ULINT_body__(CTUD_ULINT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->CD_T.,CLK,__GET_VAR(data__->CD));
  R_TRIG_body__(&data__->CD_T);
  __SET_VAR(data__->CU_T.,CLK,__GET_VAR(data__->CU));
  R_TRIG_body__(&data__->CU_T);
  if (__GET_VAR(data__->R)) {
    __SET_VAR(data__->,CV,0);
  } else if (__GET_VAR(data__->LD)) {
    __SET_VAR(data__->,CV,__GET_VAR(data__->PV));
  } else {
    if (!((__GET_VAR(data__->CU_T.Q) && __GET_VAR(data__->CD_T.Q)))) {
      if ((__GET_VAR(data__->CU_T.Q) && (__GET_VAR(data__->CV) < __GET_VAR(data__->PV)))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) + 1));
      } else if ((__GET_VAR(data__->CD_T.Q) && (__GET_VAR(data__->CV) > 0))) {
        __SET_VAR(data__->,CV,(__GET_VAR(data__->CV) - 1));
      };
    };
  };
  __SET_VAR(data__->,QU,(__GET_VAR(data__->CV) >= __GET_VAR(data__->PV)));
  __SET_VAR(data__->,QD,(__GET_VAR(data__->CV) <= 0));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // CTUD_ULINT_body__() 





void TP_init__(TP *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

// Code part
void TP_body__(TP *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,CURRENT_TIME,__CURRENT_TIME);
  if ((((__GET_VAR(data__->STATE) == 0) && !(__GET_VAR(data__->PREV_IN))) && __GET_VAR(data__->IN))) {
    __SET_VAR(data__->,STATE,1);
    __SET_VAR(data__->,Q,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,START_TIME,__GET_VAR(data__->CURRENT_TIME));
  } else if ((__GET_VAR(data__->STATE) == 1)) {
    if (LE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __time_add(__GET_VAR(data__->START_TIME), __GET_VAR(data__->PT)), __GET_VAR(data__->CURRENT_TIME))) {
      __SET_VAR(data__->,STATE,2);
      __SET_VAR(data__->,Q,__BOOL_LITERAL(FALSE));
      __SET_VAR(data__->,ET,__GET_VAR(data__->PT));
    } else {
      __SET_VAR(data__->,ET,__time_sub(__GET_VAR(data__->CURRENT_TIME), __GET_VAR(data__->START_TIME)));
    };
  };
  if (((__GET_VAR(data__->STATE) == 2) && !(__GET_VAR(data__->IN)))) {
    __SET_VAR(data__->,ET,__time_to_timespec(1, 0, 0, 0, 0, 0));
    __SET_VAR(data__->,STATE,0);
  };
  __SET_VAR(data__->,PREV_IN,__GET_VAR(data__->IN));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // TP_body__() 





void TON_init__(TON *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

// Code part
void TON_body__(TON *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,CURRENT_TIME,__CURRENT_TIME);
  if ((((__GET_VAR(data__->STATE) == 0) && !(__GET_VAR(data__->PREV_IN))) && __GET_VAR(data__->IN))) {
    __SET_VAR(data__->,STATE,1);
    __SET_VAR(data__->,Q,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,START_TIME,__GET_VAR(data__->CURRENT_TIME));
  } else {
    if (!(__GET_VAR(data__->IN))) {
      __SET_VAR(data__->,ET,__time_to_timespec(1, 0, 0, 0, 0, 0));
      __SET_VAR(data__->,Q,__BOOL_LITERAL(FALSE));
      __SET_VAR(data__->,STATE,0);
    } else if ((__GET_VAR(data__->STATE) == 1)) {
      if (LE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __time_add(__GET_VAR(data__->START_TIME), __GET_VAR(data__->PT)), __GET_VAR(data__->CURRENT_TIME))) {
        __SET_VAR(data__->,STATE,2);
        __SET_VAR(data__->,Q,__BOOL_LITERAL(TRUE));
        __SET_VAR(data__->,ET,__GET_VAR(data__->PT));
      } else {
        __SET_VAR(data__->,ET,__time_sub(__GET_VAR(data__->CURRENT_TIME), __GET_VAR(data__->START_TIME)));
      };
    };
  };
  __SET_VAR(data__->,PREV_IN,__GET_VAR(data__->IN));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // TON_body__() 





void TOF_init__(TOF *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PT,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ET,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->PREV_IN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CURRENT_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->START_TIME,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

// Code part
void TOF_body__(TOF *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,CURRENT_TIME,__CURRENT_TIME);
  if ((((__GET_VAR(data__->STATE) == 0) && __GET_VAR(data__->PREV_IN)) && !(__GET_VAR(data__->IN)))) {
    __SET_VAR(data__->,STATE,1);
    __SET_VAR(data__->,START_TIME,__GET_VAR(data__->CURRENT_TIME));
  } else {
    if (__GET_VAR(data__->IN)) {
      __SET_VAR(data__->,ET,__time_to_timespec(1, 0, 0, 0, 0, 0));
      __SET_VAR(data__->,STATE,0);
    } else if ((__GET_VAR(data__->STATE) == 1)) {
      if (LE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __time_add(__GET_VAR(data__->START_TIME), __GET_VAR(data__->PT)), __GET_VAR(data__->CURRENT_TIME))) {
        __SET_VAR(data__->,STATE,2);
        __SET_VAR(data__->,ET,__GET_VAR(data__->PT));
      } else {
        __SET_VAR(data__->,ET,__time_sub(__GET_VAR(data__->CURRENT_TIME), __GET_VAR(data__->START_TIME)));
      };
    };
  };
  __SET_VAR(data__->,Q,(__GET_VAR(data__->IN) || (__GET_VAR(data__->STATE) == 1)));
  __SET_VAR(data__->,PREV_IN,__GET_VAR(data__->IN));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // TOF_body__() 





void DERIVATIVE_init__(DERIVATIVE *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XIN,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->XOUT,0,retain)
  __INIT_VAR(data__->X1,0,retain)
  __INIT_VAR(data__->X2,0,retain)
  __INIT_VAR(data__->X3,0,retain)
}

// Code part
void DERIVATIVE_body__(DERIVATIVE *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if (__GET_VAR(data__->RUN)) {
    __SET_VAR(data__->,XOUT,((((3.0 * (__GET_VAR(data__->XIN) - __GET_VAR(data__->X3))) + __GET_VAR(data__->X1)) - __GET_VAR(data__->X2)) / (10.0 * TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (TIME)__GET_VAR(data__->CYCLE)))));
    __SET_VAR(data__->,X3,__GET_VAR(data__->X2));
    __SET_VAR(data__->,X2,__GET_VAR(data__->X1));
    __SET_VAR(data__->,X1,__GET_VAR(data__->XIN));
  } else {
    __SET_VAR(data__->,XOUT,0.0);
    __SET_VAR(data__->,X1,__GET_VAR(data__->XIN));
    __SET_VAR(data__->,X2,__GET_VAR(data__->XIN));
    __SET_VAR(data__->,X3,__GET_VAR(data__->XIN));
  };

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // DERIVATIVE_body__() 





void HYSTERESIS_init__(HYSTERESIS *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->XIN1,0,retain)
  __INIT_VAR(data__->XIN2,0,retain)
  __INIT_VAR(data__->EPS,0,retain)
  __INIT_VAR(data__->Q,0,retain)
}

// Code part
void HYSTERESIS_body__(HYSTERESIS *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if (__GET_VAR(data__->Q)) {
    if ((__GET_VAR(data__->XIN1) < (__GET_VAR(data__->XIN2) - __GET_VAR(data__->EPS)))) {
      __SET_VAR(data__->,Q,0);
    };
  } else if ((__GET_VAR(data__->XIN1) > (__GET_VAR(data__->XIN2) + __GET_VAR(data__->EPS)))) {
    __SET_VAR(data__->,Q,1);
  };

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // HYSTERESIS_body__() 





void INTEGRAL_init__(INTEGRAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->R1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XIN,0,retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->Q,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XOUT,0,retain)
}

// Code part
void INTEGRAL_body__(INTEGRAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,Q,!(__GET_VAR(data__->R1)));
  if (__GET_VAR(data__->R1)) {
    __SET_VAR(data__->,XOUT,__GET_VAR(data__->X0));
  } else if (__GET_VAR(data__->RUN)) {
    __SET_VAR(data__->,XOUT,(__GET_VAR(data__->XOUT) + (__GET_VAR(data__->XIN) * TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
      NULL,
      (TIME)__GET_VAR(data__->CYCLE)))));
  };

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // INTEGRAL_body__() 





void PID_init__(PID *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PV,0,retain)
  __INIT_VAR(data__->SP,0,retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->KP,0,retain)
  __INIT_VAR(data__->TR,0,retain)
  __INIT_VAR(data__->TD,0,retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->XOUT,0,retain)
  __INIT_VAR(data__->ERROR,0,retain)
  INTEGRAL_init__(&data__->ITERM,retain);
  DERIVATIVE_init__(&data__->DTERM,retain);
}

// Code part
void PID_body__(PID *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,ERROR,(__GET_VAR(data__->PV) - __GET_VAR(data__->SP)));
  __SET_VAR(data__->ITERM.,RUN,__GET_VAR(data__->AUTO));
  __SET_VAR(data__->ITERM.,R1,!(__GET_VAR(data__->AUTO)));
  __SET_VAR(data__->ITERM.,XIN,__GET_VAR(data__->ERROR));
  __SET_VAR(data__->ITERM.,X0,(__GET_VAR(data__->TR) * (__GET_VAR(data__->X0) - __GET_VAR(data__->ERROR))));
  __SET_VAR(data__->ITERM.,CYCLE,__GET_VAR(data__->CYCLE));
  INTEGRAL_body__(&data__->ITERM);
  __SET_VAR(data__->DTERM.,RUN,__GET_VAR(data__->AUTO));
  __SET_VAR(data__->DTERM.,XIN,__GET_VAR(data__->ERROR));
  __SET_VAR(data__->DTERM.,CYCLE,__GET_VAR(data__->CYCLE));
  DERIVATIVE_body__(&data__->DTERM);
  __SET_VAR(data__->,XOUT,(__GET_VAR(data__->KP) * ((__GET_VAR(data__->ERROR) + (__GET_VAR(data__->ITERM.XOUT) / __GET_VAR(data__->TR))) + (__GET_VAR(data__->DTERM.XOUT) * __GET_VAR(data__->TD)))));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // PID_body__() 





void RAMP_init__(RAMP *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->RUN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->X0,0,retain)
  __INIT_VAR(data__->X1,0,retain)
  __INIT_VAR(data__->TR,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->CYCLE,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->XOUT,0.0,retain)
  __INIT_VAR(data__->XI,0,retain)
  __INIT_VAR(data__->T,__time_to_timespec(1, 0, 0, 0, 0, 0),retain)
}

// Code part
void RAMP_body__(RAMP *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,BUSY,__GET_VAR(data__->RUN));
  if (__GET_VAR(data__->RUN)) {
    if (GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->T), __GET_VAR(data__->TR))) {
      __SET_VAR(data__->,BUSY,0);
      __SET_VAR(data__->,XOUT,__GET_VAR(data__->X1));
    } else {
      __SET_VAR(data__->,XOUT,(__GET_VAR(data__->XI) + (((__GET_VAR(data__->X1) - __GET_VAR(data__->XI)) * TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (TIME)__GET_VAR(data__->T))) / TIME_TO_REAL((BOOL)__BOOL_LITERAL(TRUE),
        NULL,
        (TIME)__GET_VAR(data__->TR)))));
      __SET_VAR(data__->,T,__time_add(__GET_VAR(data__->T), __GET_VAR(data__->CYCLE)));
    };
  } else {
    __SET_VAR(data__->,XOUT,__GET_VAR(data__->X0));
    __SET_VAR(data__->,XI,__GET_VAR(data__->X0));
    __SET_VAR(data__->,T,__time_to_timespec(1, 0, 0, 0, 0, 0));
  };

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // RAMP_body__() 





void SEMA_init__(SEMA *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->CLAIM,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RELEASE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUSY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_INTERNAL,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void SEMA_body__(SEMA *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,Q_INTERNAL,(__GET_VAR(data__->CLAIM) || (__GET_VAR(data__->Q_INTERNAL) && !(__GET_VAR(data__->RELEASE)))));
  __SET_VAR(data__->,BUSY,__GET_VAR(data__->Q_INTERNAL));

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // SEMA_body__() 





void H8WT_init__(H8WT *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->YGB,0,retain)
  __INIT_VAR(data__->IDX,0,retain)
  __INIT_VAR(data__->BIT,-1,retain)
  __INIT_VAR(data__->INB,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->INU8,0,retain)
}

// Code part
void H8WT_body__(H8WT *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  //do_h8wt(data__);;

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // H8WT_body__() 





void H8RD_init__(H8RD *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->XFP,0,retain)
  __INIT_VAR(data__->IDX,0,retain)
  __INIT_VAR(data__->BIT,0,retain)
  __INIT_VAR(data__->OUTB,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->OUTU8,0,retain)
}

// Code part
void H8RD_body__(H8RD *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  //do_h8rd(data__);;

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // H8RD_body__() 





void HHH_init__(HHH *data__, BOOL retain) {
  __INIT_VAR(data__->AAA,0,retain)
  H8RD_init__(&data__->HRD,retain);
  H8WT_init__(&data__->HWT,retain);
}

// Code part
void HHH_body__(HHH *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->HRD.,XFP,0);
  __SET_VAR(data__->HRD.,IDX,480);
  __SET_VAR(data__->HRD.,BIT,0);
  H8RD_body__(&data__->HRD);
  __SET_VAR(data__->HWT.,YGB,0);
  __SET_VAR(data__->HWT.,IDX,1);
  __SET_VAR(data__->HWT.,BIT,1);
  __SET_VAR(data__->HWT.,INB,__GET_VAR(data__->HRD.OUTB));
  H8WT_body__(&data__->HWT);

  /* to humour the compiler, we insert a goto */
  goto __end;

__end:
  return;
} // HHH_body__() 





