#include "common.h"

s32 Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
void Ot_AddRestoreEnv(void);
void func_002790B0(void);
void *memcpy(void *dst, void *src, u32 n);
extern s32 gOtHead;
extern s32 gOtTail;

s32 Ot_Send(void) {
    s32 var_s1;
    s32 var_s0;
    u16 temp_v1;

    if (gOtTail == 0) {
        return 0;
    }
    Ot_AddRestoreEnv();
    var_s0 = gOtHead;
    var_s1 = Dma_BeginDirect();
    if (var_s0 != 0) {
        do {
            memcpy((void *) var_s1, (void *) (var_s0 + 0x10), (u32) (*(u16 *) var_s0) << 4);
            temp_v1 = *(u16 *) var_s0;
            var_s0 = *(s32 *) (var_s0 + 4);
            var_s1 += temp_v1 << 4;
        } while (var_s0 != 0);
    }
    Dma_EndDirect(var_s1);
    func_002790B0();
    return 1;
}
