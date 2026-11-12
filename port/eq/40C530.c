#include "common.h"

extern u8 *D_0042BB78 __attribute__((section(".data")));
extern u8 D_0042DFD0[];
extern u8 D_0042DFE8[];
extern u8 D_0042E000[];
extern u8 D_0042E010[];
extern u8 D_0042E020[];
extern u8 D_0042E030[];
extern u8 D_0042E040[];
extern u8 D_0042E058[];
extern u8 D_0042E078[];
extern u8 D_0042E098[];
extern u8 D_0042E0D8[];
extern u8 D_0042E3D8[];
extern u8 D_0042E3F0[];
extern u8 D_0042E400[];
extern u8 D_0042E418[];
extern u8 D_0042E490[];
extern u8 D_0042E4A8[];
extern u8 D_0042E4C0[];
extern u8 D_0042E4D8[];
extern u8 D_0042E4E8[];
extern u8 D_0042E4F8[];
extern u8 D_0042E510[];
extern u8 D_0042E530[];
extern u8 D_0042E548[];

void func_00277E70(u8 *arg0, s32 arg1, s64 arg2);
s32 func_0026EBC0(u8 *layer, u8 *name, u8 *obj);
void func_0026EEF8(u8 *layer, u8 *obj, f32 value);
void func_0026EC48(u8 *layer, u8 *obj, u8 *rect);
void func_0026EEC8(u8 *layer, u8 *obj, s32 x, s32 y);
void func_0026EFC8(u8 *layer, u8 *obj, s32 mode);
f32 func_0026F148(u8 *layer, u8 *obj);
void func_0026EF88(u8 *layer, u8 *obj, f32 value);
void func_0026EB20(u8 *layer, s32 a, s32 b);
void func_0026EA58(u8 *layer);
s32 func_00249BB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
s32 func_00249DB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
s32 func_00325830();

/* menu context (D_0042BB78) fields */
#define MW(o) (*(s32 *)(D_0042BB78 + (o)))
#define MP(o) (*(u8 **)(D_0042BB78 + (o)))
#define MF(o) (*(f32 *)(D_0042BB78 + (o)))

/* per-player view of the slot tables: k = player * 5 + slot */
#define SLOT_COL(flag, k4) (*(s32 *)(D_0042BB78 + ((flag) ? 0x240 : 0x244) + (k4)))
#define SLOT_ROW(flag, k4) (*(s32 *)(D_0042BB78 + ((flag) ? 0x268 : 0x26C) + (k4)))

/* 0x0040C530: draw the memory card / character select menu layers */
void func_0040C530(void) {
    u8 sp[0x5A0] __attribute__((aligned(16)));
    u8 *const obj = sp;                  /* scratch layer object */
    u8 *const nameBuf = sp + 0x10;       /* 32 byte name buffer */
    s32 *const rect = (s32 *)(sp + 0x30);
    u8 *const rects50 = sp + 0x50;       /* 3 rects of 20 bytes */
    u8 *const texts = sp + 0x90;         /* 3 strings of 255 bytes */
    u8 *const obj2 = sp + 0x390;
    u8 *const rects3A0 = sp + 0x3A0;     /* 6 rects of 20 bytes */
    s32 mode[2];
    u8 *const nameBuf2 = sp + 0x430;
    u8 *const obj3 = sp + 0x4B0;
    s32 *const rect4C0 = (s32 *)(sp + 0x4C0);
    s32 *const rect4E0 = (s32 *)(sp + 0x4E0);
    u8 *const rect500 = sp + 0x500;
    u8 *layer;
    s32 i;
    s32 j;
    s32 xoff;
    s32 yoff;

    func_00277E70(MP(0x118), 0, 0x80);
    layer = D_0042BB78 + 0x50;

    /* character animation timers */
    for (i = 0; i < 2; i++) {
        if ((MW(0x240) & (0x40 << i)) != 0) {
            MF(0x37D4 + i * 4) = MF(0x37D4 + i * 4) + 0x1.333332p-4f;
            if (1.0f <= MF(0x37D4 + i * 4)) {
                MF(0x37D4 + i * 4) = 1.0f;
            }
        } else {
            MW(0x37D4 + i * 4) = 0;
        }
        func_0026EBC0(layer, (i == 0) ? D_0042DFD0 : D_0042DFE8, obj);
        func_0026EEF8(layer, obj, MF(0x37D4 + i * 4));
    }

    /* name and form text of the highlighted slot of each player */
    for (i = 0; i < 2; i++) {
        s32 sel;
        s32 k4;
        s32 id;
        s32 flag;
        s32 col;
        s32 row;

        flag = (MW(0x240) & (0x400 << i)) != 0;
        sel = MW(0x2DC + i * 4);
        k4 = sel * 4 + i * 0x14;
        if (flag) {
            id = *(s32 *)(D_0042BB78 + 0x2E0 + k4);
        } else {
            u8 *table = MP(0x360 + i * 4);

            row = SLOT_ROW(0, k4);
            col = SLOT_COL(0, k4);
            id = *(s32 *)(table + (row * 7 + col) * 44);
        }
        col = SLOT_COL(flag, k4);
        row = SLOT_ROW(flag, k4);
        if (col + row * 7 >= 0x4A) {
            id = 0x84;
        }
        func_0026EBC0(layer, (i == 0) ? D_0042E010 : D_0042E000, obj);
        func_00249BB8(layer, obj, 0, 0, MW(0x1C), id, (i == 0) ? 2 : 0);
        func_0026EBC0(layer, (i == 0) ? D_0042E030 : D_0042E020, obj);
        func_00249DB8(layer, obj, 0, 0, MW(0x20), id, (i == 0) ? 2 : 0);
    }

    func_0026EBC0(layer, D_0042E040, obj);
    func_0026EFC8(layer, obj, 0x10);

    /* free character plates (5 per player) */
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            func_00325830(nameBuf, (i != 0) ? D_0042E058 : D_0042E078, j + 1);
            func_0026EBC0(layer, nameBuf, obj);
            if (j == 4) {
                rect[0] = i << 6;
                rect[1] = 0xA0;
                rect[2] = (i << 6) + 0x40;
                rect[3] = 0xF0;
            } else {
                rect[0] = j << 6;
                rect[1] = i * 0x50;
                rect[2] = (j << 6) + 0x40;
                rect[3] = i * 0x50 + 0x50;
            }
            func_0026EC48(layer, obj, (u8 *)rect);
        }
    }

    /* typing text tables */
    __builtin_memcpy(rects50, D_0042E098, 0x3C);
    __builtin_memcpy(texts, D_0042E0D8, 0x2FD);

    for (i = 0; i < 2; i++) {
        s32 stage;
        s32 sel;
        s32 flag;

        layer = D_0042BB78 + 0xC8 + i * 0x28;
        func_0026EB20(layer, 0, 0xA6);
        func_0026EBC0(layer, D_0042E3D8, obj2);
        sel = MW(0x2BC + i * 4);
        func_0026EEC8(layer, obj2, 0, sel * 22);
        func_0026EBC0(layer, texts + sel * 255, obj);
        func_0026EEF8(layer, obj2, func_0026F148(layer, obj));
        func_0026EBC0(layer, D_0042E3F0, obj);
        func_0026EC48(layer, obj, rects50 + MW(0x2BC + i * 4) * 20);
        if (i == 0) {
            func_0026EBC0(layer, D_0042E400, obj);
            func_0026EFC8(layer, obj, 0x10);
        }
        for (stage = 0; stage < 3; stage++) {
            s32 k4;
            s32 col;
            s32 row;
            s32 val;
            u8 *table;

            func_0026EBC0(layer, texts + stage * 255, obj);
            func_0026EC48(layer, obj, rects50 + stage * 20);
            flag = (MW(0x240) & (0x400 << i)) != 0;
            table = MP(0x360 + i * 4);
            k4 = MW(0x2DC + i * 4) * 4 + i * 0x14;
            col = SLOT_COL(flag, k4);
            row = SLOT_ROW(flag, k4);
            val = *(s32 *)(table + (row * 7 + col) * 44);
            if (val == 0x82) {
                if (stage == 2) {
                    func_0026EF88(layer, obj, 0x1.999998p-2f);
                }
            } else {
                if (stage == 2) {
                    func_0026EF88(layer, obj, 1.0f);
                }
            }
        }
    }

    /* colour selection grids */
    __builtin_memcpy(rects3A0, D_0042E418, 0x78);
    for (i = 0; i < 2; i++) {
        s32 cursor;

        layer = D_0042BB78 + 0xC8 + i * 0x28;
        xoff = (MW(0x2D4 + i * 4) < 3) ? 25 : 0;
        yoff = (MW(0x2D4 + i * 4) < 4) ? 14 : 0;
        func_0026EBC0(layer, D_0042E490, obj3);
        cursor = MW(0x2C4 + i * 4);
        func_0026EEC8(layer, obj3, xoff + (cursor % 3) * 50, yoff + (cursor / 3) * 28);
        func_0026EC48(layer, obj3, rects3A0 + MW(0x2C4 + i * 4) * 20);
        for (j = 0; j < 6; j++) {
            func_00325830(nameBuf2, D_0042E4A8, j + 1);
            func_0026EBC0(layer, nameBuf2, obj3);
            func_0026EC48(layer, obj3, rects3A0 + j * 20);
            func_0026EEC8(layer, obj3, xoff, yoff);
            if (j < MW(0x2D4 + i * 4)) {
                func_0026EFC8(layer, obj3, 4);
            } else {
                func_0026EFC8(layer, obj3, 8);
            }
            if (j == MW(0x2C4 + i * 4)) {
                f32 pulse = func_0026F148(layer, obj3);

                func_0026EBC0(layer, D_0042E490, obj3);
                func_0026EEF8(layer, obj3, pulse);
            }
        }
    }

    /* character plate, cursor and L/R button animation */
    for (i = 0; i < 2; i++) {
        s32 kind;
        s32 flag;
        s32 k4;
        s32 col;
        s32 row;
        u8 *entry;

        __builtin_memset(mode, 0, 8);
        layer = D_0042BB78 + 0x78 + i * 0x28;
        func_0026EB20(layer, 0, (i == 0) ? 0x18 : 0x16C);
        if ((MW(0x240) & (0x1000 << i)) != 0) {
            mode[i] = 1;
        }
        if ((MW(0x240) & (0x100 << i)) != 0) {
            mode[i] = 2;
        }
        if (MW(0x37C8) != 1) {
            if ((MW(0x240) & 0x100) == 0) {
                mode[1] = 2;
            }
        }
        if (MW(0x37C8) == 1) {
            kind = (i != 0);
        } else if (MW(0x37C8) == 0) {
            kind = (i == 0) ? 0 : 2;
        } else if (MW(0x37C8) == 2) {
            kind = 2;
        } else {
            kind = 0;
        }
        rect4C0[0] = (kind - ((kind >> 1) << 1)) << 6;
        rect4C0[1] = (kind >> 1) << 5;
        rect4C0[2] = rect4C0[0] + 0x40;
        rect4C0[3] = ((kind >> 1) << 5) + 0x20;
        func_0026EBC0(layer, D_0042E4C0, obj);
        func_0026EC48(layer, obj, (u8 *)rect4C0);

        func_0026EBC0(layer, D_0042E4D8, obj);
        col = *(s32 *)(D_0042BB78 + 0x244 + (MW(0x2DC + i * 4) + i * 5) * 4);
        func_0026EEC8(layer, obj, col * 60, 0);
        if (mode[i] == 1) {
            func_0026EFC8(layer, obj, 2);
        } else if (mode[i] == 2) {
            func_0026EFC8(layer, obj, 8);
        } else {
            func_0026EFC8(layer, obj, 5);
        }

        rect4E0[0] = 0x20;
        rect4E0[1] = 0;
        rect4E0[2] = 0x40;
        rect4E0[3] = 0x20;
        func_0026EBC0(layer, D_0042E4E8, obj);
        func_0026EC48(layer, obj, (u8 *)rect4E0);

        func_0026EBC0(layer, D_0042E4F8, obj);
        col = *(s32 *)(D_0042BB78 + 0x244 + (MW(0x2DC + i * 4) + i * 5) * 4);
        func_0026EEC8(layer, obj, col * 60, 0);
        if (mode[i] == 1) {
            func_0026EFC8(layer, obj, 2);
        } else if (mode[i] == 2) {
            func_0026EFC8(layer, obj, 8);
        } else {
            flag = (MW(0x240) & (0x400 << i)) != 0;
            k4 = MW(0x2DC + i * 4) * 4 + i * 0x14;
            col = SLOT_COL(flag, k4);
            row = SLOT_ROW(flag, k4);
            entry = MP(0x360 + i * 4) + (row * 7 + col) * 44;
            if (*(s32 *)(entry + 4) != 0) {
                func_0026EFC8(layer, obj, 4);
            } else {
                func_0026EFC8(layer, obj, 8);
            }
            func_0026EFC8(layer, obj, 1);
        }

        func_0026EBC0(layer, D_0042E510, obj);
        if (MW(0x37BC) < 2) {
            func_0026EFC8(layer, obj, 8);
        } else if (mode[i] == 1) {
            func_0026EFC8(layer, obj, 2);
        } else if (mode[i] == 2) {
            func_0026EFC8(layer, obj, 8);
        } else {
            func_0026EFC8(layer, obj, 5);
        }
        if (MW(0x37BC) >= 2) {
            __builtin_memcpy(rect500, D_0042E530, 0x14);
            func_0026EBC0(layer, D_0042E548, obj);
            func_0026EC48(layer, obj, rect500);
        }
    }

    for (i = 0; i < 5; i++) {
        func_0026EA58(D_0042BB78 + 0x28 + i * 0x28);
    }
}
