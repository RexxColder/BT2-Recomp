#include "m2c_macros.h"

M2C_UNK func_00281F00(void *);                      /* extern */
void *memset(void *, s32, s32);                     /* extern */
extern s32 D_00387B00;

// Clears the 400-byte buffer at arg0, calls func_00281F00(arg0), and stores arg0 in D_00387B00.
void func_00281F50(void *arg0) {
    memset(arg0, 0, 0x190);
    func_00281F00(arg0);
    D_00387B00 = (s32) arg0;
}
