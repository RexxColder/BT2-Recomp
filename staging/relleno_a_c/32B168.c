#include "common.h"

void *memmove(void *d, const void *s, u32 n);
void *memchr(const void *s, s32 c, u32 n);
s32 __swsetup(u8 *fp);
s32 func_0032A828(u8 *fp);   /* fflush de la EE (0x0032A828): por dirección; el nombre "fflush" es el del host */

/* FILE de newlib (EE): _p +0, _r +4, _w +8, _flags +0xC (u16), _bf._base +0x10, _bf._size +0x14,
 * _cookie +0x1C, _write +0x24. uio: iov +0, iovcnt +4, resid +8. iov: base +0, len +4. */
#define FP_P(fp)     (*(u8 **)((fp) + 0x0))
#define FP_W(fp)     (*(s32 *)((fp) + 0x8))
#define FP_FLAGS(fp) (*(u16 *)((fp) + 0xC))
#define FP_BASE(fp)  (*(u8 **)((fp) + 0x10))
#define FP_SIZE(fp)  (*(s32 *)((fp) + 0x14))
#define FP_WRITE(fp, p, n) (((s32 (*)(s32, u8 *, s32))(*(s32 *)((fp) + 0x24)))(*(s32 *)((fp) + 0x1C), (p), (n)))
#define UIO_RESID(u) (*(s32 *)((u) + 0x8))

/* 0x0032B168 __sfvwrite (newlib fvwrite.c, versión sin realloc de __SSTR). Escribe el uio en fp:
 *  - resid == 0 -> 0; sin poder escribir (!__SWR o _bf._base NULL) y __swsetup falla -> EOF.
 *  - __SNBF (2): escribe por _write en trozos de hasta BUFSIZ (0x400).
 *  - !__SLBF (1): totalmente con buffer; __SSTR (0x200) copia lo que entra en _w y "finge" haber copiado todo.
 *  - __SLBF: con buffer por líneas (memchr '\n', fflush al cruzar el salto).
 *  - error: _flags |= __SERR (0x40), EOF.
 * Comparaciones como en el asm: len vs _w / _bf._size SIN signo en el caso de buffer completo; s vs w CON signo
 * en el de línea; _p > _bf._base sin signo. fflush es el de la EE (func_0032A828). */
s32 __sfvwrite(u8 *fp, u8 *uio) {
    u8 *iov;
    u8 *p = NULL;
    u32 len;
    s32 w;
    s32 s;
    s32 nlknown;
    s32 nldist = 0;

    if (UIO_RESID(uio) == 0) {
        return 0;
    }
    if (!(FP_FLAGS(fp) & 8) || FP_BASE(fp) == NULL) {
        if (__swsetup(fp) != 0) {
            return -1;
        }
    }
    iov = *(u8 **)(uio + 0);
    len = 0;
    if (FP_FLAGS(fp) & 2) {
        do {
            while (len == 0) {
                p = *(u8 **)(iov + 0);
                len = *(u32 *)(iov + 4);
                iov += 8;
            }
            w = FP_WRITE(fp, p, (len <= 0x400) ? (s32)len : 0x400);
            if (w <= 0) {
                goto err;
            }
            p += w;
            len -= w;
        } while ((UIO_RESID(uio) -= w) != 0);
    } else if (!(FP_FLAGS(fp) & 1)) {
        do {
            while (len == 0) {
                p = *(u8 **)(iov + 0);
                len = *(u32 *)(iov + 4);
                iov += 8;
            }
            w = FP_W(fp);
            if (FP_FLAGS(fp) & 0x200) {
                if (len < (u32)w) {
                    w = len;
                }
                memmove(FP_P(fp), p, w);
                FP_W(fp) -= w;
                FP_P(fp) += w;
                w = len;
            } else if ((u32)FP_P(fp) > (u32)FP_BASE(fp) && len > (u32)w) {
                memmove(FP_P(fp), p, w);
                FP_P(fp) += w;
                if (func_0032A828(fp) != 0) {
                    goto err;
                }
            } else if (len >= (u32)(w = FP_SIZE(fp))) {
                w = FP_WRITE(fp, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = len;
                memmove(FP_P(fp), p, w);
                FP_W(fp) -= w;
                FP_P(fp) += w;
            }
            p += w;
            len -= w;
        } while ((UIO_RESID(uio) -= w) != 0);
    } else {
        nlknown = 0;
        do {
            while (len == 0) {
                nlknown = 0;
                p = *(u8 **)(iov + 0);
                len = *(u32 *)(iov + 4);
                iov += 8;
            }
            if (!nlknown) {
                u8 *nl = memchr(p, '\n', len);
                nldist = (nl != NULL) ? (s32)(nl + 1 - p) : (s32)len + 1;
                nlknown = 1;
            }
            s = (len < (u32)nldist) ? (s32)len : nldist;
            w = FP_W(fp) + FP_SIZE(fp);
            if ((u32)FP_P(fp) > (u32)FP_BASE(fp) && s > w) {
                memmove(FP_P(fp), p, w);
                FP_P(fp) += w;
                if (func_0032A828(fp) != 0) {
                    goto err;
                }
            } else if (s >= (w = FP_SIZE(fp))) {
                w = FP_WRITE(fp, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = s;
                memmove(FP_P(fp), p, w);
                FP_W(fp) -= w;
                FP_P(fp) += w;
            }
            if ((nldist -= w) == 0) {
                if (func_0032A828(fp) != 0) {
                    goto err;
                }
                nlknown = 0;
            }
            p += w;
            len -= w;
        } while ((UIO_RESID(uio) -= w) != 0);
    }
    return 0;

err:
    FP_FLAGS(fp) |= 0x40;
    return -1;
}
