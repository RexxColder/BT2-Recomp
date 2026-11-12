#include "common.h"

extern u8 *D_0042A574 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern void func_0026EB78(u8 *arg0, const char *arg1);
extern s32 func_0026EB70(u8 *arg0);
extern s32 func_00249510();
extern void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_00298460(s32 arg0, s32 arg1, s32 arg2);
extern void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_001018B8(void);
extern void EftShotFx_Update_2494A0(void);
extern s32 func_003F3F90(void);
extern s32 func_003F4298(s32 arg0);

#define ST(o) (*(s32 *)(D_0042A574 + (o)))
#define GS(o) (*(s32 *)(D_003876A4 + (o)))

/* advance state: st = st + 1 */
static inline __attribute__((always_inline)) void adv(void) {
    ST(0x124) = ST(0x124) + 1;
}

/* wait for 0x200 on the +0x44 object; returns nonzero when set */
static inline __attribute__((always_inline)) s32 waitbit(void) {
    return func_0026EB70(D_0042A574 + 0x44) & 0x200;
}

/* start a named anim then advance */
static inline __attribute__((always_inline)) void anim_adv(const char *name) {
    func_0026EB78(D_0042A574 + 0x44, name);
    adv();
}

/* s0 path 509C: state++ ; [0x118]=t0; func_2493C0 */
static inline __attribute__((always_inline)) void st_next(s32 t0) {
    u8 *a0 = D_0042A574;
    s32 v0 = *(s32 *)(a0 + 0x124);
    *(s32 *)(a0 + 0x124) = v0 + 1;
    ST(0x118) = t0;
    func_002493C0(*(s32 *)(D_0042A574 + 0xC), 0x37A6, 0x3BBF, 0, ST(0x118));
}

/* set state = next target and remember return */
static inline __attribute__((always_inline)) void st_call(s32 target) {
    u8 *a = D_0042A574;
    *(s32 *)(a + 0x128) = *(s32 *)(a + 0x124) + 1;
    ST(0x124) = target;
}

void func_003F48D8(u32 arg0) {
    u32 st = (u32)ST(0x124);
    if (st >= 0x7B) {
        return;
    }
    switch (st) {
    case 0: {
        s32 v = GS(0x1C);
        s32 r;
        if (v == 13) {
            r = 21;
        } else if (v == 20) {
            r = 1;
        } else if (v == 19) {
            r = 101;
        } else {
            return;
        }
        ST(0x124) = r;
        return;
    }
    case 1:
        func_0026EB78(D_0042A574 + 0x44, "fr_gameover");
        adv();
        func_00249510(7, -0x50);
        return;
    case 2:
        if (waitbit()) {
            st_next(0x2A);
        }
        return;
    case 3: case 23: case 43: case 63: case 83: case 103:
        if (*(s32 *)(D_003B0B00 + 0x134) & 0x4000) {
            adv();
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        return;
    case 4:
        anim_adv("fr_gameover_out");
        return;
    case 5:
        if (waitbit()) {
            adv();
        }
        return;
    case 6:
        ST(0x124) = 0x79;
        return;
    case 21:
        func_0026EB78(D_0042A574 + 0x44, "fr_clear");
        adv();
        func_00249510(9, -0x50);
        return;
    case 22: case 102:
        if (waitbit()) {
            st_next(0x2B);
        }
        return;
    case 24: {
        u8 *D = D_003876A4;
        u8 *E = D_00387F2C;
        s32 a2 = GS(0x60);
        (void)D;
        if ((s32)*(u16 *)(E + (GS(0x58) * 15 + GS(0x64)) * 4 + 0x20E) < a2) {
            st_call(0x29);
        } else {
            adv();
        }
        return;
    }
    case 25: {
        s32 v = func_003F3F90();
        ST(0x130) = v;
        if (ST(0x130) == 0) {
            adv();
            return;
        }
        ST(0x134) = 0;
        ST(0x128) = ST(0x124) + 1;
        ST(0x124) = 0x51;
        return;
    }
    case 26:
        st_call(0x3D);
        return;
    case 27:
        ST(0x118) = 0x31;
        func_002493C0(ST(0xC), 0x37A6, 0x3BBF, 0, ST(0x118));
        adv();
        return;
    case 28:
        if (func_001018B8() != 5) {
            if (!(*(s32 *)(D_003B0B00 + 0x134) & 0x4000)) {
                return;
            }
        }
        EftShotFx_Update_2494A0();
        if (*(s32 *)(D_003B0B00 + 0x134) & 0x4000) {
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
        adv();
        return;
    case 29:
        anim_adv("fr_clear_out");
        return;
    case 30:
        if (waitbit()) {
            adv();
        }
        return;
    case 31: {
        u8 *D, *E, *q;
        u16 *p;
        s32 t0;
        ST(0x124) = 0x79;
        D = D_003876A4;
        E = D_00387F2C;
        p = (u16 *)(E + (*(s32 *)(D + 0x58) * 15 + *(s32 *)(D + 0x64)) * 4 + 0x20E);
        if ((s32)*p < *(s32 *)(D + 0x60)) {
            D = D_003876A4;
            E = D_00387F2C;
            *p = *(u16 *)(D + 0x60);
            q = E + *(s32 *)(D + 0x64) + 0x2C0;
            if (*(s8 *)q < *(s32 *)(D + 0x58) + 1) {
                *q = *(u8 *)(D + 0x58) + 1;
                E = D_00387F2C;
                D = D_003876A4;
            }
            t0 = *(s32 *)(D + 0x64);
            if (*(s32 *)(ST(0x13C) + t0 * 56 + 0xC) == 2) {
                E[(*(s32 *)(D + 0x58) * 15 + t0) * 4 + 0x20C] = D[0x44];
                D = D_003876A4;
                E = D_00387F2C;
                E[(*(s32 *)(D + 0x58) * 15 + *(s32 *)(D + 0x64)) * 4 + 0x20D] = D[0x48];
            } else {
                E[(*(s32 *)(D + 0x58) * 15 + t0) * 4 + 0x20C] = D[0x44];
                D = D_003876A4;
                E = D_00387F2C;
                E[(*(s32 *)(D + 0x58) * 15 + *(s32 *)(D + 0x64)) * 4 + 0x20D] = 0xFF;
            }
        }
        D = D_003876A4;
        if (*(s32 *)(D + 0x64) == 14) {
            *(s32 *)(D + 0x1C) = 19;
        } else {
            *(s32 *)(D + 0x1C) = 18;
        }
        return;
    }
    case 41:
        anim_adv("fr_new_record");
        return;
    case 42:
        if (waitbit()) {
            adv();
        }
        return;
    case 44:
        anim_adv("fr_new_record_out");
        return;
    case 45:
        if (waitbit()) {
            adv();
        }
        return;
    case 46:
        ST(0x124) = ST(0x128);
        return;
    case 61:
        anim_adv("fr_item_get");
        return;
    case 62:
        if (waitbit()) {
            func_00297FE0(2, 8, 0x40, 0x40, 1);
            st_next(0x2D);
        }
        return;
    case 64:
        anim_adv("fr_item_get_out");
        return;
    case 65:
        if (waitbit()) {
            adv();
        }
        return;
    case 66: {
        s32 s1 = func_003F4298(GS(0x64));
        s32 v = func_003F4298(GS(0x64));
        func_00298460(s1, *(s32 *)(v * 48 + ST(0x18) + 0x10), 1);
        ST(0x124) = ST(0x128);
        return;
    }
    case 81:
        if (ST(0x134) < 15) {
            for (;;) {
                u8 *a0 = D_0042A574;
                s32 a1 = *(s32 *)(a0 + 0x134);
                if (*(s32 *)(a0 + 0x130) & (1 << a1)) {
                    anim_adv("fr_course_get");
                    return;
                }
                *(s32 *)(a0 + 0x134) = a1 + 1;
                if (!(ST(0x134) < 15)) {
                    break;
                }
            }
        }
        ST(0x124) = ST(0x128);
        return;
    case 82:
        if (waitbit()) {
            func_00297FE0(2, 4, 0x40, 0x40, 1);
            adv();
        }
        return;
    case 84:
        anim_adv("fr_course_get_out");
        return;
    case 85:
        if (waitbit()) {
            adv();
        }
        return;
    case 86:
        ST(0x124) = 0x51;
        ST(0x134) = ST(0x134) + 1;
        return;
    case 101:
        func_0026EB78(D_0042A574 + 0x44, "fr_all_clear");
        adv();
        func_00249510(10, -0x50);
        return;
    case 104:
        ST(0x124) = 0x79;
        return;
    case 121:
        ST(0x114) = ST(0x114) | 1;
        func_00243A80(0, 0, 0);
        *(s32 *)(u32)arg0 = 0;
        adv();
        return;
    default:
        return;
    }
}
