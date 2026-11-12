#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern u8 *D_00387A10;
extern u8 *D_00387F2C;
extern u8 D_00376410[];
extern u8 D_00376420[];
extern u8 D_00376430[];
extern u8 D_00376440[];
extern u8 D_00376450[];
extern u8 D_00376468[];
extern u8 D_00376480[];
extern u8 D_00387A18[];
extern u8 D_00387A20[];

extern void func_0026E9E8(u8 *p);
extern void func_0026EA58(u8 *p);
extern void func_0026EBC0(u8 *obj, u8 *name, u8 *out);
extern void func_0026EFC8(u8 *obj, u8 *h, s32 flags);
extern void func_0026EC48(u8 *obj, u8 *h, s32 *rect);
extern void func_0026EC18(u8 *obj, u8 *h, s32 idx);
extern void func_00325830(u8 *buf, u8 *fmt, s32 n);
extern void func_0024A8A0(u8 *out, s32 val, s32 digits);
extern void func_0024AB10(u8 *obj, u8 *handles, s32 a2, s32 a3, s32 t0, u8 *digits);
extern void func_00249A98(u8 *obj, u8 *h, s32 a2, s32 a3, s32 t0, s32 t1);
extern void func_0024A598(u8 *obj, u8 *h, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
extern void BattleSetup_Finish(void);

/* Memory-card map screen draw: hides/shows the button, card, slot and map-point sprites from the state in
   D_00387A10 and then updates the three text/sprite groups. */
void func_00259740(void) {
    u8 sp[0xB0];
    s32 *rect = (s32 *)(sp + 0x10);
    u8 *obj;
    u8 *D;
    u8 *F;
    s32 i;
    s32 found;
    s32 v;
    s32 e;

    D = D_00387A10;
    for (i = 0; i < 3; i++) {
        func_0026E9E8(D_00387A10 + i * 0x28 + 4);
    }
    D = D_00387A10;
    obj = D + 4;
    func_0026EBC0(obj, D_00376410, sp);
    if (W(D_00387A10, 0xAC) & 2) {
        rect[0] = 0; rect[1] = 0x40; rect[2] = 0x100; rect[3] = 0x60;
        func_0026EFC8(obj, sp, 4);
        func_0026EC48(obj, sp, rect);
    } else {
        func_0026EFC8(obj, sp, 8);
    }
    func_0026EBC0(obj, D_00376420, sp);
    D = D_00387A10;
    if (W(D, 0xAC) & 1) {
        v = W(D, 0xB8) << 5;
        rect[0] = 0; rect[1] = v; rect[2] = 0x100; rect[3] = v + 0x20;
        func_0026EFC8(obj, sp, 4);
        func_0026EC48(obj, sp, rect);
    } else {
        func_0026EFC8(obj, sp, 8);
    }
    for (i = 0; i < 7; i++) {
        func_00325830(sp + 0x30, D_00376430, 6 - i);
        func_0026EBC0(obj, sp + 0x30, sp + 0x50 + i * 8);
    }
    F = D_00387F2C;
    found = 0;
    func_0024A8A0(sp + 0x90, W(F, 0x283C), 7);
    func_0024AB10(obj, sp + 0x50, 0, 0, W(D_00387A10, 0xC8), sp + 0x90);
    for (i = 0; i < 4; i++) {
        if (*(s16 *)(D_00387F2C + 0x24DE + i * 4) != 0) {
            rect[0] = i << 6;
            rect[1] = 0;
            rect[2] = (i << 6) + 0x40;
            rect[3] = 0x40;
            found = 1;
        }
    }
    func_0026EBC0(obj, D_00387A18, sp);
    if (found) {
        func_0026EFC8(obj, sp, 4);
        func_0026EC48(obj, sp, rect);
    } else {
        func_0026EFC8(obj, sp, 8);
    }
    for (i = 0; i < 7; i++) {
        s32 row;
        s32 col;

        func_00325830(sp + 0xA0, D_00376440, 6 - i);
        func_0026EBC0(obj, sp + 0xA0, sp);
        row = (i < 0 ? i + 3 : i) >> 2;
        col = i - row * 4;
        if (*(s16 *)(D_00387F2C + 0x24C0 + i * 4 + 2) != 0) {
            rect[0] = col * 32;
            rect[1] = row * 32;
            rect[2] = col * 32 + 32;
            rect[3] = row * 32 + 32;
            func_0026EFC8(obj, sp, 4);
            func_0026EC48(obj, sp, rect);
        } else {
            func_0026EFC8(obj, sp, 8);
        }
    }

    D = D_00387A10;
    obj = D + 0x2C;
    v = W(D, 0xB4) << 6;
    rect[0] = 0; rect[1] = v; rect[2] = 0x80; rect[3] = v + 0x40;
    func_0026EBC0(obj, D_00376450, sp);
    func_0026EC48(obj, sp, rect);
    D = D_00387A10;
    v = W(D, 0xB0);
    {
        s32 d16 = (v < 0 ? v + 15 : v) >> 4;
        s32 rem = v - (d16 << 4);
        s32 r2 = (rem + ((u32)rem >> 31)) >> 1;
        s32 m2 = v - (((v + ((u32)v >> 31)) >> 1) << 1);

        rect[1] = r2 << 5;
        rect[3] = (r2 << 5) + 0x20;
        rect[0] = m2 << 8;
        rect[2] = (m2 << 8) + 0x100;
    }
    func_0026EBC0(obj, D_00376468, sp);
    func_0026EC48(obj, sp, rect);
    v = W(D_00387A10, 0xB0);
    func_0026EC18(obj, sp, (v < 0 ? v + 15 : v) >> 4);

    D = D_00387A10;
    obj = D + 0x54;
    if (W(D, 0xBC) == 1000) {
        rect[1] = 0x20; rect[0] = 0x40; rect[2] = 0x80; rect[3] = 0x40;
        func_0026EBC0(obj, D_00387A20, sp);
        func_0026EC48(obj, sp, rect);
        func_0026EBC0(obj, D_00376480, sp);
        func_00249A98(obj, sp, 0, 0, W(D_00387A10, 0xC0), 0);
    } else {
        s32 bc;

        func_0026EBC0(obj, D_00387A20, sp);
        bc = W(D, 0xBC);
        e = W(*(u8 **)(D + 0xC4) + bc * 0x30, 8);
        if (e == 4) {
            s32 a = bc - 0x164;
            s32 b = a < 0 ? bc - 0x161 : a;

            rect[1] = (b >> 2) << 5;
            rect[3] = rect[1] + 0x20;
            bc = W(D, 0xBC);
            a = bc - 0x164;
            b = a < 0 ? bc - 0x161 : a;
            rect[0] = (a - ((b >> 2) << 2)) << 6;
            rect[2] = rect[0] + 0x40;
            func_0026EC18(obj, sp, 1);
        } else {
            s32 b = e < 0 ? e + 3 : e;

            rect[1] = (b >> 2) << 5;
            rect[3] = rect[1] + 0x20;
            bc = W(D, 0xBC);
            e = W(*(u8 **)(D + 0xC4) + bc * 0x30, 8);
            b = e < 0 ? e + 3 : e;
            rect[0] = (e - ((b >> 2) << 2)) << 6;
            rect[2] = rect[0] + 0x40;
            func_0026EC18(obj, sp, 0);
        }
        func_0026EC48(obj, sp, rect);
        func_0026EBC0(obj, D_00376480, sp);
        func_0024A598(obj, sp, 0, 0, W(D_00387A10, 0), W(D_00387A10, 0xBC) + 1, 0);
    }
    for (i = 0; i < 3; i++) {
        func_0026EA58(D_00387A10 + i * 0x28 + 4);
    }
    BattleSetup_Finish();
}
