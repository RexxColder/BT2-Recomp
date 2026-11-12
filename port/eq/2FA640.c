#include "common.h"

typedef s32 (*FA640Fn)(void *arg0);
void func_002F9B38(u8 *arg0, u8 *arg1, s32 arg2);
void *func_002F98F0(u8 *arg0, u8 *arg1, s32 arg2);
void func_002F9300(void *arg0);
extern u8 D_0037D770[] __attribute__((section(".data")));
extern u8 D_0037D7C0[] __attribute__((section(".data")));
extern u8 D_0037D7E8[] __attribute__((section(".data")));

s32 func_002FA640(s32 arg0) {
    u8 frame[0x260];   /* tamano de locales del original (antes 0x134) */
    u8 *sp130;
    void *var_a0;
    void *temp_v0_2;
    FA640Fn fn;

    sp130 = frame + 0x130;
    func_002F9B38(frame, sp130, arg0);
    var_a0 = D_0037D770;
    if (*sp130 != 0) {
        temp_v0_2 = func_002F98F0(frame, sp130, arg0);
        if (temp_v0_2 == NULL) {
            func_002F9300(D_0037D7C0);
        }
        fn = *(FA640Fn *)((u8 *)temp_v0_2 + 0x40);
        if (fn == NULL) {
            var_a0 = D_0037D7E8;
            goto block_9;
        }
        return fn(sp130);
    }
block_9:
    func_002F9300(var_a0);
    return 0;
}
