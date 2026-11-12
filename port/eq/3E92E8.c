#include "common.h"

extern u8 *D_004279D4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

extern s32 func_0026EB60();
extern s32 func_0026EB78();
extern s32 func_002979F0();
extern s32 func_00297FE0();
extern s32 func_00101408();
extern s32 func_003E83D8();
extern void func_00243A80();
extern void func_0024B4C8();
extern s32 func_0029C7E0();
extern void func_0029C550();
extern void func_0029C820();

/* Settings menu object (G) and the save-data block (S = D_00387F2C). */
#define G (D_004279D4)   /* el asm: lui s1, %hi(D_004279D4); addiu s0, s1, %lo(..): el m2c lo habia leido como D_00427AD4 */
#define S (D_00387F2C)
#define GW(off) (*(s32 *)(G + (off)))
#define SW(off) (*(s32 *)(S + (off)))

#define FLAGS GW(0xC8)      /* active sub-menu bit mask */
#define PAGE GW(0xCC)       /* selected main-menu row 0..5 */
#define VALUE GW(0xD0)      /* value being edited */
#define MODE GW(0xD4)       /* last confirmed sub-menu */
#define JP_VOICE GW(0xE8)
#define SAVED_SPEAKER GW(0x184)
#define SAVED_VOL1 GW(0x188)
#define SAVED_VOL2 GW(0x18C)
#define SAVED_VOL3 GW(0x190)
#define IN_MENU GW(0x2EC)
#define IN_MENU_TIMER GW(0x2F4)

#define PAD_HELD (*(s32 *)(D_003B0B00 + 0x144))
#define PAD_PRESS (*(s32 *)(D_003B0B00 + 0x134))
#define PAD_UP 0x10
#define PAD_RIGHT 0x20
#define PAD_DOWN 0x40
#define PAD_LEFT 0x80
#define PAD_CROSS 0x4000
#define PAD_CIRCLE 0x1000

#define REDRAW(arg) func_00297FE0(0, (arg), 0x40, 0x40, 1)
#define DIRTY() (*(s32 *)(D_003876A4 + 0x18) |= 1)

/* 0x003E92E8: sound-settings menu update; arg0 receives 0 when the menu is closed. */
s32 func_003E92E8(s32 *arg0) {
    if (func_0026EB60(G + 0x10) == 0) {
        return 0;
    }

    if (FLAGS & 0x20) {
        if (IN_MENU != 0) {
            return IN_MENU;
        }
        if (IN_MENU_TIMER > 0) {
            SAVED_SPEAKER = 0;
            SAVED_VOL1 = 9;
            SAVED_VOL2 = 9;
            SAVED_VOL3 = 9;
            JP_VOICE |= 1;
            *(s64 *)(S + 0x10A4) = *(s64 *)(G + 0x184);
            *(s64 *)(S + 0x10AC) = *(s64 *)(G + 0x18C);
            SW(0x1008) = JP_VOICE;
            DIRTY();
            func_0024B4C8();
        }
        FLAGS ^= 0x20;
        return FLAGS;
    }

    if (FLAGS & 0x1) {
        /* speaker: two values (0..1) */
        if (PAD_HELD & PAD_RIGHT) {
            VALUE++;
            if (VALUE >= 2) {
                VALUE = 0;
            }
        } else if (PAD_HELD & PAD_LEFT) {
            VALUE--;
            if (VALUE < 0) {
                VALUE = 1;
            }
        } else if (PAD_PRESS & PAD_CROSS) {
            SAVED_SPEAKER = VALUE;
            DIRTY();
            FLAGS &= ~1;
            REDRAW(1);
            func_0026EB78(G + 0x10, "fr_speaker_out");
            MODE = 0;
            SW(0x10A4) = VALUE;
            return func_002979F0(SW(0x10A4) ^ 1);
        } else if (PAD_PRESS & PAD_CIRCLE) {
            FLAGS &= ~1;
            REDRAW(2);
            func_0026EB78(G + 0x10, "fr_speaker_out");
            MODE = 0;
            SW(0x10A4) = SAVED_SPEAKER;
            VALUE = SAVED_SPEAKER;
            return func_002979F0(SW(0x10A4) ^ 1);
        } else {
            return -2;
        }
        REDRAW(0);
        SW(0x10A4) = VALUE;
        return func_002979F0(SW(0x10A4) ^ 1);
    }

    if (FLAGS & 0x2) {
        /* volume 1: 0..9 */
        if (PAD_HELD & PAD_RIGHT) {
            VALUE++;
            if (VALUE >= 10) {
                VALUE = 9;
            } else {
                REDRAW(0);
            }
        } else if (PAD_HELD & PAD_LEFT) {
            VALUE--;
            if (VALUE < 0) {
                VALUE = 0;
            } else {
                REDRAW(0);
            }
        } else if (PAD_PRESS & PAD_CROSS) {
            SAVED_VOL1 = VALUE;
            DIRTY();
            FLAGS &= ~2;
            REDRAW(1);
            func_0026EB78(G + 0x10, "fr_volume_out");
            MODE = 1;
            return 1;
        } else if (PAD_PRESS & PAD_CIRCLE) {
            FLAGS &= ~2;
            REDRAW(2);
            func_0026EB78(G + 0x10, "fr_volume_out");
            MODE = 1;
            SW(0x10A8) = SAVED_VOL1;
            return func_00101408();
        } else {
            return -3;
        }
        SW(0x10A8) = VALUE;
        return func_00101408();
    }

    if (FLAGS & 0x4) {
        /* volume 2: 0..9 */
        if (PAD_HELD & PAD_RIGHT) {
            VALUE++;
            if (VALUE >= 10) {
                VALUE = 9;
                return 9;
            }
        } else if (PAD_HELD & PAD_LEFT) {
            VALUE--;
            if (VALUE < 0) {
                VALUE = 0;
                return 0;
            }
        } else if (PAD_PRESS & PAD_CROSS) {
            SAVED_VOL2 = VALUE;
            DIRTY();
            FLAGS &= ~4;
            REDRAW(1);
            func_0026EB78(G + 0x10, "fr_volume_out");
            MODE = 2;
            return 2;
        } else if (PAD_PRESS & PAD_CIRCLE) {
            FLAGS &= ~4;
            REDRAW(2);
            func_0026EB78(G + 0x10, "fr_volume_out");
            MODE = 2;
            SW(0x10AC) = SAVED_VOL2;
            return SAVED_VOL2;
        } else {
            return -5;
        }
        REDRAW(0);
        SW(0x10AC) = VALUE;
        return func_003E83D8();
    }

    if (FLAGS & 0x8) {
        /* volume 3: 0..9 (stale v0 return values are lui constants) */
        if (PAD_HELD & PAD_RIGHT) {
            VALUE++;
            if (VALUE >= 10) {
                VALUE = 9;
                SW(0x10B0) = VALUE;
                return 0x380000;
            }
        } else if (PAD_HELD & PAD_LEFT) {
            VALUE--;
            if (VALUE < 0) {
                VALUE = 0;
                SW(0x10B0) = VALUE;
                return 0x380000;
            }
        } else if (PAD_PRESS & PAD_CROSS) {
            SAVED_VOL3 = VALUE;
            DIRTY();
            FLAGS &= ~8;
            REDRAW(1);
            func_0026EB78(G + 0x10, "fr_volume_out");
            MODE = 3;
            return 3;
        } else if (PAD_PRESS & PAD_CIRCLE) {
            FLAGS &= ~8;
            SW(0x10B0) = SAVED_VOL3;
            REDRAW(2);
            func_0026EB78(G + 0x10, "fr_volume_out");
            MODE = 3;
            return 3;
        } else {
            return -9;
        }
        REDRAW(0);
        SW(0x10B0) = VALUE;
        return 0x380000;
    }

    if (FLAGS & 0x10) {
        /* Japanese voice on/off */
        if (PAD_HELD & (PAD_RIGHT | PAD_LEFT)) {
            VALUE = (VALUE == 0);
            if (VALUE != 0) {
                SW(0x1008) &= ~1;
            } else {
                SW(0x1008) |= 1;
            }
            return REDRAW(0);
        }
        if (PAD_PRESS & PAD_CROSS) {
            if (VALUE != 0) {
                JP_VOICE &= ~1;
            } else {
                JP_VOICE |= 1;
            }
            DIRTY();
            FLAGS &= ~0x10;
            REDRAW(1);
            func_0026EB78(G + 0x10, "fr_jpvoice_out");
        } else if (PAD_PRESS & PAD_CIRCLE) {
            FLAGS &= ~0x10;
            REDRAW(2);
            SW(0x1008) = JP_VOICE;
            func_0026EB78(G + 0x10, "fr_jpvoice_out");
        } else {
            return -17;
        }
        MODE = 4;
        return 4;
    }

    /* main list */
    if (PAD_HELD & PAD_UP) {
        PAGE--;
        if (PAGE < 0) {
            PAGE = 5;
        }
    } else if (PAD_HELD & PAD_DOWN) {
        PAGE++;
        if (PAGE >= 6) {
            PAGE = 0;
        }
    } else if (PAD_PRESS & PAD_CROSS) {
        switch ((u32)PAGE) {
        case 0:
            FLAGS |= 1;
            VALUE = SAVED_SPEAKER;
            func_0026EB78(G + 0x10, "fr_speaker_in");
            break;
        case 1:
            FLAGS |= 2;
            VALUE = SAVED_VOL1;
            func_0026EB78(G + 0x10, "fr_volume_in");
            break;
        case 2:
            FLAGS |= 4;
            VALUE = SAVED_VOL2;
            func_0026EB78(G + 0x10, "fr_volume_in");
            func_003E83D8();
            break;
        case 3:
            FLAGS |= 8;
            VALUE = SAVED_VOL3;
            func_0026EB78(G + 0x10, "fr_volume_in");
            break;
        case 4:
            FLAGS |= 0x10;
            VALUE = (JP_VOICE ^ 1) & 1;
            func_0026EB78(G + 0x10, "fr_jpvoice_in");
            break;
        case 5:
            FLAGS |= 0x20;
            IN_MENU = 1;
            func_0029C7E0(0);
            func_0029C550(0);
            func_0029C820(1);
            IN_MENU_TIMER = 0;
            break;
        default:
            break;
        }
        return REDRAW(1);
    } else if (PAD_PRESS & PAD_CIRCLE) {
        /* leave: restore the saved settings block */
        __builtin_memcpy(S + 0x1008, G + 0xE8, 0xAC);
        *arg0 = 0;
        func_00243A80(0, 0, 0);
        return REDRAW(2);
    } else {
        return 0x380000;
    }
    REDRAW(0);
    return func_003E83D8();
}
