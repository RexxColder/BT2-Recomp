#include "common.h"

void func_001AA9D8(u8 *arg0);
void FlashShapePool_Term(u8 *arg0);

void func_001AB4E0(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x38);

    func_001AA9D8(arg0);
    FlashShapePool_Term(obj + 0xE8);
}
