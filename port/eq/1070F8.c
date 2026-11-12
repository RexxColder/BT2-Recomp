#include "common.h"

extern u8 *gObjOutline;

s32 BtlMenu_IsSkillList(u8 *arg0);
s32 BtlMenu_IsControls(u8 *arg0);
s32 func_00106958(u8 *arg0);
s32 func_00106998(s32 arg0);
s32 func_00106B58(u8 *arg0);
s32 func_00106C98(u8 *arg0);
s32 func_00106D68(u8 *arg0);
u8 *func_00106DC0(u8 *out, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
u8 *func_00106F48(u8 *dl, s32 x0, s32 x1, s32 y0, s32 y1, s32 flag);
s32 func_001081F0(u8 *dl, s32 a1, s32 a2, s32 a3, s32 t0);
s32 func_00108440(u8 *dl, s32 a1, s32 a2, s32 a3, s32 t0);
u8 *func_00108E98(u8 *dl, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
s32 func_00109698(u8 *dl, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1);
void func_002A1340(void);
void Font_PushCursor(void);
void Font_SetHome(s32 x, s32 y);
void func_002A14B0(f32 f);
s32 Font_GetGlyphHeight(void);
void func_002A1508(s32 arg0, s32 arg1);
void func_002A1590(s32 arg0);
void func_002A15D0(s32 arg0);
void func_002A1678(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_SetShadowOffset(s32 arg0, s32 arg1);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_Print(s32 str);
void Font_NewLine(void);
void Font_PopCursor(void);
void func_002A13E8(void);

#define FP(p, o) (*(f32 *)((p) + (o)))
#define PP(p, o) (*(u8 **)((p) + (o)))

/* Draw one menu node (a1) into display list a0; recurses into the selected child. */
u8 *func_001070F8(u8 *dl, u8 *menu) {
    s32 bank;
    s32 padX;
    s32 padY;
    s32 isSkill;
    s32 kind;
    s32 w, h, x0, y0;
    s32 xa, xb, ya, yb, hSub;
    s32 i, half, tx, ty, id;
    u8 *tbl;
    u8 *child;
    s32 hdl;

    bank = *(s32 *)(gObjOutline + 8);
    padX = *(s16 *)(menu + 0xC);
    padY = *(s16 *)(menu + 0xE);
    isSkill = BtlMenu_IsSkillList(menu);
    kind = *(s32 *)(menu + 0x1C);
    if (kind < 0) {
        return dl;
    }
    if (kind < 4) {
        w = (s32)FP(menu, 0x20);
        h = (s32)FP(menu, 0x24);
        if (w < 4 && h >= 4) {
            w = 4;
        }
        if (h < 4 && w >= 4) {
            h = 4;
        }
        x0 = (0x200 - w) >> 1;
        y0 = (0x1C0 - h) >> 1;
        return func_00106F48(dl, x0, x0 + w, y0, y0 + h, isSkill != 0);
    }
    if (kind != 4) {
        return dl;
    }

    if (!func_00106D68(menu)) {
        w = func_00106B58(menu);
        h = func_00106C98(menu);
        x0 = (0x200 - func_00106B58(menu)) >> 1;
        y0 = (0x1C0 - func_00106C98(menu)) >> 1;
        dl = func_00106F48(dl, x0, x0 + w, y0, y0 + h, isSkill != 0);
        if (isSkill) {
            ya = y0 + padY;
            yb = y0 - padY + h;
            xa = x0 + padX;
            xb = x0 - padX + w;
            tbl = gObjOutline;
            dl = func_00108E98(dl, xa, xb, ya, yb, *(s32 *)(tbl + bank * 4 + 0x10), bank);
            dl = (u8 *)func_00109698(dl, xa, xb, ya, yb, *(s32 *)(gObjOutline + bank * 4 + 0x10));
        } else if (BtlMenu_IsControls(menu)) {
            dl = (u8 *)func_001081F0(dl, x0 + padX, x0 - padX + w, y0 + padY, y0 - padY + h);
        } else if (func_00106958(menu)) {
            dl = (u8 *)func_00108440(dl, x0 + padX, x0 - padX + w, y0 + padY, y0 - padY + h);
        } else {
            ty = y0 + padY;
            func_002A1340();
            Font_PushCursor();
            i = 0;
            Font_SetHome(0x100, ty + 0x2A);
            func_002A14B0(FP(menu, 0x8));
            func_002A1508(0, 0x1C - Font_GetGlyphHeight());
            func_002A1590(1);
            func_002A15D0(2);
            func_002A1678(0, 0, 0, 0x40);
            Font_SetShadowOffset(1, 2);
            if (*(s32 *)(menu + 4) > 0) {
                half = (w + ((u32)w >> 31)) >> 1;
                do {
                    if (*(s32 *)(menu + 0x18) == i) {
                        Font_SetColorRGBA(0xFF, 0xFF, 0xFF, 0x80);
                    } else {
                        Font_SetColorRGBA(0x40, 0x40, 0x40, 0x80);
                    }
                    id = *(s16 *)(PP(menu, 0) + i * 32 + bank * 2);
                    i++;
                    if (id < 0) {
                        dl = func_00106DC0(dl, x0 + half, ty + 0xE, 0x100, 0x20, 0x13, ~id, 1);
                    } else {
                        Font_Print(func_00106998(id));
                        Font_NewLine();
                    }
                } while (i < *(s32 *)(menu + 4));
            }
            Font_PopCursor();
            func_002A13E8();
        }
    }

    if (*(s32 *)(menu + 4) > 0) {
        i = 0;
        do {
            child = PP(PP(menu, 0) + i * 32, 8);
            if (child != NULL && *(s32 *)(menu + 0x14) == i) {
                dl = func_001070F8(dl, child);
            }
            i++;
        } while (i < *(s32 *)(menu + 4));
    }
    return dl;
}
