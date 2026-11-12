#include "common.h"

extern u8 gGfx[] __attribute__((section(".data")));

void *func_00284058(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_s6;
    s32 temp_v0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 var_v1;
    void *var_t5_2;
    s64 temp_t7;
    s64 var_v0;
    s64 var_v0_2;
    void *temp_t5;
    void *temp_t5_10;
    void *temp_t5_11;
    void *temp_t5_12;
    void *temp_t5_13;
    void *temp_t5_14;
    void *temp_t5_15;
    void *temp_t5_16;
    void *temp_t5_17;
    void *temp_t5_18;
    void *temp_t5_19;
    void *temp_t5_20;
    void *temp_t5_21;
    void *temp_t5_22;
    void *temp_t5_23;
    void *temp_t5_24;
    void *temp_t5_25;
    void *temp_t5_26;
    void *temp_t5_27;
    void *temp_t5_2;
    void *temp_t5_3;
    void *temp_t5_4;
    void *temp_t5_5;
    void *temp_t5_6;
    void *temp_t5_7;
    void *temp_t5_8;
    void *temp_t5_9;
    void *var_t5;

    temp_s6 = arg1 & 0xFF;
    (*(s64 *)((u8 *)(arg0) + (0))) = (s64) (((s64)0x10000000 << 0x20) | 0x800D);
    (*(s64 *)((u8 *)(arg0) + (8))) = 0xE;
    temp_t5_2 = arg0 + 0x10;
    (*(s64 *)((u8 *)(arg0) + (0x10))) = 1;
    (*(s64 *)((u8 *)(temp_t5_2) + (8))) = 0x46;
    temp_t5_3 = temp_t5_2 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_3) + (8))) = 0x4A;
    (*(s64 *)((u8 *)(temp_t5_2) + (0x10))) = 0;
    temp_t5_4 = temp_t5_3 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_4) + (8))) = 0x4B;
    (*(s64 *)((u8 *)(temp_t5_3) + (0x10))) = 0;
    temp_t5_5 = temp_t5_4 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_4) + (0x10))) = 0x40150;
    (*(s64 *)((u8 *)(temp_t5_5) + (8))) = 0x4C;
    temp_t5_6 = temp_t5_5 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_6) + (8))) = 0x4E;
    (*(s64 *)((u8 *)(temp_t5_5) + (0x10))) = (s64) (((((s64)1 << 0x10) | 0x3100) << 0x10) | 0xE0);
    temp_t5_7 = temp_t5_6 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_6) + (0x10))) = (s64) (((s64)0x7800 << 0x20) | 0x7800);
    (*(s64 *)((u8 *)(temp_t5_7) + (8))) = 0x18;
    temp_t5_8 = temp_t5_7 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_7) + (0x10))) = (s64) ((((s64)0xFF0000 << 0x10) | 0xFF) << 0x10);
    (*(s64 *)((u8 *)(temp_t5_8) + (8))) = 0x40;
    temp_t5_9 = temp_t5_8 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_9) + (8))) = 8;
    (*(s64 *)((u8 *)(temp_t5_8) + (0x10))) = (s64) (((((s64)0x6FC << 0x10) | 0x7F) << 0x10) | 0xC00A);
    temp_t5_10 = temp_t5_9 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_10) + (8))) = 0x42;
    (*(s64 *)((u8 *)(temp_t5_9) + (0x10))) = (s64) (((s64)0x80 << 0x20) | 0x64);
    temp_t5_11 = temp_t5_10 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_10) + (0x10))) = 0x60;
    (*(s64 *)((u8 *)(temp_t5_11) + (8))) = 0x14;
    temp_t5_12 = temp_t5_11 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_12) + (8))) = 0x47;
    (*(s64 *)((u8 *)(temp_t5_11) + (0x10))) = 0x20000;
    temp_t5_13 = temp_t5_12 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_12) + (0x10))) = 0x46;
    (*(s64 *)((u8 *)(temp_t5_13) + (8))) = 0;
    temp_t5_14 = temp_t5_13 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_13) + (0x10))) = (s64) ((((s64)0x3F800000 << 0x10) | 0x8000) << 0x10);
    (*(s64 *)((u8 *)(temp_t5_14) + (8))) = 1;
    temp_t5_15 = temp_t5_14 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_15) + (8))) = 0xE;
    (*(s64 *)((u8 *)(temp_t5_14) + (0x10))) = (s64) (((s64)0x10000000 << 0x20) | 0x8006);
    temp_t5_16 = temp_t5_15 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_16) + (8))) = 0x3F;
    (*(s64 *)((u8 *)(temp_t5_15) + (0x10))) = 0;
    temp_t5_17 = temp_t5_16 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_17) + (8))) = 6;
    var_t0 = 4;
    (*(s64 *)((u8 *)(temp_t5_16) + (0x10))) = (s64) (((*(s32 *)((u8 *)(gGfx) + (0x234))) & 1) ? ((((s64)0x20000006 << 0x10) | 0x6402) << 0x10) : (((((s64)0x20000006 << 0x10) | 0x6402) << 0x10) | 0xE00));
    temp_t5_18 = temp_t5_17 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_17) + (0x10))) = 0x44;
    var_v1 = 0;
    (*(s64 *)((u8 *)(temp_t5_18) + (8))) = 0x42;
    temp_t5_19 = temp_t5_18 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_19) + (8))) = 0x47;
    (*(s64 *)((u8 *)(temp_t5_18) + (0x10))) = 0;
    temp_t5_20 = temp_t5_19 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_19) + (0x10))) = 0x116;
    (*(s64 *)((u8 *)(temp_t5_20) + (8))) = 0;
    temp_t5_21 = temp_t5_20 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_20) + (0x10))) = (s64) (((((s64)0x3F800000 << 0x10) | 0x8080) << 0x10) | 0x8080);
    (*(s64 *)((u8 *)(temp_t5_21) + (8))) = 1;
    temp_t5_22 = temp_t5_21 + 0x10;
    if (temp_s6 != 0) {
        var_v1 = ((arg2 ^ 1) != 0) ? 0 : 0x10;
        var_t0 = 3;
    }
    temp_v0 = var_v1 << 5;
    var_a2 = temp_v0;
    (*(s64 *)((u8 *)(temp_t5_21) + (0x10))) = (s64) (((s64)0x44000000 << 0x20) | 0x8010);
    (*(s64 *)((u8 *)(temp_t5_22) + (8))) = 0x5353;
    var_t5 = temp_t5_22 + 0x10;
    var_a1 = 0;
    temp_t7 = (s64)0x8800 << 0x10;
    var_t4 = 0x7800;
    var_a3 = var_a2 + 0x20;
    var_t3 = 0x7800;
    var_t2 = 0x7900;
    var_t1 = 0x7900;
    do {
        switch (var_a1) {                           /* irregular */
        case 0:
            (*(s64 *)((u8 *)(var_t5) + (0))) = (s64) (((arg2 ^ 1) != 0) ? (temp_v0 << var_t0) : ((temp_v0 + 3) << var_t0));
            (*(s64 *)((u8 *)(var_t5) + (8))) = (s64) (var_t3 | 0x78000000);
            var_t5_2 = var_t5 + 0x10;
            (*(s64 *)((u8 *)(var_t5) + (0x10))) = (s64) ((var_a3 << var_t0) | 0x1C000000);
            (*(s64 *)((u8 *)(var_t5_2) + (8))) = (s64) (var_t2 | temp_t7);
            break;
        case 15:
            (*(s64 *)((u8 *)(var_t5) + (0))) = (s64) (var_a2 << var_t0);
            (*(s64 *)((u8 *)(var_t5) + (8))) = 0x78008700;
            var_t5_2 = var_t5 + 0x10;
            var_v0 = ((var_a2 + 0x1F) << var_t0) | 0x1C000000;
            (*(s64 *)((u8 *)(var_t5_2) + (8))) = (s64) (((s64)0x8800 << 0x10) | 0x8800);
block_11:
            *(s64 *)var_t5_2 = var_v0;
            break;
        default:
            (*(s64 *)((u8 *)(var_t5) + (0))) = (s64) (var_a2 << var_t0);
            (*(s64 *)((u8 *)(var_t5) + (8))) = (s64) (var_t4 | 0x78000000);
            var_t5_2 = var_t5 + 0x10;
            var_v0 = ((var_a2 + 0x20) << var_t0) | 0x1C000000;
            (*(s64 *)((u8 *)(var_t5_2) + (8))) = (s64) (var_t1 | temp_t7);
            goto block_11;
        }
        var_t5 = var_t5_2 + 0x10;
        var_a1 += 1;
        var_t1 += 0x100;
        var_t4 += 0x100;
        var_a2 += 0x20;
        var_t2 += 0x100;
        var_a3 += 0x20;
        var_t3 += 0x100;
    } while (var_a1 < 0x10);
    (*(s64 *)((u8 *)(var_t5_2) + (0x10))) = (s64) (((s64)0x10000000 << 0x20) | 0x8006);
    (*(s64 *)((u8 *)(var_t5) + (8))) = 0xE;
    temp_t5_23 = var_t5 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_23) + (8))) = 0x4C;
    (*(s64 *)((u8 *)(var_t5) + (0x10))) = (s64) (((*(s32 *)((u8 *)(gGfx) + (0x234))) & 1) ? 0x80000 : 0x80070);
    temp_t5_24 = temp_t5_23 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_23) + (0x10))) = (s64) (((s64)0x7200 << 0x20) | 0x7000);
    (*(s64 *)((u8 *)(temp_t5_24) + (8))) = 0x18;
    temp_t5_25 = temp_t5_24 + 0x10;
    if (temp_s6 != 0) {
        if (arg2 == 0) {
            var_v0_2 = (((s64)0x01BF0000 << 0x10) | 0x100) << 0x10;
        } else {
            var_v0_2 = ((((s64)0x01BF0000 << 0x10) | 0x1FF) << 0x10) | 0x100;
        }
    } else {
        var_v0_2 = (((s64)0x01BF0000 << 0x10) | 0x1FF) << 0x10;
    }
    (*(s64 *)((u8 *)(temp_t5_24) + (0x10))) = var_v0_2;
    (*(s64 *)((u8 *)(temp_t5_25) + (8))) = 0x40;
    temp_t5_26 = temp_t5_25 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_25) + (0x10))) = 0x70000;
    (*(s64 *)((u8 *)(temp_t5_26) + (8))) = 0x47;
    temp_t5_27 = temp_t5_26 + 0x10;
    (*(s64 *)((u8 *)(temp_t5_26) + (0x10))) = (s64) (((((s64)1 << 0x10) | 0x3100) << 0x10) | 0xE0);
    (*(s64 *)((u8 *)(temp_t5_27) + (8))) = 0x4E;
    temp_t5 = temp_t5_27 + 0x10;
    (*(s64 *)((u8 *)(temp_t5) + (8))) = 8;
    (*(s64 *)((u8 *)(temp_t5_27) + (0x10))) = 0;
    return temp_t5 + 0x10;
}
