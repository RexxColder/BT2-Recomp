#include "common.h"

typedef s32 (*FuncPtr)();

s32 func_002FB108();
s32 strlen();
s32 strncmp();
extern u8 D_0039D93C[] __attribute__((section(".data")));

s32 func_002FA6E8(s32 arg0) {
    s32 sp[2];
    s32 s4;
    s32 s5;
    s32 k;
    s32 off;
    s32 tp;
    s32 fn;

    s4 = 0;
    s5 = strlen(arg0);
    k = 0;
    off = 0;
    do {
        k += 1;
        if (strncmp(arg0, (s32)(D_0039D93C + off), s5) == 0) {
            tp = *(s32 *)(D_0039D93C + off - 4);
            if (func_002FB108(arg0) != 0) {
                if (tp != 0 && *(s32 *)(tp + 0x60) != 0) {
                    sp[1] = arg0;
                    s4 = ((FuncPtr)(*(s32 *)(tp + 0x60)))((s32)sp, 4, 0, 0);
                    return s4;
                }
            } else {
                if (tp != 0 && *(s32 *)(tp + 0x44) != 0) {
                    fn = *(s32 *)(tp + 0x44);
                    s4 = ((FuncPtr)fn)();
                    return s4;
                }
            }
        }
        off = k * 16;
    } while (k < 0x20);
    return s4;
}
