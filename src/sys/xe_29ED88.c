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


/* Queues one program 8 draw per node that has a mesh, with the node's matrices and vectors. */
void Vu1Node_Draw(Vu1Node *node) {
    u32 *p;

    while (1) {
        if (node->hasMesh) {
            p = Vu1Pkt_CallProg8(node);
            Mtx_Copy(p + 0x14, node->parent);
            Mtx_Copy(p + 4, node->world);
            Vec4_Copy(p + 0x24, node->unkD0);
            Vec4_Copy(p + 0x28, node->unkE0);
        }
        if (node->last) {
            break;
        }
        node = (Vu1Node *)((u8 *)node + node->size);
    }
}

/* Program 8 draw: 0xA quadwords of per-node constants, then the node's VIF stream. */
u32 *Vu1Pkt_CallProg8(Vu1Node *node) {
    u32 *p = Dma_Alloc(0xC0);

    p[0] = VU1_DMA_CALL | 0xB;
    p[1] = (u32)node->vif & VU1_ADDR_MASK;
    p[2] = VU1_VIF_FLUSHE;
    p[3] = VU1_VIF_UNPACK_V4_32(0xA, 0);
    p[0x2C] = VU1_VIF_MSCALF(0);
    p[0x2D] = VU1_VIF_BASE(0x12);
    p[0x2E] = VU1_VIF_OFFSET(0x1F7);
    p[0x2F] = VU1_VIF_NOP;
    return p;
}

/* Program 8 setup: uploads the microprogram and reserves 0x12 quadwords of constants. */
u32 *Vu1Pkt_LoadProg8(void) {
    u32 *p;

    Dma_AddRef(D_002C3080, D_002C3380 - D_002C3080);
    p = Dma_Alloc(0x140);
    p[0] = VU1_DMA_CNT | 0x13;
    p[1] = 0;
    p[2] = VU1_VIF_FLUSHE;
    p[3] = VU1_VIF_UNPACK_V4_32(0x12, 0);
    p[0x4C] = VU1_VIF_NOP;
    p[0x4D] = VU1_VIF_BASE(0x12);
    p[0x4E] = VU1_VIF_OFFSET(0x1F7);
    p[0x4F] = VU1_VIF_NOP;
    return p;
}
