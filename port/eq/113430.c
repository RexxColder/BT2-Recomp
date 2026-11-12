#include "common.h"
#include "sys/dma.h"

s32 func_00112A78(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
u64 *func_00112EC0(u64 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);

void func_00113430(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    u64 *dma;

    if (arg0 != NULL) {
        if (func_00112A78(arg0, arg1, arg3, arg4) == 0) {
            return;
        }
    }
    dma = Dma_BeginDirect();
    dma = func_00112EC0(dma, arg0, arg1, arg2 & 0xFF, arg5, arg6, arg3, arg4);
    Dma_EndDirect(dma);
}
