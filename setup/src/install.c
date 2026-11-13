#include "install.h"

#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <time.h>
#include <unistd.h>

#include "sha1.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define BT2_COPY_BUF (1u << 20)
#define BT2_SPACE_MARGIN (64ull << 20)

static const char *kRequired[] = {
    BT2_ELF_NAME,
    "SYSTEM.CNF",
    BT2_DBZP_NAME,
    "DATA/ZS2US_1.AFS",
    "DATA/ZS2US_2.AFS",
    "DATA/ZS2US.DIR",
    "DATA/LOGO_O.SFD",
    "DATA/ZS2USOP.SFD",
    "DATA/ZS2USED.SFD",
};

typedef struct {
    const IsoFile *f;
    const Iso *iso;
    int eu;
} PlanItem;

typedef struct {
    PlanItem items[ISO_MAX_FILES + 1];
    int count;
} Plan;

typedef struct {
    Bt2EventFn fn;
    void *user;
    Bt2CancelFn cancel;
    void *cancel_user;
    int steps;
    int files_total;
    int files_done;
    int copied;
    int skipped;
    uint64_t total_bytes;
    uint64_t done_bytes;
} Ctx;

static void emit_error(Ctx *c, int code, const char *fmt, ...)
{
    char msg[1400];
    va_list ap;
    Bt2Event ev;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);
    if (c == NULL || c->fn == NULL) {
        return;
    }
    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_ERROR;
    ev.code = code;
    ev.message = msg;
    ev.files_done = c->files_done;
    ev.files_total = c->files_total;
    ev.done_bytes = c->done_bytes;
    ev.total_bytes = c->total_bytes;
    c->fn(&ev, c->user);
}

static int cancelled(const Ctx *c)
{
    return c != NULL && c->cancel != NULL && c->cancel(c->cancel_user) != 0;
}

void bt2_human_bytes(uint64_t n, char *out, size_t outsz)
{
    /* Decimal, como los tamaños de disco y el README (2,98 GB = 2.977.184.094 bytes). */
    if (n >= 1000000000ull) {
        snprintf(out, outsz, "%.2f GB", (double)n / 1e9);
    } else if (n >= 1000000ull) {
        snprintf(out, outsz, "%.1f MB", (double)n / 1e6);
    } else if (n >= 1000ull) {
        snprintf(out, outsz, "%.1f KB", (double)n / 1e3);
    } else {
        snprintf(out, outsz, "%llu B", (unsigned long long)n);
    }
}

static int starts_with_ci(const char *s, const char *prefix)
{
    return strncasecmp(s, prefix, strlen(prefix)) == 0;
}

static const char *base_name(const char *path)
{
    const char *slash = strrchr(path, '/');
    return slash != NULL ? slash + 1 : path;
}

static int is_elf_name(const char *path)
{
    return strcasecmp(path, BT2_ELF_NAME) == 0;
}

static int is_dbzp_name(const char *path)
{
    return strcasecmp(path, BT2_DBZP_NAME) == 0;
}

static int wanted_file(const char *path)
{
    return is_elf_name(path) || strcasecmp(path, "SYSTEM.CNF") == 0 || starts_with_ci(path, "BIN/") ||
           starts_with_ci(path, "DATA/") || starts_with_ci(path, "IRX/");
}

static int cmp_plan(const void *a, const void *b)
{
    const PlanItem *pa = (const PlanItem *)a;
    const PlanItem *pb = (const PlanItem *)b;
    return strcmp(pa->f->path, pb->f->path);
}

static void plan_build(Plan *plan, const Iso *iso)
{
    int i;
    plan->count = 0;
    for (i = 0; i < iso->count; i++) {
        if (wanted_file(iso->files[i].path)) {
            PlanItem *it = &plan->items[plan->count++];
            it->f = &iso->files[i];
            it->iso = iso;
            it->eu = 0;
        }
    }
    qsort(plan->items, (size_t)plan->count, sizeof(plan->items[0]), cmp_plan);
    for (i = 0; i < plan->count; i++) {
        if (is_elf_name(plan->items[i].f->path)) {
            PlanItem tmp = plan->items[0];
            plan->items[0] = plan->items[i];
            plan->items[i] = tmp;
            break;
        }
    }
}

/* Región detectada por los nombres de los programas. 0 USA, 1 PAL, 2 Japón, 3 otra. */
static int detect_region(const Iso *iso, char *detail, size_t detailsz)
{
    int i;
    int region = 3;
    const char *found = NULL;

    detail[0] = '\0';
    for (i = 0; i < iso->count; i++) {
        const char *name = base_name(iso->files[i].path);
        if (starts_with_ci(name, "SLES_")) {
            region = 1;
            found = name;
            break;
        }
        if (starts_with_ci(name, "SLPS_") || starts_with_ci(name, "SLPM_") || starts_with_ci(name, "SLED_")) {
            region = 2;
            found = name;
            break;
        }
        if (starts_with_ci(name, "SLUS_") && found == NULL) {
            region = 3;
            found = name;
        }
    }
    if (found != NULL) {
        snprintf(detail, detailsz, "%s", found);
    }
    return region;
}

static int missing_required(const Iso *iso, char *out, size_t outsz)
{
    int i, n = 0;
    size_t used = 0;
    out[0] = '\0';
    for (i = 0; i < (int)(sizeof(kRequired) / sizeof(kRequired[0])); i++) {
        if (iso_find(iso, kRequired[i]) == NULL) {
            int w = snprintf(out + used, outsz > used ? outsz - used : 0, "%s%s", n == 0 ? "" : "\n", kRequired[i]);
            if (w > 0 && used + (size_t)w < outsz) {
                used += (size_t)w;
            }
            n++;
        }
    }
    return n;
}

static int regular_size(const char *path, uint64_t *size)
{
    struct stat st;
    if (stat(path, &st) != 0 || !S_ISREG(st.st_mode)) {
        return -1;
    }
    *size = (uint64_t)st.st_size;
    return 0;
}

static int hash_path(const char *path, char hex[41], char *err, size_t errsz)
{
    FILE *f = fopen(path, "rb");
    Bt2Sha1 sha;
    unsigned char *buf;
    size_t n;

    if (f == NULL) {
        snprintf(err, errsz, "no se puede leer %s: %s.", path, strerror(errno));
        return -1;
    }
    buf = (unsigned char *)malloc(BT2_COPY_BUF);
    if (buf == NULL) {
        fclose(f);
        snprintf(err, errsz, "sin memoria para verificar %s.", path);
        return -1;
    }
    bt2_sha1_init(&sha);
    while ((n = fread(buf, 1, BT2_COPY_BUF, f)) > 0) {
        bt2_sha1_update(&sha, buf, n);
    }
    if (ferror(f)) {
        free(buf);
        fclose(f);
        snprintf(err, errsz, "no se pudo leer %s hasta el final.", path);
        return -1;
    }
    free(buf);
    fclose(f);
    bt2_sha1_final(&sha, hex);
    return 0;
}

static int hash_iso_file(const Iso *iso_mut, const IsoFile *f, char hex[41], char *err, size_t errsz)
{
    Iso *iso = (Iso *)iso_mut;
    Bt2Sha1 sha;
    unsigned char *buf;
    int e;
    char readerr[512];

    buf = (unsigned char *)malloc(BT2_COPY_BUF);
    if (buf == NULL) {
        snprintf(err, errsz, "sin memoria para verificar %s.", f->path);
        return -1;
    }
    bt2_sha1_init(&sha);
    for (e = 0; e < f->nextents; e++) {
        uint64_t left = f->ext[e].size;
        uint64_t off = f->ext[e].offset;
        while (left > 0) {
            size_t n = left > BT2_COPY_BUF ? BT2_COPY_BUF : (size_t)left;
            if (iso_read(iso, off, buf, n, readerr, sizeof(readerr)) != 0) {
                free(buf);
                snprintf(err, errsz, "%s", readerr);
                return -1;
            }
            bt2_sha1_update(&sha, buf, n);
            off += n;
            left -= n;
        }
    }
    free(buf);
    bt2_sha1_final(&sha, hex);
    return 0;
}

static int get_free_space(const char *dest, uint64_t *free_bytes)
{
    char probe[PATH_MAX];
    struct statvfs vfs;

    if (dest == NULL || dest[0] == '\0') {
        return -1;
    }
    if (strlen(dest) >= sizeof(probe)) {
        return -1;
    }
    snprintf(probe, sizeof(probe), "%s", dest);
    for (;;) {
        if (statvfs(probe, &vfs) == 0) {
            *free_bytes = (uint64_t)vfs.f_bavail * (uint64_t)vfs.f_frsize;
            return 0;
        }
        {
            char *slash = strrchr(probe, '/');
            if (slash == NULL) {
                break;
            }
            if (slash == probe) {
                probe[1] = '\0';
            } else {
                *slash = '\0';
            }
        }
    }
    if (statvfs(".", &vfs) == 0) {
        *free_bytes = (uint64_t)vfs.f_bavail * (uint64_t)vfs.f_frsize;
        return 0;
    }
    return -1;
}

static int mkdir_p(const char *path, char *err, size_t errsz)
{
    char tmp[PATH_MAX];
    size_t len, i;

    if (path == NULL || path[0] == '\0' || strcmp(path, ".") == 0) {
        return 0;
    }
    len = strlen(path);
    if (len >= sizeof(tmp)) {
        snprintf(err, errsz, "ruta demasiado larga: %s", path);
        return -1;
    }
    memcpy(tmp, path, len + 1);
    while (len > 1 && tmp[len - 1] == '/') {
        tmp[--len] = '\0';
    }
    for (i = 1; i < len; i++) {
        if (tmp[i] == '/') {
            char saved = tmp[i];
            tmp[i] = '\0';
            if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
                snprintf(err, errsz, "no se puede crear la carpeta %s: %s.", tmp, strerror(errno));
                return -1;
            }
            tmp[i] = saved;
        }
    }
    if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
        snprintf(err, errsz, "no se puede crear la carpeta %s: %s.", tmp, strerror(errno));
        return -1;
    }
    {
        struct stat st;
        if (stat(tmp, &st) != 0 || !S_ISDIR(st.st_mode)) {
            snprintf(err, errsz, "%s existe pero no es una carpeta.", tmp);
            return -1;
        }
    }
    return 0;
}

static void path_dirname(const char *path, char *out, size_t outsz)
{
    const char *slash = strrchr(path, '/');
    if (slash == NULL) {
        snprintf(out, outsz, ".");
    } else if (slash == path) {
        snprintf(out, outsz, "/");
    } else {
        size_t n = (size_t)(slash - path);
        if (n >= outsz) {
            n = outsz - 1;
        }
        memcpy(out, path, n);
        out[n] = '\0';
    }
}

static void json_escape(FILE *f, const char *s)
{
    const unsigned char *p = (const unsigned char *)s;
    while (*p != '\0') {
        switch (*p) {
        case '\\': fputs("\\\\", f); break;
        case '"': fputs("\\\"", f); break;
        case '\n': fputs("\\n", f); break;
        case '\r': fputs("\\r", f); break;
        case '\t': fputs("\\t", f); break;
        default:
            if (*p < 0x20) {
                fprintf(f, "\\u%04x", *p);
            } else {
                fputc(*p, f);
            }
            break;
        }
        p++;
    }
}

static double now_seconds(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

/* Copia un archivo del plan (o lo saltea si ya está completo). Devuelve 0, 1, 2 (cancelado) o 3 (hash). */
static int copy_plan_item(Ctx *c, const char *dest, const PlanItem *it, int force, char elf_hex[41])
{
    const IsoFile *f = it->f;
    Iso *iso = (Iso *)it->iso;
    char dst[PATH_MAX];
    char part[PATH_MAX];
    char dir[PATH_MAX];
    char msg[1200];
    char got[41] = "";
    char want[41] = "";
    FILE *out = NULL;
    Bt2Sha1 sha;
    int need_hash = is_elf_name(f->path) || is_dbzp_name(f->path);
    uint64_t existing = 0;
    uint64_t file_done = 0;
    int skip = 0;
    int e;
    Bt2Event ev;

    if (snprintf(dst, sizeof(dst), "%s/%s", dest, f->path) >= (int)sizeof(dst) ||
        snprintf(part, sizeof(part), "%s.part", dst) >= (int)sizeof(part)) {
        emit_error(c, 1, "La ruta de destino es demasiado larga para %s.", f->path);
        return 1;
    }
    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_FILE;
    ev.path = f->path;
    ev.file_size = f->size;
    ev.index = c->files_done + 1;
    ev.files_total = c->files_total;
    ev.files_done = c->files_done;
    ev.done_bytes = c->done_bytes;
    ev.total_bytes = c->total_bytes;
    if (c->fn != NULL) {
        c->fn(&ev, c->user);
    }
    if (cancelled(c)) {
        return 2;
    }

    if (!force && regular_size(dst, &existing) == 0 && existing == f->size) {
        skip = 1;
        if (need_hash) {
            if (hash_path(dst, got, msg, sizeof(msg)) != 0) {
                emit_error(c, 1, "%s", msg);
                return 1;
            }
            snprintf(want, sizeof(want), "%s", is_elf_name(f->path) ? BT2_ELF_SHA1 : BT2_DBZP_SHA1);
            if (strcmp(got, want) != 0) {
                skip = 0; /* el archivo instalado no sirve: se vuelve a copiar desde el disco */
                memset(&ev, 0, sizeof(ev));
                ev.kind = BT2_EV_NOTE;
                ev.message = "El programa instalado no coincide con el del disco; se vuelve a copiar.";
                ev.done_bytes = c->done_bytes;
                ev.total_bytes = c->total_bytes;
                ev.files_done = c->files_done;
                ev.files_total = c->files_total;
                if (c->fn != NULL) {
                    c->fn(&ev, c->user);
                }
            } else if (is_elf_name(f->path)) {
                snprintf(elf_hex, 41, "%s", got);
            }
        }
    }

    if (skip) {
        c->skipped++;
        c->files_done++;
        c->done_bytes += f->size;
        memset(&ev, 0, sizeof(ev));
        ev.kind = BT2_EV_NOTE;
        ev.message = "ya estaba";
        ev.path = f->path;
        ev.file_size = f->size;
        ev.file_done = f->size;
        ev.done_bytes = c->done_bytes;
        ev.total_bytes = c->total_bytes;
        ev.files_done = c->files_done;
        ev.files_total = c->files_total;
        if (c->fn != NULL) {
            c->fn(&ev, c->user);
        }
        memset(&ev, 0, sizeof(ev));
        ev.kind = BT2_EV_PROGRESS;
        ev.path = f->path;
        ev.file_size = f->size;
        ev.file_done = f->size;
        ev.done_bytes = c->done_bytes;
        ev.total_bytes = c->total_bytes;
        ev.files_done = c->files_done;
        ev.files_total = c->files_total;
        if (c->fn != NULL) {
            c->fn(&ev, c->user);
        }
        return 0;
    }

    path_dirname(dst, dir, sizeof(dir));
    if (mkdir_p(dir, msg, sizeof(msg)) != 0) {
        emit_error(c, 1, "%s", msg);
        return 1;
    }
    out = fopen(part, "wb");
    if (out == NULL) {
        emit_error(c, 1, "No se pudo escribir %s: %s. ¿El disco está lleno o la carpeta es de sólo lectura?", part,
                   strerror(errno));
        return 1;
    }
    if (need_hash) {
        bt2_sha1_init(&sha);
    }
    for (e = 0; e < f->nextents; e++) {
        uint64_t left = f->ext[e].size;
        uint64_t off = f->ext[e].offset;
        while (left > 0) {
            unsigned char *buf;
            size_t n = left > BT2_COPY_BUF ? BT2_COPY_BUF : (size_t)left;
            buf = (unsigned char *)malloc(n);
            if (buf == NULL) {
                fclose(out);
                unlink(part);
                emit_error(c, 1, "Sin memoria para copiar %s.", f->path);
                return 1;
            }
            if (iso_read(iso, off, buf, n, msg, sizeof(msg)) != 0) {
                free(buf);
                fclose(out);
                unlink(part);
                emit_error(c, 1, "%s", msg);
                return 1;
            }
            if (fwrite(buf, 1, n, out) != n) {
                free(buf);
                fclose(out);
                unlink(part);
                emit_error(c, 1, "No se pudo escribir %s: %s. ¿El disco está lleno?", dst, strerror(errno));
                return 1;
            }
            if (need_hash) {
                bt2_sha1_update(&sha, buf, n);
            }
            free(buf);
            off += n;
            left -= n;
            file_done += n;
            c->done_bytes += n;
            memset(&ev, 0, sizeof(ev));
            ev.kind = BT2_EV_PROGRESS;
            ev.path = f->path;
            ev.file_size = f->size;
            ev.file_done = file_done;
            ev.done_bytes = c->done_bytes;
            ev.total_bytes = c->total_bytes;
            ev.files_done = c->files_done;
            ev.files_total = c->files_total;
            if (c->fn != NULL) {
                c->fn(&ev, c->user);
            }
            if (cancelled(c)) {
                fclose(out);
                unlink(part);
                return 2;
            }
        }
    }
    {
        int flush_bad = fflush(out) != 0;
        int close_bad = fclose(out) != 0;
        if (flush_bad || close_bad) {
            unlink(part);
            emit_error(c, 1, "No se pudo escribir %s: %s. ¿El disco está lleno?", dst, strerror(errno));
            return 1;
        }
    }
    if (need_hash) {
        bt2_sha1_final(&sha, got);
        snprintf(want, sizeof(want), "%s", is_elf_name(f->path) ? BT2_ELF_SHA1 : BT2_DBZP_SHA1);
        if (strcmp(got, want) != 0) {
            unlink(part);
            emit_error(c, 3,
                       "El %s del disco no es el de la edición USA sin modificar.\nEsperado: %s\nObtenido: %s\n"
                       "El port se construyó sobre la edición USA original; una imagen parcheada o dañada no sirve.",
                       f->path, want, got);
            return 3;
        }
        if (is_elf_name(f->path)) {
            snprintf(elf_hex, 41, "%s", got);
        }
    }
    if (rename(part, dst) != 0) {
        unlink(part);
        emit_error(c, 1, "No se pudo guardar %s: %s. ¿El disco está lleno?", dst, strerror(errno));
        return 1;
    }
    c->copied++;
    c->files_done++;
    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_PROGRESS;
    ev.path = f->path;
    ev.file_size = f->size;
    ev.file_done = f->size;
    ev.done_bytes = c->done_bytes;
    ev.total_bytes = c->total_bytes;
    ev.files_done = c->files_done;
    ev.files_total = c->files_total;
    if (c->fn != NULL) {
        c->fn(&ev, c->user);
    }
    return 0;
}

int bt2_preflight(const char *iso_path, const char *dest, const char *eu_iso_path, int force, Bt2Preflight *out)
{
    Iso iso;
    Iso eu;
    char err[1024];
    char missing[1024];
    char human_total[64], human_free[64], human_need[64];
    Plan plan;
    int i, nmissing;
    uint64_t total = 0, already = 0;
    int already_files = 0;

    memset(out, 0, sizeof(*out));
    out->elf_hash_ok = -1;
    out->dbzp_hash_ok = -1;
    memset(&eu, 0, sizeof(eu));

    if (iso_open(&iso, iso_path, err, sizeof(err)) != 0) {
        snprintf(out->error, sizeof(out->error), "%s", err);
        return 1;
    }
    snprintf(out->volume_id, sizeof(out->volume_id), "%s", iso.volume_id);
    out->iso_bytes = iso.bytes;

    if (iso_find(&iso, BT2_ELF_NAME) == NULL) {
        char detail[128];
        out->region = detect_region(&iso, detail, sizeof(detail));
        if (out->region == 1) {
            snprintf(out->error, sizeof(out->error),
                     "Esta ISO es la edición PAL (%s). El port está hecho sobre la edición USA (SLUS-21441); "
                     "las otras regiones no sirven para arrancar.", detail[0] ? detail : "SLES_...");
        } else if (out->region == 2) {
            snprintf(out->error, sizeof(out->error),
                     "Esta ISO es la edición japonesa (%s). El port está hecho sobre la edición USA "
                     "(SLUS-21441); las otras regiones no sirven para arrancar.", detail[0] ? detail : "SLPS_...");
        } else if (detail[0] != '\0') {
            snprintf(out->error, sizeof(out->error),
                     "Esta no es la edición USA de Budokai Tenkaichi 2: el disco trae %s en vez de "
                     "SLUS_214.41. Otras revisiones o regiones no sirven para arrancar.", detail);
        } else {
            snprintf(out->error, sizeof(out->error),
                     "Esta no es una ISO de Budokai Tenkaichi 2: no hay ningún programa de PlayStation 2 "
                     "(SLUS_214.41) en el disco.");
        }
        iso_close(&iso);
        return 1;
    }

    nmissing = missing_required(&iso, missing, sizeof(missing));
    if (nmissing > 0) {
        snprintf(out->error, sizeof(out->error),
                 "A la ISO le faltan archivos que el port necesita:\n  %s\n"
                 "La imagen puede estar incompleta o no ser la edición USA.", missing);
        iso_close(&iso);
        return 1;
    }

    plan_build(&plan, &iso);
    for (i = 0; i < plan.count; i++) {
        total += plan.items[i].f->size;
    }
    out->file_count = plan.count;
    out->region = 0;

    {
        const IsoFile *elf = iso_find(&iso, BT2_ELF_NAME);
        const IsoFile *dbzp = iso_find(&iso, BT2_DBZP_NAME);
        char got[41];
        if (hash_iso_file(&iso, elf, got, err, sizeof(err)) != 0) {
            snprintf(out->error, sizeof(out->error), "%s", err);
            iso_close(&iso);
            return 1;
        }
        out->elf_hash_ok = strcmp(got, BT2_ELF_SHA1) == 0;
        if (!out->elf_hash_ok) {
            snprintf(out->error, sizeof(out->error),
                     "El %s del disco no es el de la edición USA sin modificar.\nEsperado: %s\nObtenido: %s\n"
                     "El port se construyó sobre la edición USA original; una imagen parcheada o dañada no sirve.",
                     BT2_ELF_NAME, BT2_ELF_SHA1, got);
            iso_close(&iso);
            return 3;
        }
        if (hash_iso_file(&iso, dbzp, got, err, sizeof(err)) != 0) {
            snprintf(out->error, sizeof(out->error), "%s", err);
            iso_close(&iso);
            return 1;
        }
        out->dbzp_hash_ok = strcmp(got, BT2_DBZP_SHA1) == 0;
        if (!out->dbzp_hash_ok) {
            snprintf(out->error, sizeof(out->error),
                     "El %s del disco no es el de la edición USA sin modificar.\nEsperado: %s\nObtenido: %s\n"
                     "El port se construyó sobre la edición USA original; una imagen parcheada o dañada no sirve.",
                     BT2_DBZP_NAME, BT2_DBZP_SHA1, got);
            iso_close(&iso);
            return 3;
        }
    }

    out->eu_requested = eu_iso_path != NULL && eu_iso_path[0] != '\0';
    if (out->eu_requested) {
        const IsoFile *afs;
        if (iso_open(&eu, eu_iso_path, err, sizeof(err)) != 0) {
            snprintf(out->error, sizeof(out->error), "No se pudo abrir la ISO PAL: %s", err);
            iso_close(&iso);
            return 1;
        }
        afs = iso_find(&eu, BT2_EU_AFS);
        if (afs == NULL) {
            snprintf(out->error, sizeof(out->error),
                     "La ISO PAL no tiene %s; ¿es el disco PAL correcto de Budokai Tenkaichi 2?", BT2_EU_AFS);
            iso_close(&eu);
            iso_close(&iso);
            return 1;
        }
        out->eu_present = 1;
        out->eu_bytes = afs->size;
        total += afs->size;
        out->file_count++;
    }
    out->total_bytes = total;

    if (!force) {
        for (i = 0; i < plan.count; i++) {
            char path[PATH_MAX];
            uint64_t size = 0;
            if (snprintf(path, sizeof(path), "%s/%s", dest, plan.items[i].f->path) < (int)sizeof(path) &&
                regular_size(path, &size) == 0 && size == plan.items[i].f->size) {
                already += size;
                already_files++;
            }
        }
        if (out->eu_requested) {
            char path[PATH_MAX];
            uint64_t size = 0;
            if (snprintf(path, sizeof(path), "%s/%s", dest, BT2_EU_AFS) < (int)sizeof(path) &&
                regular_size(path, &size) == 0 && size == out->eu_bytes) {
                already += size;
                already_files++;
            }
        }
    }
    out->already_files = already_files;
    out->already_bytes = already;
    out->need_bytes = total > already ? total - already : 0;

    if (get_free_space(dest, &out->free_bytes) == 0) {
        out->free_known = 1;
    } else {
        out->free_known = 0;
        out->free_bytes = 0;
    }
    {
        uint64_t required = out->need_bytes > 0 ? out->need_bytes + BT2_SPACE_MARGIN : (1ull << 20);
        if (out->free_known && out->free_bytes < required) {
            bt2_human_bytes(out->free_bytes, human_free, sizeof(human_free));
            bt2_human_bytes(required, human_need, sizeof(human_need));
            snprintf(out->error, sizeof(out->error),
                     "No hay espacio suficiente en el destino: quedan %s libres y se necesitan al menos %s "
                     "(datos + 64 MB de margen).", human_free, human_need);
            iso_close(&eu);
            iso_close(&iso);
            return 1;
        }
    }

    bt2_human_bytes(total, human_total, sizeof(human_total));
    if (out->free_known) {
        bt2_human_bytes(out->free_bytes, human_free, sizeof(human_free));
        snprintf(out->message, sizeof(out->message), "Edición USA · %d archivos · %s · libre %s", out->file_count,
                 human_total, human_free);
    } else {
        snprintf(out->message, sizeof(out->message), "Edición USA · %d archivos · %s", out->file_count, human_total);
    }
    out->ok = 1;
    iso_close(&eu);
    iso_close(&iso);
    return 0;
}

static void scan_tree(const char *dir, int *files, uint64_t *bytes, int depth)
{
    DIR *d;
    struct dirent *ent;

    if (depth > 8) {
        return;
    }
    d = opendir(dir);
    if (d == NULL) {
        return;
    }
    while ((ent = readdir(d)) != NULL) {
        char path[PATH_MAX];
        struct stat st;
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        if (snprintf(path, sizeof(path), "%s/%s", dir, ent->d_name) >= (int)sizeof(path)) {
            continue;
        }
        if (lstat(path, &st) != 0) {
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            scan_tree(path, files, bytes, depth + 1);
        } else if (S_ISREG(st.st_mode)) {
            if (strcmp(ent->d_name, BT2_MARKER) == 0) {
                continue;
            }
            {
                size_t n = strlen(ent->d_name);
                if (n > 5 && strcmp(ent->d_name + n - 5, ".part") == 0) {
                    continue;
                }
            }
            (*files)++;
            *bytes += (uint64_t)st.st_size;
        }
    }
    closedir(d);
}

int bt2_check_dest(const char *dest, int verify_hash, Bt2Check *out)
{
    char marker[PATH_MAX];
    char err[512];
    char missing[1024];
    size_t used = 0;
    int i, n = 0;
    uint64_t bytes = 0;
    int files = 0;

    memset(out, 0, sizeof(*out));
    out->elf_hash_ok = -1;
    out->dbzp_hash_ok = -1;
    missing[0] = '\0';
    if (snprintf(marker, sizeof(marker), "%s/%s", dest, BT2_MARKER) >= (int)sizeof(marker)) {
        snprintf(out->missing, sizeof(out->missing), "ruta de destino demasiado larga");
        return 1;
    }
    {
        uint64_t size = 0;
        out->marker = regular_size(marker, &size) == 0;
    }
    for (i = 0; i < (int)(sizeof(kRequired) / sizeof(kRequired[0])); i++) {
        char path[PATH_MAX];
        uint64_t size = 0;
        int ok = 0;
        if (snprintf(path, sizeof(path), "%s/%s", dest, kRequired[i]) < (int)sizeof(path) &&
            regular_size(path, &size) == 0 && size > 0) {
            if (is_elf_name(kRequired[i])) {
                ok = size == BT2_ELF_BYTES;
            } else if (is_dbzp_name(kRequired[i])) {
                ok = size == BT2_DBZP_BYTES;
            } else {
                ok = 1;
            }
        }
        if (!ok) {
            int w = snprintf(missing + used, sizeof(missing) - used, "%s%s", n == 0 ? "" : "\n", kRequired[i]);
            if (w > 0 && used + (size_t)w < sizeof(missing)) {
                used += (size_t)w;
            }
            n++;
        }
    }
    scan_tree(dest, &files, &bytes, 0);
    out->files = files;
    out->bytes = bytes;

    if (!out->marker) {
        snprintf(out->summary, sizeof(out->summary), "falta el marcador %s", BT2_MARKER);
        snprintf(out->missing, sizeof(out->missing), "%s", missing);
        return 1;
    }
    if (n > 0) {
        snprintf(out->summary, sizeof(out->summary), "faltan %d archivos", n);
        snprintf(out->missing, sizeof(out->missing), "%s", missing);
        return 1;
    }
    if (verify_hash) {
        char path[PATH_MAX], got[41];
        if (snprintf(path, sizeof(path), "%s/%s", dest, BT2_ELF_NAME) < (int)sizeof(path)) {
            if (hash_path(path, got, err, sizeof(err)) != 0) {
                snprintf(out->summary, sizeof(out->summary), "%s", err);
                return 1;
            }
            out->elf_hash_ok = strcmp(got, BT2_ELF_SHA1) == 0;
            if (!out->elf_hash_ok) {
                snprintf(out->summary, sizeof(out->summary),
                         "el %s instalado no coincide con la edición USA (obtenido %s)", BT2_ELF_NAME, got);
                return 3;
            }
        }
        if (snprintf(path, sizeof(path), "%s/%s", dest, BT2_DBZP_NAME) < (int)sizeof(path)) {
            if (hash_path(path, got, err, sizeof(err)) != 0) {
                snprintf(out->summary, sizeof(out->summary), "%s", err);
                return 1;
            }
            out->dbzp_hash_ok = strcmp(got, BT2_DBZP_SHA1) == 0;
            if (!out->dbzp_hash_ok) {
                snprintf(out->summary, sizeof(out->summary),
                         "el %s instalado no coincide con la edición USA (obtenido %s)", BT2_DBZP_NAME, got);
                return 3;
            }
        }
    }
    {
        char human[64];
        bt2_human_bytes(bytes, human, sizeof(human));
        snprintf(out->summary, sizeof(out->summary), "%d archivos, %s", files, human);
    }
    return 0;
}

static int write_marker(const char *dest, const char *iso_path, const char *elf_sha1, int eu_afs, int files,
                        uint64_t bytes, char *err, size_t errsz)
{
    char path[PATH_MAX];
    char part[PATH_MAX];
    char stamp[32];
    time_t now = time(NULL);
    struct tm tm;
    FILE *f;

    if (snprintf(path, sizeof(path), "%s/%s", dest, BT2_MARKER) >= (int)sizeof(path) ||
        snprintf(part, sizeof(part), "%s.part", path) >= (int)sizeof(part)) {
        snprintf(err, errsz, "la ruta del marcador es demasiado larga.");
        return -1;
    }
    localtime_r(&now, &tm);
    strftime(stamp, sizeof(stamp), "%Y-%m-%dT%H:%M:%S", &tm);
    f = fopen(part, "wb");
    if (f == NULL) {
        snprintf(err, errsz, "no se pudo escribir %s: %s.", part, strerror(errno));
        return -1;
    }
    fputs("{\n  \"version\": 1,\n  \"elf_sha1\": \"", f);
    fputs(elf_sha1, f);
    fputs("\",\n  \"eu_afs\": ", f);
    fputs(eu_afs ? "true" : "false", f);
    fprintf(f, ",\n  \"files\": %d,\n  \"bytes\": %llu,\n  \"iso\": \"", files, (unsigned long long)bytes);
    json_escape(f, iso_path);
    fputs("\",\n  \"installed_at\": \"", f);
    fputs(stamp, f);
    fputs("\"\n}\n", f);
    if (fflush(f) != 0 || fclose(f) != 0) {
        unlink(part);
        snprintf(err, errsz, "no se pudo escribir %s: %s.", part, strerror(errno));
        return -1;
    }
    if (rename(part, path) != 0) {
        unlink(part);
        snprintf(err, errsz, "no se pudo guardar %s: %s.", path, strerror(errno));
        return -1;
    }
    return 0;
}

void bt2_list_iso(const Iso *iso, FILE *out)
{
    const IsoFile **v;
    int i;
    uint64_t total = 0;

    v = (const IsoFile **)malloc(sizeof(*v) * (size_t)iso->count);
    if (v == NULL) {
        return;
    }
    for (i = 0; i < iso->count; i++) {
        v[i] = &iso->files[i];
    }
    for (i = 0; i < iso->count; i++) {
        int j;
        for (j = i + 1; j < iso->count; j++) {
            if (strcmp(v[j]->path, v[i]->path) < 0) {
                const IsoFile *tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }
        }
    }
    for (i = 0; i < iso->count; i++) {
        fprintf(out, "%12llu  %s\n", (unsigned long long)v[i]->size, v[i]->path);
        total += v[i]->size;
    }
    fprintf(out, "\n%d archivos, %llu bytes\n", iso->count, (unsigned long long)total);
    free(v);
}

int bt2_install(const char *iso_path, const char *dest, const char *eu_iso_path, int force, Bt2CancelFn cancel,
                void *cancel_user, Bt2EventFn fn, void *user)
{
    Iso iso;
    Iso eu;
    Plan plan;
    Ctx c;
    char err[1024];
    char human_total[64], human_done[64], human_free[64];
    char missing[1024];
    char elf_hex[41] = "";
    uint64_t total = 0, already = 0, free_bytes = 0;
    int i, rc = 1, eu_on;
    double t0;
    Bt2Event ev;

    memset(&iso, 0, sizeof(iso));
    memset(&eu, 0, sizeof(eu));
    memset(&c, 0, sizeof(c));
    c.fn = fn;
    c.user = user;
    c.cancel = cancel;
    c.cancel_user = cancel_user;
    c.steps = (eu_iso_path != NULL && eu_iso_path[0] != '\0') ? 5 : 4;
    eu_on = c.steps == 5;
    t0 = now_seconds();

    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_STEP;
    ev.step = 1;
    ev.steps = c.steps;
    ev.step_name = "Validar imagen";
    if (fn != NULL) {
        fn(&ev, user);
    }

    if (iso_open(&iso, iso_path, err, sizeof(err)) != 0) {
        emit_error(&c, 1, "%s", err);
        return 1;
    }
    if (iso_find(&iso, BT2_ELF_NAME) == NULL) {
        char detail[128];
        int region = detect_region(&iso, detail, sizeof(detail));
        if (region == 1) {
            emit_error(&c, 1,
                       "Esta ISO es la edición PAL (%s). El port está hecho sobre la edición USA (SLUS-21441); "
                       "las otras regiones no sirven para arrancar.", detail[0] ? detail : "SLES_...");
        } else if (region == 2) {
            emit_error(&c, 1,
                       "Esta ISO es la edición japonesa (%s). El port está hecho sobre la edición USA "
                       "(SLUS-21441); las otras regiones no sirven para arrancar.", detail[0] ? detail : "SLPS_...");
        } else {
            emit_error(&c, 1,
                       "Esta no es la edición USA de Budokai Tenkaichi 2: no hay SLUS_214.41 en el disco%s%s.",
                       detail[0] ? " (trae " : "", detail[0] ? detail : "");
        }
        iso_close(&iso);
        return 1;
    }
    if (missing_required(&iso, missing, sizeof(missing)) > 0) {
        emit_error(&c, 1,
                   "A la ISO le faltan archivos que el port necesita:\n  %s\n"
                   "La imagen puede estar incompleta o no ser la edición USA.", missing);
        iso_close(&iso);
        return 1;
    }
    {
        const IsoFile *elf = iso_find(&iso, BT2_ELF_NAME);
        const IsoFile *dbzp = iso_find(&iso, BT2_DBZP_NAME);
        char got[41];
        if (hash_iso_file(&iso, elf, got, err, sizeof(err)) != 0) {
            emit_error(&c, 1, "%s", err);
            iso_close(&iso);
            return 1;
        }
        if (strcmp(got, BT2_ELF_SHA1) != 0) {
            emit_error(&c, 3,
                       "El %s del disco no es el de la edición USA sin modificar.\nEsperado: %s\nObtenido: %s\n"
                       "El port se construyó sobre la edición USA original; una imagen parcheada o dañada no sirve.",
                       BT2_ELF_NAME, BT2_ELF_SHA1, got);
            iso_close(&iso);
            return 3;
        }
        if (hash_iso_file(&iso, dbzp, got, err, sizeof(err)) != 0) {
            emit_error(&c, 1, "%s", err);
            iso_close(&iso);
            return 1;
        }
        if (strcmp(got, BT2_DBZP_SHA1) != 0) {
            emit_error(&c, 3,
                       "El %s del disco no es el de la edición USA sin modificar.\nEsperado: %s\nObtenido: %s\n"
                       "El port se construyó sobre la edición USA original; una imagen parcheada o dañada no sirve.",
                       BT2_DBZP_NAME, BT2_DBZP_SHA1, got);
            iso_close(&iso);
            return 3;
        }
    }

    plan_build(&plan, &iso);
    for (i = 0; i < plan.count; i++) {
        total += plan.items[i].f->size;
    }
    if (eu_on) {
        const IsoFile *afs;
        char readerr[512];
        if (iso_open(&eu, eu_iso_path, readerr, sizeof(readerr)) != 0) {
            emit_error(&c, 1, "No se pudo abrir la ISO PAL: %s", readerr);
            iso_close(&iso);
            return 1;
        }
        afs = iso_find(&eu, BT2_EU_AFS);
        if (afs == NULL) {
            emit_error(&c, 1, "La ISO PAL no tiene %s; ¿es el disco PAL correcto de Budokai Tenkaichi 2?", BT2_EU_AFS);
            iso_close(&eu);
            iso_close(&iso);
            return 1;
        }
        total += afs->size;
        plan.items[plan.count].f = afs;
        plan.items[plan.count].iso = &eu;
        plan.items[plan.count].eu = 1;
        plan.count++;
    }
    c.files_total = plan.count;
    c.total_bytes = total;

    if (get_free_space(dest, &free_bytes) == 0) {
        if (!force) {
            for (i = 0; i < plan.count; i++) {
                char path[PATH_MAX];
                uint64_t size = 0;
                if (snprintf(path, sizeof(path), "%s/%s", dest, plan.items[i].f->path) < (int)sizeof(path) &&
                    regular_size(path, &size) == 0 && size == plan.items[i].f->size) {
                    already += size;
                }
            }
        }
        {
            uint64_t remaining = total > already ? total - already : 0;
            uint64_t required = remaining > 0 ? remaining + BT2_SPACE_MARGIN : (1ull << 20);
            if (free_bytes < required) {
                bt2_human_bytes(free_bytes, human_free, sizeof(human_free));
                bt2_human_bytes(required, human_total, sizeof(human_total));
                emit_error(&c, 1,
                           "No hay espacio suficiente en el destino: quedan %s libres y se necesitan al menos %s "
                           "(datos + 64 MB de margen).", human_free, human_total);
                iso_close(&eu);
                iso_close(&iso);
                return 1;
            }
        }
    }
    if (mkdir_p(dest, err, sizeof(err)) != 0) {
        emit_error(&c, 1, "%s", err);
        iso_close(&eu);
        iso_close(&iso);
        return 1;
    }

    /* Paso 2: el programa, primero, para fallar barato si el disco no es el USA. */
    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_STEP;
    ev.step = 2;
    ev.steps = c.steps;
    ev.step_name = "Programa";
    if (fn != NULL) {
        fn(&ev, user);
    }
    rc = copy_plan_item(&c, dest, &plan.items[0], force, elf_hex);
    if (rc != 0) {
        if (rc == 2) {
            emit_error(&c, 1, "Instalación cancelada. Los archivos ya copiados se conservan; se puede retomar.");
            rc = 2;
        }
        iso_close(&eu);
        iso_close(&iso);
        return rc;
    }

    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_STEP;
    ev.step = 3;
    ev.steps = c.steps;
    ev.step_name = "Datos del juego";
    if (fn != NULL) {
        fn(&ev, user);
    }
    for (i = 1; i < plan.count; i++) {
        if (plan.items[i].eu) {
            continue;
        }
        rc = copy_plan_item(&c, dest, &plan.items[i], force, elf_hex);
        if (rc != 0) {
            if (rc == 2) {
                emit_error(&c, 1, "Instalación cancelada. Los archivos ya copiados se conservan; se puede retomar.");
                rc = 2;
            }
            iso_close(&eu);
            iso_close(&iso);
            return rc;
        }
    }

    if (eu_on) {
        int eu_index = -1;
        memset(&ev, 0, sizeof(ev));
        ev.kind = BT2_EV_STEP;
        ev.step = 4;
        ev.steps = c.steps;
        ev.step_name = "Multiidioma (PAL)";
        if (fn != NULL) {
            fn(&ev, user);
        }
        for (i = 0; i < plan.count; i++) {
            if (plan.items[i].eu) {
                eu_index = i;
                break;
            }
        }
        if (eu_index >= 0) {
            rc = copy_plan_item(&c, dest, &plan.items[eu_index], force, elf_hex);
            if (rc != 0) {
                if (rc == 2) {
                    emit_error(&c, 1, "Instalación cancelada. Los archivos ya copiados se conservan; se puede retomar.");
                    rc = 2;
                }
                iso_close(&eu);
                iso_close(&iso);
                return rc;
            }
        }
    }

    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_STEP;
    ev.step = c.steps;
    ev.steps = c.steps;
    ev.step_name = "Marcador";
    if (fn != NULL) {
        fn(&ev, user);
    }
    if (elf_hex[0] == '\0') {
        snprintf(elf_hex, sizeof(elf_hex), "%s", BT2_ELF_SHA1);
    }
    if (write_marker(dest, iso_path, elf_hex, eu_on, c.files_total, c.total_bytes, err, sizeof(err)) != 0) {
        emit_error(&c, 1, "%s", err);
        iso_close(&eu);
        iso_close(&iso);
        return 1;
    }

    bt2_human_bytes(c.total_bytes, human_total, sizeof(human_total));
    bt2_human_bytes(c.done_bytes, human_done, sizeof(human_done));
    (void)human_done;
    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_DONE;
    ev.files_done = c.files_done;
    ev.files_total = c.files_total;
    ev.done_bytes = c.done_bytes;
    ev.total_bytes = c.total_bytes;
    ev.code = 0;
    {
        static char done_msg[512];
        snprintf(done_msg, sizeof(done_msg), "Listo: %d archivos, %s (%d copiados, %d ya estaban) en %.1f s.",
                 c.files_total, human_total, c.copied, c.skipped, now_seconds() - t0);
        ev.message = done_msg;
    }
    if (fn != NULL) {
        fn(&ev, user);
    }
    iso_close(&eu);
    iso_close(&iso);
    return 0;
}

/* Paso opcional, aparte de la instalación: agrega los datos multiidioma (DATA/ZS2EU_1.AFS de la ISO PAL) a una
   instalación que ya existe. No pide la ISO USA otra vez. Mismos eventos que bt2_install (2 pasos). */
int bt2_install_eu(const char *eu_iso_path, const char *dest, int force, Bt2CancelFn cancel, void *cancel_user,
                   Bt2EventFn fn, void *user)
{
    Iso eu;
    Plan plan;
    Ctx c;
    Bt2Event ev;
    char err[512], elf_hex[41] = "";
    const IsoFile *afs;
    double t0 = now_seconds();
    int rc;

    memset(&eu, 0, sizeof(eu));
    memset(&plan, 0, sizeof(plan));
    memset(&c, 0, sizeof(c));
    c.fn = fn;
    c.user = user;
    c.cancel = cancel;
    c.cancel_user = cancel_user;
    c.steps = 2;

    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_STEP;
    ev.step = 1;
    ev.steps = 2;
    ev.step_name = "Validar ISO PAL";
    if (fn != NULL) {
        fn(&ev, user);
    }
    if (iso_open(&eu, eu_iso_path, err, sizeof(err)) != 0) {
        emit_error(&c, 1, "No se pudo abrir la ISO PAL: %s", err);
        return 1;
    }
    afs = iso_find(&eu, BT2_EU_AFS);
    if (afs == NULL) {
        emit_error(&c, 1, "Esa ISO no tiene %s: tiene que ser la edición europea (PAL) de Budokai Tenkaichi 2.",
                   BT2_EU_AFS);
        iso_close(&eu);
        return 1;
    }
    plan.items[0].f = afs;
    plan.items[0].iso = &eu;
    plan.items[0].eu = 1;
    plan.count = 1;
    c.files_total = 1;
    c.total_bytes = afs->size;

    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_STEP;
    ev.step = 2;
    ev.steps = 2;
    ev.step_name = "Multiidioma (PAL)";
    if (fn != NULL) {
        fn(&ev, user);
    }
    rc = copy_plan_item(&c, dest, &plan.items[0], force, elf_hex);
    iso_close(&eu);
    if (rc != 0) {
        if (rc == 2) {
            emit_error(&c, 1, "Cancelado. Se puede retomar.");
        }
        return rc;
    }
    memset(&ev, 0, sizeof(ev));
    ev.kind = BT2_EV_DONE;
    ev.files_done = c.files_done;
    ev.files_total = 1;
    ev.done_bytes = c.done_bytes;
    ev.total_bytes = c.total_bytes;
    {
        static char msg[256];
        snprintf(msg, sizeof(msg), "Idiomas agregados (español, francés, alemán e italiano) en %.1f s.", now_seconds() - t0);
        ev.message = msg;
    }
    if (fn != NULL) {
        fn(&ev, user);
    }
    return 0;
}
