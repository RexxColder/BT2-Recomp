#include "common.h"

s32 Rand_Range();
s32 func_002B8280(s32 arg0, s32 arg1, s32 arg2);
void func_002BACC8(s32 arg0);
void func_002BAD68(s32 arg0, s32 arg1);
void func_002BAF70(s32 arg0, s32 arg1, s32 arg2);
void func_002FFF90(s32 arg0);
extern u8 D_00379CB8[] __attribute__((section(".data")));

void Port_MovieStartAfs(s32 ptid, s32 flid);

void func_002BB038(s32 arg0, s32 arg1, s32 arg2) {
    /* CRI fuera de juego: el preview del escenario es una pelicula del AFS (ptid, flid); la reproduce el HLE de
       port/full/plat_movie.c (Port_MovieStartAfs). El handle real no existe en el port. */
    (void)arg0;
    Port_MovieStartAfs(arg1, arg2);
}
