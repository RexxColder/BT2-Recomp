#include "common.h"

/* Character-select menu UI refresh (memory card / single chara screen). G = D_0042BB74 is the screen state block;
 * G+0x28*(n+1) are the UI layers, driven through script-like calls: SetName(layer, name, buf) then Move/Rect/Anim. */
extern u8 *D_0042BB74 __attribute__((section(".data")));

/* script node names (rodata): the layer helper is given the node name and fills a 16-byte handle */
extern char D_0042D960[], D_0042D978[];                    /* mc_single_chara_l / _r */
extern char D_0042D990[], D_0042D9A0[];                    /* mc_name_text_l / _r */
extern char D_0042D9B0[], D_0042D9C0[];                    /* mc_form_text_l / _r */
extern char D_0042D9D0[];                                  /* mc_name_plate_turn */
extern char D_0042D9E8[];                                  /* 15 words: type text rectangles */
extern char D_0042DA28[];                                  /* 3 x 255 bytes: type text node names */
extern char D_0042DD28[], D_0042DD40[], D_0042DD50[];      /* mc_type_text_onanime / type_text_on / mc_type_plate_turn */
extern char D_0042DD68[];                                  /* 30 words: colour select rectangles */
extern char D_0042DDE0[], D_0042DDF8[];                    /* mc_select_color_on / mc_select_color_off_%d */
extern char D_0042DE10[], D_0042DE28[], D_0042DE38[];      /* mc_chara_plate_text / mc_chara_cursor / mc_r_button */
extern char D_0042DE48[], D_0042DE60[], D_0042DE98[];      /* mc_lr_buttonanime / ..yazirushi_anime / ..yazurushi_down */
extern char D_0042DE80[];                                  /* 5 words: arrow rectangle */

void func_277E70(u8 *arg0, s32 arg1, s32 arg2);
void func_26EBC0(u8 *layer, char *name, void *handle);
void func_26EEF8(u8 *layer, void *handle, f32 value);
void func_26EB20(u8 *layer, s32 arg1, s32 arg2);
void func_26EEC8(u8 *layer, void *handle, s32 x, s32 y);
f32 func_26F148(u8 *layer, void *handle);
void func_26EC48(u8 *layer, void *handle, void *rect);
void func_26EFC8(u8 *layer, void *handle, s32 flags);
void func_26EF88(u8 *layer, void *handle, f32 value);
void func_26EA58(u8 *layer);
void func_249BB8(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_249DB8(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_24B6C8(s32 arg0);
s32 func_325830(char *buf, char *fmt, s32 arg);

/* stack frame, offsets as in the original */
struct Frame {
    u8 handle[16];          /* 0x000 */
    s32 typeRects[15];      /* 0x010 */
    char typeNames[3][255]; /* 0x050 */
    u8 pad_34D[3];
    u8 animHandle[16];      /* 0x350 */
    s32 colorRects[30];     /* 0x360 */
    u8 pad_3D8[8];
    s32 off[2];             /* 0x3E0: x/y offset, later per-side cursor state */
    u8 pad_3E8[8];
    char fmtBuf[128];       /* 0x3F0 */
    u8 plateHandle[16];     /* 0x470 */
    s32 plateRect[4];       /* 0x480 */
    u8 pad_490[16];
    s32 btnRect[4];         /* 0x4A0 */
    u8 pad_4B0[16];
    s32 arrowRect[5];       /* 0x4C0 */
};

#define G_S32(off) (*(s32 *)(D_0042BB74 + (off)))
#define G_U32(off) (*(u32 *)(D_0042BB74 + (off)))
#define G_F32(off) (*(f32 *)(D_0042BB74 + (off)))

void func_00406CA0(void) {
    struct Frame fr;
    u8 *layer;
    f32 step = 0x1.333332p-4f;
    f32 fade;
    s32 i, k, m;
    s32 idx, typeIdx;
    u8 *tbl;
    s32 nameId;
    s32 off;
    u8 *entry;

    func_277E70(*(u8 **)(D_0042BB74 + 0x118), 0, 0x80);
    layer = D_0042BB74 + 0x50;

    /* fade in the two portraits (+0.075 per frame, clamped at 1.0) while their select bit is set */
    for (i = 0; i < 2; i++) {
        f32 *alpha = (f32 *)(D_0042BB74 + 8 + 0x36C0 + i * 4);

        if (G_U32(0x210) & (0x40 << i)) {
            *alpha = *alpha + step;
            if (*alpha >= 1.0f) {
                *alpha = 1.0f;
            }
        } else {
            *(s32 *)alpha = 0;
        }
        func_26EBC0(layer, i == 0 ? D_0042D960 : D_0042D978, fr.handle);
        func_26EEF8(layer, fr.handle, G_F32(0x36C0 + i * 4 + 8));
    }

    /* name and form text of the highlighted entry of each side */
    for (i = 0; i < 2; i++) {
        s32 col = G_S32(0x214 + i * 4);
        s32 row = G_S32(0x21C + i * 4);

        idx = row * 7 + col;
        tbl = *(u8 **)(D_0042BB74 + 0x260 + i * 4);
        nameId = *(s32 *)(tbl + idx * 44);
        if (idx >= 0x4A) {
            nameId = 0x84;
        }
        func_26EBC0(layer, i == 0 ? D_0042D9A0 : D_0042D990, fr.handle);
        func_249BB8(layer, fr.handle, 0, 0, G_S32(0x1C), nameId, i == 0 ? 2 : 0);
        func_26EBC0(layer, i == 0 ? D_0042D9C0 : D_0042D9B0, fr.handle);
        func_249DB8(layer, fr.handle, 0, 0, G_S32(0x20), nameId, i == 0 ? 2 : 0);
    }

    func_26EBC0(layer, D_0042D9D0, fr.handle);
    func_26EFC8(layer, fr.handle, 0x10);

    __builtin_memcpy(fr.typeRects, D_0042D9E8, 0x3C);
    __builtin_memcpy(fr.typeNames, D_0042DA28, 0x2FD);

    /* type text of each side, sliding in */
    off = 0;
    for (i = 0; i < 2; i++) {
        u8 *sub = D_0042BB74 + off + 0xC8;
        s32 *rect;

        func_26EB20(sub, 0, 0xA6);
        func_26EBC0(sub, D_0042DD28, fr.animHandle);
        typeIdx = G_S32(0x22C + i * 4);
        func_26EEC8(sub, fr.animHandle, 0, typeIdx * 22);
        func_26EBC0(sub, fr.typeNames[typeIdx], fr.handle);
        fade = func_26F148(sub, fr.handle);
        func_26EEF8(sub, fr.animHandle, fade);
        func_26EBC0(sub, D_0042DD40, fr.handle);
        func_26EC48(sub, fr.handle, &fr.typeRects[typeIdx * 5]);
        if (i == 0) {
            func_26EBC0(sub, D_0042DD50, fr.handle);
            func_26EFC8(sub, fr.handle, 0x10);
        }

        rect = fr.typeRects;
        for (m = 0; m < 3;) {
            func_26EBC0(sub, fr.typeNames[m], fr.handle);
            func_26EC48(sub, fr.handle, rect);
            rect += 5;
            idx = G_S32(0x21C + i * 4) * 7 + G_S32(0x214 + i * 4);
            tbl = *(u8 **)(D_0042BB74 + 0x260 + i * 4);
            if (*(s32 *)(tbl + idx * 44) == 0x82) {
                if (m == 2) {
                    func_26EF88(sub, fr.handle, 0x1.999998p-2f);
                }
            } else if (m == 2) {
                func_26EF88(sub, fr.handle, 1.0f);
            }
            m++;
        }
        off += 0x28;
    }

    __builtin_memcpy(fr.colorRects, D_0042DD68, 0x78);

    /* colour select grid (3 columns) of each side */
    off = 0;
    for (i = 0; i < 2; i++) {
        u8 *sub;
        s32 cx, cy;

        cx = func_24B6C8(G_S32(0x244 + i * 4)) < 3 ? 25 : 0;
        fr.off[0] = cx;
        cy = func_24B6C8(G_S32(0x244 + i * 4)) < 4 ? 14 : 0;
        fr.off[1] = cy;
        sub = D_0042BB74 + off + 0xC8;
        func_26EBC0(sub, D_0042DDE0, fr.plateHandle);
        func_26EEC8(sub, fr.plateHandle, fr.off[0] + (G_S32(0x234 + i * 4) % 3) * 50,
                    fr.off[1] + (G_S32(0x234 + i * 4) / 3) * 28);
        func_26EC48(sub, fr.plateHandle, &fr.colorRects[G_S32(0x234 + i * 4) * 5]);
        for (m = 0; m < 6;) {
            s32 next = m + 1;

            func_325830(fr.fmtBuf, D_0042DDF8, next);
            func_26EBC0(sub, fr.fmtBuf, fr.plateHandle);
            func_26EC48(sub, fr.plateHandle, &fr.colorRects[m * 5]);
            func_26EEC8(sub, fr.plateHandle, fr.off[0], fr.off[1]);
            if (m < func_24B6C8(G_S32(0x244 + i * 4))) {
                func_26EFC8(sub, fr.plateHandle, 4);
            } else {
                func_26EFC8(sub, fr.plateHandle, 8);
            }
            if (m == G_S32(0x234 + i * 4)) {
                fade = func_26F148(sub, fr.plateHandle);
                func_26EBC0(sub, D_0042DDE0, fr.plateHandle);
                func_26EEF8(sub, fr.plateHandle, fade);
            }
            m = next;
        }
        off += 0x28;
    }

    /* character plates and cursors (side 0 uses the 0x18 layer script, side 1 the 0x168 one) */
    off = 0;
    for (i = 0; i < 2; i++) {
        s32 state;
        s32 plate;
        u8 *sub;
        s32 *flag = &fr.off[i];

        __builtin_memset(fr.off, 0, 8);
        sub = D_0042BB74 + off + 0x78;
        func_26EB20(sub, 0, i == 0 ? 0x18 : 0x168);
        if (G_U32(0x210) & (0x1000 << i)) {
            *flag = 1;
        }
        if (G_U32(0x210) & (0x100 << i)) {
            *flag = 2;
        }
        if (G_S32(0x36C4) != 1) {
            s32 keep = fr.off[1];

            if (!(G_U32(0x210) & 0x100)) {
                keep = 2;
            }
            fr.off[1] = keep;
        }

        state = G_S32(0x36C4);
        if (state == 1) {
            plate = i != 0;
        } else if (state < 2) {
            plate = (state == 0) ? (i == 0 ? 0 : 2) : 0;
        } else if (state == 2) {
            plate = 2;
        } else {
            plate = 0;
        }
        fr.plateRect[0] = (plate & 1) * 64;
        fr.plateRect[1] = (plate >> 1) * 32;
        fr.plateRect[2] = (plate & 1) * 64 + 64;
        fr.plateRect[3] = (plate >> 1) * 32 + 32;
        func_26EBC0(sub, D_0042DE10, fr.handle);
        func_26EC48(sub, fr.handle, fr.plateRect);

        func_26EBC0(sub, D_0042DE28, fr.handle);
        func_26EEC8(sub, fr.handle, G_S32(0x214 + i * 4) * 60, 0);
        if (*flag == 1) {
            func_26EFC8(sub, fr.handle, 2);
        } else if (*flag == 2) {
            func_26EFC8(sub, fr.handle, 8);
        } else {
            func_26EFC8(sub, fr.handle, 5);
        }

        fr.btnRect[0] = 0x20;
        fr.btnRect[1] = 0;
        fr.btnRect[2] = 0x40;
        fr.btnRect[3] = 0x20;
        func_26EBC0(sub, D_0042DE38, fr.handle);
        func_26EC48(sub, fr.handle, fr.btnRect);

        func_26EBC0(sub, D_0042DE48, fr.handle);
        func_26EEC8(sub, fr.handle, G_S32(0x214 + i * 4) * 60, 0);
        if (*flag == 1) {
            func_26EFC8(sub, fr.handle, 2);
        } else if (*flag == 2) {
            func_26EFC8(sub, fr.handle, 8);
        } else {
            idx = G_S32(0x21C + i * 4) * 7 + G_S32(0x214 + i * 4);
            entry = *(u8 **)(D_0042BB74 + 0x260 + i * 4) + idx * 44;
            if (*(s32 *)(entry + 4) != 0) {
                func_26EFC8(sub, fr.handle, 4);
            } else {
                func_26EFC8(sub, fr.handle, 8);
            }
            func_26EFC8(sub, fr.handle, 1);
        }

        func_26EBC0(sub, D_0042DE60, fr.handle);
        if (G_S32(0x36BC) < 2) {
            func_26EFC8(sub, fr.handle, 8);
        } else if (*flag == 1) {
            func_26EFC8(sub, fr.handle, 2);
        } else if (*flag == 2) {
            func_26EFC8(sub, fr.handle, 8);
        } else {
            func_26EFC8(sub, fr.handle, 5);
        }
        if (G_S32(0x36BC) >= 2) {
            __builtin_memcpy(fr.arrowRect, D_0042DE80, 0x14);
            func_26EBC0(sub, D_0042DE98, fr.handle);
            func_26EC48(sub, fr.handle, fr.arrowRect);
        }
        off += 0x28;
    }

    /* run the six layers */
    for (k = 0; k < 6; k++) {
        func_26EA58(D_0042BB74 + k * 0x28 + 0x28);
    }
}
