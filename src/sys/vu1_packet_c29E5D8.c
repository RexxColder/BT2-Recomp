#define D_002BF6B0 D_0033BA80  /* fix_targets */ /* the original uses 0x33ba80 here */
#define D_002BFAB0 D_0033BE70  /* fix_targets */ /* the original uses 0x33be70 here */
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

/* Program 7 draw: current matrix, the two camera matrices and w, then the caller's vertex chain. */
u32 *Vu1Pkt_CallProg7(u32 chain, f32 w);

/* Program 7 setup: uploads the microprogram and the two camera matrices. */
u32 *Vu1Pkt_LoadProg7(void);

/* Program 0 draw: 0x22 quadwords of constants for the caller to fill, then the caller's chain. */
u32 *Vu1Pkt_CallProg0(u32 chain);

/* Program 0 setup: uploads the microprogram and reserves its constant block. */
u32 *func_0029E5D8(void) {
    u32 *p;

    Dma_AddRef(D_002BF6B0, D_002BFAB0 - D_002BF6B0);
    p = Dma_Alloc(0x240);
    p[0] = VU1_DMA_CNT | 0x23;
    p[1] = 0;
    p[2] = VU1_VIF_FLUSHE;
    p[3] = VU1_VIF_UNPACK_V4_32(0x22, 0);
    p[0x8C] = VU1_VIF_NOP;
    p[0x8D] = VU1_VIF_BASE(0x22);
    p[0x8E] = VU1_VIF_OFFSET(0x1EF);
    p[0x8F] = VU1_VIF_NOP;
    return p;
}

/* Program 1 draw: as program 0, for an object whose chain starts at +0x60. */
u32 *Vu1Pkt_CallProg1(u32 obj);

/* Program 1 setup. */
u32 *Vu1Pkt_LoadProg1(void);

/* Program 2/3 draw: 0xB quadwords of per-object constants, then the object's chain at +0x60. */
u32 *Vu1Pkt_CallProg2(u32 obj);

/* Program 2 (alt = 0) or 3 setup: uploads the microprogram and reserves 0x13 quadwords of constants. */
u32 *Vu1Pkt_LoadProg2(s32 alt);

/* Program 4 draw: runs the caller's chain with the constants already loaded. */
void Vu1Pkt_CallProg4(u32 chain);

/* Program 4 setup: uploads the microprogram, the two camera matrices and the given matrix. */
void Vu1Pkt_LoadProg4(void *mtx);

/* Program 5 draw: one matrix, then the caller's chain. No callers. */
void Vu1Pkt_CallProg5(u32 chain, void *mtx);

/* Program 5 setup: identity, the two camera matrices and the given matrix. No callers. */
void Vu1Pkt_LoadProg5(void *mtx);

/* ORs bits into words 4 and 5 (the second shifted left 5) of every node-header block in a node list's VIF streams. */
void Vu1Node_OrFlags(Vu1Node *node, u32 bits0, u32 bits1);

/* Poses a node list at `frame`: per node, position and rotation from its key track (the pair of keys around the frame,
   interpolated linearly), then the node matrices through the VU0 matrix stack.
   The shape the code needs: the later key is a walking pointer stepped at the top of the body, the earlier key is
   written `(next - 1)` at every use (so its frame number is reloaded in each block while the later key's stays in a
   register), the key count is a local, and the frame word is read as the fourth float of `pos` when it is copied. */
void Vu1Node_Animate(Vu1Node *node, Vu1Track *track, void *mtx, f32 frame);

/* Queues one program 8 draw per node that has a mesh, with the node's matrices and vectors. */
void Vu1Node_Draw(Vu1Node *node);

/* Program 8 draw: 0xA quadwords of per-node constants, then the node's VIF stream. */
u32 *Vu1Pkt_CallProg8(Vu1Node *node);

/* Program 8 setup: uploads the microprogram and reserves 0x12 quadwords of constants. */
u32 *Vu1Pkt_LoadProg8(void);

/* Program 6 draw: runs the caller's chain with the constants already loaded. */
void Vu1Pkt_CallProg6(u32 chain);

/* Program 6 setup: uploads the microprogram, obj's matrices (+0x100, +0x80 and +0xC0 each times +0x40), a matrix and a vector. */
void Vu1Pkt_LoadProg6(u8 *obj, void *mtx, f32 *vec);
