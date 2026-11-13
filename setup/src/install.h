/* Motor del instalador de BT2: validación de la ISO, copia con progreso, marcador `.installed`.
 *
 * La GUI y la consola usan el mismo motor. La copia se hace en el hilo que llama a bt2_install(); los
 * eventos se entregan por callback desde ese hilo (la GUI los encola con un mutex).
 */
#ifndef BT2_INSTALL_H
#define BT2_INSTALL_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "iso.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BT2_ELF_NAME "SLUS_214.41"
#define BT2_ELF_SHA1 "cf01d5b2023843eecf7cf8ccda8bcd102dd61db7"
#define BT2_ELF_BYTES 2675936u
#define BT2_DBZP_NAME "BIN/DBZP.BIN"
#define BT2_DBZP_SHA1 "0463612b526e6e90a48636bb419720e212515ed1"
#define BT2_DBZP_BYTES 513167u
#define BT2_EU_AFS "DATA/ZS2EU_1.AFS"
#define BT2_MARKER ".installed"

typedef enum {
    BT2_EV_STEP,      /* empieza un paso: step/steps/step_name */
    BT2_EV_FILE,      /* empieza un archivo: path/file_size/index/files_total */
    BT2_EV_PROGRESS,  /* bytes copiados: done_bytes/total_bytes/file_done/file_size/files_done */
    BT2_EV_NOTE,      /* detalle para el usuario: message */
    BT2_EV_ERROR,     /* terminó mal: code/message */
    BT2_EV_DONE       /* terminó bien: files_done/done_bytes/message */
} Bt2EventKind;

typedef struct {
    Bt2EventKind kind;
    int step;
    int steps;
    const char *step_name;
    const char *path;
    const char *message;
    uint64_t file_size;
    uint64_t file_done;
    uint64_t done_bytes;
    uint64_t total_bytes;
    int index;
    int files_done;
    int files_total;
    int code;
} Bt2Event;

typedef void (*Bt2EventFn)(const Bt2Event *ev, void *user);
/* Devuelve distinto de cero para cortar la instalación en el próximo bloque. */
typedef int (*Bt2CancelFn)(void *user);

typedef struct {
    int ok;                 /* 1 si se puede instalar */
    int region;             /* 0 USA, 1 PAL, 2 Japón, 3 otra/desconocida */
    char volume_id[64];
    uint64_t iso_bytes;
    int file_count;         /* archivos que se copiarían (sin el AFS PAL) */
    uint64_t total_bytes;   /* bytes a copiar (con el AFS PAL si se pidió) */
    int eu_requested;
    int eu_present;
    uint64_t eu_bytes;
    int already_files;      /* ya presentes con el tamaño correcto */
    uint64_t already_bytes;
    int free_known;
    uint64_t free_bytes;
    uint64_t need_bytes;    /* faltante real (total - ya presentes) */
    int elf_hash_ok;        /* 1 coincide, 0 no, -1 no se pudo revisar */
    int dbzp_hash_ok;
    char message[1024];     /* resumen en una línea */
    char error[1024];       /* motivo del rechazo */
} Bt2Preflight;

typedef struct {
    int marker;
    int files;
    uint64_t bytes;
    int elf_hash_ok;        /* 1 ok, 0 mal, -1 no verificado */
    int dbzp_hash_ok;
    char summary[256];
    char missing[1024];     /* lista de archivos faltantes, uno por línea */
} Bt2Check;

/* Valida la ISO (región, archivos requeridos, SHA-1 del programa, espacio). No escribe nada.
 * Devuelve 0 si está todo bien, 1 error, 3 hash distinto. */
int bt2_preflight(const char *iso_path, const char *dest, const char *eu_iso_path, int force, Bt2Preflight *out);

/* Revisa una instalación existente. `verify_hash` calcula SHA-1 del ELF/DBZP instalados.
 * Devuelve 0 ok, 1 faltan archivos/marcador, 3 hash distinto. */
int bt2_check_dest(const char *dest, int verify_hash, Bt2Check *out);

/* Instala. `cancel` puede ser NULL; si devuelve distinto de cero se corta al próximo bloque.
 * Devuelve 0 ok, 1 error, 2 cancelado, 3 hash distinto. */
int bt2_install_eu(const char *eu_iso_path, const char *dest, int force, Bt2CancelFn cancel, void *cancel_user,
                   Bt2EventFn fn, void *user);
int bt2_install(const char *iso_path, const char *dest, const char *eu_iso_path, int force,
                Bt2CancelFn cancel, void *cancel_user, Bt2EventFn fn, void *user);

/* "2.98 GB", "513.2 MB", etc. */
void bt2_human_bytes(uint64_t n, char *out, size_t outsz);

/* Lista el contenido de una ISO ya abierta, ordenado por ruta. */
void bt2_list_iso(const Iso *iso, FILE *out);

#ifdef __cplusplus
}
#endif

#endif /* BT2_INSTALL_H */
