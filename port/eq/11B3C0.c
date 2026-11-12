#include "common.h"


s32 func_0011ADA0(u8 *arg0, u8 *arg1);
s32 func_0011AF68(u8 *arg0, u8 *arg1);
s32 func_0011B138(u8 *arg0, u8 *arg1);
void *func_001272E0(s32 arg0);
s32 func_00127480(void *arg0, s32 arg1);
s32 func_00202088(s32 arg0, u8 *arg1);
s32 func_002023D0(s32 arg0, s32 arg1);
s32 func_00202630(s32 arg0, u8 *arg1, s32 arg2);
s32 func_00202798(s32 arg0, u8 *arg1, s32 arg2);
void EftHit_SetTaskFlag(s32 arg0, s32 arg1, s32 arg2);
s32 func_001A6028(f32 f12, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 EftHit_IsMultiHit(u8 *arg0);
void EftDet_HitFighterMulti(u8 *arg0, s32 arg1, s32 arg2);
void EftDet_HitFighter(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *D_00387A40;
void bt2_fightlog_note(const char *fmt, ...);

/* Hit test chosen by the record's kind (kinds 2..6 share one routine). Kept as a switch: a table of function
   pointers on the stack cannot be initialised in the 32-bit-pointer PC build. */
static s32 HitTestByKind(s32 kind, u8 *a, u8 *b) {
    switch (kind) {
    case 0:
        return func_0011ADA0(a, b);
    case 1:
        return func_0011AF68(a, b);
    default:
        return func_0011B138(a, b);
    }
}

/* Walks the per-object table (count at +0x6000, 0x180-byte records), picks a hit test
   from the handler table by the record's kind, and dispatches the matching hit routine. */
void func_0011B3C0(void) {
    u8 *base;
    u8 *ent;
    u8 *rec;
    u8 *slot;
    s32 k;
    s32 count;
    s32 v7;
    s32 gbase;
    s32 flags;
    s32 hit;
    s32 r;
    s32 ok;

    base = (u8 *)func_001272E0((s32)func_0011B138);
    k = 0;
    count = *(s32 *)(base + 0x6000);
    if (count <= 0) {
        return;
    }

    do {
        ent = base + k * 0x180;
        rec = base + 0x130 + k * 0x180;
        slot = base + 0xA0 + k * 0x180;

        if (func_00127480(ent, 1) != 0) {
            gbase = *(s32 *)D_00387A40;
            v7 = *(s32 *)ent ^ 1;
            s32 t;
            {   /* B3b log temporal: cada registro vivo, su kind y el resultado de la prueba */
                t = HitTestByKind(*(s32 *)(ent + 0x70), (u8 *)(gbase + 0x18580 * v7), ent + 0x70);
                if (*(s32 *)(ent + 0xC) != 0)
                    bt2_fightlog_note("B3B REG k %d dueno J%d kind %d C %08X fl %08X test %d", k, *(s32 *)ent + 1,
                                      *(s32 *)(ent + 0x70), *(s32 *)(ent + 0xC), *(s32 *)(rec + 0x8), t);
                if (*(s32 *)(ent + 0xC) != 0) {
                    f32 *a = (f32 *)(ent + 0x70 + 0x84), *b = (f32 *)(gbase + 0x18580 * v7 + 0xF78);
                    f32 *c = (f32 *)(s32)*(s32 *)(ent + 0x70 + 0xC);
                    bt2_fightlog_note("B3B CAJA rec %.0f %.0f %.0f / %.0f %.0f %.0f  luch %.0f %.0f %.0f / %.0f %.0f %.0f  esfera %.0f %.0f %.0f r %.1f",
                                      a[0], a[1], a[2], a[4], a[5], a[6], b[0], b[1], b[2], b[4], b[5], b[6], c[0], c[1], c[2], c[8]);
                }
            }
            if (t != 0) {
                flags = *(s32 *)(rec + 0x8);
                ok = ((flags & 1) == 0) || (*(f32 *)rec < *(f32 *)(rec + 0x4));
                if (ok) {
                    *(s32 *)(rec + 0x8) = flags | 2;
                    if (func_00202088(v7, ent) == 0) {
                        hit = 0;
                        r = func_002023D0(v7, (s32)ent);
                        if (r != 0) {
                            hit = 0x40;
                        } else if (func_00202630(v7, ent, (s32)slot) != 0) {
                            hit = 0x80;
                        } else if (func_00202798(v7, ent, (s32)slot) != 0) {
                            EftHit_SetTaskFlag(k, 0x20, (s32)slot);
                        } else if (EftHit_IsMultiHit(ent) == 0) {
                            EftDet_HitFighter(ent, v7, k);
                        } else {
                            EftDet_HitFighterMulti(ent, v7, k);
                        }
                        if (hit != 0) {
                            EftHit_SetTaskFlag(k, hit, (s32)slot);
                            func_001A6028(1.0f, (s32)slot, v7, *(s32 *)(rec - 0x12C),
                                          (s32)(ent + 0x20), (s32)(ent + 0x30));
                        }
                    }
                }
            }
        }

        k++;
        count = *(s32 *)(base + 0x6000);
    } while (k < count);
}
