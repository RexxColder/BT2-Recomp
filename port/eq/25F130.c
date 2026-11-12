#include "common.h"

void func_0025F130(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 t;
    u8 *p;
    u8 *t0;
    u8 *a1;
    s32 n;
    s32 cnt;

    t = *(u16 *)(arg0 + 6);
    if (t != 0) {
        p = arg0 + t * 4;
        t0 = p + 4;
        if ((*(u16 *)p & 1) == 0) {
            n = *(u16 *)(p + 2);
            if ((arg1 & 0xFF) && n != 0) {
                a1 = t0;
                cnt = n;
                do {
                    cnt -= 1;
                    *(s32 *)a1 = 0;
                    a1 += 0x18;
                } while (cnt != 0);
            }
            if ((arg2 & 0xFF) && n != 0) {
                a1 = t0 + 4;
                cnt = n;
                do {
                    cnt -= 1;
                    *(s32 *)a1 = 0;
                    a1 += 0x18;
                } while (cnt != 0);
            }
            if ((arg3 & 0xFF) && n != 0) {
                a1 = t0 + 8;
                cnt = n;
                do {
                    cnt -= 1;
                    *(s32 *)a1 = 0;
                    a1 += 0x18;
                } while (cnt != 0);
            }
        }
    }
}
