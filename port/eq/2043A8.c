#include "common.h"

s32 func_0025FBE8(u8 *arg0, s64 arg1);
s32 BtlObjAnim_GetEventArg(u8 *arg0, s32 arg1);
s32 BtlObjAnim_MaskToNode(s32 arg0);
void func_00260CB8(u8 *arg0, s32 *arg1, s32 arg2);
void sceVu0ApplyMatrix(f32 *out, f32 *in, f32 *m);
void func_00176D68(u8 *arg0, s32 *arg1, s32 arg2);

void func_002043A8(u8 *arg0) {
    s32 sp[4];
    s32 s2 = 0;
    s32 s3;
    s32 mask = 1;
    s32 m;
    s32 node;

    if (func_0025FBE8(*(u8 **)(arg0 + 0x1530), 8) == 0) {
        return;
    }
    s3 = BtlObjAnim_GetEventArg(*(u8 **)(arg0 + 0x1530), 8);
    do {
        s2 += 1;
        m = s3 & mask;
        if (m != 0) {
            node = BtlObjAnim_MaskToNode(m);
            func_00260CB8(*(u8 **)(arg0 + 0x1530), sp, node);
            sp[3] = 0;
            sceVu0ApplyMatrix((f32 *)sp, (f32 *)(*(u8 **)(arg0 + 0x1530) + 0xA00), (f32 *)sp);
            func_00176D68(*(u8 **)(arg0 + 0x1534), sp, node);
        }
        mask = 1 << s2;
    } while (s2 < 0x13);
}
