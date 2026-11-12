#include "common.h"

extern u8 *D_0042BB80 __attribute__((section(".data")));
extern u8 D_0042ED70[] __attribute__((section(".data")));
extern u8 D_0042EE18[] __attribute__((section(".data")));

void *memcpy(void *dst, const void *src, u32 n);
void func_26EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_26F118(u8 *a0, u8 *a1, s32 *a2, s32 *a3);
f32 func_26F148(s32 a0, s32 *a1);
void TexFile_UploadOne(s32 a0, s32 a1, s32 a2, s32 a3);
void func_003B4C20(s32 a0, s32 a1);
void *Dma_BeginDirect(void);
void *func_00418A68(void *a0, u8 *a1, s32 a2, s32 a3, f32 f12, s32 t0);
void Dma_EndDirect(void *a0);

/* 0x00418CC8: copies the 0xA8-byte block at D_0042ED70 into a 0x100-byte frame (the asm's aligned and unaligned
 * copy loops both do this), runs func_26EBC0 / func_26F118 / func_26F148 on G+0x30 with the frame record at +0xB0,
 * uploads the texture of G->0xCC, then two func_00418A68 passes (t0 = 0, then 1, the second chained on the first's
 * return) between Dma_BeginDirect and Dma_EndDirect. */
void func_00418CC8(void) {
    u8 frame[0x100];
    u8 *s0;
    f32 f20;
    void *p;

    memcpy(frame, D_0042ED70, 0xA8);
    s0 = D_0042BB80 + 0x30;
    func_26EBC0(s0, D_0042EE18, frame + 0xB0);
    func_26F118(D_0042BB80 + 0x30, frame + 0xB0, (s32 *)(frame + 0xC0), (s32 *)(frame + 0xC4));
    f20 = func_26F148(D_0042BB80 + 0x30, (s32 *)(frame + 0xB0));
    TexFile_UploadOne(*(s32 *)(D_0042BB80 + 0xCC), 0, 0x3000, 0x3040);
    func_003B4C20(*(s32 *)(D_0042BB80 + 0xC0), 0x3041);
    p = Dma_BeginDirect();
    p = func_00418A68(p, frame, *(s32 *)(frame + 0xC0), *(s32 *)(frame + 0xC4), f20, 0);
    p = func_00418A68(p, frame + 0x38, *(s32 *)(frame + 0xC0), *(s32 *)(frame + 0xC4), f20, 1);
    Dma_EndDirect(p);
}
