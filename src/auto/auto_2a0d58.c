#include "common.h"

/* Timer_Reset */
u32 Timer_Reset(u32 a0) { return BtlCtrl_SetChargeFx(a0, 0); }
