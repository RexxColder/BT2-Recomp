#include "common.h"

s32 func_002FC550(s32 arg0);
s32 func_002FD318(void *arg0, void *arg1);
void func_002FDF58(u8 *arg0, void *arg1);
s32 func_002FF130(u8 *arg0, void *arg1);
s32 sceCdSync(s32 arg0);
s32 sceCdRead(s32 lsn, s32 sectors, void *buf, void *mode);
s32 strcasecmp(const char *a, const char *b);
void *memset(void *dst, s32 val, u32 n);
extern u8 D_00356E18[] __attribute__((section(".data")));
extern u8 D_0037E4C0[] __attribute__((section(".rodata")));

s32 func_002FE2C0(u8 *arg0, u8 *arg1) {
    u8 sp[0x80];
    u8 *buf;
    s32 v0;
    s32 lsn;

    buf = &sp[0x40];
    buf[0] = arg0[0];
    buf[1] = arg0[1];
    buf[2] = arg0[2];
    buf[3] = arg0[3];
    buf[4] = 0;
    if (strcasecmp((const char *)buf, (const char *)D_0037E4C0) != 0) {
        memset(D_00356E18, 0, 0x80);
        func_002FDF58(arg0, D_00356E18);
        func_002FC550(0x9000);
        while (sceCdSync(1) == 1) {
        }
        func_002FC550(0x9001);
        func_002FC550(0x9100);
        v0 = func_002FD318(sp, D_00356E18);
        if (v0 == 0) {
            func_002FC550(0x9101);
            return 0;
        }
        func_002FC550(0x9102);
        sp[0x30] = 0;
        sp[0x31] = 1;
        sp[0x32] = 0;
        sp[0x33] = 0;
        func_002FC550(0x9200);
        lsn = (s32)((u32)sp[0] | ((u32)sp[1] << 8) | ((u32)sp[2] << 16) | ((u32)sp[3] << 24));
        v0 = sceCdRead(lsn, 2, arg1, &sp[0x30]);
        if (v0 == 0) {
            func_002FC550(0x9201);
            return 0;
        }
        func_002FC550(0x9202);
        func_002FC550(0x9300);
        while (sceCdSync(1) == 1) {
        }
        func_002FC550(0x9301);
        return 1;
    }
    return func_002FF130(arg0 + 4, arg1);
}
