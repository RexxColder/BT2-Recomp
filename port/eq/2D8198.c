#include "common.h"

char *strncpy(char *d, const char *s, u32 n);
extern s32 D_0037AE30[];
extern s32 D_0037AE48[];
extern s32 D_0037AE60[];

/* 0x002D8198: arg1 is three s32 indices; copy the first char of the string picked by each index from three
 * 2-entry pointer tables to arg0+2, arg0+3, arg0+4. */
void func_002D8198(u8 *arg0, s32 *arg1) {
    strncpy((char *)(arg0 + 2), (const char *)D_0037AE30[arg1[0]], 1);
    strncpy((char *)(arg0 + 3), (const char *)D_0037AE48[arg1[1]], 1);
    strncpy((char *)(arg0 + 4), (const char *)D_0037AE60[arg1[2]], 1);
}
