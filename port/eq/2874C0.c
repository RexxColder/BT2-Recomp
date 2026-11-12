#include "m2c_macros.h"

s32 OldPass_GetBit(s32 index);
extern char D_00389850[] __attribute__((section(".data")));

/* The 64 characters of the current format, in value order (as in BT3 src/sys/misc_a_b.c). */
void OldPass_BitsToText(s32 bitCount) {
    static const char charset[] =
        "QRST2VWX1JKLMN5P"
        "0BCD3FGHYZ4bcd9f"
        "wxyz!#$%6pqrst8v"
        "gh7jklmn&@-+*()?";
    s32 n;
    s32 i;
    u32 value;

    for (n = 0; n < bitCount / 6; n++) {
        value = 0;
        for (i = 0; i < 6; i++) {
            value |= OldPass_GetBit(n * 6 + i) << i;
        }
        D_00389850[n] = charset[value];
        D_00389850[n + 1] = 0;
    }
}
