#include "common.h"

void func_002F9300(s32 arg0);
s32 func_002F98F0(s32 arg0, s32 arg1, s32 arg2);
void func_002F9B38(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037D4D8[] __attribute__((section(".data")));
extern u8 D_0037D530[] __attribute__((section(".data")));
extern u8 D_0037D558[] __attribute__((section(".data")));

s32 func_002FA148(s32 arg0, s32 arg1) {
    u8 buf[0x260];   /* tamano de locales del original (antes 0x134) */
    s8 *sp130;
    u8 *a0;
    s32 fn;
    u8 *obj;

    sp130 = (s8 *)(buf + 0x130);
    if (arg0 == 0) {
        a0 = D_0037D4D8;
        goto out;
    }
    func_002F9B38((s32)buf, (s32)sp130, arg0);
    if (*sp130 == 0) {
        a0 = D_0037D4D8;
        goto out;
    }
    obj = (u8 *)func_002F98F0((s32)buf, (s32)sp130, arg0);
    if (obj == NULL) {
        func_002F9300((s32)D_0037D530);
    }
    fn = *(s32 *)(obj + 0x5C);
    if (fn != 0) {
        return ((s32 (*)(s32, s32))fn)((s32)sp130, arg1);
    }
    a0 = D_0037D558;
out:
    func_002F9300((s32)a0);
    return 0;
}
