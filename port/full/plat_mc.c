/*
 * Memory card library (Sony libmc) on PC: slot 1 is a formatted card whose contents are ordinary files in a folder;
 * slot 2 is empty.
 *
 *     saves/card1/BASLUS-21678DBZT3/...     (the folder is `saves` in the current directory, or $BT2_SAVES)
 *
 * The game's paths ("/BASLUS-21678DBZT3/icon.sys") are used as they are below that folder, so a save made here
 * has the same files as one on a console card (icon.sys, the icon, the data file).
 *
 * The library is asynchronous: a call only starts a request and returns 0; sceMcSync reports the request's number
 * and its result. Here every request is carried out at once and sceMcSync hands the stored result over.
 * Results follow libmc (what src/battle/stgm_a_b.c and src/sys/mcflow_a.c test):
 *     sceMcGetInfo   0 = the card seen last time, -1 = a formatted card seen for the first time, -10 = no card;
 *                    type 2 = a PS2 card, free = free clusters of 1 KB, format 1 = formatted
 *     sceMcOpen      a file handle >= 0, or -4 = no such file      (mode: 1 read, 2 write, 0x200 create)
 *     sceMcMkdir     0, or -4 = it exists already
 *     sceMcGetDir    the number of entries that match (the game only asks "is this directory there": 1 or 0)
 *     sceMcRead / sceMcWrite   bytes transferred;   sceMcSeek   the new position;   sceMcClose / sceMcFormat   0
 * Nombres de BT2 (build_port/bt3_names.csv: sceMc* en 0x31D248..). Carpeta: $BT2_SAVES (saves/card1). Adaptado de plat_mc.c de Tenkaichi3Decomp.
 */
#include <stdint.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path) /* Windows: no permission bits */
#endif

typedef uint32_t u32;
#define P_(x) ((void *)(uintptr_t)(x))
#define MC_FILES 8
#define MC_FREE_CLUSTERS 8000 /* an empty 8 MB card */

static int sLastCmd, sLastResult;
static int sSeen;             /* slot 1 was reported once: later sceMcGetInfo calls answer "same card" */
static FILE *sFiles[MC_FILES];

static int request(int cmd, int result) {
    if (getenv("BT2_MC_LOG") != NULL) { fprintf(stderr, "mc: req cmd %d -> %d\n", cmd, result); }
    sLastCmd = cmd;
    sLastResult = result;
    return 0;
}

/* The host path of a card path; creates the card's folder on first use. Returns 0 for slot 2 (no card). */
static int host_path(int port, const char *name, char *out, size_t size) {
    const char *root = getenv("BT2_SAVES") != NULL ? getenv("BT2_SAVES") : "saves";
    char dir[512];

    if (port != 0) {
        return 0;
    }
    mkdir(root, 0755);
    snprintf(dir, sizeof(dir), "%s/card1", root);
    mkdir(dir, 0755);
    while (*name == '/') {
        name++;
    }
    if (strstr(name, "..") != NULL) {
        return 0;
    }
    snprintf(out, size, "%s/%s", dir, name);
    return 1;
}

int sceMcInit(void) { return 0; } /* sceMcInit */

/* sceMcGetInfo: the outputs are filled when the request completes. */
int sceMcGetInfo(int port, int slot, u32 type_, u32 free_, u32 format_) {
    int *type = P_(type_), *freeClusters = P_(free_), *format = P_(format_);
    char path[600];
    int card = slot == 0 && host_path(port, "", path, sizeof(path));

    if (type != NULL) { *type = card ? 2 : 0; }
    if (freeClusters != NULL) { *freeClusters = card ? MC_FREE_CLUSTERS : 0; }
    if (format != NULL) { *format = card ? 1 : 0; }
    if (!card) {
        return request(1, -10);
    }
    if (!sSeen) {
        sSeen = 1;
        return request(1, -1);
    }
    return request(1, 0);
}

/* sceMcOpen */
int sceMcOpen(int port, int slot, u32 name_, int mode) {
    char *name = P_(name_);
    char path[600];
    FILE *f;
    int fd;

    if (getenv("BT2_MC_LOG") != NULL) { fprintf(stderr, "mc: open? port %d slot %d '%s' mode %d\n", port, slot, name, mode); }
    if (slot != 0 || !host_path(port, name, path, sizeof(path))) {
        return request(2, -10);
    }
    for (fd = 0; fd < MC_FILES && sFiles[fd] != NULL; fd++) {
    }
    if (fd == MC_FILES) {
        return request(2, -7); /* too many open files */
    }
    f = fopen(path, (mode & 2) ? "r+b" : "rb");
    if (f == NULL && (mode & 0x200)) {
        f = fopen(path, "w+b");
    }
    if (f == NULL) {
        return request(2, -4);
    }
    if (getenv("BT2_MC_LOG") != NULL) {
        fprintf(stderr, "mc: open %s (mode %d)\n", path, mode);
    }
    sFiles[fd] = f;
    return request(2, fd);
}

/* sceMcMkdir */
int sceMcMkdir(int port, int slot, u32 name_) {
    char *name = P_(name_);
    char path[600];

    if (slot != 0 || !host_path(port, name, path, sizeof(path))) {
        return request(11, -10);
    }
    return request(11, mkdir(path, 0755) == 0 ? 0 : -4);
}

/* sceMcClose */
int sceMcClose(int fd) {
    if (fd < 0 || fd >= MC_FILES || sFiles[fd] == NULL) {
        return request(3, -4);
    }
    fclose(sFiles[fd]);
    sFiles[fd] = NULL;
    return request(3, 0);
}

/* sceMcSeek: origin 0 = start, 1 = current, 2 = end */
int sceMcSeek(int fd, int offset, int origin) {
    if (fd < 0 || fd >= MC_FILES || sFiles[fd] == NULL) {
        return request(4, -4);
    }
    fseek(sFiles[fd], offset, origin == 0 ? SEEK_SET : origin == 1 ? SEEK_CUR : SEEK_END);
    return request(4, (int)ftell(sFiles[fd]));
}

/* sceMcRead */
int sceMcRead(int fd, u32 buf_, int size) {
    void *buf = P_(buf_);
    int n;
    if (fd < 0 || fd >= MC_FILES || sFiles[fd] == NULL) {
        return request(5, -4);
    }
    n = (int)fread(buf, 1, (size_t)size, sFiles[fd]);
    if (getenv("BT2_MC_LOG") != NULL) {
        fprintf(stderr, "mc: read fd %d size %d -> %d bytes\n", fd, size, n);
    }
    return request(5, n);
}

/* sceMcWrite */
int sceMcWrite(int fd, u32 buf_, int size) {
    void *buf = P_(buf_);
    int n;

    if (fd < 0 || fd >= MC_FILES || sFiles[fd] == NULL) {
        return request(6, -4);
    }
    n = (int)fwrite(buf, 1, (size_t)size, sFiles[fd]);
    fflush(sFiles[fd]);
    return request(6, n);
}

/* sceMcGetDir: the number of entries matching `name` ("*" = everything in the root, otherwise one name). The
   table is not filled: nothing in the game reads it. */
int sceMcGetDir(int port, int slot, u32 name_, int mode, int maxent, u32 table) {
    char *name = P_(name_);
    char path[600];
    struct stat st;
    int n = 0;

    (void)mode; (void)maxent; (void)table;
    if (getenv("BT2_MC_LOG") != NULL) { fprintf(stderr, "mc: getdir port %d slot %d '%s' mode %d max %d\n", port, slot, name, mode, maxent); }
    if (slot != 0 || !host_path(port, strcmp(name, "*") == 0 ? "" : name, path, sizeof(path))) {
        return request(13, -10);
    }
    if (strcmp(name, "*") == 0) {
        DIR *d = opendir(path);
        struct dirent *e;
        while (d != NULL && (e = readdir(d)) != NULL) {
            if (e->d_name[0] != '.') {
                n++;
            }
        }
        if (d != NULL) {
            closedir(d);
        }
    } else {
        n = stat(path, &st) == 0 ? 1 : 0;
    }
    return request(13, n);
}

/* sceMcFormat: the folder is always "formatted"; nothing is erased. */
int sceMcFormat(int port, int slot) {
    (void)slot;
    return request(16, port == 0 ? 0 : -10);
}

/* sceMcSync: 1 = the request has finished (its number and result are returned), -1 = nothing was pending. */
int sceMcSync(int mode, u32 cmd_, u32 result_) {
    int *cmd = P_(cmd_), *result = P_(result_);
    (void)mode;
    if (getenv("BT2_MC_LOG") != NULL) { fprintf(stderr, "mc: sync mode %d last %d\n", mode, sLastCmd); }
    if (sLastCmd == 0) {
        return -1;
    }
    if (cmd != NULL) { *cmd = sLastCmd; }
    if (result != NULL) { *result = sLastResult; }
    sLastCmd = 0;
    return 1;
}
