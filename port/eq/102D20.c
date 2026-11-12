#include "common.h"

extern void *gBtlCam;

void func_0025BF08(s32 arg0);
void func_0025C058(void);
void func_00273630(void *arg0);
void func_00275068(void *arg0);
void func_00280F18(void);
void func_00265BC8(void);
void func_00265D40(s32 arg0, s32 arg1, f32 farg0);
s32 func_00265EB8(s32 arg0);
void func_002810B0(void);
void func_002810E8(void);
void func_00281360(void);
void func_002A2AF0(void);
void BattleSetup_Finish(void);
void BtlScene_DrawFrame(s32 arg0);
void Ot_Draw(void);
void Dma_AddScissor(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00105860(void);

s32 func_00102D20(void) {
    u8 *cam;
    s32 result;

    func_0025BF08(0);
    func_0025C058();
    func_00273630(*(void **)((u8 *)gBtlCam + 0x600));
    func_00275068(*(void **)((u8 *)gBtlCam + 0x600));
    func_0025BF08(1);
    func_0025C058();
    func_00273630(*(void **)((u8 *)gBtlCam + 0x600));
    func_00275068(*(void **)((u8 *)gBtlCam + 0x600));
    func_00280F18();
    func_00265BC8();
    func_0025BF08(0);
    func_0025C058();
    cam = *(u8 **)((u8 *)gBtlCam + 0x600);
    func_00265D40(0, *(s32 *)(cam + 0x254), *(f32 *)(cam + 0x2C4));
    func_0025BF08(1);
    func_0025C058();
    cam = *(u8 **)((u8 *)gBtlCam + 0x600);
    func_00265D40(1, *(s32 *)(cam + 0x254), *(f32 *)(cam + 0x2C4));
    func_00265EB8(1);
    func_002810B0();
    func_0025BF08(0);
    func_0025C058();
    BtlScene_DrawFrame(1);
    Ot_Draw();
    func_0025BF08(1);
    func_0025C058();
    BtlScene_DrawFrame(0);
    Ot_Draw();
    func_002810E8();
    Dma_AddScissor(0, 0x1FF, 0, 0x1BF);
    result = 1;
    if (func_00105860() == 0) {
        BattleSetup_Finish();
        func_002A2AF0();
        func_00281360();
        result = 0;
    }
    return result;
}
