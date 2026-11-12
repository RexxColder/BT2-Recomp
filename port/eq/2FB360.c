#include "common.h"

void func_002F9300(s32 arg0);
extern u8 D_0037DD78[] __attribute__((section(".data")));

s64 EftSprAnim_FreeSlot(u8 *arg0) {
    u64 var_s0;
    s32 (*fn)(s32, s32, s32, s32);
    u32 r1;
    u32 r2;

    if (arg0 == NULL) {
        func_002F9300((s32)D_0037DD78);
        return -1;
    }
    var_s0 = 0x7FFFFFFF;
    fn = (s32 (*)(s32, s32, s32, s32))(*(s32 *)(*(u8 **)arg0 + 0x60));
    if (fn != NULL) {
        r1 = (u32)fn(*(s32 *)(arg0 + 4), 0x12D, 0, 0);
        var_s0 = (u64)r1 << 32;
        fn = (s32 (*)(s32, s32, s32, s32))(*(s32 *)(*(u8 **)arg0 + 0x60));
        r2 = (u32)fn(*(s32 *)(arg0 + 4), 0x12E, 0, 0);
        var_s0 = var_s0 + (u64)r2;
    }
    return (s64)var_s0;
}
