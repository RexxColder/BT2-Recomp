/*
 * Heap del juego en la RAM del PS2 (etapa 4). El C de newlib del juego (malloc, free, ...) se mantiene, pero
 * _malloc_r / _free_r / _memalign_r (que en la consola llaman a sbrk) las sirve el host: un asignador first-fit
 * sobre [HEAP_LO, HEAP_END) con los metadatos FUERA de la RAM del PS2 (el juego pide todo con memalign(0x40,..)).
 *   HEAP_LO  = 0x430590 (D_43058F + 1: lo que func_0028BA70 espera, size = 0x1EFE000 - D_43058F)
 *   HEAP_END = 0x01EFE000
 * Los hilos no existen (un solo hilo), asi que __malloc_lock/unlock son vacios.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>

#define HEAP_LO 0x00430590u
#define HEAP_END 0x01EFE000u

typedef struct Blk { uint32_t addr, size; int used; struct Blk *next; void *bt[8]; int nbt; } Blk;
static Blk *sHead, *sFreeNodes;
static unsigned long sLive, sPeak;
static int sDiag = -1;      /* BT2_HEAPDIAG: -1 sin leer, 0 off, 1 on (se lee una sola vez) */
static int sFailReported = 0;

static Blk *node(void) {
    Blk *b = sFreeNodes;
    if (b) { sFreeNodes = b->next; return b; }
    return malloc(sizeof(Blk));
}
static void init(void) {
    if (sHead) return;
    sHead = node();
    sHead->addr = HEAP_LO; sHead->size = HEAP_END - HEAP_LO; sHead->used = 0; sHead->next = NULL;
}
void heap_dump(void);   /* volcado de diagnostico (top 40 grupos); solo util con BT2_HEAPDIAG=1 */

void heap_dump(void) {
    struct Grp { void *k0, *k1, *k2, *k3; uint32_t size; unsigned long total; int cnt; };
    struct Grp g[256]; int ng = 0, i, j, lim; Blk *q;
    for (q = sHead; q; q = q->next) {
        if (!q->used) continue;
        for (i = 0; i < ng; i++)
            if (g[i].k0 == q->bt[0] && g[i].k1 == q->bt[1] && g[i].k2 == q->bt[2] &&
                g[i].k3 == q->bt[3] && g[i].size == q->size) break;
        if (i == ng) {
            if (ng >= 256) continue;
            g[ng].k0 = q->bt[0]; g[ng].k1 = q->bt[1]; g[ng].k2 = q->bt[2]; g[ng].k3 = q->bt[3];
            g[ng].size = q->size; g[ng].total = 0; g[ng].cnt = 0; ng++;
        }
        g[i].cnt++; g[i].total += q->size;
    }
    for (i = 0; i < ng; i++)   /* orden desc por bytes totales */
        for (j = i + 1; j < ng; j++)
            if (g[j].total > g[i].total) { struct Grp t = g[i]; g[i] = g[j]; g[j] = t; }
    lim = ng < 40 ? ng : 40;
    fprintf(stderr, "bt2full: BT2_HEAPDIAG top %d grupos de bloques usados\n", lim);
    for (i = 0; i < lim; i++) {
        void *fr[4]; fr[0] = g[i].k0; fr[1] = g[i].k1; fr[2] = g[i].k2; fr[3] = g[i].k3;
        fprintf(stderr, "bt2full:   grupo %d: cnt=%d size=0x%X total=0x%lX\n", i, g[i].cnt, g[i].size, g[i].total);
        backtrace_symbols_fd(fr, 4, 2);
    }
}

static uint32_t alloc_aligned(uint32_t align, uint32_t size) {
    Blk *b;
    init();
    if (sDiag < 0) sDiag = getenv("BT2_HEAPDIAG") ? 1 : 0;
    if (align < 16) align = 16;
    size = (size + 15) & ~15u;
    if (size == 0) size = 16;
    for (b = sHead; b; b = b->next) {
        uint32_t a, pad;
        if (b->used) continue;
        a = (b->addr + align - 1) & ~(align - 1);
        pad = a - b->addr;
        if (b->size < pad + size) continue;
        if (pad) {   /* trozo libre delante */
            Blk *n = node();
            n->addr = a; n->size = b->size - pad; n->used = 0; n->next = b->next;
            b->size = pad; b->next = n;
            b = n;
        }
        if (b->size > size) {   /* resto libre detras */
            Blk *n = node();
            n->addr = b->addr + size; n->size = b->size - size; n->used = 0; n->next = b->next;
            b->size = size; b->next = n;
        }
        b->used = 1;
        if (sDiag) {   /* backtrace() saltando 2 frames (backtrace + alloc_aligned) */
            void *tmp[16]; int n = backtrace(tmp, 16), i, skip = 2;
            if (n < 0) n = 0;
            if (skip > n) skip = n;
            for (i = 0; i < 8 && i + skip < n; i++) b->bt[i] = tmp[i + skip];
            for (; i < 8; i++) b->bt[i] = NULL;
            b->nbt = (n - skip) > 8 ? 8 : n - skip;
        }
        sLive += b->size; if (sLive > sPeak) sPeak = sLive;
        return b->addr;
    }
    if (sDiag && !sFailReported) {
        sFailReported = 1;
        heap_dump();
    }
    fprintf(stderr, "bt2full: malloc(0x%X, alineado a 0x%X) no cabe en el heap del juego (vivo 0x%lX)\n", size, align, sLive);
    return 0;
}
static void free_addr(uint32_t p) {
    Blk *b, *prev = NULL;
    if (!sHead || p == 0) return;
    for (b = sHead; b; prev = b, b = b->next) {
        if (b->addr != p) continue;
        if (!b->used) { fprintf(stderr, "bt2full: free doble de 0x%X\n", p); return; }
        b->used = 0; sLive -= b->size;
        if (b->next && !b->next->used) { Blk *n = b->next; b->size += n->size; b->next = n->next; n->next = sFreeNodes; sFreeNodes = n; }
        if (prev && !prev->used) { prev->size += b->size; prev->next = b->next; b->next = sFreeNodes; sFreeNodes = b; }
        return;
    }
    fprintf(stderr, "bt2full: free de 0x%X que no es del heap del juego\n", p);
}

uint32_t _malloc_r(uint32_t r, uint32_t size) { (void)r; return alloc_aligned(16, size); }
uint32_t _memalign_r(uint32_t r, uint32_t align, uint32_t size) { (void)r; return alloc_aligned(align, size); }
void _free_r(uint32_t r, uint32_t p) { (void)r; free_addr(p); }
void __malloc_unlock(uint32_t r) { (void)r; }
