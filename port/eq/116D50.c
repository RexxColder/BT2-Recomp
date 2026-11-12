#include "common.h"

s32 func_0010B080(void);
s32 func_0010B0A0(s32 arg0);
void func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00113CB8(u8 *arg0, s32 arg1, s32 arg2, s16 arg3);
void func_00113B00(u8 *arg0, s32 arg1, s32 arg2);
f32 func_0020C1E8(u32 arg0);
f32 func_0020C288(u32 arg0);
void func_00113860(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(u8 *arg0, s32 arg1);
f32 sinf(f32 farg0);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00383F34;
extern f32 D_00383F38;
extern f32 D_00383F3C;
extern f32 D_00383F40;
extern f32 D_00383F44;

/* 0x00116D50: build the 0x60-byte sprite records of panel k in the draw buffer, then submit them.
 * base = HUD block (+0x1130 + k * 0x110: per-panel state), view = player view, a3/t0 = screen position. */
void func_00116D50(s32 base, s32 k, s32 view, s32 posX, s32 posY) {
    s32 obj = func_0010B080();
    u8 *buf = (u8 *)(u32)func_0010B0A0(k) + 0x3720;
    f32 *angle = (f32 *)((u8 *)(u32)base + k * 0x110 + 0x1130 + 0x60);
    u8 *rec240 = buf + 0x240;
    f32 f21;
    f32 f20;
    f32 a;
    f32 glow;
    s32 shift;

    func_00114508((s32)(u32)buf, 2, 0, 12);
    func_00113CB8(buf, 0, *(s32 *)((u8 *)(u32)obj + 0x10), 0);
    func_00113B00(buf, posX, posY);
    __builtin_memcpy(buf + 0xC0, buf, 0x60);
    *(s16 *)(buf + 0xD4) = 1;
    *(s32 *)(buf + 0xC0) = *(s32 *)(buf + 0xC0) | 0x80;
    __builtin_memcpy(buf + 0x180, buf, 0x60);
    f21 = func_0020C1E8((u32)view);
    func_00113860(buf + 0x24C, 0, 0, 0x10, 0x40, 2);
    func_00113D80(rec240, 0);
    func_00113B00(rec240, *(s16 *)(buf + 4) + 0x64, *(s16 *)(buf + 6) + 0x22);
    __builtin_memcpy(buf + 0x2A0, rec240, 0x60);
    *(s32 *)(buf + 0x2A0) = *(s32 *)(buf + 0x2A0) | 0x20000;
    f20 = func_0020C288((u32)view);
    if (f20 == 0.0f) {
        *angle = 0.0f;
    } else {
        *angle = *angle + f20 * 20.0f / 180.0f * D_00383F34;
    }
    a = *angle;
    if (a < D_00383F38) {
        a = a + D_00383F3C;
        *angle = a;
    } else if (D_00383F40 < a) {
        a = a - D_00383F44;
        *angle = a;
    }
    glow = (__builtin_fabsf(sinf(a)) * f20 * 0.5f + f20 * 0.5f) * 128.0f;
    buf[0x2B7] = 0x32;
    buf[0x2B6] = 0xEC;
    buf[0x2B8] = 0xE;
    buf[0x2B9] = (u8)(u32)glow;
    __builtin_memcpy(buf + 0x3C0, rec240, 0x60);
    *(s32 *)(buf + 0x3C0) = *(s32 *)(buf + 0x3C0) | 0x10000;
    buf[0x3D9] = 0x64;
    __builtin_memcpy(buf + 0x360, buf + 0x3C0, 0x60);
    func_00113860(buf + 0x36C, 0x20, 0, 0x30, 0x40, 2);
    *(s32 *)(buf + 0x360) = *(s32 *)(buf + 0x360) | 0x80;
    shift = (s32)(64.0f - f21 * 64.0f);
    *(u16 *)(buf + 0x366) = (u16)(*(u16 *)(buf + 0x366) - 0x40 + shift);
    *(u16 *)(buf + 0x36A) = (u16)(*(u16 *)(buf + 0x36A) - 0x40 + shift);
    BtlRec_CallFlagged((s32)(u32)buf, 1, 12);
}
