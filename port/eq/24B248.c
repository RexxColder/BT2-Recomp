#include "common.h"

extern u8 *D_00387F2C;

void func_0024B248(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    s32 var_t3 = 0;
    u8 *var_t0_2;
    u8 *temp_a3;

    if (arg2 != NULL) {
        s32 cnt = 0;
        u8 *p = arg1;
        s32 k = 6;
        do {
            s16 v = *(s16 *)p;
            p += 4;
            k -= 1;
            if (v != 0) {
                cnt += 1;
            }
        } while (k >= 0);
        {
            f32 prod = (f32)arg3 * *(f32 *)(arg2 + cnt * 4 + 0x1C);
            s32 tr = (s32)prod;
            f32 diff = prod - (f32)tr;
            var_t3 = tr;
            if (diff > 0.5f || (diff == 0.5f && (tr & 1))) {
                var_t3 = tr + 1;
            } else if (diff < -0.5f || (diff == -0.5f && (tr & 1))) {
                var_t3 = tr - 1;
            }
        }
    }

    var_t0_2 = arg1;
    temp_a3 = arg1 + 0x1C;
    do {
        s32 idx = *(s16 *)var_t0_2;
        if (idx != 0) {
            u8 *temp_a0 = (arg0 + idx * 0x30) - 0x30;
            if (*(s32 *)temp_a0 & 0x10) {
                u16 cnt2 = (u16)(*(u16 *)(var_t0_2 + 2) + var_t3);
                *(u16 *)(var_t0_2 + 2) = cnt2;
                if ((s16)cnt2 >= *(s32 *)(temp_a0 + 0x2C)) {
                    s32 cont;
                    do {
                        s32 old = *(s16 *)var_t0_2;
                        s16 nw = (s16)(old + 1);
                        u8 *tmp;
                        u16 flagv;
                        u8 *tp;

                        *(s16 *)var_t0_2 = nw;
                        *(u16 *)(var_t0_2 + 2) = (u16)(*(u16 *)(var_t0_2 + 2) - *(u16 *)(arg0 + old * 0x30 - 4));
                        tmp = D_00387F2C + ((s32)(nw << 16) >> 14) + 0x1F2C;
                        flagv = *(u16 *)tmp;
                        if (!(flagv & 1)) {
                            *(u16 *)tmp = (u16)(flagv | 1);
                            *(u16 *)(D_00387F2C + (nw * 4) + 0x1F2C) |= 2;
                        }
                        tp = (arg0 + nw * 0x30) - 0x30;
                        if (*(s32 *)tp & 0x10) {
                            cont = ((s16)*(u16 *)(var_t0_2 + 2) >= *(s32 *)(tp + 0x2C));
                        } else {
                            *(u16 *)(var_t0_2 + 2) = 0;
                            cont = 0;
                        }
                    } while (cont);
                }
            }
        }
        var_t0_2 += 4;
    } while ((s32)var_t0_2 < (s32)temp_a3);
}
