#include "common.h"

void func_002EA050(char *arg0);
extern char D_0037CC58[] __attribute__((section(".data")));

void func_002F5ED8(u8 *arg0) {
    if (arg0 == 0) {
        func_002EA050(D_0037CC58);
        return;
    }
    *(s16 *)(arg0 + 0x6A) = 0;
    *(s16 *)(arg0 + 0x60) = 0;
    *(s32 *)(arg0 + 0x64) = 0;
    *(s16 *)(arg0 + 0x68) = 0;
}
