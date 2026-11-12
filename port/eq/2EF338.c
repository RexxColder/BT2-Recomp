#include "common.h"

extern s32 D_0034BBBC __attribute__((section(".data")));
void func_002EE3F0(void);

void EftStage_Recreate(void) {
    D_0034BBBC = 1;
    func_002EE3F0();
}
