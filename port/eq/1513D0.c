#include "common.h"

extern u8 D_0036E040[];
extern f32 D_00384660;
extern f32 D_00384664;
extern f32 D_00384668;
extern f32 D_0038466C;

extern s32 rand(void);
void bt2_fightlog_note(const char *fmt, ...);
extern void func_00129C28(u8 *dst, u8 *src);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Set(u8 *dst, f32 x, f32 y, f32 z);
extern void Vec3_Cross(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Mtx_StoreIdentity(u8 *m);
extern void Mtx_RotateX(f32 a, u8 *dst, u8 *src);
extern void Mtx_RotateY(f32 a, u8 *dst, u8 *src);
extern void Mtx_RotateZ(f32 a, u8 *dst, u8 *src);
extern void Mtx_MulVec4(u8 *dst, u8 *mtx, u8 *vec);
extern f32 Mathf_Asin(f32 x);
extern f32 atan2f(f32 y, f32 x);

extern void func_0014F320(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0, u8 *t1, u8 *t2, f32 f12, f32 f13, f32 f14);
extern void func_0014F7D8(u8 *a0, u8 *a1, s32 a2, u8 *a3, s32 t0, u8 *t1, u8 *t2, f32 f12, f32 f13);
extern void func_0014F8E0(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13, f32 f14);
extern void func_0014FB50(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, u8 *st1, s32 st2, f32 f12, f32 f13);
extern void func_0014FD40(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13, f32 f14);
extern void func_0014FF78(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13);
extern void func_001501C0(u8 *a0, u8 *a1, s32 a2, u8 *a3, s32 t0, u8 *t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13, f32 f14, f32 f15);
extern void func_001503E0(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13);
extern void func_00150700(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, s32 t3, u8 *st0, u8 *st1, f32 f12, f32 f13, f32 f14);
extern void func_00150570(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13);
extern void func_00150990(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13, f32 f14);
extern void func_00150C68(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, u8 *st1, f32 f12, f32 f13);
extern void func_00150E90(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13, f32 f14);
extern void func_00151138(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, u8 *t2, u8 *t3, u8 *st0, f32 f12, f32 f13, f32 f14);

/* Plays one effect slot (kind `type`, sub-slot `slot`): picks the direction vector and the per-pass origin,
   then dispatches to the per-kind spawner (15 kinds). Updates the slot state bytes of p2. */
void func_001513D0(u8 *p0, u8 *ctx, u8 *p2, u8 *p3, u8 *p4, u8 *dir, s32 type, s32 slot,
                   f32 scale, s32 a10, s32 flags) {
    u8 mtx[0x40];
    u8 vTmp[16];
    u8 vOrg[16];
    u8 vAxis[16];
    u8 vOut[16];
    s32 tbl[6];
    s32 *cw = (s32 *)ctx;
    u8 *rec;
    u8 *ent;
    s32 owner;
    u8 *cam;
    f32 entF;
    /* B10 log temporal: punteros de entrada (antes de cualquier lectura) */
    bt2_fightlog_note("B10 1513D0 p0 %p ctx %p p2 %p p3 %p p4 %p dir %p tipo %d slot %d a10 %d fl %X *ctx %08X",
                      p0, ctx, p2, p3, p4, dir, type, slot, a10, flags, ((unsigned long)ctx >= 0x1000) ? *(u32 *)ctx : 0xDEAD);
    rec = *(u8 **)ctx + 272 * type;
    ent = rec + 32 * slot + 16;
    owner = *(s32 *)p0;
    cam = *(u8 **)(p0 + 0x20);
    entF = *(f32 *)(ent + 8);
    s32 idx;
    s32 nPass = 1;
    s32 j;
    s32 flagA;
    s32 flagB;
    s32 cflags;
    f32 amp;
    f32 ang;
    f32 pitch;
    f32 yaw;
    f32 w;
    u8 *pass;

    __builtin_memcpy(tbl, D_0036E040, 24);
    idx = tbl[ent[0]];
    cflags = flags;

    switch (ent[6]) {
    case 0:
        func_00129C28(vOut, dir);
        break;
    case 1:
        func_00129C28(vOut, dir);
        Vec3_Scale(vOut, vOut, -1.0f);
        break;
    case 2:
        Vec4_Set(vAxis, 0.0f, 1.0f, 0.0f, 1.0f);
        if (*(f32 *)(dir + 4) == -1.0f) {
            Vec4_Set(vAxis, 0.0f, 0.0f, 1.0f, 1.0f);
        }
        Vec3_Cross(vOut, dir, vAxis);
        Vec3_Cross(vOut, dir, vOut);
        break;
    case 3:
        Vec4_Set(vAxis, 0.0f, 1.0f, 0.0f, 1.0f);
        if (*(f32 *)(dir + 4) == -1.0f) {
            Vec4_Set(vAxis, 0.0f, 0.0f, 1.0f, 1.0f);
        }
        Vec3_Cross(vOut, dir, vAxis);
        Vec3_Cross(vOut, dir, vOut);
        Vec3_Scale(vOut, vOut, -1.0f);
        break;
    case 4:
        Vec4_Set(vOut, 0.0f, -1.0f, 0.0f, 1.0f);
        break;
    case 5:
        Vec4_Set(vOut, 0.0f, 1.0f, 0.0f, 1.0f);
        break;
    default:
        break;
    }

    flagA = flags & 1;
    if (flagA != 0) {
        u8 *st = p2 + slot + type * 8;
        if (!(st[0] & 2)) {
            if (ent[1] == 3) {
                if (ent[2] != 0) {
                    return;
                }
                if (entF <= 0.0f) {
                    return;
                }
                st[0] |= 1;
            }
            if (ent[2] == 0) {
                if (entF <= 0.0f) {
                    return;
                }
            }
        }
    }
    flagB = flags & 2;
    if (flagB != 0) {
        if (ent[1] == 3) {
            cflags = flags & 0xFD;
        }
    }

    if ((*(u32 *)p3 & (1 << ((idx * 2 + 1) & 31))) != 0) {
        nPass = 2;
    }

    for (j = 0; j < nPass; j++) {
        pass = p2 + 868 * j + 228;
        w = *(f32 *)(pass + (type * 8 + slot) * 4) * scale;
        if (idx < 0) {
            func_00129C28(vTmp, p4);
        } else if (ent[7] & 8) {
            func_00129C28(vTmp, p3 + idx * 32 + 0x1A0);
        } else {
            func_00129C28(vTmp, p3 + idx * 64 + j * 32 + 0x20);
        }
        if (flagA != 0) {
            Vec4_Set(vOrg, 0.0f, 0.0f, 0.0f, 1.0f);
            amp = (f32)*(s16 *)(ent + 22);
            if (0.0f < amp) {
                ang = (f32)rand() / D_00384664 * D_00384660;
                if (D_00384668 <= ang) {
                    ang = ang - D_00384660;
                }
                amp = amp * D_0038466C;
                Vec3_Set(vOrg, 0.0f, amp * ((f32)rand() / D_00384664), 0.0f);
                Mtx_StoreIdentity(mtx);
                Mtx_RotateZ(ang, mtx, mtx);
                Mtx_MulVec4(vOrg, mtx, vOrg);
                pitch = Mathf_Asin(-*(f32 *)(dir + 4));
                yaw = atan2f(*(f32 *)(dir + 0), *(f32 *)(dir + 8));
                Mtx_StoreIdentity(mtx);
                Mtx_RotateX(pitch, mtx, mtx);
                Mtx_RotateY(yaw, mtx, mtx);
                Mtx_MulVec4(vOrg, mtx, vOrg);
                Vec3_Add(vTmp, vTmp, vOrg);
            }
        }

        if ((u32)type < 15) {
            switch (type) {
            case 0:
                func_0014F7D8(ctx, ent, cw[24], pass + 0x240, cflags, (u8 *)owner, vTmp, entF, w);
                break;
            case 1:
                func_0014F8E0(ctx, ent, cw[slot + 96], cw[slot + 104], pass + a10 * 4 + 0x244, cflags, (u8 *)owner, vTmp, vOut, entF, w, scale);
                break;
            case 2:
                func_0014FB50(ctx, ent, cw[182], cw[183], pass + 0x264, cflags, (u8 *)owner, vTmp, p4, vOut, *(s32 *)(cam + 0xC), entF, w);
                break;
            case 3:
                func_0014FD40(ctx, ent, cw[254], cw[255], pass + 0x268, cflags, (u8 *)owner, vTmp, vOut, entF, scale, w);
                break;
            case 4:
                func_0014FF78(ctx, ent, cw[slot + 390], cw[slot + 398], pass + a10 * 4 + 0x26C, cflags, (u8 *)owner, vTmp, vOut, entF, w);
                break;
            case 5:
                if ((rec[2] >> ent[3]) & 1) {
                    return;
                }
                func_001501C0(ctx, ent, cw[slot + 406], pass + a10 * 4 + 0x28C, cflags, (u8 *)owner, vTmp, vOut,
                              pass + (type * 8 + a10) * 4, entF, *(f32 *)(p2 + slot * 4 + 0xC0), scale, w);
                break;
            case 6:
                func_001503E0(ctx, ent, cw[slot + 1398], cw[slot + 1403], pass + a10 * 4 + 0x2A8, cflags, (u8 *)owner, vTmp, vOut, entF, w);
                break;
            case 7:
                func_00150700(ctx, ent, cw[slot + 1478], cw[slot + 1483], pass + a10 * 4 + 0x2BC, cflags, (u8 *)owner,
                              *(s32 *)(cam + 0xC), vTmp, vOut, entF, w, scale);
                break;
            case 8:
                func_0014F320(p0, ent, (s32)pass, a10, cflags, (u8 *)owner, vTmp, entF, w, scale);
                break;
            case 9:
                func_00150570(ctx, ent, cw[slot + 1526], cw[slot + 1531], pass + a10 * 4 + 0x2A8, cflags, (u8 *)owner, vTmp, vOut, entF, w);
                break;
            case 10:
                func_00150990(ent, ctx + 0x1800, cw[slot + 1606], cw[slot + 1614], pass + a10 * 4 + 0x2E4, cflags, (u8 *)owner, vTmp, vOut, entF, w, scale);
                break;
            case 11:
                func_00150990(ent, ctx + 0x1958, cw[slot + 1692], cw[slot + 1700], pass + a10 * 4 + 0x304, cflags, (u8 *)owner, vTmp, vOut, entF, w, scale);
                break;
            case 12: {
                /* BEAMPOS: where the beam is created (handle before/after, origin vTmp, target p4, length) */
                u32 *hp = (u32 *)(pass + a10 * 4 + 0x324);
                u32 h0 = *hp;
                f32 *o_ = (f32 *)vTmp, *t_ = (f32 *)p4;
                func_00150C68(ctx, ent, cw[slot + 1778], cw[slot + 1782], pass + a10 * 4 + 0x324, cflags, (u8 *)owner, vTmp, p4, vOut, entF, w);
                bt2_fightlog_note("BEAMPOS crear fl %X handle %08X -> %08X origen %.1f %.1f %.1f destino %.1f %.1f %.1f largo %.1f",
                                  cflags, h0, *hp, o_[0], o_[1], o_[2], t_[0], t_[1], t_[2],
                                  __builtin_sqrtf((t_[0] - o_[0]) * (t_[0] - o_[0]) + (t_[1] - o_[1]) * (t_[1] - o_[1]) +
                                                  (t_[2] - o_[2]) * (t_[2] - o_[2])));
                break;
            }
            case 13:
                func_00150E90(ent, ctx + 0x1BE8, cw[slot + 1856], cw[slot + 1864], pass + a10 * 4 + 0x334, cflags, (u8 *)owner, vTmp, vOut, entF, w, scale);
                break;
            case 14:
                func_00151138(ent, ctx + 0x1D40, cw[slot + 1942], cw[slot + 1946], pass + a10 * 4 + 0x354, cflags, (u8 *)owner, vTmp, vOut, entF, w, scale);
                break;
            }
        }
        if (type != 5 && (cflags & 0x20)) {
            *(f32 *)(pass + (type * 8 + a10) * 4) = *(f32 *)(pass + (type * 8 + a10) * 4) + *(f32 *)(ent + 16) * scale;
        }
    }

    if (flagA != 0) {
        u8 *st;
        if (type == 5) {
            *(f32 *)(p2 + slot * 4 + 0xC0) = scale;
        }
        st = p2 + slot + type * 8;
        st[0] = (st[0] | 2) & 0xFB;
    }
    if (flagB != 0) {
        u8 *st = p2 + slot + type * 8;
        st[0] |= 4;
    }
}
