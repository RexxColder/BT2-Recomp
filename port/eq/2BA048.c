#include "common.h"

void func_002BA048(void *arg0) {
    void *obj;
    void *vt;
    void (*fn)(void *);

    obj = *(void **)((u8 *)arg0 + 0x17C);
    if (obj != NULL) {
        vt = *(void **)obj;
        fn = *(void (**)(void *))((u8 *)vt + 0xC);
        fn(obj);
    }
}
