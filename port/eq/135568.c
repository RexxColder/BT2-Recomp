#include "common.h"

void Tex_Upload(s32 arg0, s32 arg1, s32 arg2);
extern u8 *gEftBurst;

void EftBurst_SetTexture(s32 arg0, s32 arg1, s32 arg2) {
    if (*(s32 *)(gEftBurst + 0x230) != arg0) {
        *(s32 *)(gEftBurst + 0x230) = arg0;
        if (arg0 != 0) {
            Tex_Upload(arg0, arg1, arg2);
        }
    }
}
