#include "common.h"

s32 __sfvwrite(u8 *fp, u8 *uio);

/* 0x00326980 __sprint (newlib, vfprintf.c): vuelca el uio pendiente. uio->uio_resid (+8) == 0 ->
 * uio_iovcnt (+4) = 0 y 0. Si no: err = __sfvwrite(fp, uio); resid = iovcnt = 0; devuelve err.
 * arg0 (struct _reent *) no se usa. */
s32 __sprint(u8 *ptr, u8 *fp, u8 *uio) {
    s32 err;

    (void)ptr;
    if (*(s32 *)(uio + 8) == 0) {
        *(s32 *)(uio + 4) = 0;
        return 0;
    }
    err = __sfvwrite(fp, uio);
    *(s32 *)(uio + 4) = 0;
    *(s32 *)(uio + 8) = 0;
    return err;
}
