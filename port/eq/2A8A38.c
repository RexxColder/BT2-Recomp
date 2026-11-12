#include "common.h"

extern s32 func_002A89E8(s32 arg0);
extern void func_002AC520(void);
extern void func_002A8A20(void);
extern u8 *D_00387F2C;
extern u8 D_003B2608[];
extern u8 D_003B29C0[];

s32 func_002A8A38(void) {
    if (func_002A89E8(0) != 0) {
        __builtin_memcpy(D_003B2608, D_00387F2C + 0xE0, 0x4C);
        __builtin_memcpy(D_003B29C0, D_00387F2C + 0xE0, 0x4C);
        func_002AC520();
    }
    func_002A8A20();
    __builtin_memcpy(D_003B2608, D_003B29C0, 0x4C);
    __builtin_memcpy(D_00387F2C + 0xE0, D_003B2608, 0x4C);
    return 1;
}
