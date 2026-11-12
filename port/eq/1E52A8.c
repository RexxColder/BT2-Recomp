#include "common.h"

void func_001E5328(s32 arg0, s32 arg1, s32 arg2);

/* 0x001E52A8(obj): NULL gives 0.0f. Otherwise n = byte obj+0x21CC; arr[i] = the float at obj+0x70 + i*0x1B0 for
 * i < n; func_001E5328(arr, 0, n - 1); the result is arr[n - 1] (0.0f when n == 0, where the original reads below
 * the array). */
f32 func_001E52A8(u8 *arg0) {
    f32 arr[32];
    s32 n;
    s32 i;

    if (arg0 == 0) {
        return 0.0f;
    }
    n = arg0[0x21CC];
    for (i = 0; i < n; i++) {
        arr[i] = *(f32 *)(arg0 + 0x70 + i * 0x1B0);
    }
    func_001E5328((s32)arr, 0, n - 1);
    if (n == 0) {
        return 0.0f;
    }
    return arr[n - 1];
}
