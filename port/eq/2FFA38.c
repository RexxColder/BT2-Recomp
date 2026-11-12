#include "common.h"

s32 func_002FF9A0();
void func_003007A0(s32 arg0);
void func_003007B8(s32 arg0);
void func_003007F8(s32 arg0);
extern u8 D_0037E828[] __attribute__((section(".data")));
extern u8 D_0037E858[] __attribute__((section(".data")));

s32 func_002FFA38(s32 arg0) {
    s32 sp[4];
    s32 v;
    s32 s0;
    s32 i;

    if (arg0 == 0) {
        func_003007F8((s32)D_0037E828);
        return 0;
    }
    func_003007A0((s32)sp);
    v = func_002FF9A0();
    if (v == 0) {
        func_003007F8((s32)D_0037E858);
        func_003007B8((s32)sp);
        return v;
    }
    *(u8 *)(v + 1) = 0;
    *(s32 *)(v + 8) = arg0;
    s0 = ((s32 (*)(s32, s32))(*(s32 *)(*(s32 *)arg0 + 0x24)))(arg0, 0);
    s0 = s0 + ((s32 (*)(s32, s32))(*(s32 *)(*(s32 *)arg0 + 0x24)))(arg0, 1);
    *(s32 *)(v + 0x18) = s0;
    *(s32 *)(v + 0x14) = (s32)(s0 * 8) / 10;
    for (i = 0; i < 16; i++) {
        *(s32 *)(v + 0x230 - (i * 0x20)) = 0;
    }
    *(u8 *)(v + 0) = 1;
    func_003007B8((s32)sp);
    return v;
}
