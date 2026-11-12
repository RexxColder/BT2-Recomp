#include "common.h"

void func_0018FC58(void **arg0, void **arg1, void *arg2) {
    if (*arg0 != NULL) {
        *(void **) ((u8 *) arg2 + 0x104) = *arg1;
        *(void **) ((u8 *) *arg1 + 0x100) = arg2;
        *arg1 = arg2;
        return;
    }
    *arg0 = arg2;
    *arg1 = arg2;
}
