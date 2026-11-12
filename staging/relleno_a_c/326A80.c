#include "common.h"

void __sinit(u8 *s);
s32 _vfprintf_r(u8 *data, u8 *fp, const char *fmt, u32 ap);
extern u8 *D_0036A600 __attribute__((section(".data")));

/* 0x00326A80 vfprintf (newlib): fp->_data (+0x54) NULL -> _impure_ptr (D_0036A600) y lo guarda en fp; si
 * data->__sdidinit (+0x38) == 0 -> __sinit(data); tail call _vfprintf_r(fp->_data, fp, fmt, ap) (se relee
 * fp->_data después de __sinit, como el asm).
 * ap es una va_list de la EE (puntero a ranuras de 8 bytes), no una va_list del host: por eso u32. */
s32 func_00326A80(u8 *fp, const char *fmt, u32 ap) {
    u8 *data = *(u8 **)(fp + 0x54);

    if (data == NULL) {
        data = D_0036A600;
        *(u8 **)(fp + 0x54) = data;
    }
    if (*(s32 *)(data + 0x38) == 0) {
        __sinit(data);
    }
    return _vfprintf_r(*(u8 **)(fp + 0x54), fp, fmt, ap);
}
