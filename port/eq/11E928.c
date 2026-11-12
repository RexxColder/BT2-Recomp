#include "common.h"

void func_0028BB60(s32 arg0);
extern u8 *D_003876A0;
extern u8 *D_003876FC;

void func_0011E928(void) {
    s32 p;

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 2)) {
        if (D_003876FC != NULL) {
            p = *(s32 *)D_003876FC;
            if (p != 0) {
                func_0028BB60(p);
                *(s32 *)D_003876FC = 0;
            }
            func_0028BB60((s32)D_003876FC);
            D_003876FC = NULL;
        }
    }
}
