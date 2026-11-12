#include "m2c_macros.h"

M2C_UNK Queue_Destroy(s32);                         /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
extern s32 D_00387E04;

void func_002A8648(void) {
    Queue_Destroy(D_00387E04 + 0xA0);
    func_0028BB60(D_00387E04);
    D_00387E04 = 0;
}
