#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00383E0C;

s32 Font_GetGlyphHeight(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002A1340(void);
void func_002A15D0(s32 arg0);
void func_002A1508(s32 arg0, s32 arg1);
s32 func_00106DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_002A14B0(f32 farg0);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002A1678(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001069B0(s32 arg0, s32 arg1);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
void func_002A13E8(void);

s32 func_001081F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 r;
    f32 f20;
    f32 f21;

    s0 = arg3;
    s1 = arg1;
    s2 = arg2 - arg1;
    s5 = s1 + 0x1A;
    s6 = s1 + 0x20;
    s7 = (s32)arg0;
    f20 = D_00383E0C;
    s4 = *(s32 *)(D_003876A0 + 0xC8);
    s3 = Font_GetGlyphHeight((s32)arg0, arg1, arg2, arg3);
    func_002A1340();
    f21 = 1.0f;
    func_002A15D0(2);
    s4 = s4 + 1;
    func_002A1508(1, 2);

    /* block 1 */
    s7 = func_00106DC0(s7, s1, s0, s2, 0x20, 0x14, 0, 0);
    s3 = s3 << 2;
    func_002A14B0(f20);
    Font_SetColorRGBA(0xFC, 0xF5, 0xDE, 0x80);
    func_002A1678(0x87, 0x4F, 0x14, 0x80);
    r = func_001069B0(0, 0);
    Font_PrintAt(s5, s0 + 2, r);
    func_002A14B0(f21);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, 0x80);
    func_002A1678(0, 0x10, 0x10, 0x40);
    r = func_001069B0(0, s4);
    Font_PrintAt(s6, s0 + 0x25, r);
    s0 = s0 + s3;

    /* block 2 */
    s7 = func_00106DC0(s7, s1, s0 + 0x2A, s2, 0x20, 0x15, 0, 0);
    func_002A14B0(f20);
    Font_SetColorRGBA(0xFC, 0xF5, 0xDE, 0x80);
    func_002A1678(0x87, 0x4F, 0x14, 0x80);
    r = func_001069B0(1, 0);
    Font_PrintAt(s5, s0 + 0x2C, r);
    func_002A14B0(f21);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, 0x80);
    func_002A1678(0, 0x10, 0x10, 0x40);
    r = func_001069B0(1, s4);
    Font_PrintAt(s6, s0 + 0x4F, r);
    func_002A13E8();
    return s7;
}
