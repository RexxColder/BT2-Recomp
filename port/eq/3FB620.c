#include "common.h"

f32 func_26F148(s32 arg0, s32 *arg1);
void func_26F118(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);
s32 func_2A0EA8(u8 *arg0);
void func_2A13E8(void);
void func_2A1340(void);
void func_2A1590(u8 *arg0);
void func_2A15D0(s32 arg0);
void func_2A15F0(s32 arg0);
void Font_PrintAt(s32 arg0, s32 arg1, u8 *arg2);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_SetShadowOffset(s32 arg0, s32 arg1);

/* 0x003FB620: text draw, like 0x003EA470 (f20 = func_26F148(arg0, arg1), sp[0]/sp[1] from func_26F118). Returns if
 * arg5 < 0 or *arg1 < 0. val = tbl[arg5]; r = func_2A0EA8(tbl + (val & ~3)): r == 1 -> sp[1] += 6, r == 2 -> sp[1] -= 6.
 * func_2A1340(), func_2A1590(arg6), Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(f20*128) & 0xFF), func_2A15D0(2),
 * Font_SetShadowOffset(1, 2), func_2A15F0(((s32)(f20*64) << 24) | 0x202020), Font_PrintAt(sp[0] + arg2, sp[1] + arg3,
 * tbl + (val & ~3)), func_2A13E8(). */
void func_003FB620(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, u8 *arg6) {
    s32 sp[2];
    f32 f20;
    s32 val;
    s32 r;

    if (arg5 < 0) {
        return;
    }
    if (*arg1 < 0) {
        return;
    }
    func_26F118(arg0, arg1, &sp[0], &sp[1]);
    f20 = func_26F148(arg0, arg1);

    val = *(s32 *)(arg4 + arg5 * 4);
    r = func_2A0EA8(arg4 + (s32)((u32)val & ~3u));
    if (r == 1) {
        sp[1] = sp[1] + 6;
    } else if (r == 2) {
        sp[1] = sp[1] - 6;
    }
    func_2A1340();
    func_2A1590(arg6);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(f20 * 128.0f) & 0xFF);
    func_2A15D0(2);
    Font_SetShadowOffset(1, 2);
    func_2A15F0(((s32)(f20 * 64.0f) << 24) | 0x202020);
    val = *(s32 *)(arg4 + arg5 * 4);
    Font_PrintAt(sp[0] + arg2, sp[1] + arg3, arg4 + (s32)((u32)val & ~3u));
    func_2A13E8();
}
