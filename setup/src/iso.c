#include "iso.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define ISO_SECTOR 2048u
#define ISO_MAX_DIR_BYTES (64u * 1024u * 1024u)
#define ISO_MAX_DEPTH 8

static uint32_t le32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static void set_err(char *err, size_t errsz, const char *text)
{
    if (err != NULL && errsz > 0) {
        snprintf(err, errsz, "%s", text);
    }
}

static IsoFile *find_mutable(Iso *iso, const char *path)
{
    int i;
    for (i = 0; i < iso->count; i++) {
        if (strcasecmp(iso->files[i].path, path) == 0) {
            return &iso->files[i];
        }
    }
    return NULL;
}

static int add_file(Iso *iso, const char *path, uint64_t offset, uint64_t size, int multi, char *err, size_t errsz)
{
    IsoFile *prev = find_mutable(iso, path);

    if (prev != NULL) {
        /* Mismo nombre: si el record anterior era multi-extent, este lo continúa. Si no, es un duplicado
         * raro (no debería pasar en un disco de PS2); nos quedamos con el primero. */
        if (prev->open_multi && prev->nextents < ISO_MAX_EXTENTS) {
            prev->ext[prev->nextents].offset = offset;
            prev->ext[prev->nextents].size = size;
            prev->nextents++;
            prev->size += size;
            prev->open_multi = multi;
        }
        return 0;
    }
    if (iso->count >= ISO_MAX_FILES) {
        set_err(err, errsz, "la imagen tiene demasiados archivos para el instalador (más de 1024).");
        return -1;
    }
    if (strlen(path) >= ISO_PATH_MAX) {
        set_err(err, errsz, "la imagen tiene un nombre de archivo demasiado largo.");
        return -1;
    }
    {
        IsoFile *f = &iso->files[iso->count++];
        memset(f, 0, sizeof(*f));
        snprintf(f->path, sizeof(f->path), "%s", path);
        f->ext[0].offset = offset;
        f->ext[0].size = size;
        f->nextents = 1;
        f->size = size;
        f->open_multi = multi;
    }
    return 0;
}

static int walk(Iso *iso, uint32_t lba, uint32_t size, const char *prefix, int depth, char *err, size_t errsz)
{
    unsigned char *data;
    uint64_t off = (uint64_t)lba * ISO_SECTOR;
    size_t pos = 0;

    if (depth > ISO_MAX_DEPTH) {
        return 0;
    }
    if (size == 0) {
        return 0;
    }
    if (size > ISO_MAX_DIR_BYTES) {
        set_err(err, errsz, "la imagen tiene un directorio anormalmente grande (imagen dañada).");
        return -1;
    }
    if (off > iso->bytes || (uint64_t)size > iso->bytes - off) {
        set_err(err, errsz, "el directorio de la imagen cae fuera del archivo (imagen incompleta o dañada).");
        return -1;
    }
    data = (unsigned char *)malloc(size);
    if (data == NULL) {
        set_err(err, errsz, "sin memoria para leer el directorio de la imagen.");
        return -1;
    }
    if (iso_read(iso, off, data, size, err, errsz) != 0) {
        free(data);
        return -1;
    }

    while (pos < (size_t)size) {
        unsigned char len = data[pos];
        uint32_t ext, nbytes;
        unsigned char flags, nlen;
        char name[256];
        char full[ISO_PATH_MAX];
        size_t nl;

        if (len == 0) {
            /* Los records no cruzan de sector: lo que queda del sector está vacío. */
            pos = (pos / ISO_SECTOR + 1) * ISO_SECTOR;
            continue;
        }
        if (len < 34 || pos + len > (size_t)size) {
            break; /* record truncado: se ignora el resto, como hacen los lectores tolerantes */
        }
        ext = le32(data + pos + 2);
        nbytes = le32(data + pos + 10);
        flags = data[pos + 25];
        nlen = data[pos + 32];
        if ((size_t)33 + nlen > (size_t)len) {
            break;
        }
        memcpy(name, data + pos + 33, nlen);
        name[nlen] = '\0';
        pos += len;

        if (nlen == 1 && (name[0] == 0 || name[0] == 1)) {
            continue; /* "." y ".." */
        }
        {
            char *semi = strchr(name, ';');
            if (semi != NULL) {
                *semi = '\0';
            }
        }
        nl = strlen(name);
        while (nl > 0 && name[nl - 1] == '.') {
            name[--nl] = '\0';
        }
        if (nl == 0) {
            continue;
        }
        if (snprintf(full, sizeof(full), "%s%s", prefix, name) >= (int)sizeof(full)) {
            set_err(err, errsz, "la imagen tiene una ruta demasiado larga.");
            free(data);
            return -1;
        }
        if (flags & 2) {
            char dirpath[ISO_PATH_MAX];
            if (snprintf(dirpath, sizeof(dirpath), "%s/", full) >= (int)sizeof(dirpath)) {
                set_err(err, errsz, "la imagen tiene una ruta demasiado larga.");
                free(data);
                return -1;
            }
            if (walk(iso, ext, nbytes, dirpath, depth + 1, err, errsz) != 0) {
                free(data);
                return -1;
            }
        } else if (add_file(iso, full, (uint64_t)ext * ISO_SECTOR, nbytes, (flags & 0x80) != 0, err, errsz) != 0) {
            free(data);
            return -1;
        }
    }
    free(data);
    return 0;
}

int iso_read(Iso *iso, uint64_t offset, void *buf, size_t n, char *err, size_t errsz)
{
    if (iso == NULL || iso->f == NULL) {
        set_err(err, errsz, "la imagen no está abierta.");
        return -1;
    }
    if (offset > iso->bytes || (uint64_t)n > iso->bytes - offset) {
        set_err(err, errsz, "la imagen del disco está incompleta (se intentó leer más allá del final).");
        return -1;
    }
    if (fseeko(iso->f, (off_t)offset, SEEK_SET) != 0) {
        set_err(err, errsz, "no se pudo reposicionar la lectura de la imagen del disco.");
        return -1;
    }
    if (fread(buf, 1, n, iso->f) != n) {
        set_err(err, errsz, "no se pudo leer la imagen del disco hasta el final (¿está incompleta?).");
        return -1;
    }
    return 0;
}

int iso_open(Iso *iso, const char *path, char *err, size_t errsz)
{
    unsigned char pvd[ISO_SECTOR];
    unsigned char *root;
    uint32_t root_lba, root_size;
    long end;

    memset(iso, 0, sizeof(*iso));
    if (path == NULL || path[0] == '\0') {
        set_err(err, errsz, "no se indicó la imagen del disco.");
        return -1;
    }
    iso->f = fopen(path, "rb");
    if (iso->f == NULL) {
        char msg[ISO_PATH_MAX + 128];
        snprintf(msg, sizeof(msg), "no se puede abrir la imagen \"%s\": %s.", path, strerror(errno));
        set_err(err, errsz, msg);
        return -1;
    }
    if (fseeko(iso->f, 0, SEEK_END) != 0 || (end = ftello(iso->f)) < 0) {
        set_err(err, errsz, "no se pudo medir la imagen del disco.");
        iso_close(iso);
        return -1;
    }
    iso->bytes = (uint64_t)end;
    if (iso->bytes < 17 * (uint64_t)ISO_SECTOR) {
        set_err(err, errsz, "este archivo no es una imagen de disco ISO9660 (.iso): es demasiado chico. "
                            "Los formatos comprimidos (.chd, .cso, .gz) hay que convertirlos a .iso primero.");
        iso_close(iso);
        return -1;
    }
    if (iso_read(iso, 16 * (uint64_t)ISO_SECTOR, pvd, sizeof(pvd), err, errsz) != 0) {
        iso_close(iso);
        return -1;
    }
    if (pvd[0] != 1 || memcmp(pvd + 1, "CD001", 5) != 0) {
        set_err(err, errsz, "este archivo no es una imagen de disco ISO9660 (.iso). "
                            "Los formatos comprimidos (.chd, .cso, .gz) hay que convertirlos a .iso primero.");
        iso_close(iso);
        return -1;
    }
    memcpy(iso->volume_id, pvd + 40, 32);
    iso->volume_id[32] = '\0';
    {
        size_t i;
        for (i = 0; i < 32; i++) {
            if (iso->volume_id[i] == '\0') {
                break;
            }
        }
        while (i > 0 && (iso->volume_id[i - 1] == ' ' || iso->volume_id[i - 1] == '\0')) {
            iso->volume_id[--i] = '\0';
        }
    }
    root = pvd + 156;
    if (root[0] < 34) {
        set_err(err, errsz, "la imagen tiene un directorio raíz inválido (imagen dañada).");
        iso_close(iso);
        return -1;
    }
    root_lba = le32(root + 2);
    root_size = le32(root + 10);
    if (root_size == 0 || (uint64_t)root_lba * ISO_SECTOR >= iso->bytes) {
        set_err(err, errsz, "la imagen tiene un directorio raíz inválido (imagen dañada).");
        iso_close(iso);
        return -1;
    }
    if (walk(iso, root_lba, root_size, "", 0, err, errsz) != 0) {
        iso_close(iso);
        return -1;
    }
    return 0;
}

void iso_close(Iso *iso)
{
    if (iso != NULL && iso->f != NULL) {
        fclose(iso->f);
        iso->f = NULL;
    }
}

const IsoFile *iso_find(const Iso *iso, const char *path)
{
    int i;
    if (iso == NULL || path == NULL) {
        return NULL;
    }
    for (i = 0; i < iso->count; i++) {
        if (strcasecmp(iso->files[i].path, path) == 0) {
            return &iso->files[i];
        }
    }
    return NULL;
}
