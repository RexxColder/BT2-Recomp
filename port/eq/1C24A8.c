#include "common.h"

extern u8 *D_00387898;
extern u8 *D_003876A0;
s64 EftVram_AddClut(u8 *arg0);
s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);
s64 EftVram_AddTex(u8 *arg0, s32 arg1, s32 arg2);
void func_001EBD08(u8 *arg0, u8 *arg1);
u8 *func_001EBD90(u8 *arg0, s32 arg1);
s32 func_001C1898(u8 *arg0, s32 arg1);

void func_001C24A8(u8 *arg0) {
    u8 *s6;
    u8 *rec;
    u8 *slot;
    u8 *G;
    u8 *s2;
    s32 g;
    s32 s3;
    s32 fp;
    s32 s4;
    s32 t;
    s32 s1;
    s32 s2i;
    s32 s0i;
    s32 cnt;
    s32 mode;
    s32 k;
    s32 inc;
    s64 s5;
    s64 s0;

    s6 = *(u8 **)(arg0 + 0x38);

    g = 0;
    s3 = 0;
    fp = 0x100;
    do {
        G = D_00387898;
        if (*(s32 *)(G + fp + 8) != 0) {
            s5 = -1;
            s2 = G + 16 * g + 0x110;
            if (*s2 != 3) {
                s4 = 0;
                t = *s2;
                for (;;) {
                    G = D_00387898;
                    s2++;
                    slot = G + s3 + 16 * s4 + 8;
                    if (t == 1) {
                        *(s64 *)slot = s5 | ((s64)EftVram_AddClut(slot) << 37);
                    } else if (t < 2) {
                        s0 = (s64)EftVram_AddClut(slot) << 37;
                        s5 = EftVram_AddImage(slot, 1, 0);
                        *(s64 *)slot = s5 | s0;
                    } else {
                        *(s64 *)slot = EftVram_AddTex(slot, 1, 0);
                    }
                    if (*s2 == 3) {
                        break;
                    }
                    s4++;
                    t = *s2;
                }
            }
        }
        g++;
        s3 += 0x108;
        fp += 0x108;
    } while (g <= 0);

    if ((*(u64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }

    k = *(s16 *)(s6 + 0xF406);
    for (;;) {
        k = (s16)(k - 1);
        rec = func_001EBD90(s6 + 0xF400, k);
        if (rec == NULL) {
            break;
        }
        inc = (s16)(*(u16 *)(rec + 6) + 1);
        *(s16 *)(rec + 6) = (s16)inc;
        if (inc < 0) {
            continue;
        }
        if (inc < *(s16 *)(rec + 4)) {
            mode = 1;
        } else if (*(u8 *)(rec + 0xD1) == 1) {
            *(s16 *)(rec + 6) = 0;
            mode = 1;
        } else {
            mode = 0;
        }

        if (mode == 0) {
            cnt = *(u8 *)(rec + 0xD0);
            s1 = cnt - 1;
            if (s1 >= 0) {
                do {
                    func_001EBD08(s6 + 0x20D48, *(u8 **)(rec + 0x30 + 4 * s1));
                    cnt = *(u8 *)(rec + 0xD0);
                    s0i = s1;
                    if (s1 < cnt - 1) {
                        for (s0i = s1; s0i < cnt - 1; s0i++) {
                            *(u8 **)(rec + 0x30 + 4 * s0i) = *(u8 **)(rec + 0x30 + 4 * (s0i + 1));
                        }
                    }
                    *(u8 **)(rec + 0x30 + 4 * s0i) = NULL;
                    s1--;
                    *(u8 *)(rec + 0xD0) = (u8)(cnt - 1);
                } while (s1 >= 0);
            }
            func_001EBD08(s6 + 0xF400, rec);
        } else {
            s2i = *(u8 *)(rec + 0xD0) - 1;
            if (s2i >= 0) {
                do {
                    u8 *s1p = *(u8 **)(rec + 0x30 + 4 * s2i);
                    s32 v1 = func_001C1898(s1p, *(s16 *)(rec + 6));
                    if (v1 == 1 && *(u8 *)(rec + 0xD1) != 1) {
                        func_001EBD08(s6 + 0x20D48, s1p);
                        cnt = *(u8 *)(rec + 0xD0);
                        s0i = s2i;
                        if (s2i < cnt - 1) {
                            for (s0i = s2i; s0i < cnt - 1; s0i++) {
                                *(u8 **)(rec + 0x30 + 4 * s0i) = *(u8 **)(rec + 0x30 + 4 * (s0i + 1));
                            }
                        }
                        *(u8 **)(rec + 0x30 + 4 * s0i) = NULL;
                        *(u8 *)(rec + 0xD0) = (u8)(cnt - 1);
                    }
                    s2i--;
                } while (s2i >= 0);
            }
        }
    }
}
