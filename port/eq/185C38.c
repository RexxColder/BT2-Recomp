#include "common.h"

void func_00185C38(void **arg0, void **arg1, void *arg2) {
    if (*arg0 != NULL) {
        *(void **) ((u8 *) arg2 + 0xC4) = *arg1;
        *(void **) ((u8 *) *arg1 + 0xC0) = arg2;
        *arg1 = arg2;
        return;
    }
    *arg0 = arg2;
    *arg1 = arg2;
}
