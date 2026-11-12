#include "common.h"

s32 Gsc_CallAction(s32 arg0);
s32 Gsc_GetInt(void);
s32 func_0029F6F8(s32 arg0);

s32 func_002A7C08(s32 arg0, s32 *arg1) {
    s32 ret = 0;

    if (arg0 == 0) {
        *arg1 = Gsc_CallAction(Gsc_GetInt());
    } else if (arg0 == 2) {
        ret = func_0029F6F8(*arg1) == 0;
    }
    return ret;
}
