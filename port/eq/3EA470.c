#include "common.h"

extern u8 *D_00428F48 __attribute__((section(".data")));

f32 func_26F148(s32 arg0, s32 *arg1);
void func_26F118(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);
s32 func_2A0EA8(u8 *arg0);
void func_2A13E8(void);
void func_2A1340(s32 arg0);
void func_2A1590(s32 arg0);
void func_2A15D0(s32 arg0);
void func_2A15F0(s32 arg0);
void Font_PrintAt(s32 arg0, s32 arg1, u8 *arg2);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_SetShadowOffset(s32 arg0, s32 arg1);

/* 0x003EA470: text draw. Returns at once if arg2 < 0 or *arg1 < 0. G = D_00428F48, tbl = G->0x8. sp[0], sp[1] get
 * func_26F118(arg0, arg1, &sp[0], &sp[1]); f20 = func_26F148(arg0, arg1). val = tbl[arg2] (word at tbl + arg2*4);
 * r = func_2A0EA8(tbl + (val & ~3)); sp[1] = r == 1 ? sp[1] + 6 : sp[1] - 5; func_2A1340(2); func_2A1590(arg3);
 * Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(f20 * 128.0f) & 0xFF); func_2A15D0(2); Font_SetShadowOffset(1, 2);
 * func_2A15F0(((s32)(f20 * 64.0f) << 24) | 0x202020); Font_PrintAt(sp[0], sp[1], tbl + (val & ~3)); func_2A13E8(). */
void func_003EA470(s32 arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 sp[2];
    f32 f20;
    u8 *tbl;
    s32 val;
    s32 r;

    if (arg2 < 0) {
        return;
    }
    if (*arg1 < 0) {
        return;
    }
    tbl = *(u8 **)(D_00428F48 + 0x8);

    func_26F118(arg0, arg1, &sp[0], &sp[1]);
    f20 = func_26F148(arg0, arg1);

    val = *(s32 *)(tbl + arg2 * 4);
    r = func_2A0EA8(tbl + (s32)((u32)val & ~3u));
    if (r == 1) {
        sp[1] = sp[1] + 6;
    } else {
        sp[1] = sp[1] - 5;
    }
    func_2A1340(2);
    func_2A1590(arg3);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(f20 * 128.0f) & 0xFF);
    func_2A15D0(2);
    Font_SetShadowOffset(1, 2);
    func_2A15F0(((s32)(f20 * 64.0f) << 24) | 0x202020);
    val = *(s32 *)(tbl + arg2 * 4);
    Font_PrintAt(sp[0], sp[1], tbl + (s32)((u32)val & ~3u));
    func_2A13E8();
}
