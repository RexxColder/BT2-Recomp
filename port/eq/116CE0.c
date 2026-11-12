#include "common.h"

extern s32 func_0010B0A0(s32 arg0);
extern s32 Tex_Log2Size(s32 arg0);
extern void func_0010C650(s64 arg0);
extern void func_00112BB8(s32 arg0, s32 arg1);
extern void Dma_AddTexFlush(void);

void func_00116CE0(s32 arg0) {
    s32 base = func_0010B0A0(arg0);
    s64 log2Width = Tex_Log2Size(0x80);
    s64 log2Height = Tex_Log2Size(0x80);

    func_0010C650((log2Width << 26) | (log2Height << 30) | 0x800009C00LL);
    func_00112BB8(base + 0x38A0, 1);
    Dma_AddTexFlush();
}
