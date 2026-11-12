#include "common.h"

extern s32 D_003436A8 __attribute__((section(".data")));
extern s32 D_003436AC __attribute__((section(".data")));
extern s32 D_003436B0 __attribute__((section(".data")));
extern s32 D_003436B4 __attribute__((section(".data")));
extern s32 D_003436B8 __attribute__((section(".data")));
extern s32 D_003436BC __attribute__((section(".data")));
extern s32 D_003436C0 __attribute__((section(".data")));
extern s32 D_003436C4 __attribute__((section(".data")));
extern s32 D_003436C8 __attribute__((section(".data")));
extern s32 D_003436CC __attribute__((section(".data")));

/* 0x001F49E8: for arg0 = 0x28E..0x297 returns one of D_003436A8..CC and stores a code in *arg1 (1, 2, 2, 2, 1, 2,
 * 0, 1, 0, 0 in that order; the cases 0x294, 0x296 and 0x297 store 0). Other arg0: returns 0 and stores nothing. */
static s32 func_001F49E8_real(s32 arg0, s32 *arg1);
void bt2_fightlog_note(const char *fmt, ...);
/* B10 log temporal: id de tarea de tecnica pedido, clase devuelta y codigo */
s32 func_001F49E8(s32 arg0, s32 *arg1) {
    s32 r = func_001F49E8_real(arg0, arg1);
    bt2_fightlog_note("B10 TAREA-ID %X -> clase %08X cod %d (desde %p)", arg0, r, *arg1, __builtin_return_address(0));
    return r;
}
static s32 func_001F49E8_real(s32 arg0, s32 *arg1) {
    switch (arg0 - 0x28E) {
        case 0:
            *arg1 = 1;
            return D_003436A8;
        case 1:
            *arg1 = 2;
            return D_003436AC;
        case 2:
            *arg1 = 2;
            return D_003436B0;
        case 3:
            *arg1 = 2;
            return D_003436B4;
        case 4:
            *arg1 = 1;
            return D_003436B8;
        case 5:
            *arg1 = 2;
            return D_003436BC;
        case 6:
            *arg1 = 0;
            return D_003436C0;
        case 7:
            *arg1 = 1;
            return D_003436C4;
        case 8:
            *arg1 = 0;
            return D_003436C8;
        case 9:
            *arg1 = 0;
            return D_003436CC;
        default:
            return 0;
    }
}
