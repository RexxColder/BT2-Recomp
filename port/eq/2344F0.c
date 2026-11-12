#include "common.h"

extern f32 D_00386958;

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
s32 func_00217488(void *arg0);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
s32 func_00206958(u8 *a0, s64 a1);
void func_00211418(s32 arg0, s32 arg1);
void func_0020FC38(u8 *a0, s32 a1);
s32 func_00212320(s32 arg0);
s32 func_002411E0(u8 *a0, s32 a1);
void *BtlChar_GetPos(s32 arg0);

u8 *func_002344F0(u8 *obj) {
    s32 kind;
    s32 anim;
    s32 cur;
    u8 *pos;

    func_002113C0((s32)obj, 7, (s32)0xFFFDFFFF, 0);
    if (func_00211310((s32)obj, 0, 1) != 0) {
        func_00215068(obj, 1, 9, D_00386958, 1.0f);
        func_00215E88(1.0f, (s32)obj, 3);
    }

    kind = func_00217488(obj);
    switch (kind) {
    case 184:
    case 190:
        BattleSide_SetChara(obj, 284);
        func_00206958(obj, (s64)0x0020000000000000LL);
        func_002113C0((s32)obj, 15, 0x1000, 1);
        func_00211418((s32)obj, 0x80000);
        break;
    case 185:
    case 191:
        BattleSide_SetChara(obj, 318);
        func_00206958(obj, (s64)0x0040000000000000LL);
        func_002113C0((s32)obj, 15, 0x2000, 1);
        func_00211418((s32)obj, 0x80000);
        break;
    case 186:
    case 192:
        BattleSide_SetChara(obj, 386);
        func_00206958(obj, (s64)0x0080000000000000LL);
        func_002113C0((s32)obj, 15, 0x4000, 1);
        func_00211418((s32)obj, 0x100000);
        break;
    default:
        break;
    }

    anim = func_00217488(obj);
    if (anim < 193 && anim >= 190) {
        *(s32 *)(obj + 0x8DC) |= 1;
    }
    func_0020FC38(obj, 43);
    func_002113C0((s32)obj, 0, 2, 1);

    cur = func_00212320((s32)obj);
    if ((func_002411E0(obj, cur) & 0x20000) != 0) {
        if (func_00211310((s32)obj, 8, 1) == 0) {
            *(s32 *)(*(u8 **)(obj + 0x1530) + 0xAF0) &= 0xFF00FFFF;
            *(s32 *)(*(u8 **)(obj + 0x1530) + 0xAF0) |= 0x40000;
        }
    }
    *(s32 *)(obj + 0xA30) = 0;

    pos = (u8 *)BtlChar_GetPos((s32)obj);
    *(s32 *)(pos + 0xC0) = 0;
    pos = (u8 *)BtlChar_GetPos((s32)obj);
    *(s32 *)(pos + 0xC4) = 0;
    return pos;
}
