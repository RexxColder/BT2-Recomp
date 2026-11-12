#include "common.h"

u8 *BtlObjVis_GetView_207EA0(s32 arg0);
extern u8 *D_00387A40;

void func_0020CA90(s32 arg0) {
    s32 i;
    u8 *view;
    s32 v;

    i = 0;
    if (*(s32 *)(D_00387A40 + 4) > 0) {
        do {
            view = BtlObjVis_GetView_207EA0(i);
            if (view != NULL) {
                v = *(s32 *)(view + 0xAF0);
                if (i == arg0) {
                    v = v | 2;
                } else {
                    v = v & ~2;
                }
                *(s32 *)(view + 0xAF0) = v;
            }
            i += 1;
        } while (i < *(s32 *)(D_00387A40 + 4));
    }
}
