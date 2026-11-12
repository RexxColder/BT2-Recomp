#include "m2c_macros.h"

M2C_UNK McCard_Probe(M2C_UNK);                      /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK sceMcInit();                                /* extern */
extern M2C_UNK gMcCardPort __attribute__((section(".data")));

void McCard_Init(void) {
    memset(&gMcCardPort, 0, 0x48);
    sceMcInit();
    McCard_Probe(0);
}
