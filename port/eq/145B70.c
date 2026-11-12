#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern u8 *gEftWeather;
extern u8 *D_003876A0;
extern u8 D_00340200[] __attribute__((section(".data")));

s32 BtlPool_GetCurrent(void);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
void *memset(void *dst, s32 c, u32 n);
u8 *func_002768D8(s32 arg0);
s32 func_00276AC8(void);
s32 func_00276D00(void);
void func_00145B20(s32 arg0);
s32 EftTexSet_Load32(void *arg0, void *arg1);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);

/* 0x00145B70: sets up the weather effect block (0x2C0 bytes from the current pool, gEftWeather), calls a
 * per-mode routine chosen by func_00276AC8 (modes 0, 4, 7, 13, 14 always; the others when func_00276D00
 * returns non-zero), loads a texture set from the block of D_003876A0 (+0x40 when its flag bit 62 is set) and
 * adds the child task list to the task list D_00340200. */
void func_00145B70(s32 arg0) {
    u8 *ptr;
    s32 s0;
    s32 idx;
    s32 a;
    s32 r;

    gEftWeather = (u8 *)(s32)BtlPool_Alloc(BtlPool_GetCurrent(), 0x2C0);
    memset(gEftWeather, 0, 0x2C0);
    LD32(gEftWeather, 0) = 0;
    LD32(gEftWeather, 0x2A0) = 0;
    LD32(gEftWeather, 0x210) = 0x80;
    LD32(gEftWeather, 0x214) = 0x80;
    LD32(gEftWeather, 0x218) = 0x80;
    LD32(gEftWeather, 0x21C) = 0x80;
    s0 = (s32)func_002768D8(6);   /* asm: el daddu s0,v0 esta en el delay slot del jal 276AC8 -> s0 = resultado de 2768D8 (un puntero), no el de 276AC8 */
    idx = (s32)func_00276AC8() - 1;
    if ((u32)idx < 0xF && (idx == 0 || idx == 4 || idx == 7 || idx == 13 || idx == 14)) {
        func_00145B20(s0);
    } else if (func_00276D00() != 0) {
        func_00145B20(s0);
    }

    ptr = (u8 *)(s32)LD32(D_003876A0, 4);
    if ((*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 47)) != 0) {
        ptr += 0x40;
    }
    a = LD32(ptr, 0x2C);
    a = (s32)(((u32)a >> 2) << 2);
    EftTexSet_Load32(gEftWeather + 8, ptr + a);

    r = BtlTask_CreateChildList(arg0, 1, 0x5A0);
    LD32(gEftWeather, 0) = r;
    gEftWeather[0x2B0] = 1;
    BtlTaskList_AddTail(r, (s32)D_00340200, 0);
}
