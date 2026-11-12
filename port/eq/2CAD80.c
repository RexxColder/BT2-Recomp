#include "common.h"

void func_002CAD80(void *arg0) {
    if (arg0 != NULL) {
        if (*(s32 *) arg0 != 4) {
            *(s32 *) arg0 = 0;
        } else {
            *(s32 *) arg0 = 3;
        }
        *(s32 *) ((u8 *) arg0 + 0x58) = -1;
    }
}
