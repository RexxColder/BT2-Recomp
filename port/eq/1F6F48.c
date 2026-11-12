#include "common.h"

#define W(p, off) (*(s32 *)((p) + (off)))
/* the flags word of the object held at +0x1530 of the unit s0 */
#define FLAGS(s0) (*(s32 *)((u8 *)W((s0), 0x1530) + 0xAF0))

s32 func_00211270(void);
u8 *func_00211288(s32 arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);

void func_001F6F48(void) {
    s32 s1;
    s32 s3;
    s32 i;
    u8 *s0;

    s1 = 0;
    s3 = -1;
    for (;;) {
        if (!(s1 < func_00211270())) {
            break;
        }
        if (func_00211310(func_00211288(s1), 9, 4) == 0) {
            s1++;
            continue;
        }
        s3 = s1;
        break;
    }

    s1 = 0;
    if (s3 < 0) {
        for (;;) {
            if (!(s1 < func_00211270())) {
                break;
            }
            i = s1;
            s1++;
            s0 = func_00211288(i);
            if (func_00211310(s0, 9, 0x100000) != 0 || func_00211310(s0, 9, 0x4000) != 0) {
                FLAGS(s0) = FLAGS(s0) & ~2;
            } else {
                FLAGS(s0) = FLAGS(s0) | 2;
            }
        }
        return;
    }

    while (s1 < func_00211270()) {
        s0 = func_00211288(s1);
        if (s1 == s3 && func_00211310(s0, 9, 0x100000) == 0 && func_00211310(s0, 9, 0x4000) == 0) {
            FLAGS(s0) = FLAGS(s0) | 2;
        } else {
            FLAGS(s0) = FLAGS(s0) & ~2;
        }
        s1++;
    }
}
