#include "common.h"

extern s32 D_00383E00;
extern s32 D_00383E04;
extern s32 D_00383E08;
extern u8 *D_00387A40;

void func_00104E90(void) {
    *(s32 *)(D_00387A40 + 0x38030) = D_00383E00;
    *(s32 *)(D_00387A40 + 0x38034) = D_00383E04;
    *(s32 *)(D_00387A40 + 0x38038) = D_00383E08;
}
