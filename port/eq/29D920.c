#include "common.h"
#include "vu0_state.h"

void bt2_fightlog_note(const char *fmt, ...);

/* Vu0Screen_StoreMtx(a0): store vf24..vf27 to a0 +0x0, +0x10, +0x20, +0x30. */
void Vu0Screen_StoreMtx(u8 *arg0) {
    if ((unsigned long)arg0 < 0x1000) {   /* diagnostico: puntero nulo + desplazamiento (crash cvc-091058, arg0 0xB0) */
        static int told;
        if (told++ < 5) bt2_fightlog_note("NULO Vu0Screen_StoreMtx arg0 %p desde %p", arg0, __builtin_return_address(0));
        return;
    }
    memcpy(arg0 + 0x00, gVu0.vf[24], 16);
    memcpy(arg0 + 0x10, gVu0.vf[25], 16);
    memcpy(arg0 + 0x20, gVu0.vf[26], 16);
    memcpy(arg0 + 0x30, gVu0.vf[27], 16);
}
