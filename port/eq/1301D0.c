#include "common.h"

extern u8 *gEftBubble;

void *func_00130170(void);
void func_003126C8(s32 arg0, s32 arg1);

/* Allocates a bubble node, links it at the tail of gEftBubble's list, fills its fields
   (reciprocal and ratio terms from the float inputs) and bumps the list count.
   Returns the new count, or 0 when no node was available. */
s32 func_001301D0(u8 *arg0, u8 *arg1, u8 b2, u8 b3, u8 b5, s32 w6, s32 w7, u8 b8,
                  f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32 ff, f32 fg, f32 fh,
                  f32 fi, f32 fj, u8 b9) {
    u8 *node;
    u8 *tail;
    s32 count;

    node = (u8 *)func_00130170();
    if (node == NULL) {
        return 0;
    }

    if (*(u8 **)(gEftBubble + 0x8) != NULL) {
        *(u8 **)(node + 0x58) = *(u8 **)(gEftBubble + 0xC);
        *(u8 **)(node + 0x5C) = NULL;
    } else {
        *(u8 **)(gEftBubble + 0x8) = node;
        *(u8 **)(node + 0x58) = NULL;
        *(u8 **)(node + 0x5C) = NULL;
    }

    tail = *(u8 **)(gEftBubble + 0xC);
    if (tail == NULL) {
        *(u8 **)(gEftBubble + 0xC) = node;
    } else {
        *(u8 **)(tail + 0x5C) = node;
        *(u8 **)(gEftBubble + 0xC) = node;
    }

    func_003126C8((s32)node, (s32)arg0);
    func_003126C8((s32)(node + 0x10), (s32)arg1);

    *(f32 *)(node + 0x20) = (fa == 0.0f) ? 0.0f : 1.0f / fa;
    *(f32 *)(node + 0x24) = fb;
    *(f32 *)(node + 0x28) = fd;
    *(f32 *)(node + 0x2C) = fc;
    if (fj <= 0.0f) {
        *(f32 *)(node + 0x30) = 0.0f;
    } else {
        *(f32 *)(node + 0x30) = (0.0f - fc) / (fj * 30.0f);
    }
    *(f32 *)(node + 0x34) = fe;
    *(f32 *)(node + 0x38) = (ff == 0.0f) ? 0.0f : 1.0f / ff;
    *(f32 *)(node + 0x3C) = fg;
    *(f32 *)(node + 0x40) = fh;
    *(f32 *)(node + 0x44) = fi;
    *(s32 *)(node + 0x48) = w6;
    *(s32 *)(node + 0x4C) = w7;
    *(u8 *)(node + 0x50) = b2;
    *(u8 *)(node + 0x51) = b3;
    *(u8 *)(node + 0x52) = b5;
    *(u8 *)(node + 0x53) = b8;
    *(u8 *)(node + 0x54) = b9;
    *(u8 *)(node + 0x55) = 1;

    count = *(s32 *)(gEftBubble + 0x10) + 1;
    *(s32 *)(gEftBubble + 0x10) = count;
    return count;
}
