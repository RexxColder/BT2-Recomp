#include "common.h"

void func_00259E78(void);
void func_00259EE0(void);
void func_00259F40(void);
extern u8 *D_003876A0;
extern u8 D_003B2A0C[] __attribute__((section(".data")));

void func_002A9750(void) {
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        if (D_003B2A0C[4] != 0) {
            if (D_003B2A0C[0] != 0) {
                func_00259E78();
                D_003B2A0C[0] = 0;
            }
            if (D_003B2A0C[2] != 0) {
                func_00259F40();
                D_003B2A0C[2] = 0;
            }
            if (D_003B2A0C[1] != 0) {
                func_00259EE0();
                D_003B2A0C[1] = 0;
            }
        }
    }
}
