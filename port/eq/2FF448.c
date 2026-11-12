#include "common.h"

void func_002FED70(u8 *arg0, s32 *arg1);
void func_002FC550(s32 arg0);
s32 func_002FC8C8(s32 arg0);
void func_002EFAB8(u8 *arg0, u8 *arg1);
void func_002FF640(void);
extern u8 D_00356E98[] __attribute__((section(".data")));
extern u8 D_0037E708[] __attribute__((section(".data")));
extern u8 D_0037E730[] __attribute__((section(".data")));
extern u8 D_0037E750[] __attribute__((section(".data")));

s32 func_002FF448(void) {
    s32 sp[64];
    u8 *base;
    s32 count;
    s32 i;
    s32 ok = 0;
    s32 r;
    u8 *elem;

    base = *(u8 **)(D_00356E98 + 0);
    if (base == NULL) {
        return 0;
    }
    count = *(s32 *)(D_00356E98 + 4);
    i = 0;
    if (count != 0) {
        do {
            elem = base + ((*(s32 *)(D_00356E98 + 8) << 3) + (*(s32 *)(D_00356E98 + 0xC) * i + i));
            func_002FED70(elem, sp);
            if (*(s8 *)elem != 0) {
                func_002FC550(0x6900);
                r = func_002FC8C8(*(s32 *)(base + i * 8));
                func_002FC550(0x6901);
                if (r < 0) {
                    func_002EFAB8(D_0037E708, (u8 *)sp);
                } else {
                    ok++;
                    func_002EFAB8(D_0037E730, (u8 *)sp);
                }
            }
            i++;
        } while (i < count);
    }
    func_002EFAB8(D_0037E750, (u8 *)(s32)ok);
    func_002FF640();
    return 1;
}
