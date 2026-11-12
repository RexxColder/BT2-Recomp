#include "common.h"

extern u8 *D_00387930;
void func_0028BB60(u8 *arg0);

void func_001F6CF8(void) {
    u8 *v1 = D_00387930;
    u8 *q;

    if (v1 != NULL) {
        q = *(u8 **)v1;
        if (q != NULL) {
            func_0028BB60(q);
            *(u8 **)D_00387930 = NULL;
            v1 = D_00387930;
        }
        func_0028BB60(v1);
        D_00387930 = NULL;
    }
}
