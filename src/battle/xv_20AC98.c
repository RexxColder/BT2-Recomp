#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);
s32 func_0023F410(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
extern s32 D_00387930;

/* o = func_00211288(arg0) when D_00387930 is set and arg0 < 2: 1 when func_0023F410(o) has bit 0x10 clear,
 * func_00217488(o) == 0x2D and BtlObjXf_Update(o) == 0x41; else 0 */
s32 func_0020AC98(u32 arg0) {
    s32 o;
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        o = func_00211288(arg0);
        if (!(func_0023F410(o) & 0x10) && (func_00217488(o) == 0x2D) && (BtlObjXf_Update(o) == 0x41)) {
            return 1;
        }
    }
    return 0;
}
