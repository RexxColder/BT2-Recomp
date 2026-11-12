#include "common.h"

s32 BtlObjAnim_GetEventArg(s32 arg0, s32 arg1);
s32 BtlObjAnim_MaskToNode(s32 arg0);
void func_00176D68(s32 arg0, s32 arg1, s32 arg2);
void func_001A5EF0(s32 arg0, s32 arg1, s32 arg2);
void func_001B56D8(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_0025FBE8(s32 arg0, s64 arg1);
void func_00260CB8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00269A40(s32 arg0, s32 arg1);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002A8D90(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
s32 rand(void);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);

void func_002A8FD0(u8 *arg0) {
    u8 sp[0x50];
    s32 r;
    s32 s0;
    s32 s3;
    s32 s4;
    s32 mask;
    s32 t;
    s32 node;
    s32 hi;

    r = func_00269A40((s32)arg0, 0x11);
    if (r == 0) {
        r = func_00269A40((s32)arg0, 0);
        if (r != 0) {
            func_003126C8((s32)sp, r + 0x30);
        } else {
            func_003126C8((s32)sp, (s32)(arg0 + 0x9A0));
        }
    } else {
        func_003126C8((s32)sp, r + 0x30);
    }
    func_002A8D90((s32)sp, (s32)(sp + 0x40), (s32)(sp + 0x44));

    if (func_0025FBE8((s32)arg0, 8) != 0) {
        s3 = 0;
        s4 = BtlObjAnim_GetEventArg((s32)arg0, 8);
        mask = 1 << 0;
        do {
            s3 += 1;
            t = s4 & mask;
            if (t != 0) {
                node = BtlObjAnim_MaskToNode(t);
                func_00260CB8((s32)arg0, (s32)(sp + 0x10), node);
                *(s32 *)(sp + 0x1C) = 0;
                sceVu0ApplyMatrix((s32)(sp + 0x10), (s32)(arg0 + 0xA00), (s32)(sp + 0x10));
                func_00176D68(*(s32 *)(arg0 + 0x10), (s32)(sp + 0x10), node);
            }
            mask = 1 << s3;
        } while (s3 < 0x13);
    }

    if (func_0025FBE8((s32)arg0, 0x80) != 0) {
        node = BtlObjAnim_MaskToNode(BtlObjAnim_GetEventArg((s32)arg0, 0x80));
        func_00208DE8(*(s32 *)(arg0 + 0x10), (s32)(sp + 0x20), node);
        func_001A5EF0(6, (s32)(sp + 0x20), *(s32 *)(arg0 + 0x10));
        t = rand() % 2;
        func_00297FE0(1, t + 9, *(s32 *)(sp + 0x40), *(s32 *)(sp + 0x44), 0);
    }

    if (func_0025FBE8((s32)arg0, 0x100) != 0) {
        s0 = 0;
        node = BtlObjAnim_MaskToNode(BtlObjAnim_GetEventArg((s32)arg0, 0x100));
        func_00208DE8(*(s32 *)(arg0 + 0x10), (s32)(sp + 0x30), node);
        hi = rand() % 6;
        if (hi == 1) {
            s0 = 1;
        } else if (hi == 2) {
            s0 = 2;
        } else if (hi == 4) {
            s0 = 4;
        }
        func_001A5EF0(s0, (s32)(sp + 0x30), *(s32 *)(arg0 + 0x10));
        t = rand() % 2;
        func_00297FE0(1, t + 2, *(s32 *)(sp + 0x40), *(s32 *)(sp + 0x44), 0);
    }

    if (func_0025FBE8((s32)arg0, (s64)0x8000 << 27) != 0) {
        func_001B56D8(*(s32 *)(arg0 + 0x10), 0);
    }
}
