#include "common.h"

extern u8 *D_00421C98 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 D_00421F98[] __attribute__((section(".data")));
extern u8 D_00421FB0[] __attribute__((section(".data")));
extern u8 D_00421FB8[] __attribute__((section(".data")));
extern u8 D_00421FC8[] __attribute__((section(".data")));
extern u8 D_00421FD8[] __attribute__((section(".data")));
extern u8 D_00421FE8[] __attribute__((section(".data")));
extern u8 D_00421FF8[] __attribute__((section(".data")));
extern u8 D_00422010[] __attribute__((section(".data")));
extern u8 D_00422020[] __attribute__((section(".data")));
extern u8 D_00422030[] __attribute__((section(".data")));
extern u8 D_00422330[] __attribute__((section(".data")));
extern u8 D_00422340[] __attribute__((section(".data")));
extern u8 D_00422640[] __attribute__((section(".data")));
extern u8 D_00422940[] __attribute__((section(".data")));
extern u8 D_00422950[] __attribute__((section(".data")));
extern u8 D_00422960[] __attribute__((section(".data")));

void func_0026EBC0(void *a0, void *a1, void *a2);
void func_0026ED60(void *a0, void *a1, void *a2, void *a3, s32 t0, f32 f12, f32 f13);
void func_00249FB8(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_002495A8(void *a0, void *a1, s32 a2, s32 a3);
void func_00249778(void *a0, void *a1, s32 a2, s32 a3);
s32 func_001018B8(void);
s32 func_002498D8(void *a0, void *a1, s32 a2);
void func_0026EC48(void *a0, void *a1, void *a2);
void func_0026EFC8(void *a0, void *a1, s32 a2);
f32 func_0026F148(void *a0, void *a1);
void func_0026EEC8(void *a0, void *a1, s32 a2, s32 a3);
void func_0026EEF8(void *a0, void *a1, s32 a2, s32 a3, f32 f12);
void func_0026EF88(void *a0, void *a1, s32 a2, s32 a3, f32 f12);
void func_0026EC78(void *a0, void *a1, s32 a2, s32 a3, void *t0, s32 t1, s32 t2, s32 t3);
s32 func_0026EB70(void *a0);
void func_003C08D8(s32 a0);
void func_003C0890(s32 a0);
void func_0024A598(void *a0, void *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_0026EA58(void *a0);
void func_0024C060(void);
s32 BattleSetup_Finish(void);

#define G (D_00421C98)
#define GW(off) (*(s32 *)(G + (off)))
#define W(off) (*(s32 *)(sp + (off)))
#define R(off) ((void *)(sp + (off)))

s32 func_003C0FD0(void) {
    u8 sp[0x6D0];
    u8 *s2;
    s32 i;

    /* background */
    __builtin_memcpy(sp + 0x10, D_00421F98, 20);
    s2 = G + 0x18;
    func_0026EBC0(s2, D_00421FB0, sp);
    func_0026ED60(s2, sp, sp + 0x10, G + 0x15C, 0, -0.25f, 0.0f);
    /* text window + guide */
    s2 = G + 0x68;
    func_0026EBC0(s2, D_00421FB8, sp);
    func_00249FB8(s2, sp, 0, 0, GW(0xC), GW(0x12C), 1);
    if (GW(0x134) == 0) {
        func_0026EBC0(s2, D_00421FC8, sp);
        func_002495A8(s2, sp, (s32)(G + 0x140), 1);
        func_0026EBC0(s2, D_00421FD8, sp);
        func_00249778(s2, sp, (s32)(G + 0x144), 3);
    } else {
        func_0026EBC0(s2, D_00421FE8, sp);
        func_002495A8(s2, sp, (s32)(G + 0x148), 1);
        func_0026EBC0(s2, D_00421FF8, sp);
        func_00249778(s2, sp, (s32)(G + 0x14C), 3);
    }
    if (func_001018B8() == 5) {
        func_0026EBC0(s2, D_00421FD8, sp);
        func_002498D8(s2, sp, 3);
        func_0026EBC0(s2, D_00421FF8, sp);
        func_002498D8(s2, sp, 3);
    }
    /* button icon 2 */
    W(0x34) = 0x20;
    W(0x38) = 0x100;
    W(0x3C) = 0x40;
    W(0x30) = 0;
    func_0026EBC0(s2, D_00422010, sp);
    func_0026EC48(s2, sp, sp + 0x30);
    if ((GW(0x124) & 0xC) != 0 || GW(0x9A4) > 0) {
        func_0026EFC8(s2, sp, 8);
    } else {
        func_0026EFC8(s2, sp, 4);
    }
    /* button icon 3 */
    W(0x34) = 0x40;
    W(0x38) = 0x100;
    W(0x3C) = 0x60;
    W(0x30) = 0;
    func_0026EBC0(s2, D_00422020, sp);
    func_0026EC48(s2, sp, sp + 0x30);
    if (*(s16 *)(D_00387F2C + 0x2802) > 0) {
        if ((GW(0x124) & 0xC) != 0 || GW(0x9A4) > 0) {
            func_0026EFC8(s2, sp, 8);
        } else {
            func_0026EFC8(s2, sp, 4);
        }
    } else {
        func_0026EFC8(s2, sp, 8);
    }
    /* text off/on strip: names table of 3 x 255 bytes */
    __builtin_memcpy(sp + 0x50, D_00422030, 0x2FD);
    {
        f32 f20;
        W(0x350 + 0x00) = 0;
        W(0x350 + 0x04) = GW(0x128) << 5;
        W(0x350 + 0x08) = 0x200;
        W(0x350 + 0x0C) = (GW(0x128) << 5) + 0x20;
        W(0x350 + 0x10) = 0;
        func_0026EBC0(s2, sp + 0x50 + 255 * GW(0x128), sp);
        f20 = func_0026F148(s2, sp);
        func_0026EBC0(s2, D_00422330, sp);
        func_0026EEC8(s2, sp, 0, 55 * GW(0x128));
        func_0026EC48(s2, sp, sp + 0x350);
        func_0026EEF8(s2, sp, 0, 0, f20);
        if (GW(0x128) != 2) {
            func_0026EF88(s2, sp, 0, 0, 1.0f);
        } else if ((*(s32 *)(D_00387F2C + 0xE08) & 1) != 0) {
            func_0026EF88(s2, sp, 0, 0, 0x1.333332p-1f);
        }
    }
    __builtin_memcpy(sp + 0x70, D_00422340, 0x2FD);
    for (i = 0; i < 3;) {
        W(0x5C) = (i << 5) + 0x20;
        W(0x54) = i << 5;
        W(0x50) = 0;
        W(0x58) = 0x200;
        func_0026EBC0(s2, sp + 0x70 + 255 * i, sp);
        func_0026EC48(s2, sp, sp + 0x50);
        if (i == GW(0x128)) {
            func_0026EFC8(s2, sp, 8);
        } else {
            func_0026EFC8(s2, sp, 4);
        }
        if (i == 2) {
            if ((*(s32 *)(D_00387F2C + 0xE08) & 1) != 0) {
                func_0026EF88(s2, sp, 0, 0, 0x1.333332p-1f);
            }
        }
        i++;
    }
    /* icons */
    __builtin_memcpy(sp + 0x3B0, D_00422640, 0x2FD);
    for (i = 0; i < 3;) {
        W(0x39C) = (i << 6) + 0x40;
        W(0x394) = i << 6;
        W(0x398) = 0x40;
        W(0x390) = 0;
        func_0026EBC0(s2, sp + 0x3B0 + 255 * i, sp);
        if (i == GW(0x128)) {
            __builtin_memcpy(sp + 0x6B0, D_00422940, 12);
            __builtin_memcpy(sp + 0x6C0, D_00422950, 12);
            func_0026EC78(s2, sp, (s32)(G + 0x154), (s32)(G + 0x158), sp + 0x390,
                          W(0x6B0 + 4 * i), 1, W(0x6C0 + 4 * i));
        } else {
            func_0026EC48(s2, sp, sp + 0x390);
        }
        if (i == 2) {
            if ((*(s32 *)(D_00387F2C + 0xE08) & 1) != 0) {
                func_0026EF88(s2, sp, 0, 0, 0x1.333332p-1f);
            }
        }
        i++;
    }
    if ((func_0026EB70(G + 0x68) & 8) != 0) {
        GW(0x160) = (GW(0x160) == 0);
    }
    if (GW(0x160) != 0) {
        func_003C08D8(1);
        func_003C08D8(0);
    } else {
        func_003C08D8(GW(0x134));
        if (GW(0x134) != 0) {
            func_003C0890(0);
        } else {
            func_003C0890(1);
        }
    }
    func_0026EBC0(s2, D_00422960, sp);
    func_0024A598(s2, sp, 0, 0, GW(0x14), 4, 0);
    for (i = 0; i < 3; i++) {
        func_0026EA58(G + 0x28 * i + 0x18);
    }
    func_0024C060();
    return BattleSetup_Finish();
}
