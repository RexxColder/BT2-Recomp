#include "m2c_macros.h"

extern s32 D_00345208 __attribute__((section(".data")));
extern s16 D_0037B208[] __attribute__((section(".data")));
void func_002B2770(s8 *arg0);

/* Three recursive filter taps over arg1 signed samples: each tap's coefficient starts at table entry
 * 0x100, 0x200, 0x300 and is replaced by the table entry at (coef * table[0x80 + sample]) % 1024. The three
 * final coefficients are stored as s16 to arg2, arg3 and arg4. */
s32 SndFilt_Run3(s8 *arg0, s32 arg1, s16 *arg2, s16 *arg3, s16 *arg4) {
    s32 c1;
    s32 c2;
    s32 c3;
    s32 i;
    s32 prod;

    if (D_00345208 == 0) {
        func_002B2770(arg0);
    }
    *arg2 = 0;
    *arg3 = 0;
    *arg4 = 0;
    if (arg0 == NULL && arg1 <= 0) {
        return 0;
    }

    c1 = D_0037B208[0x100];
    for (i = 0; i < arg1; i++) {
        prod = c1 * D_0037B208[0x80 + arg0[i]];
        c1 = D_0037B208[prod % 1024];
    }

    c2 = D_0037B208[0x200];
    for (i = 0; i < arg1; i++) {
        prod = c2 * D_0037B208[0x80 + arg0[i]];
        c2 = D_0037B208[prod % 1024];
    }

    c3 = D_0037B208[0x300];
    for (i = 0; i < arg1; i++) {
        prod = c3 * D_0037B208[0x80 + arg0[i]];
        c3 = D_0037B208[prod % 1024];
    }

    *arg2 = (s16)c1;
    *arg3 = (s16)c2;
    *arg4 = (s16)c3;
    return 0;
}
