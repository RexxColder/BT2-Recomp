#include "m2c_macros.h"

M2C_UNK List_GetCount(M2C_UNK *);                   /* extern */
extern M2C_UNK gGscFileList __attribute__((section(".data")));

void Fade_DrawSlot2(void) {
    List_GetCount(&gGscFileList);
}
