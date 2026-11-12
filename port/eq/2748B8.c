#include "common.h"

/* Stage breakable-object groups update (once per frame).
 * gBtlStage: +0x44 group count, +0x48 first group index, +0x5C node table (words, scaled by 4 = byte offsets).
 * Group (0x50 bytes): +0x00 flags (bit 1 = active), +0x24 node count, +0x28 first node index,
 * +0x2C lifetime (0 = 148), +0x30 timer, +0x34 flags2 (0x80 = splash on falling through y = 0), +0x40 vec4. */

extern u8 *gBtlStage;    /* gp-0x4340 */
extern u8 *D_003876A0;   /* gp-0x4750: battle state, s64 flags at +0x4D8 */
extern f32 D_00387004;   /* gp-0x4DEC: dust size of material 0 */

s32 StgNode_IsRigid(u8 *node);
void StgRigid_Release(s32 rigid);
void func_00273C38(u8 *node, f32 *out, f32 t);
void func_00312638(f32 *dst, f32 *src, f32 *mtx);
void func_00312FB0(f32 *dst, f32 *src, f32 scale);
s32 func_00101E98(void);
s32 func_00274050(u8 *out, u8 *group, s32 index);
void sceVu0Normalize(f32 *dst, f32 *src);
void func_00273A60(f32 *dst, f32 *src);
void func_002425D8(u8 *a, u8 *b, f32 *c);
void func_00273C08(u8 *node, f32 *out);
s32 StgRigid_Create(f32 *mtx, s32 flags, f32 mass);
s32 StgObj_GetMaterial(u8 *group);
void StgRigid_Launch(s32 rigid, u8 *dir, s32 material);
void StgRigid_GetMatrix(u8 *node, s32 rigid);
s32 StgObj_GetDust(u8 *group, f32 *size);
void func_001D0858(f32 *mtx, s32 kind, f32 a, f32 b, f32 c);
void func_0013B608(f32 *pos, f32 scale);

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F(p, off) (*(f32 *)((u8 *)(p) + (off)))
/* word i of the table at 4*idx of gBtlStage's node table: an entry index, scaled to a byte offset */
#define TBL() (*(u8 **)(gBtlStage + 0x5C))
#define NODE(idx) (TBL() + (s32)(idx) * 4)

void func_002748B8(void) {
    u8 fr[0xc0];   /* tamano de locales del original (antes 0xa0) */            /* sp+0x00 .. 0x9F: matrices/vectors handed to the callees */
    f32 *mtx = (f32 *)fr;   /* sp+0x00 (also read as a vec4) */
    f32 *prev = (f32 *)(fr + 0x10);
    f32 *center = (f32 *)(fr + 0x20);
    f32 dust;               /* sp+0xA0 */
    u8 *groups;             /* sp+0xA4 */
    u8 *e;
    s32 i;
    s32 first;

    groups = NODE(W(gBtlStage, 0x48));
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) || W(gBtlStage, 0x44) == 0) {
        return;
    }
    i = 0;
    e = groups;
    do {
        if (W(e, 0x00) & 2) {
            s32 lim;
            u32 *nodes;
            s32 n;

            first = ((f32)W(e, 0x30) == 0.0f);
            W(e, 0x30) = (s32)((f32)W(e, 0x30) + 2.0f);
            lim = W(e, 0x2C);
            if (lim == 0) {
                lim = 148;
                W(e, 0x2C) = 148;
            }
            if ((f32)lim <= (f32)W(e, 0x30)) {
                /* lifetime over: stop the group and release its rigid bodies */
                W(e, 0x30) = 0;
                W(e, 0x00) ^= 2;
                nodes = (u32 *)NODE(W(e, 0x28));
                if (W(e, 0x24) != 0) {
                    n = 0;
                    do {
                        u8 *node = NODE(nodes[n]);
                        u8 *obj = NODE(W(node, 8));
                        n++;
                        if (StgNode_IsRigid(obj) && W(obj, 0x4C) >= 0) {
                            StgRigid_Release(W(obj, 0x4C));
                        }
                    } while ((u32)n < (u32)W(e, 0x24));
                }
                goto next;
            }
            if (first) {
                /* first frame: center of the group's nodes, then the launch direction */
                u32 count;
                f32 cnt;

                center[0] = 0.0f;
                center[1] = 0.0f;
                center[2] = 0.0f;
                center[3] = 1.0f;
                nodes = (u32 *)NODE(W(e, 0x28));
                for (n = 0; (u32)n < (u32)W(e, 0x24); n++) {
                    u8 *node = NODE(nodes[n]);
                    if (W(node, 8) != 0) {
                        func_00273C38(node, mtx, 0.0f);
                        func_00312638(center, center, mtx);
                    }
                }
                count = (u32)W(e, 0x24);
                cnt = (f32)count; /* unsigned -> float as the asm does */
                func_00312FB0(center, center, 1.0f / cnt);
                if (func_00101E98() != 0) {
                    u8 *hit = fr + 0x30;
                    if (func_00274050(hit, e, i) != 0) {
                        f32 *dir = (f32 *)(fr + 0x80);
                        f32 *v = (f32 *)(fr + 0x40);
                        f32 *push = (f32 *)(fr + 0x90);
                        sceVu0Normalize(dir, (f32 *)(e + 0x40));
                        func_00273A60(v, dir);
                        push[0] = v[0] * 5.0f;
                        push[1] = v[1] * 5.0f;
                        push[2] = v[2] * 5.0f;
                        func_002425D8(hit, e + 0x40, push);
                    }
                }
            }
            /* every frame: each node */
            nodes = (u32 *)NODE(W(e, 0x28));
            if (W(e, 0x24) == 0) {
                goto next;
            }
            for (n = 0; (u32)n < (u32)W(e, 0x24); n++) {
                u8 *node = NODE(nodes[n]);
                u8 *obj;
                if (W(node, 8) == 0) {
                    continue;
                }
                obj = NODE(W(node, 8));
                if (!first) {
                    func_00273C08(node, prev);
                }
                if (StgNode_IsRigid(obj)) {
                    if (first) {
                        s32 r;
                        func_00273C38(node, mtx, 0.0f);
                        r = StgRigid_Create(mtx, 0, F(node, 12));
                        W(obj, 0x4C) = r;
                        if (r >= 0) {
                            StgRigid_Launch(W(obj, 0x4C), e + 0x40, StgObj_GetMaterial(e));
                        }
                    }
                    StgRigid_GetMatrix(obj, W(obj, 0x4C));
                } else {
                    W(obj, 0x4C) = 0;
                    func_00273C38(node, mtx, (f32)W(e, 0x30));
                }
                if (first) {
                    s32 kind = StgObj_GetDust(groups + i * 0x50, &dust);
                    if (kind == 1) {
                        if (n % 3 == 0) {
                            func_001D0858(mtx, 2, 4.0f, 2.0f, dust);
                        }
                    } else if (kind == 0) {
                        if (n % 3 == 0) {
                            func_001D0858(mtx, 2, 2.0f, D_00387004, dust);
                        }
                    } else if (kind == 2) {
                        if ((n & 1) == 0) {
                            func_001D0858(mtx, 2, 4.0f, 3.0f, dust);
                        }
                    }
                } else {
                    /* splash when the node crosses y = 0 going up between the two frames */
                    func_00273C08(node, mtx);
                    if ((W(e, 0x34) & 0x80) && prev[1] < 0.0f && 0.0f < mtx[1]) {
                        func_0013B608(prev, 3.0f);
                    }
                }
            }
        }
    next:
        i++;
        e += 0x50;
    } while ((u32)i < (u32)W(gBtlStage, 0x44));
}
