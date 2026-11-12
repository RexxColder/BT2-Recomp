#include "common.h"

extern u8 *D_0042A590 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_0042BB28[] __attribute__((section(".data")));
extern u8 D_0042BB38[] __attribute__((section(".data")));
extern u8 D_0042BB40[] __attribute__((section(".data")));
extern u8 D_0042BB50[] __attribute__((section(".data")));
extern u8 D_0042BB60[] __attribute__((section(".data")));

extern void func_0026EB78(u8 *a0, u8 *a1);
extern s32 func_0026EB70(u8 *a0);
extern s32 func_0026EB60(u8 *a0);
extern void func_0026EA88(u8 *a0);
extern void func_0026EAE0(u8 *a0, s32 a1);
extern void func_0026EB08(u8 *a0);
extern void func_0026EBA8(u8 *a0, s32 a1);
extern void func_002493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern void func_00325370();
extern s64 GetTimerSystemTime();
extern s32 rand();
extern void func_003FF930(void);
extern void func_003FF990(void);
extern void func_003FFD00(void);
extern void func_003FF340(void);

#define G (D_0042A590)
#define GW(o) (*(s32 *)(G + (o)))
#define H (D_3876A4)
#define HW(o) (*(s32 *)(H + (o)))
#define REC(o) (*(s32 *)(GW(0x274) + 56 * HW(0x64) + (o)))

/* fade/timer helper shared by 3, 0x35, 0x67: skip-button shortcut, count down g[0x224] */
#define COUNTDOWN(OBJ, NAME) \
    if (D_003B0C34 & 0x4000) { \
        GW(0x224) = 0; \
        func_00297FE0(0, 1, 0x40, 0x40, 1); \
    } \
    GW(0x224) = GW(0x224) - 1; \
    if (GW(0x224) != -1) { \
        return; \
    } \
    func_0026EB78(G + (OBJ), NAME); \
    GW(0x220) = GW(0x220) + 1; \
    return;

static void set_1e0(void) {
    s32 t = REC(0xC);
    if (t == 2 || t == 4) {
        GW(0x1E0) = *(s32 *)(GW(0x120) + 0x10) + 0x180;
    } else {
        GW(0x1E0) = *(s32 *)(GW(0x120) + 0x10) + 0x1C0;
    }
}

void func_00401CE0(s32 arg0) {
    s32 st;

    st = GW(0x220);
    switch (st) {
    case 0:
    case 0xFB:
    case 0x12D:
        return;
    case 1: {
        s32 a2;
        func_0026EB78(G + 0xCC, D_0042BB28);
        GW(0x220) = GW(0x220) + 1;
        a2 = GW(0x23C);
        if (a2 == 0) {
            HW(0x40) = HW(0x40) | 0x10000;
            func_002493C0(0, 0x37A6, 0x3BBF, 0, 0x1A);
        } else if (a2 == 1) {
            func_002493C0(0, 0x37A6, 0x3BBF, 0, 0x19);
        } else if (a2 == REC(8) - 1) {
            func_002493C0(0, 0x37A6, 0x3BBF, 0, 0x14);
        } else {
            s32 r;
            func_00325370((s32)GetTimerSystemTime());
            r = rand() % 3;
            if (r == 1) {
                func_002493C0(0, 0x37A6, 0x3BBF, 0, 0x17);
            } else if (r == 0) {
                func_002493C0(0, 0x37A6, 0x3BBF, 0, 0x15);
            } else if (r == 2) {
                func_002493C0(0, 0x37A6, 0x3BBF, 0, 0x18);
            }
        }
    }
        /* fall through to the check */
    case 2:
        if (func_0026EB70(G + 0xCC) & 0x200) {
            GW(0x224) = 0xB4;
            GW(0x220) = GW(0x220) + 1;
        }
        return;
    case 3:
        COUNTDOWN(0xCC, D_0042BB38)
    case 4:
        if (func_0026EB70(G + 0xCC) & 0x200) {
            GW(0x208) = GW(0x208) | 1;
            GW(0x208) = GW(0x208) | 2;
            GW(0x214) = 0xF;
            GW(0x220) = 0;
            GW(0x234) = HW(0x6C);
        }
        return;
    case 0x33:
        func_0026EB78(G + 0xCC, D_0042BB40);
        GW(0x220) = GW(0x220) + 1;
        /* fall through */
    case 0x34:
        if (func_0026EB70(G + 0xCC) & 0x200) {
            func_00297FE0(2, 3, 0x40, 0x40, 1);
            GW(0x224) = 0xB4;
            GW(0x220) = GW(0x220) + 1;
        }
        return;
    case 0x35:
        COUNTDOWN(0xCC, D_0042BB50)
    case 0x36:
        if (func_0026EB70(G + 0xCC) & 0x200) {
            func_0026EA88(G + 0xCC);
            func_00297FE0(2, 1, 0x40, 0x40, 1);
            GW(0x220) = GW(0x220) + 1;
        }
        return;
    case 0x37:
        if (func_0026EB60(G + 0xCC) == 0) {
            return;
        }
        GW(0x220) = 0;
        if (REC(0xC) == 1) {
            GW(0x220) = 0xC9;
            return;
        }
        if (GW(0x23C) == 0) {
            s32 v = GW(0x208);
            if (v & 0x200) {
                GW(0x220) = 0x65;
                return;
            }
            if (v & 0x100) {
                GW(0x208) = v | 1;
                GW(0x208) = GW(0x208) | 2;
                GW(0x214) = 0xF;
                *(s32 *)arg0 = 0;
            }
        } else {
            if (GW(0x208) & 0x100) {
                GW(0x220) = 0x97;
                return;
            }
        }
        GW(0x220) = 0;
        return;
    case 0x65:
        GW(0x234) = REC(4);
        HW(0x40) = HW(0x40) | 4;
        HW(0x40) = HW(0x40) | 8;
        func_0026EAE0(G + 0xF4, 0x3C);
        func_0026EA88(G + 0xF4);
        GW(0x220) = GW(0x220) + 1;
        func_002493C0(0, 0x37A6, 0x3BBF, 0, 0x1C);
        /* fall through */
    case 0x66:
        if (func_0026EB70(G + 0xF4) & 0x200) {
            GW(0x224) = 0xB4;
            GW(0x220) = GW(0x220) + 1;
        }
        return;
    case 0x67:
        COUNTDOWN(0xF4, D_0042BB60)
    case 0x68:
        if (func_0026EB70(G + 0xF4) & 0x200) {
            GW(0x208) = GW(0x208) | 1;
            GW(0x208) = GW(0x208) | 2;
            GW(0x214) = 0xF;
            GW(0x220) = 0;
        }
        return;
    case 0x97:
        func_003FF930();
        GW(0x220) = GW(0x220) + 1;
        /* fall through */
    case 0x98:
        if ((func_0026EB70(G + 0x54) & 0x200) == 0) {
            return;
        }
        if (*(s8 *)(HW(0x64) + D_387F2C + 0x2C0) != 0) {
            GW(0x23C) = GW(0x23C) - 1;
            func_003FFD00();
            if (HW(0x6C) != 0) {
                HW(0x6C) = HW(0x6C) - 1;
            }
            if (GW(0x208) & 0x200) {
                GW(0x220) = 0x65;
            } else {
                GW(0x220) = 0;
            }
        } else {
            GW(0x220) = 0x15F;
            if (HW(0x6C) != 0) {
                HW(0x6C) = HW(0x6C) - 1;
            }
        }
        return;
    case 0xC9:
        GW(0x230) = REC(8) - 1;
        func_003FF930();
        GW(0x220) = GW(0x220) + 1;
        /* fall through */
    case 0xCA:
        if ((func_0026EB70(G + 0x54) & 0x200) == 0) {
            return;
        }
        GW(0x230) = GW(0x230) - 1;
        if (GW(0x230) != 0) {
            func_003FF930();
            func_0026EBA8(G + 0x54, 1);
        } else {
            GW(0x208) = GW(0x208) | 1;
            GW(0x208) = GW(0x208) | 2;
            GW(0x214) = 0xF;
            *(s32 *)arg0 = 0;
            GW(0x220) = 0;
        }
        GW(0x23C) = GW(0x23C) - 1;
        func_003FFD00();
        return;
    case 0x15F:
        func_003FF990();
        func_0026EAE0(G + 0x7C, 0x3C);
        func_0026EA88(G + 0x7C);
        func_00297FE0(2, 0, 0x40, 0x40, 1);
        set_1e0();
        GW(0x220) = GW(0x220) + 1;
        /* fall through */
    case 0x160:
        if (func_0026EB70(G + 0x7C) & 0x200) {
            GW(0x1E0) = *(s32 *)(GW(0x120) + 0x10);
            GW(0x220) = GW(0x220) + 1;
        }
        return;
    case 0x161:
        if (func_0026EB70(G + 0x7C) & 0x200) {
            GW(0x23C) = GW(0x23C) - 1;
            func_003FFD00();
            func_003FF340();
            func_003FF990();
            GW(0x220) = GW(0x220) + 1;
        }
        return;
    case 0x162:
        if (func_0026EB70(G + 0x7C) & 0x200) {
            set_1e0();
            GW(0x220) = GW(0x220) + 1;
        }
        return;
    case 0x163:
        if (func_0026EB70(G + 0x7C) & 0x200) {
            func_0026EA88(G + 0x7C);
            func_0026EB08(G + 0x7C);
            if (GW(0x208) & 0x200) {
                GW(0x220) = 0x65;
            } else {
                GW(0x220) = 0;
            }
        }
        return;
    default:
        return;
    }
}
