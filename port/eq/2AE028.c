#include "common.h"

void BtlMenu_EndDraw(s32 arg0, f32 farg0);

void func_002AE028(void *arg0) {
    BtlMenu_EndDraw((s32)arg0, 0.0f);
    *(f32 *)((u8 *)arg0 + 0x15C) = *(f32 *)(*(u8 **)arg0 + 0x9B4);
}
