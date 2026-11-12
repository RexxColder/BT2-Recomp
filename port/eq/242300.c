#include "common.h"

typedef u32 (*FnU32Void)(void);

s32 func_00100CB8(s32 arg0);
u32 func_00101E98(s32 arg0);
void *func_0028BAA8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *gScrWarp;

void func_00242300(s32 arg0) {
    if (func_00101E98(arg0) != 0) {
        gScrWarp = func_0028BAA8(0x10B0);
        memset(gScrWarp, 0, 0x10B0);
        if (((FnU32Void)func_00101E98)() >= 8U) {
            *(s32 *)gScrWarp = func_00100CB8(0x3DE5);
            *(s32 *)(gScrWarp + 0x10) = 0x3DE5;
        } else {
            *(s32 *)gScrWarp = func_00100CB8((s32)(func_00101E98(0x3DE5) + 0x3DD9));
            *(s32 *)(gScrWarp + 0x10) = (s32)(((FnU32Void)func_00101E98)() + 0x3DD9);
        }
        *(s32 *)(gScrWarp + 0x28) = *(s32 *)gScrWarp;
        *(s32 *)(gScrWarp + 0x40) = 0;
        *(s32 *)(gScrWarp + 0x44) = *(s32 *)(gScrWarp + 0x10);
        *(u32 *)(gScrWarp + 0x50) = ((FnU32Void)func_00101E98)();
    }
}
