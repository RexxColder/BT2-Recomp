#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_004213AC __attribute__((section(".data")));
extern u8 D_0042FD80[] __attribute__((section(".data")));

s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_101438(s32 a0);
void func_1012D0(void);
void func_298158(s32 a0);
void func_28BCB0(void);
void func_297A60(s32 a0, s32 a1);
void func_297EC8(void);
void func_28BCE8(void);
void func_28BB60(s32 a0);
s32 func_0041F880(s32 a0);
void func_0041C788(s32 a0);
void func_004211D8(s32 a0);

/* 0x0041BF08: menu step on G = D_3876A4 (state at G->0x1C: 6, 7, 8). Case 7 runs func_0041F880(1) (a frame loop
 * returning 0 when it ends) and moves to state 4 (ret = 0) or 8; case 8 copies the 0x64-byte table D_0042FD80 to a
 * frame buffer and sets G->0x18 |= 0x200 before returning to 7. Returns ret (1 unless case 7 ends it). */
s32 func_0041BF08(void) {
    u8 *G;
    u8 fr[0x64];
    s32 done = 0;
    s32 ret = 1;

    if (D_004213AC == 0) {
        func_100D58(*(s32 *)(D_3876A4 + 0x4) + 0xF, 0, 1);
        do {
            D_004213AC = func_100D58(0, 0, 0);
        } while (D_004213AC == 0);
    }
    func_298158(0);
    func_28BCB0();
    func_297A60(0x33CC, 0);

    do {
        G = D_3876A4;
        if (*(s32 *)(G + 0x1C) == 7) {
            func_101438(0x3E1F);
            if (func_0041F880(1) == 0) {
                func_1012D0();
                ret = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 4;
                done = 1;
            } else {
                func_1012D0();
                if ((*(s32 *)(D_3876A4 + 0x18) & 0x200) == 0) {
                    *(s32 *)(D_3876A4 + 0x1C) = 8;
                } else {
                    done = 1;
                }
            }
        } else if (*(s32 *)(G + 0x1C) == 8) {
            memcpy(fr, D_0042FD80, 0x64);
            done = 1;
            func_101438(*(s32 *)(fr + *(s32 *)(D_3876A4 + 0x30) * 4) + 0x3E1F);
            func_004211D8(2);
            func_1012D0();
            *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) | 0x200;
            *(s32 *)(D_3876A4 + 0x1C) = 7;
        } else if (*(s32 *)(G + 0x1C) == 6) {
            func_101438(0x3E40);
            func_0041C788(3);
            func_1012D0();
            *(s32 *)(D_3876A4 + 0x1C) = 7;
        }
    } while (done == 0);

    func_297EC8();
    func_28BCE8();
    func_28BB60(D_004213AC);
    D_004213AC = 0;
    return ret;
}
