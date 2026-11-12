#include "common.h"

#define FNPTR(p, off) (*(void (**)(void))((u8 *)(p) + (off)))
#define FNPTR_S32(p, off) (*(s32 (**)(void))((u8 *)(p) + (off)))

extern u8 *D_003876A0;
extern u8 D_003B2600[] __attribute__((section(".data")));
extern u8 D_003B2654[] __attribute__((section(".data")));
extern s32 gBtlCamView;

void func_00284E68(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void func_002AB0E0(void);
void func_002ACE70(void);
void func_002711A0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00297978(void);
void func_0029F250(void);
void func_002A3510(void);
void func_00260F80(void);
void func_00126258(void);
void func_001262A0(void);
s32 BtlStage_IsReady(void);
void func_00276F38(void);
void func_00280E30(void);
s32 func_0025AB48(void);
void func_0025A4E0(void);
void func_002A9698(s64 arg0);
void func_00273630(s32 arg0);
void func_00275068(s32 arg0);
void func_00280F18(void);
void func_00275B38(s32 arg0);
void func_00265BC8(void);
void func_00265D40(s32 arg0, s32 arg1, f32 farg0);
void func_00265EB8(s32 arg0);
void func_002810B0(void);
void BtlScene_DrawFrame(s32 arg0);
void Ot_Draw(void);
void func_002810E8(void);
void func_00259740(void);
void func_0029F2B0(void);
void func_002A38C0(void);
void func_002ACF68(void);
void BattleSetup_Finish(void);
void func_00281360(void);
void func_002711E8(void);
s32 func_0029F6F8(s32 arg0);
s32 func_00101E58(void);
s32 func_00101E70(void);
void func_001012D0(void);

void func_002ABF30(void) {
    u8 *s0;
    s32 s1;

    s0 = *(u8 **)(D_003B2654 + 0x58);
    s1 = 0;
    if (FNPTR(s0, 0x0) != NULL) {
        FNPTR(s0, 0x0)();
    }
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & (s64)-0x101;
    func_00284E68(0, 1, -0x101, 1.0f);
    func_002AB0E0();
    func_002ACE70();
    do {
        func_002711A0();
        func_0028B090();
        func_0028BDA0();
        func_00297978();
        if (FNPTR(s0, 0x4) != NULL) {
            FNPTR(s0, 0x4)();
        }
        if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
            func_0029F250();
            func_002A3510();
        }
        func_00260F80();
        if (*(s32 *)(D_003876A0 + 0x4) != 0) {
            func_00126258();
            func_001262A0();
        }
        if (BtlStage_IsReady() != 0) {
            func_00276F38();
        }
        func_00280E30();
        if (func_0025AB48() != 0) {
            func_0025A4E0();
        }
        {
            s64 mask = (s64)0x8000 << 20;
            if (*(s64 *)(D_003876A0 + 0x4D8) & mask) {
                func_002A9698(mask);
            }
        }
        if (BtlStage_IsReady() != 0) {
            func_00273630(gBtlCamView);
            func_00275068(gBtlCamView);
        }
        func_00280F18();
        if (BtlStage_IsReady() != 0) {
            func_00275B38(gBtlCamView);
        }
        func_00265BC8();
        func_00265D40(0, -1, 0.0f);
        func_00265EB8(0);
        func_002810B0();
        if (BtlStage_IsReady() != 0) {
            BtlScene_DrawFrame(1);
            Ot_Draw();
        }
        func_002810E8();
        func_00259740();
        if (FNPTR(s0, 0x8) != NULL) {
            FNPTR(s0, 0x8)();
        }
        func_0029F2B0();
        func_002A38C0();
        func_002ACF68();
        BattleSetup_Finish();
        func_00281360();
        func_002711E8();
        if (FNPTR_S32(s0, 0xC) != NULL) {
            if (FNPTR_S32(s0, 0xC)() != 0) {
                s1 = 1;
            }
        } else {
            if (func_0029F6F8(*(s32 *)(D_003B2654 + 0x10)) == 0) {
                s1 = 1;
            }
        }
    } while (s1 == 0);
    if (FNPTR(s0, 0x10) != NULL) {
        FNPTR(s0, 0x10)();
    }
    if (func_00101E58() != 0 && func_00101E70() == 0) {
        *(s32 *)(D_003B2600 + 0x54) = *(s32 *)(D_003B2600 + 0x54) | 0x20000;
    }
    func_001012D0();
}
