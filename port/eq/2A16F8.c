#include "common.h"

s32 func_002A1A08(s32 arg0, s32 arg1, s32 arg2);
s32 func_002A18F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 Font_ReadChar(s32 arg0, s32 arg1);
s32 Font_CharSize(s32 arg0);
s32 Font_Pow10(s32 arg0);

s32 func_002A16F8(s32 arg0, s32 arg1) {
    u8 *d;
    s32 mode;
    s32 x;
    s32 y;
    s32 v17;
    s32 result;
    s32 v7;
    s32 ch;
    s32 pow10;
    s32 cnt;
    s32 digit;

    d = (u8 *)arg1;
    result = *(s16 *)(d + 8);
    x = *(s16 *)(d + 8);
    y = *(s16 *)(d + 0xA);
    mode = *(s32 *)d;
    v7 = *(s32 *)(d + 0x1C);
    if ((u32)mode >= 5) {
        return result;
    }

    switch (mode) {
        case 0:
        case 1:
            v17 = *(s32 *)(d + 4);
            x = func_002A1A08(arg1, x, v17);
            do {
                if (mode == 0 && *(s32 *)(d + 0x44) != 0) {
                    ((void (*)(s32, s32, s32, s32, s32, s32))(*(s32 *)(d + 0x44)))(
                        arg1, arg0, (s32)&x, (s32)&y, (s32)&v17, *(s32 *)(d + 0x48));
                }
                ch = Font_ReadChar(mode, v17);
                v17 = v17 + Font_CharSize(mode);
                result = func_002A18F8(arg0, arg1, (s32)&x, (s32)&y, ch, v7, v17);
            } while (result == 0);
            break;

        case 2:
        case 3:
            ch = *(u16 *)(d + 4);
            x = func_002A1A08(arg1, x, 0);
            result = func_002A18F8(arg0, arg1, (s32)&x, (s32)&y, ch, v7, 0);
            break;

        case 4:
            x = func_002A1A08(arg1, x, 0);
            pow10 = Font_Pow10(*(s16 *)(d + 0xE));
            result = *(s16 *)(d + 0xE);
            if (result > 0) {
                cnt = 0;
                do {
                    digit = (*(s32 *)(d + 4) / pow10) % 10 + 48;
                    cnt++;
                    func_002A18F8(arg0, arg1, (s32)&x, (s32)&y, digit & 0xFFFF, v7, 0);
                    result = cnt < *(s16 *)(d + 0xE);
                    pow10 = pow10 / 10;
                } while (cnt < *(s16 *)(d + 0xE));
            }
            break;

        default:
            break;
    }
    return result;
}
