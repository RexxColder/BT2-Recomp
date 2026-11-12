#include "common.h"

void func_0025E190(u8 *arg0, s32 arg1);
void func_0025E1E8(s32 arg0);
void func_00262428(void);
void func_00262460(s32 arg0);
void func_00262500(s32 arg0);
extern u8 *D_00387A40;
extern u8 D_003B2600[] __attribute__((section(".data")));
extern s32 D_003B26B4 __attribute__((section(".data")));

void func_002A9FE0(void) {
    s32 var_s0;
    s32 var_s1;
    u8 *temp_v1;

    if (D_003B26B4 == 4) {
        var_s0 = 3;
        var_s1 = 0x3F60;
        do {
            temp_v1 = (u8 *)(*(s32 *)(D_00387A40 + 8)) + var_s1;
            var_s1 += 0x1520;
            if (*(s32 *)(temp_v1 + 0xC) != 0) {
                func_0025E190(temp_v1, 0);
                func_00262460(var_s0);
            }
            var_s0 += 1;
        } while (var_s0 < 0xC);
        func_00262500(3);
        *(s32 *)(D_003B2600 + 0x54) = *(s32 *)(D_003B2600 + 0x54) | 0x100;
        return;
    }
    func_0025E1E8(4);
    func_00262428();
}
