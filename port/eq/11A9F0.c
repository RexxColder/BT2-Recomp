#include "common.h"

s32 ColBox_Overlaps(s32 arg0, s32 arg1, s32 arg2);
s32 func_0011A620(s32 arg0, s32 arg1);
void func_0011A738(void);
extern s32 *D_00387A40;

void func_0011A9F0(void) {
    s32 off;
    s32 i;
    s32 j;
    s32 s5;
    s32 s3;
    s32 s0;

    i = 0;
    off = 0;
    func_0011A738();
    if (D_00387A40[1] > 0) {
        do {
            s3 = D_00387A40[0] + off;
            if (*(s8 *)(s3 + 0xD7D) >= 0) {
                j = 0;
                if (D_00387A40[1] > 0) {
                    s5 = 0;
                    do {
                        if (j != i) {
                            s0 = D_00387A40[0] + s5;
                            if ((ColBox_Overlaps(s3 + 0x1520, s0 + 0xF60, (s32)D_00387A40) != 0) &&
                                (func_0011A620(s3, s0 + 0xEF0) != 0)) {
                                *(s32 *)(s3 + 0xE50) = *(s32 *)(s3 + 0xE50) | (1 << (j + 0x18));
                                *(s32 *)(s0 + 0xE50) = *(s32 *)(s0 + 0xE50) | (1 << (i + 0x1C));
                            }
                        }
                        j += 1;
                        s5 += 0x18580;
                    } while (j < D_00387A40[1]);
                }
            }
            off += 0x18580;
            i += 1;
        } while (i < D_00387A40[1]);
    }
}
