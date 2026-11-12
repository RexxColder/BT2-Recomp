#include "common.h"

void EftShotFx_UpdateLines(void);
void Vu0Cur_StoreMtx(s32 arg0);
void func_0029D6E8(s32 arg0, s32 arg1);

void func_0025BDD0(s32 arg0, f32 *arg1, void *arg2) {
    f32 sp[4];

    *(f32 *)((u8 *)arg2 + 0xC) = 1.0f;
    EftShotFx_UpdateLines();
    sp[0] = -arg1[0];
    sp[1] = -arg1[1];
    sp[2] = -arg1[2];
    sp[3] = 1.0f;
    func_0029D6E8((s32)sp, (s32)arg2);
    Vu0Cur_StoreMtx(arg0);
}
