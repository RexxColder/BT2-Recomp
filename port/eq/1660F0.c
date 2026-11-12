#include "common.h"
#include "battle/eft_o.h"

typedef struct { u64 lo, hi; } q128;

s32 func_001F3758(s32 arg0);
s32 func_0020B3D0(u32 arg0);
void *EftBlastObj_Create(EftBlastObjArg *arg0);
s32 func_00191960(u8 *arg0, s32 arg1);
s32 func_001919C8(u8 *arg0);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void Mtx_StoreIdentity(void *arg0);
void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Mtx_MulVec4(f32 *arg0, f32 *arg1, f32 *arg2);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void func_00129C28(q128 *arg0, q128 *arg1);
f32 Vec3_Dot(f32 *arg0, f32 *arg1);
f32 atan2f(f32 farg0, f32 farg1);
f32 sinf(f32 farg0);
f32 BtlCharApi_GetHeight(s32 arg0);
extern s32 rand();
extern f32 D_003847B8;
extern f32 D_003847BC;
extern f32 D_003847C0;
extern f32 D_003847C4;
extern f32 D_003847C8;

/* 0x001660F0: spawn the next blast object of a shot sequence and place it around the target.
 * The task's shot data (arg+0x38): +0xD30 = number of blast objects so far, slots of 0x40 bytes at +0xAB0. */
void func_001660F0(u8 *task) {
    u8 *shot = *(u8 **)(task + 0x38);
    u8 *owner = *(u8 **)(func_001F3758((s32)(u32)task) + 0x38);
    u8 *effect = *(u8 **)(shot + 0xB0);
    s32 target = func_0020B3D0(*(u32 *)effect);
    u8 *slot = shot + (*(s32 *)(shot + 0xD30) << 6) + 0xAB0;
    EftBlastObjArg arg;
    u8 *blast;
    f32 mtx[16];
    f32 basePos[4];
    f32 offs[4];
    f32 diff[4];
    f32 angle;
    f32 scale;
    f32 mul;

    if (slot == NULL) {
        return;
    }
    arg.src = (EftOSrc *)effect;
    arg.set = (EftOSet *)owner;
    arg.nodes = (EftOEmitNodes *)(shot + 0x860);
    arg.pos = (Vec4 *)(shot + 0x70);
    arg.dir = (Vec4 *)(shot + 0x30);
    arg.index = *(s32 *)(shot + 0xD30);
    arg.count = 10;
    arg.kind = 2;
    arg.evtIdx = 1;
    arg.life = 0.0f;
    arg.scale = *(f32 *)(shot + 0x1C);
    arg.speed = *(f32 *)(*(u8 **)(effect + 0x24) + 8);
    blast = (u8 *)EftBlastObj_Create(&arg);
    *(u8 **)(slot + 4) = blast;
    func_00191960(blast, 1);
    if (!(*(s32 *)(shot + 0x10) < *(s16 *)(*(u8 **)(effect + 0x20) + 0x34))) {
        func_001919C8(*(u8 **)(slot + 4));
    }
    *(s32 *)slot = *(s32 *)slot | 1;
    func_00208DE8(target, (s32)(u32)basePos, 0x11);
    angle = (f32)*(s32 *)(shot + 0xD30) / 10.0f * D_003847B8;
    angle = angle + angle;
    if (D_003847B8 <= angle) {
        angle = angle - D_003847BC;
    }
    Mtx_StoreIdentity(mtx);
    Mtx_RotateY(angle, mtx, mtx);
    Vec4_Set(offs, 0.0f, 0.0f, -1.0f, 1.0f);
    Mtx_MulVec4(offs, mtx, offs);
    Vec3_Sub(diff, basePos, shot + 0x70);
    angle = atan2f(diff[0], diff[2]);
    Mtx_StoreIdentity(mtx);
    Mtx_RotateY(angle, mtx, mtx);
    Mtx_MulVec4(offs, mtx, offs);
    scale = BtlCharApi_GetHeight(target) / D_003847C0;
    if (scale < D_003847C4) {
        scale = D_003847C4;
    }
    mul = scale * 100.0f;
    offs[0] = offs[0] * mul;
    offs[2] = offs[2] * mul;
    offs[1] = offs[1] - scale * ((f32)rand() / D_003847C8 * 3.0f + 50.0f);
    Vec3_Add(slot + 0x10, basePos, offs);
    func_00129C28((q128 *)offs, (q128 *)(slot + 0x10));
    *(f32 *)(slot + 0x30) = (f32)rand() / D_003847C8 * D_003847B8;
    offs[1] = offs[1] + sinf(*(f32 *)(slot + 0x30)) * 10.0f;
    Vec3_Sub(slot + 0x20, offs, shot + 0x70);
    *(f32 *)(slot + 0x34) = 0.0f;
    *(f32 *)(slot + 0x38) =
        __builtin_sqrtf(Vec3_Dot((f32 *)(slot + 0x20), (f32 *)(slot + 0x20))) / *(f32 *)(*(u8 **)(effect + 0x24) + 8);
    *(s32 *)(shot + 0xD30) = *(s32 *)(shot + 0xD30) + 1;
    *(s32 *)shot = *(s32 *)shot | 0x400;
}
