#include "common.h"

extern u8 D_00421CF8 __attribute__((section(".data")));
void *memcpy(void *, const void *, unsigned int);

/* 0x003BC6A0: copies the 0x40-byte table D_00421CF8 to a local buffer. key = (signed char) buf[0]. Then for 36 entries
 * p = arg0 + 0x20 + 2*i (s16): if *p == key, *p = 0; else *p = the first index a in 1..0x3F with *p == (signed char) buf[a]
 * (when there is none, *p is left unchanged). */
void func_003BC6A0(u8 *arg0) {
    u8 buf[0x40];
    s32 key;
    u8 *p;
    s32 a2;
    s32 a1;

    memcpy(buf, &D_00421CF8, 0x40);
    key = (signed char)buf[0];
    p = arg0 + 0x20;

    for (a2 = 0x23; a2 >= 0; a2--) {
        if (*(s16 *)p == key) {
            *(s16 *)p = 0;
        } else {
            for (a1 = 1; a1 < 0x40; a1++) {
                if (*(s16 *)p == (signed char)buf[a1]) {
                    *(s16 *)p = (s16)a1;
                    break;
                }
            }
        }
        p += 2;
    }
}
