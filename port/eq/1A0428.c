#include "common.h"

extern u8 *D_00387808;
extern u8 *gBtlCamView;
extern u8 D_0036E9C0[];
extern f32 D_00384E08;

s32 BtlScene_IsTimeStopped(void);
s32 func_0020B498(u32 arg0);
s32 BtlCharApi_ObjTestAttr(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void Mtx_InverseRT(u8 *arg0, u8 *arg1);
void func_00129DE0(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
s32 func_0019F8D0(u8 *arg0);
s32 func_0019F8F8(s32 arg0);
void func_0019F940(s32 arg0, s32 arg1);
void func_001A0390(u8 *arg0, s32 arg1, f32 farg0);
extern s32 Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 EftPtcl3_Create(void *arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void func_00181760(u8 *arg0, void *arg1);
void func_001817F8(u8 *arg0, u8 *arg1);
void func_00181828(u8 *arg0, f32 farg0);
void func_001E7178(u8 *arg0);

#define FP(p, o) (*(f32 *)((p) + (o)))
#define PP(p, o) (*(u8 **)((p) + (o)))

s32 func_001A0428(u8 *task) {
    u8 posA[0x10];
    u8 posB[0x10];
    u8 mtx[0x40];
    u8 eftA[0x20];
    u8 ptcl[0x50];
    u8 msg[0x14];
    u8 *base;
    u8 *st;
    u8 *ent;
    s32 result;
    s32 ts;
    s32 tgt;
    s32 cnt;
    s32 i;
    s32 flags;
    s32 turn;
    f32 f;

    base = D_00387808 + 8;
    st = PP(task, 0x38);
    ts = BtlScene_IsTimeStopped();
    if (ts != 0) {
        return ts;
    }
    tgt = func_0020B498(*(u32 *)st);
    if (tgt != -1) {
        *(u32 *)(st + 0x28) &= ~2u;
        if (BtlCharApi_ObjTestAttr(tgt, 0x1000)) {
            *(s32 *)(st + 0x48) = tgt;
            *(u32 *)(st + 0x28) |= 2;
        }
    }
    flags = *(s32 *)(st + 0x28);
    if (BtlCharApi_ObjTestAttr(*(s32 *)st, 0x1000) || (flags & 2)) {
        if (flags & 2) {
            func_00208DE8(*(s32 *)(st + 0x48), posA, 0x36);
        } else {
            func_00208DE8(*(s32 *)st, posA, 0x36);
        }
        Mtx_InverseRT(mtx, gBtlCamView);
        func_00129DE0(posB, posA, mtx + 0x30, 0.5f);
        func_00129C28(st + 0x10, posB);
        flags = *(s32 *)(st + 0x28) | 1;
        *(s32 *)(st + 0x28) = flags;
    }
    result = flags & 1;
    if (result == 0) {
        return result;
    }

    *(s32 *)(st + 0x44) += 1;
    if (!(flags & 0x10)) {
        __builtin_memcpy(eftA, D_0036E9C0, 0x20);
        *(s32 *)(st + 0x3C) = func_0019F8D0(eftA);
        *(u32 *)(st + 0x28) |= 0x10;
    }
    if (*(s32 *)(st + 0x3C) != 0) {
        if (func_0019F8F8(*(s32 *)(st + 0x3C)) == 2) {
            func_0019F940(*(s32 *)(st + 0x3C), 1);
        }
    }
    cnt = *(s32 *)(st + 0x44);
    if (cnt == 1 || cnt == 0x21) {
        f = FP(st, 0x24);
        if (*(s16 *)(st + 0x42) == 1) {
            f = 1.0f;
        }
        func_001A0390(task, (s32)f, (f32)*(s16 *)(st + 0x42));
        *(u16 *)(st + 0x42) += 1;
    }
    flags = *(s32 *)(st + 0x28);
    if (!(flags & 4)) {
        __builtin_memset(ptcl, 0, sizeof(ptcl));
        FP(ptcl, 0x04) = FP(st, 0x24) * 1.5f;
        *(s32 *)(ptcl + 0x30) = 1;
        *(u8 **)(ptcl + 0x34) = base + 0x228;
        *(s32 *)(ptcl + 0x38) = *(s32 *)(base + 0x338) + 0x164;
        *(s32 *)(ptcl + 0x3C) = *(s32 *)(base + 0x33C) + 0x50;
        *(s32 *)(ptcl + 0x40) = *(s32 *)st;
        func_00129C28(ptcl + 0x10, st + 0x10);
        Vec4_Set(ptcl + 0x20, 0.0f, -1.0f, 0.0f, 1.0f);
        ent = (u8 *)EftPtcl3_Create(ptcl);
        *(u8 **)(st + 0x34) = ent;
        EftPtcl3_SetType((s32)ent, 2);
        flags = *(s32 *)(st + 0x28) | 4;
        *(s32 *)(st + 0x28) = flags;
    }
    if (!(flags & 8)) {
        __builtin_memset(msg, 0, sizeof(msg));
        *(u8 *)(msg + 0x00) = 2;
        *(s32 *)(msg + 0x04) = *(s32 *)st;
        *(s32 *)(msg + 0x08) = 0;
        *(s32 *)(msg + 0x0C) = *(s32 *)(base + 0x398);
        *(u8 **)(msg + 0x10) = base + 0x348;
        ent = PP(base, 0x398);
        if (*(s32 *)(ent + 0x2D0) > 0) {
            i = 0;
            do {
                FP(ent, i * 0x30 + 0x10) = 2.0f;
                *(u8 *)(ent + i * 0x30 + 0x2C) = 10;
                *(u8 *)(ent + i * 0x30 + 0x2B) = 0x60;
                i++;
                ent = PP(base, 0x398);
            } while (i < *(s32 *)(ent + 0x2D0));
        }
        func_00181760(st + 0x38, msg);
        func_001817F8(st + 0x38, st + 0x10);
        *(u32 *)(st + 0x28) |= 8;
    }
    func_00181828(st + 0x38, FP(st, 0x24));
    func_001E7178(st + 0x2C);
    func_001E7178(st + 0x30);
    f = FP(st, 0x24) + D_00384E08;
    turn = (*(u16 *)(st + 0x40) + 1) & 7;
    *(u16 *)(st + 0x40) = turn;
    FP(st, 0x24) = f;
    return turn;
}
