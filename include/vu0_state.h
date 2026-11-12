#ifndef VU0_STATE_H
#define VU0_STATE_H
/* VU0 macro-mode state for the PC build: functions that keep values in vf/vi registers across calls
 * (the game's vector library) read and write it here instead of the coprocessor. vf[0] = (0,0,0,1). */
#include "common.h"
typedef struct Vu0State {
    f32 vf[32][4];
    f32 acc[4];
    s32 vi[16];
    f32 q;
    f32 i;
    u32 r;             /* VU0 R register (vrinit / vrxor) */
    u8 mem[0x1000];    /* VU0 data memory (vsqi/vlqd stack at vi15, 16-byte units, & 0xFF) */
} Vu0State;
extern Vu0State gVu0;
#endif
