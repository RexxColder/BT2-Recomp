#include "common.h"

void func_002EA050(void *arg0);
extern u8 D_0037CB30[] __attribute__((section(".data")));

s32 func_002F5930(u8 *arg0) {
    void *obj;
    s32 (*fn)(void *, s32);
    s32 v;

    if (arg0 == NULL) {
        func_002EA050(D_0037CB30);
        return -1;
    }
    obj = *(void **)(arg0 + 0x14);
    if (obj != NULL) {
        fn = *(s32 (**)(void *, s32))((u8 *)(*(void **)obj) + 0x24);
        v = fn(obj, 1);
        return (v < 0 ? v + 0x7FF : v) >> 11;
    }
    return 0;
}
