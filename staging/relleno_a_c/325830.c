#include "common.h"

s32 vsprintf(u8 *arg0, const char *arg1, __builtin_va_list arg2);

/* 0x00325830 sprintf (newlib): el original arma un FILE de cadena en la pila (_flags = __SWR|__SSTR = 0x208,
 * _p = _bf._base = buf, _w = _bf._size = INT_MAX, _data = _impure_ptr D_0036A600), llama a vfprintf
 * (func_00326A80) con la va_list de la EE (ranuras de 8 bytes; vuelca a2..t3 y f12..f19), pone el 0 final y
 * devuelve el resultado de vfprintf.
 * En el port los llamadores son C nativo con varargs de x86-64, que la cadena de la EE no puede leer: se usa
 * vsprintf del host, como Rand_Range (port/eq/2BC568.c). ptr32.py pasa los punteros variádicos como de 8 bytes.
 * Con esto func_00326A80 / _vfprintf_r / __sprint / __sfvwrite dejan de correr desde sprintf. */
s32 func_00325830(u8 *buf, const char *fmt, ...) {
    __builtin_va_list ap;
    s32 r;

    __builtin_va_start(ap, fmt);
    r = vsprintf(buf, fmt, ap);
    __builtin_va_end(ap);
    return r;
}
