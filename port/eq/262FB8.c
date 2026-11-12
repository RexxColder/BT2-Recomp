#include "common.h"

extern u64 D_00376560[6];
extern u8 *D_00387A40;

s32 func_00267488(s32 arg0);
void Dma_AddData(s32 arg0, s32 arg1);
void Dma_AddRef(s32 arg0, s32 arg1);
void func_00286B60(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void TexFile_UploadOne(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#define P(x) ((s32)(u32)(x))

/* word stored at packet+0x24: position in the low half, 16-bit field from the entry shifted up */
static u32 pk(s32 pos, u32 w) {
    return (u32)pos | (w << 16);
}

void func_00262FB8(u8 *obj) {
    u64 pkt[8];
    u8 *ex = obj + 0xAF0;
    u8 *list;
    u8 *other = *(u8 **)(obj + 0x54);
    u8 *hdr;
    u8 *e;
    u8 *e5;
    s32 n0, n1, idx, pos, y1, y2, sel;
    u32 i, off, off5;
    s32 k;

    for (k = 0; k < 6; k++) {
        pkt[k] = D_00376560[k];
    }
    if ((*(u64 *)ex & 0x10000002) == 0x10000002) {
        list = *(u8 **)(obj + 0x50);
        if (list == NULL) {
            list = *(u8 **)(obj + 0x4C);
        }
    } else {
        list = *(u8 **)(obj + 0x4C);
    }
    hdr = *(u8 **)(obj + 0x44);
    n1 = hdr[0x25];
    n0 = hdr[0x24];
    off = 0;
    off5 = (u32)n1 << 6;
    if (*(u32 *)list != 0) {
        i = 0;
        do {
            if ((s32)i < n0) {
                off5 += 0x40;
            } else if ((s32)i < n0 + n1 && (s32)i != *(*(u8 **)(obj + 0x44) + 0x22)) {
                e = *(u8 **)(list + 0x10) + off;
                y1 = *(s32 *)(e + 0x24) + *(s32 *)(ex + 0xC0) + 0x40;
                y2 = *(s32 *)(e + 0x24) + *(s32 *)(ex + 0xC0) + 0x80;
                pos = *(s32 *)(e + 0x20) + *(s32 *)(ex + 0xBC);
                *(u32 *)((u8 *)pkt + 0x20) = 0;
                *(u32 *)((u8 *)pkt + 0x24) = pk(pos, *(u32 *)(e + 0x18));
                Dma_AddData(P(pkt), 0x30);
                e = *(u8 **)(list + 0x10) + off;
                Dma_AddRef(*(s32 *)(e + 0x38), *(s32 *)(e + 8));
                *(u32 *)((u8 *)pkt + 0x20) = 0;
                e = *(u8 **)(list + 0x10) + off;
                *(u32 *)((u8 *)pkt + 0x24) = pk(y1, *(u32 *)(e + 0x1C));
                Dma_AddData(P(pkt), 0x30);
                e = *(u8 **)(list + 0x10) + off;
                Dma_AddRef(*(s32 *)(e + 0x3C), *(s32 *)(e + 0xC));
                *(u32 *)((u8 *)pkt + 0x20) = 0;
                e5 = *(u8 **)(list + 0x10) + off5;
                *(u32 *)((u8 *)pkt + 0x24) = pk(y2, *(u32 *)(e5 + 0x1C));
                Dma_AddData(P(pkt), 0x30);
                e5 = *(u8 **)(list + 0x10) + off5;
                Dma_AddRef(*(s32 *)(e5 + 0x3C), *(s32 *)(e5 + 0xC));
                off5 += 0x40;
            } else if ((s32)i < n0 + n1 && (s32)i == *(*(u8 **)(obj + 0x44) + 0x22)) {
                e = *(u8 **)(list + 0x10) + off;
                y1 = *(s32 *)(e + 0x24) + *(s32 *)(ex + 0xC0) + 0x40;
                y2 = *(s32 *)(e + 0x24) + *(s32 *)(ex + 0xC0) + 0x80;
                pos = *(s32 *)(e + 0x20) + *(s32 *)(ex + 0xBC);
                sel = func_00267488(P(obj));
                if (sel == -1 || *(s32 *)(obj + 0x54) == 0) {
                    *(u32 *)((u8 *)pkt + 0x20) = 0;
                    e = *(u8 **)(list + 0x10) + off;
                    *(u32 *)((u8 *)pkt + 0x24) = pk(pos, *(u32 *)(e + 0x18));
                    Dma_AddData(P(pkt), 0x30);
                    e = *(u8 **)(list + 0x10) + off;
                    Dma_AddRef(*(s32 *)(e + 0x38), *(s32 *)(e + 8));
                    *(u32 *)((u8 *)pkt + 0x20) = 0;
                    e = *(u8 **)(list + 0x10) + off;
                    *(u32 *)((u8 *)pkt + 0x24) = pk(y1, *(u32 *)(e + 0x1C));
                    Dma_AddData(P(pkt), 0x30);
                    e = *(u8 **)(list + 0x10) + off;
                    Dma_AddRef(*(s32 *)(e + 0x3C), *(s32 *)(e + 0xC));
                } else {
                    sel <<= 6;
                    *(u32 *)((u8 *)pkt + 0x20) = 0;
                    e = *(u8 **)(other + 0x10) + sel;
                    *(u32 *)((u8 *)pkt + 0x24) = pk(pos, *(u32 *)(e + 0x18));
                    Dma_AddData(P(pkt), 0x30);
                    e = *(u8 **)(other + 0x10) + sel;
                    Dma_AddRef(*(s32 *)(e + 0x38), *(s32 *)(e + 8));
                    *(u32 *)((u8 *)pkt + 0x20) = 0;
                    e = *(u8 **)(other + 0x10) + sel;
                    *(u32 *)((u8 *)pkt + 0x24) = pk(y1, *(u32 *)(e + 0x1C));
                    Dma_AddData(P(pkt), 0x30);
                    e = *(u8 **)(other + 0x10) + sel;
                    Dma_AddRef(*(s32 *)(e + 0x3C), *(s32 *)(e + 0xC));
                }
                *(u32 *)((u8 *)pkt + 0x20) = 0;
                e5 = *(u8 **)(list + 0x10) + off5;
                *(u32 *)((u8 *)pkt + 0x24) = pk(y2, *(u32 *)(e5 + 0x1C));
                Dma_AddData(P(pkt), 0x30);
                e5 = *(u8 **)(list + 0x10) + off5;
                Dma_AddRef(*(s32 *)(e5 + 0x3C), *(s32 *)(e5 + 0xC));
                off5 += 0x40;
            } else {
                off5 += 0x40;
            }
            off += 0x40;
            i++;
        } while (i < *(u32 *)list);
    }

    if ((*(u64 *)(obj + 0xAF0) & 0x30000) != 0) {
        hdr = *(u8 **)(obj + 0x44);
        if (hdr[0x27] != 0) {
            k = 0;
            do {
                k++;
                func_00286B60(*(u8 **)(obj + 0x4C), hdr[0x26], hdr[0x27], *(s32 *)(ex + 0xCC), -1);
                hdr = *(u8 **)(obj + 0x44);
            } while (k < hdr[0x27]);
        }
    } else if ((*(u32 *)(obj + 0xAF0) & 0x80000) != 0) {
        hdr = *(u8 **)(obj + 0x44);
        if (hdr[0x27] != 0) {
            k = 0;
            do {
                s32 dst = *(s32 *)(ex + 0xCC) + k * 4;
                k++;
                TexFile_UploadOne(*(s32 *)(D_00387A40 + 0x38080), 1, dst, -1);
                hdr = *(u8 **)(obj + 0x44);
            } while (k < hdr[0x27]);
        }
    } else if ((*(u32 *)(obj + 0xAF0) & 0x40000) != 0) {
        hdr = *(u8 **)(obj + 0x44);
        if (hdr[0x27] != 0) {
            k = 0;
            do {
                k++;
                func_00286B60(*(u8 **)(obj + 0x4C), hdr[0x26], hdr[0x27], *(s32 *)(ex + 0xCC), -1);
                hdr = *(u8 **)(obj + 0x44);
            } while (k < hdr[0x27]);
        }
    } else if ((*(u32 *)(obj + 0xAF0) & 0x400000) != 0) {
        hdr = *(u8 **)(obj + 0x44);
        if (hdr[0x27] != 0) {
            k = 0;
            do {
                k++;
                func_00286B60(*(u8 **)(obj + 0x4C), hdr[0x26], hdr[0x27], *(s32 *)(ex + 0xCC), -1);
                hdr = *(u8 **)(obj + 0x44);
            } while (k < hdr[0x27]);
        }
    }
}
