#include "common.h"

void func_002CC300(u8 *arg0);
s32 func_002CA340(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);
extern u8 D_00399C68[] __attribute__((section(".data")));
extern u8 D_00399C90[] __attribute__((section(".data")));
extern u8 D_00399C98[] __attribute__((section(".data")));
extern s32 D_00399CD8 __attribute__((section(".data")));
extern s32 D_00399CDC __attribute__((section(".data")));
extern s32 D_00399CE0 __attribute__((section(".data")));

/* Copies the record at obj->0x1FC0 into three static blocks (unaligned 8-byte ldl/ldr pairs written as
 * memcpy), then runs the follow-up calls. */
s32 func_002CA1B0(u8 *arg0) {
    u8 *s0;
    s32 s1;

    s0 = (u8 *)(s64)*(s32 *)(arg0 + 0x1FC0);
    s1 = *(s32 *)s0;
    if (s1 == 0) {
        return 0;
    }

    memcpy(D_00399C68, s0 + 0x4, 0x24);
    memcpy(D_00399C90, s0 + 0x28, 0x8);
    memcpy(D_00399C98, s0 + 0x30, 0x40);
    D_00399CD8 = *(s32 *)(s0 + 0x1080);
    D_00399CDC = *(s32 *)(s0 + 0x1084);
    D_00399CE0 = *(s32 *)(s0 + 0x1088);
    func_002CC300(arg0);
    if (func_002CA340(s1) != 0) {
        return func_002C2FF0((s32)(s64)arg0, 0xFF000F0C);
    }
    *(s32 *)s0 = 0;
    return 0;
}
