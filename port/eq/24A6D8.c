#include "common.h"

void func_0026F118(u8 *a0, u8 *a1, s32 *a2, s32 *a3);
f32 func_0026F148(u8 *a0, u8 *a1);
void func_002A1340(void);
void func_002A1590(s32 a0);
void func_002A15D0(s32 a0);
void func_002A15F0(s32 a0);
s32 func_002A13E8(void);
void Font_SetColorRGBA(s32 a0, s32 a1, s32 a2, s32 a3);
void Font_SetShadowOffset(s32 a0, s32 a1);
void Font_PrintAt(s32 a0, s32 a1, u8 *a2);

s32 func_0024A6D8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8) {
    s32 out[2];
    s32 s4;
    s32 v0;
    s32 v1;
    f32 f20;
    s32 alpha;
    s32 a2c;

    if (arg5 < 0) {
        return 0; /* v0 is not set on this path: GUESS 0 */
    }
    s4 = arg8;
    v0 = *(s32 *)arg1;
    if (v0 < 0) {
        return v0;
    }
    func_0026F118(arg0, arg1, &out[0], &out[1]);
    f20 = func_0026F148(arg0, arg1);
    func_002A1340();
    func_002A1590(arg6);

    v1 = arg7 & 0xFF;
    alpha = (s32)((f32)v1 * f20);
    Font_SetColorRGBA((u32)arg7 >> 24, ((u32)arg7 >> 16) & 0xFF, ((u32)arg7 >> 8) & 0xFF, alpha & 0xFF);

    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);

    a2c = (((u32)s4 >> 8) & 0xFF) << 16 | (((u32)s4 >> 16) & 0xFF) << 8;
    v1 = (u32)s4 >> 24;
    alpha = (s32)((f32)(s4 & 0xFF) * f20);
    func_002A15F0((s32)(((u32)alpha << 24) | (u32)v1 | (u32)a2c));

    v0 = *(s32 *)(arg4 + arg5 * 4);
    v0 = ((u32)v0 >> 2) << 2;
    Font_PrintAt(out[0] + arg2, out[1] + arg3, arg4 + v0);
    return func_002A13E8();
}
