#include "common.h"
#include "battle/eft_o.h"

extern f32 D_00384598;
extern f32 D_0038459C;
extern f32 D_003845A0;

u8 *func_001F3758(void *a0);
void *EftBlastObj_Create(EftBlastObjArg *arg0);
s32 func_00191960(u8 *arg0, s32 arg1);
s32 func_001919C8(u8 *arg0);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void Mtx_StoreIdentity(f32 *m);
void Mtx_RotateY(f32 *dst, f32 *src, f32 angle);
s32 Vec4_Set(f32 *v, f32 x, f32 y, f32 z, f32 w);
void Mtx_MulVec4(f32 *dst, f32 *m, f32 *v);
void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
void Vec3_Add(u8 *dst, u8 *a, u8 *b);
f32 Vec3_Dot(f32 *a, f32 *b);
f32 atan2f(f32 y, f32 x);
f32 sinf(f32 x);
s32 rand(void);
void func_00129C28(f32 *dst, u8 *src);

/* Spawns one blast object plus its trail record around the owner (obj+0x38 = effect state). */
void func_0014B208(u8 *obj) {
    f32 mtx[16];
    f32 pos[4];
    f32 vec[4];
    f32 diff[4];
    EftBlastObjArg arg;
    u8 *eff;
    u8 *other;
    u8 *rec;
    u8 *rec_base;
    u8 *owner;
    f32 ang;
    f32 dist;
    s32 idx;

    other = func_001F3758(obj);
    eff = *(u8 **)(obj + 0x38);
    other = *(u8 **)(other + 0x38);
    idx = *(s32 *)(eff + 0xCB0);
    rec_base = eff + (idx << 6);
    rec = rec_base + 0xAB0;
    owner = *(u8 **)(eff + 0xB0);
    if (rec == NULL) {
        return;
    }
    arg.src = (EftOSrc *)owner;
    arg.set = (EftOSet *)other;
    arg.nodes = (EftOEmitNodes *)(eff + 0x860);
    arg.pos = (Vec4 *)(eff + 0x70);
    arg.dir = (Vec4 *)(eff + 0x30);
    arg.index = *(s32 *)(eff + 0xCB0);
    arg.count = 8;
    arg.kind = 2;
    arg.evtIdx = 1;
    arg.life = 0.0f;
    arg.scale = *(f32 *)(eff + 0x1C);
    arg.speed = *(f32 *)(*(u8 **)(owner + 0x24) + 8);
    *(void **)(rec + 4) = EftBlastObj_Create(&arg);
    func_00191960(*(u8 **)(rec + 4), 1);
    if (*(s32 *)(eff + 0x10) >= *(s16 *)(*(u8 **)(owner + 0x20) + 0x34)) {
        func_001919C8(*(u8 **)(rec + 4));
    }
    *(u32 *)rec |= 1;
    func_00208DE8(*(s32 *)owner, (s32)pos, 0x11);
    ang = ((f32)*(s32 *)(eff + 0xCB0) * 0.125f * D_00384598) * 2.0f;
    if (D_00384598 <= ang) {
        ang -= D_0038459C;
    }
    Mtx_StoreIdentity(mtx);
    Mtx_RotateY(mtx, mtx, ang);
    Vec4_Set(vec, 0.0f, 0.0f, -1.0f, 1.0f);
    Mtx_MulVec4(vec, mtx, vec);
    Vec3_Sub((u8 *)diff, (u8 *)pos, eff + 0x70);
    ang = atan2f(diff[0], diff[2]);
    Mtx_StoreIdentity(mtx);
    Mtx_RotateY(mtx, mtx, ang);
    Mtx_MulVec4(vec, mtx, vec);
    vec[0] = vec[0] * (*(f32 *)(eff + 0x1C) * 100.0f);
    vec[1] = vec[1] - *(f32 *)(eff + 0x1C) * 50.0f;
    vec[2] = vec[2] * (*(f32 *)(eff + 0x1C) * 100.0f);
    Vec3_Add(rec_base + 0xAC0, (u8 *)pos, (u8 *)vec);
    func_00129C28(vec, rec_base + 0xAC0);
    *(f32 *)(rec + 0x30) = ((f32)rand() / D_003845A0) * D_00384598;
    vec[1] = vec[1] + sinf(*(f32 *)(rec + 0x30)) * 12.0f;
    Vec3_Sub(rec_base + 0xAD0, (u8 *)vec, eff + 0x70);
    dist = __builtin_sqrtf(__builtin_fabsf(Vec3_Dot((f32 *)(rec_base + 0xAD0), (f32 *)(rec_base + 0xAD0))));
    *(f32 *)(rec + 0x34) = 0.0f;
    *(f32 *)(rec + 0x38) = dist / *(f32 *)(*(u8 **)(owner + 0x24) + 8);
    *(s32 *)(eff + 0xCB0) += 1;
    *(u32 *)eff |= 0x400;
}
