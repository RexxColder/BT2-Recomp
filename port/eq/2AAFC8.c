#include "common.h"

s32 Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
void TexFile_UploadOne(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002AA360(s32 arg0, s32 arg1, s32 arg2);
s32 func_002AA450(s32 arg0);
s32 func_002AA660(s32 arg0, s32 arg1, f32 farg0);
s32 func_002AAA20(s32 arg0);
extern s32 D_00387E08;
extern s32 D_003B2654 __attribute__((section(".data")));
extern u8 D_003B2A0C __attribute__((section(".data")));

void func_002AAFC8(void) {
    s32 var_a0;
    s32 var_s2;
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s3;

    var_s0 = &D_003B2A0C;
    var_s3 = &D_003B2A0C + 0x1C;
    if (var_s3[0x208] != 0) {
        TexFile_UploadOne(D_00387E08, 0, 0x2A00, 0x2B00);
        var_s1 = &D_003B2A0C + 0x44;
        var_s0 = var_s1;
        var_s2 = 0x17;
        var_a0 = func_002AA450(func_002AA360(Dma_BeginDirect(), 0x100, 0x100));
        do {
            if (*var_s1 != 0) {
                var_a0 = func_002AA660(var_a0, (s32)var_s0, 1.0f);
            }
            var_s1 += 0x14;
            var_s2 -= 1;
            var_s0 += 0x14;
        } while (var_s2 >= 0);
        if (D_003B2654 < 0) {
            var_a0 = func_002AA660(var_a0, (s32)(var_s3 + 0x14), 1.0f);
        }
        var_a0 = func_002AA660(var_a0, (s32)var_s3, 1.0f);
        Dma_EndDirect(func_002AAA20(var_a0));
    }
}
