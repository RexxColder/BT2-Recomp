#include "common.h"

extern u8 *D_00347600 __attribute__((section(".data")));

s32 *BtlChar_FindByObjId(void) {
    s32 count;
    s32 i;
    u8 *rec;

    count = *(s32 *)(D_00347600 + 0xC);
    for (i = 0; i < count; i++) {
        rec = D_00347600 + 0x10 + i * 0x100;
        if (*(s32 *)rec == 1) {
            return (s32 *)rec;
        }
    }
    return NULL;
}
