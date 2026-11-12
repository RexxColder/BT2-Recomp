#include "common.h"

extern u8 D_0037BA88[];
extern s32 memcmp();

s32 func_002E8A98(u8 *arg0) {
    return memcmp(arg0, D_0037BA88, 4) == 0;
}
