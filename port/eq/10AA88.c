#include "common.h"

s32 BattleResult_IsAborted(void);
void Ramp_Start(f32 farg0, f32 farg1, f32 farg2, void *arg0);
s32 Ramp_Step(void *arg0);
void func_001066E8(s32 arg0, s32 arg1);
void func_00284E68(f32 farg0, s32 arg1, s32 arg2);
extern f32 D_00383E24;

s32 func_0010AA88(u8 *arg0) {
    u8 temp_v1;
    void (*fp)(void *);

    temp_v1 = arg0[8];
    if (temp_v1 == 0) {
        fp = *(void (**)(void *))arg0;
        fp(*(void **)(arg0 + 4));
        func_001066E8(*(s32 *)(*(u8 **)(arg0 + 4) + 4), 1);
        if (BattleResult_IsAborted() != 0) {
            func_00284E68(1.0f, 0, 0);
            Ramp_Start(D_00383E24, 0.0f, 1.0f, arg0 + 0xC);
            arg0[8] = 1;
        }
        return 6;
    }
    if (temp_v1 == 1) {
        if (Ramp_Step(arg0 + 0xC) != 0) {
            return 0x63;
        }
        return 6;
    }
    return 6;
}
