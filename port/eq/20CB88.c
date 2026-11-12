#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);

void func_0020CB88(s32 arg0, s32 arg1) {
    s32 view = BtlObjVis_GetView_207EA0(arg0);
    u8 flag = (u8)arg1;

    if (view != 0) {
        if (flag == 0) {
            *(s32 *)(view + 0xAF0) = *(s32 *)(view + 0xAF0) & ~0x100;
        } else {
            *(s32 *)(view + 0xAF0) = *(s32 *)(view + 0xAF0) | 0x100;
        }
    }
}
