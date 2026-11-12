#include "common.h"

extern s32 D_00346E68;
extern u8 D_00346C28[] __attribute__((section(".data")));

void func_002DA708(s32 arg0, s32 arg1, s32 arg2);
void func_002C22F0(u8 *arg0);
void func_002CE2B0(s32 arg0);
void func_002CE318(s32 arg0);
void func_002CE3A0(s32 arg0);
void func_002C2FD8(u8 *arg0);
void func_002DA3A8(s32 arg0, s32 arg1, s32 arg2);
void func_002D0BB8(s32 arg0, s32 arg1);
s32 func_002BF8A0(s32 arg0, u8 *arg1, u8 *arg2);
void func_002D29C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002CF688(s32 arg0);
s32 func_002CE4E8(s32 arg0);

/* Allocates and initializes a 0x1F30-plus block from obj's size and span fields;
   the object header (0x44 bytes plus the word at 0x40) is copied into it. */
u8 *func_002CE080(u8 *obj, s32 arg1) {
    u8 *dst;
    s32 size;
    s32 span;

    size = *(s32 *)(obj + 0x3C);
    if (size == 0) {
        return NULL;
    }
    span = *(s32 *)(obj + 0x40);
    if ((u32)(span - 1) >= 0x6FA0) {
        return NULL;
    }
    if (D_00346E68 != 0 && D_00346E68 != span) {
        return NULL;
    }

    D_00346E68 = span;
    func_002DA708(size, 0, (s32)((u32)span >> 2));

    dst = (u8 *)(((u32)size + 31) & ~31u);
    *(s32 *)(obj + 0x4) = (s32)(((u32)*(s32 *)(obj + 0x4) + 31) & ~31u);
    *(s32 *)(dst + 0x4C) = 0;
    *(s32 *)(dst + 0x48) = 0;
    __builtin_memcpy(dst, obj, 0x44);
    *(s32 *)(dst + 0x40) = *(s32 *)(obj + 0x40);

    *(s32 *)(dst + 0x50) = 0;
    *(s32 *)(dst + 0x44) = 1;
    *(s32 *)(dst + 0x54) = 0;
    *(s32 *)(dst + 0x58) = 0;
    *(s32 *)(dst + 0x5C) = 0;
    *(s32 *)(dst + 0x60) = 0;

    func_002C22F0(dst + 0x78);
    func_002CE2B0((s32)(dst + 0x90C));
    func_002CE318((s32)(dst + 0x950));
    func_002CE3A0((s32)(dst + 0x36C0));
    func_002C2FD8(dst + 0x9F8);
    func_002DA3A8((s32)(dst + 0xA0C), (s32)D_00346C28, 0x190);
    func_002DA3A8((s32)(dst + 0xB9C), (s32)D_00346C28, 0x190);
    func_002D0BB8((s32)dst, (s32)(dst + 0xD30));
    if (func_002BF8A0((s32)dst, dst + 0x1310, obj) != 0) {
        return NULL;
    }
    func_002D29C8((s32)dst, (s32)(dst + 0x1F30), (s32)obj, arg1);
    func_002CF688((s32)(dst + 0x36B0));
    if (func_002CE4E8((s32)dst) != 0) {
        return NULL;
    }
    *(s32 *)(dst + 0x48) = 1;
    *(s32 *)(dst + 0x4C) = 1;
    return dst;
}
