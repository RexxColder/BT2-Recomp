#include "common.h"

s32 func_002DDD70(s32 arg0, s32 arg1);
void func_002E0670(s32 arg0, void *arg1);
s32 func_002E0750(void *arg0);
void func_002E0808(void *arg0, s32 arg1, void *arg2);
extern u8 D_00399DA8[] __attribute__((section(".data")));
extern s32 func_002E05A0 __attribute__((section(".data")));

s32 func_002E05A8(u8 *arg0, s32 arg1, void *arg2) {
    void *s0;
    u8 *v1;

    s0 = arg2;
    if ((arg1 == 8) && (s0 == NULL)) {
        s0 = (void *)&func_002E05A0;
    }
    if (arg0 == NULL) {
        func_002E0670(arg1, s0);
        v1 = D_00399DA8;
    } else {
        if (func_002E0750(arg0) != 0) {
            return func_002DDD70(0, 0xFF030202);
        }
        v1 = arg0 + 0x190;
    }
    *(void **)(v1 + arg1 * 4) = s0;
    func_002E0808(arg0, arg1, s0);
    return 0;
}
