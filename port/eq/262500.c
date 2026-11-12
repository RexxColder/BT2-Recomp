#include "common.h"

void func_0028BB60(s32 arg0);
extern u8 D_00388A48[] __attribute__((section(".data")));

void func_00262500(s32 arg0) {
    s32 i;
    u8 *entry;

    i = arg0;
    if (i < 0x10) {
        entry = D_00388A48 + i * 0x30;
        do {
            if (*(s32 *)entry & 1) {
                if (*(s32 *)(entry + 0x24) != 0) {
                    func_0028BB60(*(s32 *)(entry + 0x24));
                    *(s32 *)(entry + 0x24) = 0;
                }
                if (*(s32 *)(entry + 0x28) != 0) {
                    func_0028BB60(*(s32 *)(entry + 0x28));
                    *(s32 *)(entry + 0x28) = 0;
                }
                if (*(s32 *)(entry + 0x2C) != 0) {
                    func_0028BB60(*(s32 *)(entry + 0x2C));
                    *(s32 *)(entry + 0x2C) = 0;
                }
                *(s32 *)entry = *(s32 *)entry & ~1;
            }
            i += 1;
            entry += 0x30;
        } while (i < 0x10);
    }
}
