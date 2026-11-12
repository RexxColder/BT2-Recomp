#include "common.h"

s32 BtlChar_FrameMod(s32 arg0);
void func_00210000(u8 *arg0, s32 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002411E0(u8 *arg0, s32 arg1);
s32 func_002418E8(u8 *arg0, s32 arg1, u8 *arg2);
s32 func_00241958(u8 *arg0, s32 arg1);
f32 func_00241A00(u8 *arg0, s32 arg1);
f32 func_00241A58(u8 *arg0, s32 arg1);

void bt2_fightlog_note(const char *fmt, ...);
void func_00201B90(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    u8 *temp_a2;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 flag;

    temp_a2 = arg0 + 0xB48;
    bt2_fightlog_note("IMPACTO-201B90 victima %08X (acc %X B48 %d) atacante %08X (acc %X B48 %d) reaccion %d", (s32)arg0,
                      *(s32 *)(arg0 + 0xC00), *(s32 *)(arg0 + 0xB48), (s32)arg1, *(s32 *)(arg1 + 0xC00), *(s32 *)(arg1 + 0xB48), arg3);
    temp_s3 = *(s32 *)(*(u8 **)(arg2 + 0x64) + 4);
    if (*(s32 *)(arg1 + 0xB48) < 3) {
        *(s32 *)(arg0 + 0xB48) = arg3;
        *(s32 *)(temp_a2 + 0x18) = 0;
        *(s32 *)(temp_a2 + 0x10) = 0;
        *(s32 *)(arg0 + 0xB64) = 0;
        *(s32 *)(arg0 + 0xB68) = 0;
        *(s32 *)(arg1 + 0xAB0) = temp_s3;
        *(s32 *)(arg1 + 0xAB4) = func_002418E8(arg1, temp_s3, temp_a2);
        temp_v0 = func_002411E0(arg1, temp_s3);
        flag = (temp_v0 & 0x8000) != 0;
        if (temp_v0 & 0x800) {
            *(u8 *)(arg1 + 0xAB8) = 1;
            *(f32 *)(arg1 + 0xABC) = func_00241A00(arg1, temp_s3);
            *(f32 *)(arg1 + 0xAC0) = func_00241A58(arg1, temp_s3);
        } else {
            *(u8 *)(arg1 + 0xAB8) = 0;
            *(s32 *)(arg1 + 0xABC) = 0;
            *(s32 *)(arg1 + 0xAC0) = 0;
        }
        if (temp_v0 & 0x20) {
            *(u8 *)(arg1 + 0xAB9) = 1;
        } else {
            *(u8 *)(arg1 + 0xAB9) = 0;
        }
        if (temp_v0 & 0x02000000) {
            *(u8 *)(arg1 + 0xABA) = 1;
        } else {
            *(u8 *)(arg1 + 0xABA) = 0;
        }
        func_002113C0(arg1, 4, 0x04000000, 1);
        *(s32 *)(arg0 + 0xAB0) = *(s32 *)(arg1 + 0xAB0);
        *(s32 *)(arg0 + 0xAB4) = *(s32 *)(arg1 + 0xAB4);
        *(u8 *)(arg0 + 0xAB8) = *(u8 *)(arg1 + 0xAB8);
        *(u8 *)(arg0 + 0xAB9) = *(u8 *)(arg1 + 0xAB9);
        *(u8 *)(arg0 + 0xABA) = *(u8 *)(arg1 + 0xABA);
        *(f32 *)(arg0 + 0xABC) = *(f32 *)(arg1 + 0xABC);
        *(u8 *)(arg0 + 0xB54) = (u8)flag;
        *(f32 *)(arg0 + 0xAC0) = *(f32 *)(arg1 + 0xAC0);
        temp_v0_2 = func_00241958(arg1, temp_s3);
        switch (temp_v0_2) {
        case 1:
            func_00210000(arg2 + 0x20, (BtlChar_FrameMod(2) == 0) ? 0x11 : 0x1B);
            break;
        case 2:
            func_00210000(arg2 + 0x20, 0x47);
            break;
        case 3:
            func_00210000(arg2 + 0x20, 0x4A);
            break;
        }
    }
}
