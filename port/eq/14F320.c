#include "common.h"

extern f32 D_00384628;
extern u8 D_0036E030[] __attribute__((section(".data")));

s32 EftRay_Create(s32 arg0);
s32 EftRay_CreateByValue(s32 arg0);
void EftRay_SetType(s32 arg0, s32 arg1);
void EftRay_SetPos(s32 arg0, s32 arg1);
void EftRay_Kill(s32 arg0);
s32 func_001B5550(s32 arg0);
void func_001B55C8(u8 *arg0, s32 arg1);
void func_001B5630(s32 arg0);
s32 func_00129C28(s32 arg0, s32 arg1);

/* float -> int the game's way is a plain truncation */
#define F32AT(b, o) (*(f32 *)((b) + (o)))
#define S32AT(b, o) (*(s32 *)((b) + (o)))

/* 0x0014F320: creates / updates / kills a ray effect for slot `slot` of the table at obj2+0x200
   (8 bytes per slot: kind at +0, handle at +4). `flags` bit0 = create, 0xA = set position,
   bit1 = kill. The ray kind comes from obj[5]: 0 = Create (kind 0), 1 = CreateByValue (kind 1),
   2 = the func_001B5550 family. */
void func_0014F320(s32 a0, u8 *obj, u8 *obj2, s32 slot, s32 flags, s32 t1, u8 *pos, f32 f12, f32 f13,
                   f32 f14) {
    u8 sp[0x1A0];
    u8 *tmpl;
    u8 *slotp;
    f32 sx = (f32)*(s16 *)(obj + 0x18) * D_00384628;
    f32 sy = (f32)*(s16 *)(obj + 0x1A) * D_00384628;
    s32 h;
    s32 i;
    s32 kill;

    switch (obj[5]) {
    case 0:
        if (flags & 1) {
            tmpl = sp + 0x60;
            __builtin_memset(tmpl, 0, 0x10);
            S32AT(tmpl, 0x10) = 0xC0;
            S32AT(tmpl, 0x14) = 0xC0;
            S32AT(tmpl, 0x18) = 0xC0;
            S32AT(tmpl, 0x1C) = 0x70;
            F32AT(tmpl, 0x20) = f12;
            F32AT(tmpl, 0x24) = f14 * 100.0f;
            F32AT(tmpl, 0x28) = f13;
            F32AT(tmpl, 0x2C) = sx * f14;
            F32AT(tmpl, 0x30) = sy * f14;
            S32AT(tmpl, 0x34) = 1;
            S32AT(tmpl, 0x38) = obj[0x14];
            S32AT(tmpl, 0x3C) = t1;
            S32AT(tmpl, 0x40) = 1;
            S32AT(tmpl, 0x44) = 0;
            S32AT(tmpl, 0x48) = (s32)(f32)obj[0x15];
            S32AT(tmpl, 0x4C) = (s32)(f32)obj[4];
            tmpl[0x50] = 0;
            for (i = 0; i < 0x60; i += 8) {
                *(s64 *)(sp + i) = *(s64 *)(tmpl + i);
            }
            if (obj[1] == 3) {
                sp[0x50] = 1;
            }
            func_00129C28((s32)sp, (s32)pos);
            h = EftRay_Create((s32)sp);
            slotp = obj2 + slot * 8 + 0x200;
            S32AT(slotp, 4) = h;
            EftRay_SetType(h, 1);
            S32AT(slotp, 0) = 0;
        }
        break;
    case 1:
        if (flags & 1) {
            tmpl = sp + 0xC0;
            __builtin_memset(tmpl, 0, 0x10);
            F32AT(tmpl, 0x0C) = 1.0f;
            S32AT(tmpl, 0x10) = 0x80;
            S32AT(tmpl, 0x14) = 0x80;
            S32AT(tmpl, 0x18) = 0x80;
            S32AT(tmpl, 0x1C) = 0x80;
            F32AT(tmpl, 0x20) = f12;
            F32AT(tmpl, 0x24) = f14 * 800.0f;
            F32AT(tmpl, 0x28) = 2.0f;
            F32AT(tmpl, 0x2C) = sx * f14;
            F32AT(tmpl, 0x30) = sy * f14;
            S32AT(tmpl, 0x34) = 3;
            S32AT(tmpl, 0x38) = obj[0x14];
            S32AT(tmpl, 0x3C) = t1;
            S32AT(tmpl, 0x40) = 1;
            S32AT(tmpl, 0x44) = 1;
            S32AT(tmpl, 0x48) = (s32)(f32)obj[0x15];
            S32AT(tmpl, 0x4C) = (s32)(f32)obj[4];
            tmpl[0x50] = 1;
            for (i = 0; i < 0x60; i += 8) {
                *(s64 *)(sp + 0x60 + i) = *(s64 *)(tmpl + i);
            }
            func_00129C28((s32)(sp + 0x60), (s32)pos);
            h = EftRay_CreateByValue((s32)(sp + 0x60));
            slotp = obj2 + slot * 8 + 0x200;
            S32AT(slotp, 4) = h;
            EftRay_SetType(h, 1);
            S32AT(slotp, 0) = 1;
        }
        break;
    case 2:
        if (flags & 1) {
            h = (s32)(f12 * 30.0f);
            *(s64 *)(sp + 0x60) = *(s64 *)D_0036E030;
            *(s64 *)(sp + 0x68) = *(s64 *)(D_0036E030 + 8);
            __builtin_memset(sp + 0x70, 0, 0x10);
            __builtin_memset(sp + 0x80, 0, 0x10);
            F32AT(sp, 0x90) = f13;
            S32AT(sp, 0x98) = h;
            S32AT(sp, 0x9C) = t1;
            S32AT(sp, 0xA0) = 1;
            S32AT(sp, 0x94) = 1;
            func_00129C28((s32)(sp + 0x70), (s32)pos);
            func_00129C28((s32)(sp + 0x80), (s32)(sp + 0x60));
            S32AT(obj2, slot * 8 + 0x204) = func_001B5550((s32)(sp + 0x70));
        }
        if (flags & 0xA) {
            func_001B55C8(*(u8 **)(obj2 + slot * 8 + 0x204), (s32)pos);
        }
        if (flags & 2) {
            slotp = obj2 + slot * 8 + 0x204;
            func_001B5630(S32AT(slotp, 0));
            S32AT(slotp, 0) = 0;
        }
        return;
    default:
        return;
    }
    if (flags & 0xA) {
        EftRay_SetPos(S32AT(obj2, slot * 8 + 0x204), (s32)pos);
    }
    if (flags & 2) {
        slotp = obj2 + slot * 8 + 0x204;
        EftRay_Kill(S32AT(slotp, 0));
        S32AT(slotp, 0) = 0;
    }
}
