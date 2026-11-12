#include "common.h"

extern s32 D_003553E8;
extern s32 D_003553DC;

#define W(p, off) (*(s32 *)((p) + (off)))

s32 sceSifSetDma(void *arg0, s32 arg1);
void func_0032F558(s32 arg0, s32 arg1);
void func_0032F698(s32 arg0, s32 arg1);

void func_002FCE78(u8 *arg0) {
    u8 *p;
    s32 v;
    s32 c;
    s32 r;

    D_003553E8 = D_003553E8 + 1;
    if (*(s8 *)(arg0 + 1) == 1) {
        p = (u8 *)W(arg0, 0x14);
        if (W(arg0, 8) < W(p, 0x3C)) {
            func_0032F698(W(arg0, 0xC), W(arg0, 0xC) + W(arg0, 0x10) - 1);
            ((void (*)(s32, s32, s32))W(arg0, 0x20))(W(arg0, 0x24), W(arg0, 0xC), W(arg0, 0x10));
            p = (u8 *)W(arg0, 0x14);
            *(u8 *)(arg0 + 1) = 0;
            W(arg0, 8) = W(p, 0x3C);
        }
    }

    v = W(arg0, 0);
    if ((v & 0xFFFF00) == 0x10000) {
        if (D_003553DC == 1) {
            ((void (*)(s32, s32, s32))W(arg0, 0x28))(W(arg0, 0x2C), W(arg0, 0xC), W(arg0, 0x10));
            p = (u8 *)W(arg0, 0x14);
            v = W(arg0, 8) + 1;
            c = W(arg0, 0xC);
            W(arg0, 8) = v;
            W(p, 0x3C) = v;
            func_0032F558(c, c + W(arg0, 0x10) - 1);
            func_0032F698(c, c + W(arg0, 0x10) + 0x3F);
            W(arg0, 0x34) = W(arg0, 0x18);
            W(arg0, 0x30) = W(arg0, 0xC) & 0x0FFFFFFF;
            W(arg0, 0x38) = W(arg0, 0x1C);
            W(arg0, 0x3C) = 0;
            do {
                r = sceSifSetDma(arg0 + 0x30, 1);
                W(arg0, 0x40) = r;
            } while (r == 0);
            *(u8 *)(arg0 + 1) = 1;
        }
    }
}
