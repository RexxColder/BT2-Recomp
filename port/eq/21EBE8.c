#include "common.h"

s32 BtlAnim_SetBlend(f32 farg0, s32 arg0, s32 arg1);
s32 BtlPad_Test48(void *arg0, s32 arg1);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
s32 func_001FA1D0(f32 farg0, void *arg0);
s32 func_00210E18(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_002174B8(void *arg0);
void func_002174D8(void *arg0, s32 arg1);
s32 func_0023C710(void *arg0);
void func_0023E520(void *arg0);
s32 func_0023F420(void *arg0);

extern f32 D_00385E8C;
extern f32 D_00385E90;
extern f32 D_00385E94;

s32 func_0021EBE8(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x8DC) & 1) {
        if (func_00211310(arg0, 4, 2) == 0) {
            goto block_27;
        }
        if (func_0023F420(arg0) & 0x80) {
            if ((BtlPad_Test4C(arg0, 3) != 0) && (*(s32 *)(arg0 + 0x9A0) < *(s32 *)(arg0 + 0x9A4))) {
                func_002174D8(arg0, 0x10);
            }
        }
        if (BtlPad_Test48(arg0, 7) == 0) {
            if (BtlPad_Test4C(arg0, 2) != 0) {
                func_0023E520(arg0);
            }
            if ((func_0023F420(arg0) & 0x10) && (BtlPad_Test4C(arg0, 1) != 0) &&
                (*(s32 *)(arg0 + 0x9A8) < *(s32 *)(arg0 + 0x9AC))) {
                func_002174D8(arg0, 0x70);
            }
        }
        if (func_001FA1D0(D_00385E8C, arg0) == 0) {
            goto block_27;
        }
        if (func_002174B8(arg0) == -1) {
            goto block_27;
        }
        if (func_00210E18(arg0) != 0x99) {
block_27:
            if (func_00211310(arg0, 2, 1) != 0) {
                BtlAnim_SetBlend(D_00385E94, (s32)arg0, 0);
                return func_0023C710(arg0);
            }
            return -1;
        }
        BtlAnim_SetBlend(D_00385E90, (s32)arg0, 0);
        return func_002174B8(arg0);
    }
    return -1;
}
