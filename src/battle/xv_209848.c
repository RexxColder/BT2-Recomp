#include "common.h"

s32 func_00211288(s32 arg0);
extern s32 D_00387930;

/* when D_00387930 is set and arg0 < 2: byte at +0x1F8 of func_00211288(arg0), else 0 */
s32  func_00209848(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        return (u8)(*(u8 *)((u8 *)func_00211288(arg0) + 0x1F8));
    }
    return (u8)(0U);
}
