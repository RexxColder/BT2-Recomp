#include "common.h"

void func_0024C380(s32 arg0);
s32 func_0024C148(void);
void func_0024B010(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_0024B210(s32 arg0);
extern u8 *D_003879A0;
extern u8 *D_003876A4;

void func_0024F558(void) {
    u8 *d;
    s32 base0;
    s32 a2;
    s32 flags;
    s32 sel;
    s32 idx;
    s32 k;
    s32 w;

    d = D_003879A0;
    func_0024C380(0);

    a2 = func_0024C148() + 0x22 * (*(s32 *)(d + 0x1C8) + 7 * *(s32 *)(d + 0x1CC)) + 0x1408;
    func_0024B010(*(s32 *)(d + 0x334C), *(s32 *)(d + 0x3350), a2, (s32)(d + 0x326C), 0x14);

    *(s32 *)(d + 0x323C) = func_0024B210((s32)(d + 0x326C));

    flags = *(s32 *)(D_003876A4 + 0x48C);
    sel = (flags & 2) ? 0x1E4 : 0x1E0;
    idx = (*(s32 *)(d + 0x1CC) * 7 + *(s32 *)(d + 0x1C8)) * 0x2C;
    k = *(s32 *)(idx + *(s32 *)(d + sel + 8));
    base0 = k * 0x10 + *(s32 *)(d + 0x3354);
    *(s32 *)(d + 0x3234) = *(s32 *)base0;

    w = base0;
    *(s32 *)(d + 0x3238) = *(s32 *)(w + 4);
}
