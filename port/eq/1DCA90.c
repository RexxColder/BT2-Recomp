#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);
void func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);

void func_001DCA90(u8 *arg0) {
    u8 sp[0x110];
    u8 *s3;
    u8 *base;
    u8 *b0;
    u8 *s1;
    u8 *s2;
    u8 *s5;
    u8 *s6;
    s32 s7;
    s32 fp;
    s32 ac;
    s32 s4;
    s32 handle;
    s32 i;

    s3 = *(u8 **)(arg0 + 0x38);
    base = *(u8 **)s3;
    s7 = 0;
    fp = 0;
    ac = 0;
    b0 = s3;
    do {
        *(f32 *)(sp + 0x50) = *(f32 *)(base + fp);
        *(f32 *)(sp + 0x54) = *(f32 *)(base + 4 + fp);
        memset(sp + 0x60, 0, 0x10);
        memset(sp + 0x70, 0, 0x10);
        *(s32 *)(sp + 0x80) = *(u8 *)(base + 8 + s7);
        *(s32 *)(sp + 0x84) = *(s32 *)(s3 + 4);
        *(s32 *)(sp + 0x88) = *(s32 *)(s3 + 8) + 0x164 * s7;
        *(s32 *)(sp + 0x8C) = *(s32 *)(s3 + 0xC) + ac;
        *(s32 *)(sp + 0x90) = *(s32 *)(s3 + 0x244);
        /* the asm copies the 0x50 bytes at sp+0x50 down to sp+0 */
        for (i = 0; i < 0x50; i++) {
            sp[i] = sp[0x50 + i];
        }
        s5 = base + 4 + fp;
        s6 = base + 9 + s7;
        s1 = s3;
        s2 = b0 + 0x10;
        s4 = 0;
        do {
            if (*(s32 *)(s3 + 0x240) != s4) {
                *(f32 *)(sp + 4) = *(f32 *)s5 * *(f32 *)(s3 + 0x248);
                func_00129C28((s32)(sp + 0x10), (s32)(s1 + 0x50));
                func_00129C28((s32)(sp + 0x20), (s32)(s1 + 0x140));
                if (*s6 == 0) {
                    func_00129BD0((s32)(sp + 0x20), (s32)(sp + 0x20), -1.0f);
                }
                handle = EftPtcl3_Create((s32)sp);
                *(s32 *)s2 = handle;
                EftPtcl3_SetType(handle, 2);
            }
            s4 += 1;
            s2 += 4;
            s1 += 0x10;
        } while (s4 < 9);
        s7 += 1;
        fp += 4;
        ac += 0x50;
        b0 += 4;
    } while (s7 <= 0);
}
