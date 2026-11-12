#include "common.h"

s32 func_002EC9F8(s32 arg0, s32 arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6);
s32 func_002ED0F0(s32 arg0);
s32 strncpy(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_00366ED8[] __attribute__((section(".data")));

/* fname-range lookup (adxf family): arg0 selects a table entry, arg1 is a count; the out pointers receive the
 * name (strncpy to arg2), the first/last values and the sums. Returns the first call's result. */
s32 adxf_GetFnameRangeEx(s32 arg0, s32 arg1, u8 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6) {
    s32 fp;
    s32 s2;
    s32 v0;
    s32 i;
    s32 v1;
    u8 *s3;
    s32 *s5;
    u16 *p;

    fp = func_002EC9F8(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    if (fp < 0) {
        *arg3 = 0;
        *arg4 = -1;
        *arg5 = -1;
        *arg6 = -1;
        return fp;
    }

    s3 = D_00366ED8[arg0];
    if (*(s8 *)(s3 + 0xF) == 1) {
        s2 = func_002ED0F0(*(s32 *)(s3 + 0x118));
        s5 = (s32 *)(s3 + 0x11C);
        for (i = arg1; i > 0; i--) {
            s2 += func_002ED0F0(*s5);
            s5++;
        }
        s5 = (s32 *)(s3 + 0x11C);
        v0 = func_002ED0F0(s5[arg1]);
        *arg5 = v0;
        *arg6 = s5[arg1];
    } else {
        s2 = *(u16 *)(s3 + 0x118);
        p = (u16 *)(s3 + 0x11A);
        for (i = arg1; i > 0; i--) {
            s2 += *p;
            p++;
        }
        v1 = *(u16 *)(s3 + 0x11A + 2 * arg1);
        *arg5 = v1;
        *arg6 = (s32)((u32)v1 << 11);
    }

    strncpy((s32)arg2, (s32)(s3 + 0x10), 0x100);
    *arg3 = *(s32 *)(s3 + 0x110);
    *arg4 = *(s32 *)(s3 + 0x114) + s2;
    return fp;
}
