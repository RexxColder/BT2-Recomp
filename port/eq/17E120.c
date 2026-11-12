#include "common.h"

void Vu0Screen_StoreMtx(f32 *mtx);
void func_003126C8(f32 *dst, f32 *src);
void func_00312638(f32 *dst, f32 *a, f32 *b);
void func_00312650(f32 *dst, f32 *a, f32 *b);
void func_00312490(f32 *dst, f32 *a, f32 *b);
void sceVu0Normalize(f32 *dst, f32 *src);
void func_00312FB0(f32 *dst, f32 *src, f32 s);
void func_00312680(f32 *dst, f32 *src, f32 s);
s32 sceVu0RotTransPers(s32 *out, f32 *mtx, f32 *in, s32 flag);
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void func_0017E120(u8 *obj, u8 *list, f32 alpha) {
    f32 mtx[16];
    f32 corner[16];      /* four vec4 */
    s32 scr[16];         /* four projected points (x, y, z, w) */
    f32 proj[16];        /* UV scaled by 1/w */
    f32 uv[16];
    f32 axis[4], toA[4], cam[4], prev[4], cur[4], off[4];
    f32 prevA[4], prevB[4];
    u8 *node;
    u8 *next;
    s32 first;
    s32 count, count1;
    s32 clip;
    s32 i;
    u8 *pkt;

    Vu0Screen_StoreMtx(mtx);
    first = 1;
    func_003126C8(cam, (f32 *)(gBtlCamView + 0x1F0));
    count = 0;
    func_00312638(prev, (f32 *)(list + 0x30), (f32 *)(list + 0x50));
    node = *(u8 **)(list + 0);
    if (node == NULL) {
        return;
    }
    do {
        next = *(u8 **)(node + 0x30);
        if (next != NULL && (*(s32 *)node & 2) != 0) {
            func_00312650(axis, (f32 *)(next + 0x10), (f32 *)(node + 0x10));
            clip = 0;
            func_00312638(cur, prev, (f32 *)(node + 0x10));
            cur[3] = 1.0f;
            func_00312650(toA, cur, cam);
            func_00312490(axis, axis, toA);
            sceVu0Normalize(axis, axis);
            if (first) {
                func_00312FB0(off, axis, *(f32 *)(node + 8));
                func_00312638(corner + 0, cur, off);
                corner[3] = 1.0f;
                func_00312FB0(off, axis, -*(f32 *)(node + 4));
                func_00312638(corner + 4, cur, off);
                corner[7] = 1.0f;
            } else {
                func_003126C8(corner + 0, prevA);
                func_003126C8(corner + 4, prevB);
            }
            count1 = count + 1;
            func_00312FB0(off, axis, *(f32 *)(next + 8));
            func_00312638(corner + 8, cur, off);
            corner[11] = 1.0f;
            first = 0;
            func_00312FB0(off, axis, -*(f32 *)(next + 4));
            func_00312638(corner + 12, cur, off);
            corner[15] = 1.0f;
            func_003126C8(prevA, corner + 8);
            func_003126C8(prevB, corner + 12);
            {
                f32 a = (f32)(count % 2);
                f32 b = (f32)(count1 % 2);
                uv[0] = a; uv[1] = b; uv[2] = 1.0f; uv[3] = 0.0f;
                uv[4] = a; uv[5] = a; uv[6] = 1.0f; uv[7] = 0.0f;
                uv[8] = b; uv[9] = b; uv[10] = 1.0f; uv[11] = 0.0f;
                uv[12] = b; uv[13] = a; uv[14] = 1.0f; uv[15] = 0.0f;
            }
            for (i = 0; i < 4; ) {
                i++;
                sceVu0RotTransPers(&scr[(i - 1) * 4], mtx, corner + (i - 1) * 4, 1);
                func_00312680(proj + (i - 1) * 4, uv + (i - 1) * 4, 1.0f / (f32)scr[(i - 1) * 4 + 3]);
                if ((u32)scr[(i - 1) * 4 + 0] > 0xFFF0) {
                    clip = 1;
                    break;
                }
                if ((u32)scr[(i - 1) * 4 + 1] > 0xFFF0) {
                    clip = 1;
                    break;
                }
                if (scr[(i - 1) * 4 + 2] < 0) {
                    clip = 1;
                    break;
                }
            }
            if (clip == 0) {
                u8 c6[4], c3[4];
                s32 key;
                u8 *slot;
                u8 *tail;

                pkt = D_00387AD8;
                D_00387AD8 = pkt + 0x90;
                if (pkt == NULL) {
                    return;
                }
                *(u64 *)(pkt + 0x10) = 0xE400000000008001ULL;
                *(u64 *)(pkt + 0x18) = 0x42142142142160ULL;
                *(u64 *)(pkt + 0x20) = 0x5C;
                *(u64 *)(pkt + 0x00) = 0xA0000008ULL;
                c6[0] = (s32)(*(f32 *)(node + 0x20) * 255.0f);
                c6[1] = (s32)(*(f32 *)(node + 0x24) * 255.0f);
                c6[2] = (s32)(*(f32 *)(node + 0x28) * 255.0f);
                c6[3] = (s32)(*(f32 *)(node + 0x2C) * 255.0f * alpha);
                c3[0] = (s32)(*(f32 *)(next + 0x20) * 255.0f);
                c3[1] = (s32)(*(f32 *)(next + 0x24) * 255.0f);
                c3[2] = (s32)(*(f32 *)(next + 0x28) * 255.0f);
                c3[3] = (s32)(*(f32 *)(next + 0x2C) * 255.0f * alpha);
                pkt[0x30] = c6[0]; pkt[0x31] = c6[1]; pkt[0x32] = c6[2]; pkt[0x33] = c6[3];
                *(f32 *)(pkt + 0x34) = proj[2];
                pkt[0x48] = c6[0]; pkt[0x49] = c6[1]; pkt[0x4A] = c6[2]; pkt[0x4B] = c6[3];
                *(f32 *)(pkt + 0x4C) = proj[6];
                pkt[0x60] = c3[0]; pkt[0x61] = c3[1]; pkt[0x62] = c3[2]; pkt[0x63] = c3[3];
                *(f32 *)(pkt + 0x64) = proj[10];
                pkt[0x78] = c3[0]; pkt[0x79] = c3[1]; pkt[0x7A] = c3[2]; pkt[0x7B] = c3[3];
                *(f32 *)(pkt + 0x7C) = proj[14];
                *(f32 *)(pkt + 0x38) = proj[0];
                *(f32 *)(pkt + 0x3C) = proj[1];
                *(f32 *)(pkt + 0x50) = proj[4];
                *(f32 *)(pkt + 0x54) = proj[5];
                *(f32 *)(pkt + 0x68) = proj[8];
                *(f32 *)(pkt + 0x6C) = proj[9];
                *(f32 *)(pkt + 0x80) = proj[12];
                *(f32 *)(pkt + 0x84) = proj[13];
                for (i = 0; i < 4; i++) {
                    u8 *q = pkt + 0x40 + i * 0x18;
                    *(u16 *)(q + 0) = (u16)scr[i * 4 + 0];
                    *(u16 *)(q + 2) = (u16)scr[i * 4 + 1];
                    *(u64 *)q = (*(u64 *)q & 0xFF000000FFFFFFFFULL) | ((u64)((u32)scr[i * 4 + 2] & 0xFFFFFF) << 32);
                    q[7] = 0xFF;
                }
                *(u64 *)(pkt + 0x28) = *(u64 *)(obj + 0xE98);
                key = (scr[2] + scr[4 * 2 + 3] + scr[4 * 2 + 2] + scr[4 + 2]) >> 10;
                if (key < 0) {
                    slot = D_00387AE0 + 8;
                    tail = *(u8 **)(slot + 4);
                } else if (key >= 0x1000) {
                    slot = D_00387AE0 + 0xFFF8;
                    tail = *(u8 **)(slot + 4);
                } else {
                    slot = D_00387AE0 + key * 16 + 8;
                    tail = *(u8 **)(slot + 4);
                }
                *(u8 **)(tail + 4) = pkt;
                *(u8 **)(slot + 4) = pkt;
            }
            count = count1;
        }
        node = *(u8 **)(node + 0x30);
    } while (node != NULL);
}
