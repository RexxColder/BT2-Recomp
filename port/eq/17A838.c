#include "common.h"

extern u8 *gEftAuraPrm;
extern u8 *D_0038777C;
extern f32 D_00384A04;
extern f32 D_00384A08;
extern f32 D_00384A0C;
extern f32 D_00384A10;

extern void func_00129C28(void *dst, void *src);
extern void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern void func_00208DE8(s32 obj, void *out, s32 node);
extern void func_00129B58(void *arg0, void *arg1, void *arg2);
extern f32 func_00129CD8(void *arg0, void *arg1);
extern f32 sqrtf(f32 x);
extern s32 rand(void);
extern void func_00129BD0(void *arg0, void *arg1, f32 farg0);
extern void func_00129BB8(f32 farg0, void *arg0, void *arg1);
extern void func_00129C38(void *arg0, void *arg1);
extern void EftAura_GetPartOffset(u8 *aura, void *out, s32 obj, s32 part, f32 r1, f32 r2);
extern s32 EftAura_SpawnFlame(u8 *aura, s32 obj, s32 part, void *pos, void *offset, s32 alt, s32 second, f32 t);

/* Spawns flames of one body part along the line from its previous position to its current node position
   (one per `step` of length); `once` stops after the first. Returns the last spawn result. */
s32 func_0017A838(u8 *aura, s32 obj, s32 part, s32 once) {
    u8 pos[16];
    u8 nodePos[16];
    u8 delta[16];
    u8 d[16];
    u8 offset[16];
    u8 along[16];
    u8 radial[16];
    s32 ret = 0;
    s32 count = 1;
    f32 one = 1.0f;
    f32 scale;
    f32 step;
    f32 len;
    f32 t;
    f32 r1, r2;
    s32 node;
    s32 alt;
    s32 i;

    scale = *(f32 *)(aura + 0x64);
    step = *(f32 *)(gEftAuraPrm + 0x10) * scale;
    func_00129C28(pos, aura + 0x90 + 16 * part);
    Vec4_Set(delta, 0.0f, 0.0f, 0.0f, one);
    node = *(s32 *)(D_0038777C + 12 * part + 0x414);
    if (node >= 0) {
        func_00208DE8(obj, nodePos, node);
        func_00129B58(d, nodePos, pos);
        len = sqrtf(func_00129CD8(d, d));
        func_00129C28(delta, d);
        if (step < len) {
            count = (s32)(len / step + one);
        }
    }
    for (i = 0; i < count; i++) {
        if (part < 2) {
            t = (f32)rand() / D_00384A04 * D_00384A10 + D_00384A08;
        } else {
            t = (f32)rand() / D_00384A04;
        }
        func_00129BD0(along, delta, t);
        r1 = (f32)rand() / D_00384A04 * D_00384A0C + D_00384A08;
        r2 = (f32)rand() / D_00384A04 * D_00384A0C + D_00384A08;
        EftAura_GetPartOffset(aura, radial, obj, part, r1, r2);
        func_00129BB8(scale, radial, radial);
        func_00129C38(offset, radial);
        if ((*(u32 *)(aura + 4) & (1u << part)) != 0) {
            *(u32 *)(aura + 4) = *(u32 *)(aura + 4) & ~(1u << part);
            alt = 1;
        } else {
            *(u32 *)(aura + 4) = *(u32 *)(aura + 4) | (1u << part);
            alt = 0;
        }
        if ((u32)(*(s32 *)(aura + 0x30) - 1) < 2) {
            alt = !(part < 6);
        }
        ret = EftAura_SpawnFlame(aura, obj, part, pos, offset, alt, 0, t);
        if (ret != 0) {
            *(s32 *)(aura + 0x38) = *(s32 *)(aura + 0x38) + 1;
            if (*(s32 *)(aura + 0x38) < 45) {
                if (part < 2 || (rand() & 1) == 0) {
                    if (EftAura_SpawnFlame(aura, obj, part, pos, offset, 0, 1, t) != 0) {
                        *(s32 *)(aura + 0x38) = *(s32 *)(aura + 0x38) + 1;
                    }
                }
            }
        }
        if ((once & 0xFF) != 0) {
            break;
        }
    }
    return ret;
}
