#include "common.h"

extern u8 D_00387E80[];
extern u8 D_43058F[];
extern u8 D_0038BDF0[];
extern s32 D_0038B980[];
extern void func_00100000(void);
extern void func_00100250(void);
extern void func_00338520(void);
extern s32 func_00100388(s32 argc, s32 *argv);
extern s32 Syscall_0x3C();
extern s32 Syscall_0x3D();
extern s32 FlushCache(s32 mode);
extern void exit(s32 code);
extern void atexit();

/* 0x00100008 func_00100008 = _start (crt0; renamed to avoid clashing with libc crt1). Omitted (no C form, no effect on the port): the initial clearing of every GPR, FPR,
 * HI/LO and the FCSR. Clears the bss (D_00387E80 .. D_43058F: bytes to 16-byte alignment, quadwords, tail
 * bytes), SetupThread / SetupHeap syscalls, FlushCache, ei, then exit(main(argc, argv)). The weak ctor hook and
 * atexit hook slots were linked as 0 in this image (beqz skips). */
void func_00100008(void) {
    u8 *p = D_00387E80;
    u8 *quadEnd;
    u8 *sp;

    while (((u32)p & 0xF) != 0) {
        *(volatile u8 *)p = 0;
        p++;
    }
    quadEnd = (u8 *)((u32)D_43058F & 0xFFFFFFF0);
    while (p != quadEnd) {
        ((volatile u32 *)p)[0] = 0;
        ((volatile u32 *)p)[1] = 0;
        ((volatile u32 *)p)[2] = 0;
        ((volatile u32 *)p)[3] = 0;
        p += 16;
    }
    while (p != D_43058F) {
        *(volatile u8 *)p = 0;
        p++;
    }
    sp = (u8 *)Syscall_0x3C(D_0038BDF0, -1, func_00100000, D_0038B980, func_00100250);
    Syscall_0x3D(D_43058F, -1);
    func_00338520();
    FlushCache(0);
    exit(func_00100388(D_0038B980[0], D_0038B980 + 1));
}
