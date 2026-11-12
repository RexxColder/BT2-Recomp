#include "m2c_macros.h"

M2C_UNK InitAlarm();                                /* extern */
M2C_UNK InitExecPS2();                              /* extern */
M2C_UNK InitSystemCallTableAddress();               /* extern */
M2C_UNK InitTLBFunctions();                         /* extern */
M2C_UNK InitThread();                               /* extern */
M2C_UNK InitTimer(M2C_UNK);                         /* extern */
M2C_UNK StartTimerSystemTime();                     /* extern */
M2C_UNK func_0033A238();                            /* extern */
M2C_UNK supplement_crt0();                          /* extern */

void func_00338520(void) {
    supplement_crt0();
    InitSystemCallTableAddress();
    InitAlarm();
    InitTimer(2);
    StartTimerSystemTime();
    InitThread();
    InitExecPS2();
    InitTLBFunctions();
    func_0033A238();
}
