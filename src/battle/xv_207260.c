#include "common.h"

/* number of right shifts (by 1) needed to reduce arg0 to zero, minus one; 0 for arg0 < 4 */
s32 func_00207260(s32 arg0) {
    s32 n = 0;
    s32 a = arg0 >> 1;
    if (a != 0) {
        do {
            a = a >> 1;
            n++;
        } while (a != 0);
    }
    return n;
}
