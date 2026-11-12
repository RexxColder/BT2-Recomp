#include "common.h"

void func_002F0178(s32 arg0);

// Calls func_002F0178 with arg0, then sets the byte at +1 of arg0 to 1.
void func_002F0450(s32 arg0) {
    func_002F0178(arg0);
    *(s8 *)(arg0 + 1) = 1;
}
