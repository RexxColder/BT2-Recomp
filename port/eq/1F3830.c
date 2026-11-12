#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *gEftVram;

s64 EftVram_AddTex(void *arg0, s32 arg1, s32 arg2) {
    u8 *ga;
    u8 *tex8;
    s32 idx;
    s64 temp_v0;
    u32 temp_t2;
    u32 temp_t0;
    s32 temp_t1;

    ga = gEftVram;
    if (*(u32 *)((u8 *)arg0 + 8) == 0) {
        /* port guard: texture set entry never loaded (its image pointer is NULL) */
        static int warned;
        if (!warned++) {
            extern int printf(const char *, ...);
            printf("bt2: EftVram_AddTex: entry %p without image (skipped)\n", arg0);
        }
        return 0;
    }
    idx = *(s32 *)(ga + 0x800);
    *(void **)(ga + idx * 4) = arg0;
    *(s32 *)(ga + idx * 4 + 0x200) = *(s32 *)(ga + 0x804);
    *(s32 *)(ga + idx * 4 + 0x400) = *(s32 *)(ga + 0x808);
    *(s32 *)(ga + idx * 4 + 0x600) = 3;
    temp_v0 = *(s64 *)arg0 & (s64)0xFFF80003FFFFC000ULL;
    *(s64 *)arg0 = temp_v0;
    tex8 = *(u8 **)((u8 *)arg0 + 8);
    temp_t1 = *(s32 *)(tex8 + 0x10);
    temp_t2 = *(u32 *)(ga + 0x804);
    temp_t0 = *(u32 *)(ga + 0x808);
    *(s32 *)(ga + 0x804) = *(s32 *)(ga + 0x804) + temp_t1;
    *(s32 *)(ga + 0x808) = *(s32 *)(ga + 0x808) + *(s32 *)(tex8 + 0x14);
    *(s32 *)(ga + 0x800) = idx + 1;
    {   /* TEMP TEX0: report TEX0 without TCC and without CBP (white-square signature) */
        s64 r_ = temp_v0 | ((s64)temp_t0 << 37) | (((s64)arg1 << 34) | (s64)temp_t2) | ((s64)arg2 << 35);
        if ((u32)(r_ >> 32) == 0) bt2_fightlog_note("TEX0ADDTEX %llx tcc %d tfx %d clutblk %x hdrhi %x ret %p", (unsigned long long)r_, arg1, arg2, temp_t0, (u32)(*(u64 *)arg0 >> 32), __builtin_return_address(0));
        return r_;
    }
}
