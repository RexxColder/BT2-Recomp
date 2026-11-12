/* Lector ISO9660 mínimo para el instalador de BT2.
 *
 * Sin libarchive, sin montar la imagen, sin 7z: lee el volumen descriptor en el sector 16, recorre los
 * directory records desde el directorio raíz y anota el offset y el tamaño de cada archivo. Soporta
 * archivos en varios extents (flag 0x80), que en BT2 no aparecen pero son baratos de manejar.
 *
 * Los offsets son de 64 bits: los AFS del juego pasan de 1 GB y un long de 32 bits truncaría.
 */
#ifndef BT2_ISO_H
#define BT2_ISO_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ISO_MAX_EXTENTS 8
#define ISO_MAX_FILES 1024
#define ISO_PATH_MAX 512

typedef struct {
    uint64_t offset;
    uint64_t size;
} IsoExtent;

typedef struct {
    char path[ISO_PATH_MAX];
    IsoExtent ext[ISO_MAX_EXTENTS];
    int nextents;
    uint64_t size;      /* suma de los extents */
    int open_multi;     /* interno: el último record tenía el bit multi-extent */
} IsoFile;

typedef struct {
    FILE *f;
    uint64_t bytes;
    char volume_id[33];
    IsoFile files[ISO_MAX_FILES];
    int count;
} Iso;

/* Abre y recorre la imagen. Devuelve 0 si es ISO9660; -1 con `err` cargado si no. */
int iso_open(Iso *iso, const char *path, char *err, size_t errsz);
void iso_close(Iso *iso);

/* Búsqueda sin distinguir mayúsculas. NULL si no está. */
const IsoFile *iso_find(const Iso *iso, const char *path);

/* Lee `n` bytes en `offset`; devuelve 0 o -1 con `err` cargado. */
int iso_read(Iso *iso, uint64_t offset, void *buf, size_t n, char *err, size_t errsz);

#ifdef __cplusplus
}
#endif

#endif /* BT2_ISO_H */
