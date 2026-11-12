#include "common.h"

#define F32(off) (*(f32 *)(sp + (off)))
#define S32(off) (*(s32 *)(sp + (off)))
#define U32(off) (*(u32 *)(sp + (off)))

extern u8 *gBtlCamView;
extern u8 *gEftAuraPool;
extern u8 *D_0038777C;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 *D_003876A0;
extern f32 D_00384A24;

s32 func_00208DE8(s32 id, u8 *out, s32 arg);
f32 Vec3_Dot(u8 *a, u8 *b);
void func_00129B58(u8 *dst, u8 *a, u8 *b);
void Vec3_Normalize(u8 *dst, u8 *src);
void func_0017B4D8(u8 *mtx, u8 *dir, u8 *src);
void func_00129C50(u8 *dst, u8 *mtx, u8 *vec);
s32 func_00129440(u8 *out, u8 *in, s32 a2);
void func_00129BB8(u8 *dst, u8 *src, f32 s);
f32 func_0017B6D8(s32 id, u8 *a1, u8 *a2, f32 scale);
s32 func_00126630(void);

void func_0017B8B8(u8 *obj, s32 id, f32 scale) {
    u8 sp[0x1E0] __attribute__((aligned(16)));
    u8 *tabA[2];
    u8 *tabB[4];
    u8 *pool;
    u8 *node;
    u8 *next;
    u8 *pkt;
    u8 *slot;
    u8 *tail;
    u64 camMem;
    s32 reject;
    s32 i;
    s32 j;
    s32 idx;
    s32 z;
    f32 amp;
    f32 w22, w21;
    f32 d;
    f32 a;

    F32(0xE0) = *(f32 *)(gBtlCamView + 0x8);
    F32(0xE4) = *(f32 *)(gBtlCamView + 0x18);
    F32(0xE8) = *(f32 *)(gBtlCamView + 0x28);
    F32(0xEC) = 1.0f;
    if (*(u32 *)obj & 0x80) {
        tabA[0] = D_0038777C + 0x290;
        tabA[1] = D_0038777C + 0x2D0;
    } else {
        tabA[0] = D_0038777C + 0x210;
        tabA[1] = D_0038777C + 0x250;
    }
    tabB[0] = D_0038777C + 0x310;
    tabB[1] = D_0038777C + 0x350;
    tabB[2] = D_0038777C + 0x390;
    tabB[3] = D_0038777C + 0x3D0;

    for (i = 0; i < 7; i++) {
        func_00208DE8(id, sp + 0x170 + i * 16, *(s32 *)(D_0038777C + 0x488 + i * 4));
    }

    pool = gEftAuraPool;
    amp = *(f32 *)(obj + 0x3C) * *(f32 *)(obj + 0x54) * scale;
    node = *(u8 **)(pool + 0x14);
    if (node == NULL) {
        return;
    }
    for (; node != NULL; node = next) {
        next = *(u8 **)(node + 0xC0);
        if (node[7] != id) {
            continue;
        }
        reject = 0;
        F32(0xA0) = *(f32 *)(node + 0x80);
        F32(0xA4) = *(f32 *)(node + 0x84);
        F32(0xA8) = *(f32 *)(node + 0x88);
        F32(0xAC) = 1.0f;
        if (*(s32 *)(D_0038777C + 0x418 + node[9] * 12) >= 0) {
            d = __builtin_fabsf(Vec3_Dot(sp + 0xE0, sp + 0xA0));
            func_00129B58(sp + 0xF0, obj + (node[9] << 4) + 0x270, obj + 0x70);
            F32(0xF4) = 0.0f;
            Vec3_Normalize(sp + 0xF0, sp + 0xF0);
            F32(0xA0) = F32(0xA0) + F32(0xF0) * d * 0.5f;
            F32(0xA8) = F32(0xA8) + F32(0xF8) * d * 0.5f;
        }
        Vec3_Normalize(sp + 0xB0, sp + 0xA0);
        func_0017B4D8(sp, sp + 0xB0, node + 0x50);
        w22 = *(f32 *)(node + 0x20) * *(f32 *)(node + 0x18) * *(f32 *)(obj + 0x5C);
        w21 = *(f32 *)(node + 0x1C) * *(f32 *)(node + 0x18) * *(f32 *)(obj + 0x5C);
        for (j = 0; j < 4; j++) {
            s32 s4 = (j < 2);
            u8 *src = tabA[node[4]] + (j << 4);
            F32(0xD0) = *(f32 *)(src + 0) * w22;
            F32(0xD4) = *(f32 *)(tabA[node[4]] + (j << 4) + 4) * *(f32 *)(node + 0x18);
            F32(0xD8) = *(f32 *)(tabA[node[4]] + (j << 4) + 8) * w21;
            F32(0xDC) = 1.0f;
            if (!s4) {
                F32(0xD8) = F32(0xD8) * *(f32 *)(node + 0x2C);
            }
            func_00129C50(sp + 0xC0, sp, sp + 0xD0);
            func_00129440(sp + 0x110 + (j << 4), sp + 0xC0, 1);
            if (0xFFF0 < U32(0x110 + (j << 4))) {
                reject = 1;
                break;
            }
            if (0xFFF0 < U32(0x114 + (j << 4))) {
                reject = 1;
                break;
            }
            if (S32(0x118 + (j << 4)) < 0) {
                reject = 1;
                break;
            }
            a = 1.0f / (f32)S32(0x11C + (j << 4));
            func_00129BB8(sp + 0x60 + (j << 4), tabB[node[4] * 2 + node[0xA]] + (j << 4), a);
            a = func_0017B6D8(node[7], sp + 0xC0, sp + 0x170, *(f32 *)(obj + 0x64));
            F32(0x150 + j * 4) = a;
            if (s4) {
                F32(0x150 + j * 4) = a * D_00384A24;
            }
        }
        if (reject) {
            continue;
        }

        S32(0x100) = (s32)(*(f32 *)(node + 0x60) * 255.0f);
        S32(0x104) = (s32)(*(f32 *)(node + 0x64) * 255.0f);
        S32(0x108) = (s32)(*(f32 *)(node + 0x68) * 255.0f);
        for (j = 0; j < 4; j++) {
            f32 k = *(f32 *)(node + 0x6C) * 255.0f * amp;
            S32(0x160 + j * 4) = (s32)(F32(0x150 + j * 4) * k);
        }

        pkt = D_00387AD8;
        D_00387AD8 = pkt + 0x90;
        if (pkt == NULL) {
            return;
        }
        *(u64 *)(pkt + 0x00) = 0xA0000008ULL;
        *(u64 *)(pkt + 0x10) = 0xE400000000008001ULL;
        *(u64 *)(pkt + 0x18) = 0x42142142142160ULL;
        *(u64 *)(pkt + 0x20) = 0x5C;
        pkt[0x30] = sp[0x100];
        pkt[0x31] = sp[0x104];
        pkt[0x32] = sp[0x108];
        pkt[0x33] = sp[0x160];
        *(f32 *)(pkt + 0x34) = F32(0x68);
        pkt[0x48] = sp[0x100];
        pkt[0x49] = sp[0x104];
        pkt[0x4A] = sp[0x108];
        pkt[0x4B] = sp[0x164];
        *(f32 *)(pkt + 0x4C) = F32(0x78);
        pkt[0x60] = sp[0x100];
        pkt[0x61] = sp[0x104];
        pkt[0x62] = sp[0x108];
        pkt[0x63] = sp[0x168];
        *(f32 *)(pkt + 0x64) = F32(0x88);
        pkt[0x78] = sp[0x100];
        pkt[0x79] = sp[0x104];
        pkt[0x7A] = sp[0x108];
        pkt[0x7B] = sp[0x16C];
        *(f32 *)(pkt + 0x7C) = F32(0x98);
        *(f32 *)(pkt + 0x38) = F32(0x60);
        *(f32 *)(pkt + 0x3C) = F32(0x64);
        *(f32 *)(pkt + 0x50) = F32(0x70);
        *(f32 *)(pkt + 0x54) = F32(0x74);
        *(f32 *)(pkt + 0x68) = F32(0x80);
        *(f32 *)(pkt + 0x6C) = F32(0x84);
        *(f32 *)(pkt + 0x80) = F32(0x90);
        *(f32 *)(pkt + 0x84) = F32(0x94);
        for (j = 0; j < 4; j++) {
            u8 *q = pkt + 0x40 + j * 0x18;
            *(u16 *)(q + 0) = *(u16 *)(sp + 0x110 + j * 16);
            *(u16 *)(q + 2) = *(u16 *)(sp + 0x114 + j * 16);
            *(u64 *)q = (*(u64 *)q & 0xFF000000FFFFFFFFULL) | ((u64)(U32(0x118 + j * 16) & 0xFFFFFF) << 32);
            q[7] = 0xFF;
        }

        if (*(u32 *)node & 0x800) {
            camMem = *(u64 *)(gEftAuraPool + 0x288);
        } else if ((*(u32 *)obj & 0x80) == 0) {
            camMem = *(u64 *)(obj + 0x4D0);
        } else {
            camMem = *(u64 *)(obj + node[6] * 8 + 0x4D8);
        }
        *(u64 *)(pkt + 0x28) = camMem;

        z = (S32(0x118) + S32(0x148) + (S32(0x138) + S32(0x128))) >> 10;
        if (func_00126630()) {
            if (z < 0) {
                slot = D_00387AE0 + 8;
            } else if (z < 0x1000) {
                slot = D_00387AE0 + (z << 4) + 8;
            } else {
                slot = D_00387AE0 + 0xFFF8;
            }
        } else {
            if (z < 0) {
                slot = D_00387AE0 + node[0xB] * 8;
            } else if (z < 0x1000) {
                slot = D_00387AE0 + (z * 2 + node[0xB]) * 8;
            } else {
                slot = D_00387AE0 + node[0xB] * 8 + 0xFFF0;
            }
        }
        tail = *(u8 **)(slot + 4);
        *(u8 **)(tail + 4) = pkt;
        *(u8 **)(slot + 4) = pkt;
    }
}
