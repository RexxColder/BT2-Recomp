#include "common.h"

void func_00325830(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00377250[] __attribute__((section(".data")));
extern u8 D_00377268[] __attribute__((section(".data")));
extern u8 D_00377280[] __attribute__((section(".data")));
extern u8 D_00377298[] __attribute__((section(".data")));
extern u8 D_003772B0[] __attribute__((section(".data")));
extern u8 D_003772C8[] __attribute__((section(".data")));
extern u8 D_003772E0[] __attribute__((section(".data")));
extern u8 D_003772F8[] __attribute__((section(".data")));
extern u8 D_00377310[] __attribute__((section(".data")));
extern u8 D_00377328[] __attribute__((section(".data")));
extern u8 D_00377340[] __attribute__((section(".data")));
extern u8 D_00377358[] __attribute__((section(".data")));
extern u8 D_00389050[] __attribute__((section(".data")));

u8 *func_002880D0(u8 *arg0) {
    func_00325830((s32)D_00389050, (s32)D_00377250, *(s32 *)(arg0 + 0x0));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_00377268, *(s32 *)(arg0 + 0x4));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_00377280, *(s32 *)(arg0 + 0x8));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_00377298, *(s32 *)(arg0 + 0xC));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_003772B0, *(s32 *)(arg0 + 0x10));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_003772C8, *(s32 *)(arg0 + 0x14));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_003772E0, *(s32 *)(arg0 + 0x18));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_003772F8, *(s32 *)(arg0 + 0x1C));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_00377310, *(s32 *)(arg0 + 0x20));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_00377328, *(s32 *)(arg0 + 0x28));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_00377340, *(s32 *)(arg0 + 0x24));
    func_00325830((s32)(D_00389050 + strlen((char *)D_00389050)), (s32)D_00377358, *(s32 *)(arg0 + 0x2C));
    return D_00389050;
}
