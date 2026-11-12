#include "common.h"

u8 *Queue_Peek(u8 *arg0);
void Queue_Pop(u8 *arg0);
extern u8 *D_00387E04;

s32 func_002A8678(void) {
    u8 *s0 = Queue_Peek(D_00387E04 + 0xA0);

    if (s0 == NULL) {
        return 0;
    }
    if (((s32 (*)(u8 *))*(u8 **)(s0 + 0x20))(s0) == 1) {
        void (*fn)(u8 *) = (void (*)(u8 *))*(u8 **)(s0 + 0x24);

        if (fn != NULL) {
            fn(s0);
        }
        Queue_Pop(D_00387E04 + 0xA0);
    }
    return 1;
}
