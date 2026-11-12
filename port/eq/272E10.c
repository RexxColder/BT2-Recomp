#include "common.h"

extern u8 gStgDbgPlaces[];
extern s32 rand();
extern s32 func_003126C8();

/* Picks a random place (6 entries, 32 bytes each) and copies its two 16-byte halves to the outputs. */
s32 StgDbg_PickRandomPlace(s32 out0, s32 out1) {
    s32 idx = (rand() % 6) * 32;

    func_003126C8(out0, gStgDbgPlaces + idx);
    return func_003126C8(out1, gStgDbgPlaces + 0x10 + idx);
}
