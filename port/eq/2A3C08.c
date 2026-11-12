#include "common.h"

extern u8 D_003B0F40[] __attribute__((section(".data")));

/* 0x002A3C08: fin del buffer de texto asignado al slot arg0 (NULL si nunca se asigno).
 * En la PS2 un slot nulo lee la direccion 4 de la RAM (vectores) y devuelve basura;
 * en el host la pagina cero no esta mapeada, asi que devolvemos NULL y el llamador
 * omite lo que necesitaba esos datos. */
s32 *func_002A3C08(s32 arg0) {
    u8 *b;

    if (arg0 < 0 || arg0 >= 8) {
        return NULL;
    }
    b = (u8 *)*(s32 *)(D_003B0F40 + 4 + arg0 * 4);
    if (b == NULL) {
        return NULL;
    }
    return (s32 *)(b + ((*(u32 *)(b + 4)) & ~3u));
}
