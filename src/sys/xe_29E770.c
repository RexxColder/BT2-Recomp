/*
 * VU1 draw packets.   0x123130..0x123F48
 *
 * Not sound code: this is the packet layer of the 3D renderer at 0x10AD58..0x116xxx (its only callers), placed between
 * the pad and sound objects. No function here uses $gp. Everything is built in the frame's DMA buffer (Dma_Alloc /
 * Dma_AddRef) as VIF1 source-chain packets for nine VU1 microprograms, which sit right after .text:
 *     prog 0  0x2BF6B0..0x2BFAB0     prog 3  0x2C01C0..0x2C04F0     prog 6  0x2C1F00..0x2C2D30
 *     prog 1  0x2BFAB0..0x2BFEA0     prog 4  0x2C04F0..0x2C1180     prog 7  0x2C2D30..0x2C3080
 *     prog 2  0x2BFEA0..0x2C01C0     prog 5  0x2C1180..0x2C1F00     prog 8  0x2C3080..0x2C3380
 * (the program numbers are only the address order. "prog 3" here is the second variant of program 2, called 2b in
 * the listings: src/vu1/prog*.vsm, described in docs/systems/vu1/README.md.)
 *
 * Each program has a pair of builders:
 *   Vu1Pkt_LoadProgN  a "ref" tag that uploads the microprogram, then a "cnt" packet: FLUSHE, UNPACK V4-32 of the
 *                     program's constant block to VU address 0, BASE / OFFSET for its double buffer.
 *   Vu1Pkt_CallProgN  a "call" packet: FLUSHE, UNPACK of the per-object constants, MSCALF 0, BASE / OFFSET, then
 *                     the DMA chain of the object's vertex data (which ends in "ret").
 * The builders fill in the matrices they are given or the current VU0 ones (vf16-19 local-to-world, vf20-23 and
 * vf24-27 the two camera matrices); the ones that return the packet leave the remaining constants to the caller.
 * A port replaces the whole layer: the packets are meaningless without the VU1 programs.
 *
 * The Vu1Node functions walk a model's node list (see Vu1Node): keyframe posing, per-node draw packets for program 8,
 * and a flag patch in the nodes' VIF streams.
 */
#include "common.h"
#include "sys/vu1_packet.h"
#include "sys/dma.h"

extern void *memset(void *dst, s32 value, u32 size);
extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(void *dst, void *src);
extern void Mtx_StoreIdentity(void *m);
extern void Mtx_Mul(void *dst, void *a, void *b); /* matrix product */
extern void Mtx_Copy(void *dst, void *src);        /* 4x4 matrix copy */
extern void Vu0Cur_Push(void);                        /* VU0 matrix stack: push vf16-19 */
extern void Vu0Cur_PopN(s32 count);                   /* VU0 matrix stack: pop count */
extern void Vu0Cur_ResetStack(void);                        /* VU0 matrix stack: reset (vi15 = 0) */
extern void Vu0Cur_LoadMtx(void *m);                     /* vf16-19 = m */
extern void Vu0Cur_StoreMtx(void *m);                     /* m = vf16-19 (current local-to-world) */
extern void Vu0Cur_TranslateLocal(void *vec);                   /* applies a translation to vf16-19 */
extern void Vu0Cur_RotateYXZ(void *vec);                   /* applies a rotation to vf16-19 */
extern void Vu0Clip_StoreMtx(void *m);                     /* m = vf20-23 */
extern void Vu0Screen_StoreMtx(void *m);                     /* m = vf24-27 */


/* Program 4 draw: runs the caller's chain with the constants already loaded. */
void Vu1Pkt_CallProg4(u32 chain) {
    u32 *p = Dma_Alloc(0x20);

    p[0] = VU1_DMA_CALL | 1;
    p[1] = chain & VU1_ADDR_MASK;
    p[2] = VU1_VIF_FLUSHE;
    p[3] = VU1_VIF_NOP;
    p[4] = VU1_VIF_MSCALF(0);
    p[5] = VU1_VIF_BASE(0x8D);
    p[6] = VU1_VIF_OFFSET(0x1B4);
    p[7] = VU1_VIF_NOP;
}

/* Program 4 setup: uploads the microprogram, the two camera matrices and the given matrix. */
void Vu1Pkt_LoadProg4(void *mtx) {
    u32 *p;

    Dma_AddRef(D_002C04F0, D_002C1180 - D_002C04F0);
    p = Dma_Alloc(0xE0);
    Mtx_Copy(p + 0x24, mtx);
    Vu0Screen_StoreMtx(p + 4);
    Vu0Clip_StoreMtx(p + 0x14);
    p[0] = VU1_DMA_CNT | 0xD;
    p[1] = 0;
    p[2] = VU1_VIF_FLUSHE;
    p[3] = VU1_VIF_UNPACK_V4_32(0xC, 0);
    p[0x34] = VU1_VIF_NOP;
    p[0x35] = VU1_VIF_BASE(0x8D);
    p[0x36] = VU1_VIF_OFFSET(0x1B4);
    p[0x37] = VU1_VIF_NOP;
}

/* Program 5 draw: one matrix, then the caller's chain. No callers. */
void Vu1Pkt_CallProg5(u32 chain, void *mtx) {
    u32 *p = Dma_Alloc(0x60);

    Mtx_Copy(p + 4, mtx);
    p[0] = VU1_DMA_CALL | 5;
    p[1] = chain & VU1_ADDR_MASK;
    p[2] = VU1_VIF_FLUSHE;
    p[3] = VU1_VIF_UNPACK_V4_32(4, 0);
    p[0x14] = VU1_VIF_MSCALF(0);
    p[0x15] = VU1_VIF_BASE(0x8D);
    p[0x16] = VU1_VIF_OFFSET(0x1B4);
    p[0x17] = VU1_VIF_NOP;
}
