#include "common.h"

void *memset(void *, int, unsigned);
void *memcpy(void *, const void *, unsigned);
extern s32 func_00325830();
extern char D_003775E0[], D_003775F0[], D_00377600[], D_00377610[], D_00377620[], D_00377630[];
extern char D_00377640[], D_00377650[], D_00387D30[], D_00387D38[];

void func_0028A0B8(u8 *a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    u8 *s1 = a0 + 0x18;
    u8 *s0;
    s32 i;

    if (a3 < 0 || a2 < 0) {
        memset(s1, 0, 0x80);
        if (t0 == 0) {
            func_00325830(s1, D_00387D30, D_003775F0, a1);
        } else {
            func_00325830(s1, D_00387D30, D_00377600, a1);
        }
    } else {
        memset(s1, 0, 0x80);
        if (t0 == 0) {
            func_00325830(s1, D_003775E0, D_003775F0, a1, a2, a3);
        } else {
            func_00325830(s1, D_003775E0, D_00377600, a1, a2, a3);
        }
    }
    s0 = a0 + 0x98;
    memset(s0, 0, 0x80);
    func_00325830(s0, D_00377610, s1);
    for (i = 0; i < 3; i++) {
        s0 = a0 + 0x118 + i * 0x80;
        memset(s0, 0, 0x80);
        func_00325830(s0, t0 == 0 ? D_00377620 : D_00377630, s1);
    }
    s0 = a0 + 0x298;
    memset(s0, 0, 0x80);
    func_00325830(s0, D_00387D38, s1, s1);
    for (i = 0; i < 3; i++) {
        s0 = a0 + 0x35C + i * 0x40;
        memset(s0, 0, 0x40);
        if (t0 == 0) {
            memcpy(s0, D_00377640, 9);
        } else {
            memcpy(s0, D_00377650, 10);
        }
    }
}
