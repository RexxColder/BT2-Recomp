/* SHA-1 (FIPS 180-1). Implementación propia y chica; no se usa para seguridad, sólo para comparar
 * el programa del disco con el de la edición USA sin modificar. */
#include "sha1.h"

#include <stdio.h>
#include <string.h>

static uint32_t rol(uint32_t v, int n)
{
    return (v << n) | (v >> (32 - n));
}

static void compress(Bt2Sha1 *s)
{
    uint32_t w[80];
    uint32_t a = s->h[0], b = s->h[1], c = s->h[2], d = s->h[3], e = s->h[4];
    int i;

    for (i = 0; i < 16; i++) {
        w[i] = ((uint32_t)s->block[i * 4] << 24) | ((uint32_t)s->block[i * 4 + 1] << 16) |
               ((uint32_t)s->block[i * 4 + 2] << 8) | (uint32_t)s->block[i * 4 + 3];
    }
    for (i = 16; i < 80; i++) {
        w[i] = rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    }
    for (i = 0; i < 80; i++) {
        uint32_t f, k, t;
        if (i < 20) {
            f = (b & c) | (~b & d);
            k = 0x5A827999u;
        } else if (i < 40) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1u;
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDCu;
        } else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6u;
        }
        t = rol(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = rol(b, 30);
        b = a;
        a = t;
    }
    s->h[0] += a;
    s->h[1] += b;
    s->h[2] += c;
    s->h[3] += d;
    s->h[4] += e;
}

void bt2_sha1_init(Bt2Sha1 *s)
{
    s->h[0] = 0x67452301u;
    s->h[1] = 0xEFCDAB89u;
    s->h[2] = 0x98BADCFEu;
    s->h[3] = 0x10325476u;
    s->h[4] = 0xC3D2E1F0u;
    s->total = 0;
    s->fill = 0;
}

void bt2_sha1_update(Bt2Sha1 *s, const void *data, size_t n)
{
    const unsigned char *p = (const unsigned char *)data;

    s->total += n;
    while (n > 0) {
        size_t take = 64 - s->fill;
        if (take > n) {
            take = n;
        }
        memcpy(s->block + s->fill, p, take);
        s->fill += take;
        p += take;
        n -= take;
        if (s->fill == 64) {
            compress(s);
            s->fill = 0;
        }
    }
}

void bt2_sha1_final(Bt2Sha1 *s, char hex[41])
{
    uint64_t bits = s->total * 8;
    unsigned char pad = 0x80, zero = 0, len[8];
    int i;

    bt2_sha1_update(s, &pad, 1);
    while (s->fill != 56) {
        bt2_sha1_update(s, &zero, 1);
    }
    for (i = 0; i < 8; i++) {
        len[i] = (unsigned char)(bits >> (56 - i * 8));
    }
    bt2_sha1_update(s, len, 8);
    for (i = 0; i < 5; i++) {
        snprintf(hex + i * 8, 9, "%08x", s->h[i]);
    }
    hex[40] = '\0';
}
