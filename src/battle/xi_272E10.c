#include "m2c_macros.h"

M2C_UNK func_003126C8(s32, void *);                 /* extern */
s32 rand();                                         /* extern */
extern u8 gStgDbgPlaces __attribute__((section(".data")));

// Picks a random place index 0..5 (stride 0x20) and passes the two entries at +0 and +0x10 to func_003126C8.
void StgDbg_PickRandomPlace(s32 arg0, s32 arg1) {
    s32 temp_s1;

    temp_s1 = (rand() % 6) << 5;
    func_003126C8(arg0, (u8 *)&gStgDbgPlaces + temp_s1);
    func_003126C8(arg1, (u8 *)&gStgDbgPlaces + temp_s1 + 0x10);
}
