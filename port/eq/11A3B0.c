#include "common.h"

extern u8 *D_003876A0;
extern u8 D_0036CB98[] __attribute__((section(".data")));

u8 *func_0010B078(void);
s32 func_0020A908(s32 arg0);
s32 BtlCtrl_IsInterruptible(s32 arg0);
s32 BtlObjVis_GetView(s32 arg0);
s32 func_00119F30(u8 *arg0, s32 arg1, s32 arg2);
s32 func_0029D548(void);
void func_0029D580(s32 arg0);

void bt2_fightlog_note(const char *fmt, ...);
extern unsigned gPortVBlanks;
void func_0011A3B0(void) {
    u8 buf[24];
    u8 *base;
    u8 *dst;
    u8 *res;
    u8 *src;
    s32 i;
    s32 n;
    s64 flags;
    s32 r;
    s32 view;

    base = func_0010B078();
    memcpy(buf, D_0036CB98, 24);
    flags = *(s64 *)(D_003876A0 + 0x4D8);
    n = ((flags & 0x2) == 0) ? 1 : 2;
    if ((flags & 0x100) != 0) {
        if (gPortVBlanks % 30 == 0) bt2_fightlog_note("RADAR omitido (flags 0x100)");
        return;
    }
    if (n != 1 &&
        (func_0020A908(0) != 0 || func_0020A908(1) != 0 || BtlCtrl_IsInterruptible(0) != 0 ||
         BtlCtrl_IsInterruptible(1) != 0)) {
        *(f32 *)(buf + 0x10) = 428.0f;
    }

    i = 0;
    dst = base + 0x10F0;
    res = base + 0x10C8;
    src = buf + 8;
    base = base + 0x10C0;
    do {
        if (n == 1) {
            memcpy(dst, buf, 8);
        } else {
            memcpy(dst, src, 8);
        }
        dst += 0x38;
        func_0029D548();
        src += 8;
        func_0029D548();
        view = BtlObjVis_GetView(i);
        r = func_00119F30(base, i, view);
        i++;
        base += 0x38;
        *(s32 *)res = r;
        if (gPortVBlanks % 30 == 0)   /* logging del radar */
            bt2_fightlog_note("RADAR J%d view %08X -> %d (obj kind %d dir %d fade %d)", i, view, r, *(u8 *)(base - 0x38),
                              *(s32 *)(base - 0x38 + 4), *(s32 *)(base - 0x38 + 0xC));
        res += 0x38;
        func_0029D580(1);
        func_0029D580(1);
    } while (i < n);
}
