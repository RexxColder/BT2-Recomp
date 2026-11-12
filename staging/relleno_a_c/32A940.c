#include "common.h"

/* 0x0032A940 std (newlib findfp.c): inicializa un FILE estándar. _p (+0) = _r (+4) = _w (+8) = 0,
 * _flags (+0xC, s16) = flags, _file (+0xE, s16) = file, _bf._base (+0x10) = _bf._size (+0x14) =
 * _lbfsize (+0x18) = 0, _cookie (+0x1C) = fp, _read/_write/_seek/_close (+0x20..0x2C) = __sread,
 * __swrite, __sseek, __sclose (func_0032CDE0), _data (+0x54) = data.
 * Las funciones se guardan con su DIRECCIÓN PS2 (el original guarda esas direcciones; en el port el jmp de
 * full_patch_range las lleva a la versión que corresponda, y así nada compara contra una dirección de PC).
 * Las direcciones salen de config/symbols/sdk.txt (y de los bytes lui/addiu del asm). */
#define ADDR___sread  0x0032CC90u
#define ADDR___swrite 0x0032CCF8u
#define ADDR___sseek  0x0032CD78u
#define ADDR___sclose 0x0032CDE0u

void std(u8 *fp, s32 flags, s32 file, u8 *data) {
    *(u8 **)(fp + 0x54) = data;
    *(s16 *)(fp + 0xC) = (s16)flags;
    *(s16 *)(fp + 0xE) = (s16)file;
    *(u32 *)(fp + 0x20) = ADDR___sread;
    *(u32 *)(fp + 0x24) = ADDR___swrite;
    *(u32 *)(fp + 0x28) = ADDR___sseek;
    *(u32 *)(fp + 0x2C) = ADDR___sclose;
    *(s32 *)(fp + 0x0) = 0;
    *(s32 *)(fp + 0x4) = 0;
    *(s32 *)(fp + 0x8) = 0;
    *(s32 *)(fp + 0x10) = 0;
    *(s32 *)(fp + 0x14) = 0;
    *(s32 *)(fp + 0x18) = 0;
    *(u8 **)(fp + 0x1C) = fp;
}
