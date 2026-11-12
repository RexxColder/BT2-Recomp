#include "common.h"

void func_002F9300(s32 arg0);
s32 func_002F95C8(s32 arg0);
void func_002F9B38(s32 arg0, s32 arg1, s32 arg2);
void func_002F9C80(s32 arg0);
void func_002FB158(s32 arg0, s32 arg1);
extern u8 D_0037D798[] __attribute__((section(".data")));

s32 func_002FA7F8(s32 arg0, s32 arg1, s32 arg2) {
    u8 buf[0x260];   /* tamano de locales del original (antes 0x134) */
    u8 *s1;
    s32 s4;
    s32 temp;
    s32 (*fn)(s32, s32, s32);

    s1 = buf + 0x130;
    func_002F9B38((s32)buf, (s32)s1, arg0);
    s4 = 0;
    if (buf[0] == 0) {
        func_002F9C80((s32)buf);
        if (buf[0] == 0) {
            func_002F9300((s32)D_0037D798);
            return 0;
        }
    }
    func_002FB158((s32)buf, (s32)s1);
    temp = func_002F95C8((s32)buf);
    if (temp == 0) {
        return 0;
    }
    fn = *(s32 (**)(s32, s32, s32))((u8 *)temp + 0x48);
    if (fn != NULL) {
        s4 = fn(arg0, arg1, arg2);
    }
    return s4;
}
