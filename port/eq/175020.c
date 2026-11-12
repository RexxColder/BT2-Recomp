#include "common.h"

extern f32 D_003848F8;
extern f32 D_003848FC;
extern f32 D_00384900;
extern f32 D_00384904;
extern f32 D_00384908;
extern f32 D_0038490C;

s32 func_001F3758(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 func_0012D488(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
u8 *func_00174FE8(u8 *arg0);
void func_00129C28(void *arg0, void *arg1);
extern s32 Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Mtx_StoreIdentity(void *arg0);
void Mtx_RotateZ(f32 farg0, void *arg0, void *arg1);
void Mtx_RotateX(f32 farg0, void *arg0, void *arg1);
void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
void func_00129C50(void *arg0, void *arg1, void *arg2);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 y, f32 x);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
extern s32 rand(void);
void Vec3_Normalize(void *arg0, void *arg1);
s32 func_00191600(void *arg0);
s32 func_001919C8(u8 *arg0);
void EftTechEvt_RequestRestart(s32 objId);
s32 func_00191728(u8 *arg0);

#define FP(p, o) (*(f32 *)((p) + (o)))
#define PP(p, o) (*(u8 **)((p) + (o)))

s32 func_00175020(u8 *task) {
    u8 mtx[0x40];
    u8 dirVec[0x10];
    u8 posVec[0x10];
    u8 blast[0x30];
    u8 *st;
    u8 *eft;
    u8 *obj;
    u8 *slot;
    s32 ctx;
    s32 i;
    s32 anyAlive;
    s32 ra, rb;
    s32 id;
    f32 d, ang, yaw, v;

    anyAlive = 0;
    ctx = *(s32 *)(func_001F3758((s32)task) + 0x38);
    st = PP(task, 0x38);
    eft = PP(st, 0xB0);
    if (EftShot_TestBits(*(s32 *)eft, 4)) {
        *(s32 *)(st + 0x10) += 1;
        func_00208DE8(*(s32 *)eft, st + 0x50, *(s32 *)(st + 8));
        func_0012D488(eft, st + 0x30, (s32)(st + 0x70), *(s32 *)eft);
        obj = func_00174FE8(st);
        if (obj != NULL) {
            func_00129C28(posVec, st + 0x30);
            if (**(s32 **)(eft + 0x20) == 0x75) {
                Vec4_Set(dirVec, 0.0f, -3.0f, 0.0f, 1.0f);
                Mtx_StoreIdentity(mtx);
                Mtx_RotateZ(FP(st, 0x24), mtx, mtx);
                func_00129C50(dirVec, mtx, dirVec);
                ang = Mathf_Asin(-FP(st, 0x34));
                yaw = atan2f(FP(st, 0x30), FP(st, 0x38));
                Mtx_StoreIdentity(mtx);
                Mtx_RotateX(ang, mtx, mtx);
                Mtx_RotateY(yaw, mtx, mtx);
                func_00129C50(dirVec, mtx, dirVec);
                Vec3_Add(dirVec, dirVec, st + 0x70);
                v = FP(st, 0x24) + ((f32)rand() / D_00384904) * D_00384908;
                FP(st, 0x24) = v;
                if (D_0038490C <= v) {
                    FP(st, 0x24) = v - D_00384908;
                }
            } else {
                ra = rand();
                d = D_003848F8;
                rb = rand();
                FP(posVec, 0) = FP(posVec, 0) + (((f32)ra / d) - ((f32)rb / d)) * D_003848FC;
                ra = rand();
                rb = rand();
                FP(posVec, 4) = FP(posVec, 4) + (((f32)ra / d) - ((f32)rb / d)) * D_00384900;
                ra = rand();
                rb = rand();
                FP(posVec, 8) = FP(posVec, 8) + (((f32)ra / d) - ((f32)rb / d)) * D_003848FC;
                Vec3_Normalize(posVec, posVec);
                func_00129C28(dirVec, st + 0x50);
            }
            *(u8 **)(blast + 0x00) = eft;
            *(s32 *)(blast + 0x04) = ctx;
            *(u8 **)(blast + 0x08) = st + 0x860;
            *(u8 **)(blast + 0x0C) = dirVec;
            *(u8 **)(blast + 0x10) = posVec;
            *(s32 *)(blast + 0x14) = *(s32 *)(st + 0xAB0);
            *(s32 *)(blast + 0x18) = 0x1E;
            *(s32 *)(blast + 0x1C) = 2;
            *(s32 *)(blast + 0x20) = 1;
            *(s32 *)(blast + 0x24) = 0;
            FP(blast, 0x28) = FP(st, 0x1C);
            FP(blast, 0x2C) = FP(st, 0x14);
            id = func_00191600(blast);
            *(s32 *)(obj + 4) = id;
            if (!(*(s32 *)(st + 0x10) < *(s16 *)(PP(eft, 0x20) + 0x34))) {
                func_001919C8((u8 *)id);
            }
            *(s32 *)(st + 0xAB0) += 1;
            *(u32 *)st |= 0x200;
        }
        EftTechEvt_RequestRestart(*(s32 *)eft);
    }
    slot = st + 0xAB4;
    for (i = 29; i >= 0; i--) {
        if (func_00191728(PP(slot, 4))) {
            anyAlive = 1;
        } else {
            *(s32 *)(slot + 4) = 0;
        }
        slot += 8;
    }
    return anyAlive;
}
