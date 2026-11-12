#include "common.h"

void func_002B2770(s32 arg0);
void func_002B2790(s32 arg0);
void func_002B27B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002B29D8(s32 arg0, s32 arg1, s32 arg2);
s32 strlen(s32 arg0);

void func_002B2A20(s32 arg0, s32 arg1) {
    u16 buf[4]; /* buf[0] = sp+0, buf[1] = sp+2, buf[2] = sp+4 */
    u16 *p;
    s32 i;

    func_002B2770(arg0);
    func_002B27B0(arg1, strlen(arg1), (s32)&buf[0], (s32)&buf[1], (s32)&buf[2]);
    p = (u16 *)((u8 *)arg0 + 0xA);
    *(u16 *)((u8 *)arg0 + 6) = buf[1];
    *(u16 *)((u8 *)arg0 + 8) = buf[2];
    *(u16 *)((u8 *)arg0 + 4) = buf[0];
    i = 0x1F;
    do {
        *p = buf[0];
        p++;
        i -= 1;
        func_002B29D8((s32)&buf[0], (s32)&buf[1], (s32)&buf[2]);
        *(u16 *)((u8 *)arg0 + 4) = buf[0];
    } while (i >= 0);
    p = (u16 *)((u8 *)arg0 + 0xA + 0x40);
    i = 0x1F;
    do {
        *p = buf[0];
        p++;
        i -= 1;
        func_002B29D8((s32)&buf[0], (s32)&buf[1], (s32)&buf[2]);
        *(u16 *)((u8 *)arg0 + 4) = buf[0];
    } while (i >= 0);
    func_002B2790(buf[0]);
}
