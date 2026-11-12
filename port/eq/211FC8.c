#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
s32 BtlStage_FindZoneNear(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002608E8(s32 arg0);
void func_00260A50(s32 arg0);
s32 func_003126C8(s32 arg0, s32 arg1);

void func_00211FC8(u8 *arg0) {
    s32 buf[8];
    f32 *vec;
    s32 s1;
    s32 r1;
    s32 r2;

    vec = (f32 *)&buf[4];
    if (func_00211310((s32)arg0, 7, 0x40) != 0) {
        func_003126C8((s32)buf, (s32)(arg0 + 0xA50));
        func_003126C8((s32)vec, (s32)(arg0 + 0xA60));
        s1 = BtlStage_FindZoneNear(-1, (s32)buf);
        func_003126C8(*(s32 *)(arg0 + 0x1530) + 0x9A0, (s32)buf);
        func_003126C8(*(s32 *)(arg0 + 0x1530) + 0x9B0, (s32)vec);
        *(s32 *)(*(u8 **)(arg0 + 0x1530) + 0x9F0) = s1;
        r1 = BtlChar_GetPos((s32)arg0);
        *(f32 *)((u8 *)r1 + 0xB4) = vec[1];
        r2 = BtlChar_GetPos((s32)arg0);
        *(s32 *)((u8 *)r2 + 0xB0) = 0;
        *(f32 *)(arg0 + 0x150) = vec[1];
        func_002608E8(*(s32 *)(arg0 + 0x1530));
        func_00260A50(*(s32 *)(arg0 + 0x1530));
        func_002113C0((s32)arg0, 7, 0x40, 0);
    }
}
