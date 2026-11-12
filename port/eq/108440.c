#include "common.h"

s32 Font_GetGlyphHeight(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001069D8(s32 arg0, s32 arg1);
s32 func_00106DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2, s32 t3);
void func_002A1340(void);
void func_002A13E8(void);
void func_002A14B0(f32 farg0);
void func_002A1508(s32 arg0, s32 arg1);
void func_002A15D0(s32 arg0);
void func_002A1678(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002A16A8(s32 arg0);
void func_002A16B8(s32 arg0);
void func_002A2E08(s32 arg0);
extern f32 D_00383E10;
extern u8 *D_003876A4;
extern u8 func_002A2E10[] __attribute__((section(".data")));
extern u8 func_002A2E40[] __attribute__((section(".data")));
extern s32 *gObjOutline;

s32 func_00108440(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 f20;
    f32 f21;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s7;

    s0 = arg3;
    s1 = arg1;
    s2 = arg2 - s1;
    s7 = arg0;
    f20 = D_00383E10;
    s3 = *(s32 *)(D_003876A4 + 0x484);
    s4 = Font_GetGlyphHeight(arg0, arg1, arg2, arg3);
    func_002A1340();
    f21 = 1.0f;
    func_002A15D0(2);
    s3 += 1;
    func_002A1508(1, 2);
    s7 = func_00106DC0(s7, s1, s0, s2, 0x20, 0x14, 0, 0);
    func_002A14B0(f20);
    Font_SetColorRGBA(0xFC, 0xF5, 0xDE, 0x80);
    func_002A1678(0x87, 0x4F, 0x14, 0x80);
    Font_PrintAt(s1 + 0x1A, s0 + 2, func_001069D8(0, 0));
    func_002A14B0(f21);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, 0x80);
    func_002A1678(0, 0x10, 0x10, 0x40);
    Font_PrintAt(s1 + 0x0C, s0 + 0x25, func_001069D8(0, s3));
    s0 += s4 * 5;
    s7 = func_00106DC0(s7, s1, s0 + 0x2A, s2, 0x20, 0x15, 0, 0);
    func_002A14B0(f20);
    Font_SetColorRGBA(0xFC, 0xF5, 0xDE, 0x80);
    func_002A1678(0x87, 0x4F, 0x14, 0x80);
    Font_PrintAt(s1 + 0x1A, s0 + 0x2C, func_001069D8(1, 0));
    func_002A14B0(f21);
    func_002A2E08(*gObjOutline);
    func_002A16A8((s32)func_002A2E10);
    func_002A16B8((s32)func_002A2E40);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, 0x80);
    func_002A1678(0, 0x10, 0x10, 0x40);
    Font_PrintAt(s1 + 0x0C, s0 + 0x4F, func_001069D8(1, s3));
    func_002A13E8();
    return s7;
}
