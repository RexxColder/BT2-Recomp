/* SHA-1 mínimo, para verificar el programa del disco sin depender de OpenSSL ni de comandos externos. */
#ifndef BT2_SHA1_H
#define BT2_SHA1_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t h[5];
    uint64_t total;
    unsigned char block[64];
    size_t fill;
} Bt2Sha1;

void bt2_sha1_init(Bt2Sha1 *s);
void bt2_sha1_update(Bt2Sha1 *s, const void *data, size_t n);
/* Deja el hash en hex[41] (40 caracteres + NUL) y reinicia el estado. */
void bt2_sha1_final(Bt2Sha1 *s, char hex[41]);

#endif /* BT2_SHA1_H */
