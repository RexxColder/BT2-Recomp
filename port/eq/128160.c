#include "common.h"

s32 EftHit_GetHitCount(s32 arg0);
s32 EftHit_GetMaxHits(s32 arg0);
s32 EftHit_HasDefFlag20(s32 arg0);

void func_00128160(void *arg0) {
    u8 *s1;
    u8 *a1;
    u8 *v1;
    u8 *p;
    s32 var;
    u32 t;
    s32 t2;
    s32 cnt;

    s1 = (u8 *)arg0;
    a1 = *(u8 **)(s1 + 0x64);
    var = 0;
    if (a1 != NULL) {
        v1 = *(u8 **)(a1 + 0x20);
        if (*(s32 *)(v1 + 4) != 0) {
            t = *(u32 *)(v1 + 8);
            if (t < 3U) {
                var = 1;
            } else {
                var = 1;
                if (t != 7) {
                    var = (*(s32 *)(v1 + 0) == 0x150);
                }
            }
        } else if (*(s32 *)(v1 + 8) == 4) {
            var = 1;
        }

        if (var == 1 && *(s8 *)(*(u8 **)(a1 + 0x20) + 0x36) > 0) {
            p = *(u8 **)(s1 + 0x60);
            *(s32 *)(p + 4) = *(s32 *)(p + 4) | 0x4000;
            p = *(u8 **)(s1 + 0x60);
            t2 = *(s32 *)(p + 4);
            if (t2 & 1) {
                *(s32 *)(p + 4) = t2 & ~1;
            }
            if (EftHit_GetHitCount((s32)s1) > 0) {
                if (EftHit_HasDefFlag20((s32)s1) != 0) {
                    *(s32 *)(s1 + 0x50) = *(s32 *)(s1 + 0x50) | 0x10;
                } else {
                    cnt = EftHit_GetHitCount((s32)s1);
                    if (!(cnt < EftHit_GetMaxHits((s32)s1))) {
                        *(s32 *)(s1 + 0x50) = *(s32 *)(s1 + 0x50) | 0x10;
                    }
                }
            }
        }
    }
}
