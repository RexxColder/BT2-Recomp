#include "common.h"

extern s32 func_001BB928(u8 *obj, u8 *eft, u8 *color_in, u64 tex, f32 w, f32 h);

/* 0x001BBF50: walks the list at obj->+0 (next at +0x120), drawing each with f12 = f13 = node->+0x40. */
s32 func_001BBF50(u8 *obj) {
    u8 *node = *(u8 **)obj;
    s32 ret = 0;

    while (node != 0) {
        f32 w = *(f32 *)(node + 0x40);
        func_001BB928(obj, node, node + 0xA0, *(u64 *)(obj + 0x280), w, w);
        node = *(u8 **)(node + 0x120);
        ret = (s32)node;
    }
    return ret;
}
