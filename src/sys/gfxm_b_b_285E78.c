#include "common.h"
/*
 * Chunked upload files and texture files (0x109938..0x10A6E0): DMA chains built inside a chunked file, the
 * pointer fix-up of a texture file, the uploads of its textures and the packet of a run-time CLUT.
 * Proper name: tex_file.c. Split from gfxm_b.c because nothing here draws: it is the texture library that the
 * whole game calls (Res_RelocateOffsets has about 700 callers).
 */
#include "sys/dma.h"
#include "sys/gfxm_b.h"
#include "sys/gfxm_b_b.h"

extern void *memset(void *dst, s32 c, u32 n);

TexChain TexChain_Build(u8 *file);
TexChain TexChain_BuildPair(u8 *file, s32 index);
void TexChain_AddCbp(TexChain chain, s32 add);
void Tex_UploadPixels(TexEntry *e, s32 tbp);
void Tex_UploadClut(TexEntry *e, s32 cbp);

/* Writes the DMA chain of a chunk list: one REF tag per chunk, then an END tag. */
void TexChain_WriteTags(TexChain chain) {
    u32 i;
    s32 n = 0;

    for (i = 0; i < chain.count; i++) {
        chain.tags[n++] = DMA_TAG_REF + chain.list[i].size / 16;
        chain.tags[n++] = (u32)chain.list[i].data;
        chain.tags[n++] = 0;
        chain.tags[n++] = 0;
    }
    chain.tags[n++] = DMA_TAG_END;
    chain.tags[n++] = 0;
    chain.tags[n++] = 0;
    chain.tags[n++] = 0;
}

/* The round-up of the end offset to 64 bytes is INSIDE the `if (next == 0)` that leaves the walk. The compiler
   copies the loop's exit test, body of the `if` included, in front of the loop, so each exit path has its own
   copy of the round-up until cross-jumping merges them after register allocation. With the round-up behind the
   loop, 3 instructions differ: cse then knows the offset is still 0x10 on the first-chunk path
   (`addiu s0,v0,16` for the original's `addu s0,v0,s0`) and the temporary of the alignment test is alone in its
   block and takes v0 (v1 in the original, where it shares a block with the size load). */
/* Builds the chunk list and the DMA chain of a whole chunked file, in the free space behind its chunks. */
TexChain TexChain_Build(u8 *file) {
    TexChain chain;
    TexChunkHdr *hdr;
    s32 ofs = 0x10;
    s32 n = 1;
    s32 size;

    hdr = (TexChunkHdr *)file;
    while (1) {
        s32 next = hdr->next;

        if (next == 0) {
            ofs = hdr->size + ofs;
            if (ofs % 64 != 0) {
                ofs = ofs / 64 * 64 + 64;
            }
            break;
        }
        ofs += next;
        n++;
        hdr = (TexChunkHdr *)(file + ofs);
        ofs += 0x10;
    }
    memset(&chain, 0, sizeof(chain));
    chain.list = (TexChainEnt *)(file + ofs);
    chain.file = file;
    size = n * 16;
    if (size % 64 != 0) {
        size = size / 64 * 64 + 64;
    }
    ofs += size;
    chain.tags = (u32 *)(file + ofs);
    n = 0;
    ofs = 0;
    do {
        hdr = (TexChunkHdr *)(file + ofs);
        ofs += 0x10;
        chain.list[n].tag = hdr->tag;
        if (hdr->next == 0) {
            chain.list[n].size = hdr->size;
        } else {
            chain.list[n].size = hdr->next;
        }
        chain.list[n].data = (u32 *)(file + ofs);
        n++;
        ofs += hdr->next;
    } while (hdr->next != 0);
    chain.count = n;
    TexChain_WriteTags(chain);
    return chain;
}

/* TexChain_Build, then moves every chunk's destination by `cbp` blocks. */
TexChain TexChain_BuildAt(u8 *file, s32 unused, s32 cbp) {
    TexChain chain;

    chain = TexChain_Build(file);
    TexChain_AddCbp(chain, cbp);
    return chain;
}

/* Same walk as TexChain_Build. The pair count is a local set once at the top (the constant is then loaded behind
   the call's argument and the result copy avoids v0), and ONE counter serves the skip loop and the pair loop, a
   plain `for` (both counters are a3 in the original). */
/* Builds the list and chain of one pair of chunks (`index`-th pixel + CLUT pair) of a chunked file. Every pair has
   its own 0x20-byte list and 0x40-byte tag area behind the chunks. */
TexChain TexChain_BuildPair(u8 *file, s32 index) {
    TexChain chain;
    TexChunkHdr *hdr;
    s32 ofs = 0x10;
    s32 n = 1;
    s32 size;
    s32 i;
    s32 count = 2;

    hdr = (TexChunkHdr *)file;
    while (1) {
        s32 next = hdr->next;

        if (next == 0) {
            ofs = hdr->size + ofs;
            if (ofs % 64 != 0) {
                ofs = ofs / 64 * 64 + 64;
            }
            break;
        }
        ofs += next;
        n++;
        hdr = (TexChunkHdr *)(file + ofs);
        ofs += 0x10;
    }
    memset(&chain, 0, sizeof(chain));
    chain.list = (TexChainEnt *)(file + ofs + index * 0x20);
    chain.file = file;
    size = n * 16;
    if (size % 64 != 0) {
        size = size / 64 * 64 + 64;
    }
    ofs += size;
    chain.tags = (u32 *)(file + ofs + index * 0x40);
    ofs = 0;
    for (i = 0; i < index * 2; i++) {
        hdr = (TexChunkHdr *)(file + ofs);
        ofs += 0x10;
        if (hdr->next == 0) {
            break;
        }
        ofs += hdr->next;
    }
    for (i = 0; i < count; i++) {
        hdr = (TexChunkHdr *)(file + ofs);
        ofs += 0x10;
        chain.list[i].tag = hdr->tag;
        if (hdr->next == 0) {
            chain.list[i].size = hdr->size;
        } else {
            chain.list[i].size = hdr->next;
        }
        chain.list[i].data = (u32 *)(file + ofs);
        if (hdr->next == 0) {
            break;
        }
        ofs += hdr->next;
    }
    chain.count = count;
    TexChain_WriteTags(chain);
    return chain;
}

/* Builds the chains of the first `count` pairs of a chunked file and moves each one's destination by `cbp`. */
void TexChain_BuildPairs(TexChain *out, u8 *file, s32 cbp, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        out[i] = TexChain_BuildPair(file, i);
        TexChain_AddCbp(out[i], cbp);
    }
}

/* Adds `add` to the destination block pointer (word 9 of the packet) of every chunk of a chain. */
void TexChain_AddCbp(TexChain chain, s32 add) {
    u32 i;

    for (i = 0; i < chain.count; i++) {
        chain.list[i].data[9] = add + chain.list[i].data[9];
    }
}

/* Returns the GS size exponent (TW / TH) for a texture dimension; the screen sizes 112, 224, 448 and 640 round up. */
s32 Tex_Log2Size(s32 size) {
    s32 n;

    switch (size) {
        case 2:
            n = 1;
            break;
        case 4:
            n = 2;
            break;
        case 8:
            n = 3;
            break;
        case 16:
            n = 4;
            break;
        case 32:
            n = 5;
            break;
        case 64:
            n = 6;
            break;
        case 112:
            n = 7;
            break;
        case 128:
            n = 7;
            break;
        case 224:
            n = 8;
            break;
        case 256:
            n = 8;
            break;
        case 448:
            n = 9;
            break;
        case 512:
            n = 9;
            break;
        case 640:
            n = 10;
            break;
        default:
            n = 1;
            break;
    }
    return n;
}

/* Turns the word offsets of a texture file into pointers: the entry table and each entry's pixel and CLUT data. */
void Res_RelocateOffsets(TexFile **out, u8 *base, TexFile *hdr);

/* Queues the upload of a texture's pixels to GS block `tbp`. */
void Tex_UploadPixels(TexEntry *e, s32 tbp);

/* Queues the upload of a texture's CLUT to GS block `cbp`. */
void Tex_UploadClut(TexEntry *e, s32 cbp);

/* Uploads every texture of a file, packed one after the other from `tbp` / `cbp`. */
void TexFile_UploadPacked(TexFile *file, s32 tbp, s32 cbp);

/* Uploads texture `index` of a file to the given blocks; a negative block skips that half. */
void TexFile_UploadOne(TexFile *file, s32 index, s32 tbp, s32 cbp);

/* Uploads one texture entry to the given blocks; a negative block skips that half. */
void Tex_Upload(TexEntry *e, s32 tbp, s32 cbp);

/* Uploads textures `first` .. `first + count - 1` at the places TexFile_UploadPacked would give them. */
void TexFile_UploadRangePacked(TexFile *file, s32 first, s32 count, s32 tbp, s32 cbp);

/* Uploads textures `first` .. `first + count - 1` at their own block offsets from `tbp` / `cbp` (negative: skip). */
void TexFile_UploadRange(TexFile *file, s32 first, s32 count, s32 tbp, s32 cbp);

/* Uploads every texture of a file at its own block offset from `tbp` / `cbp`. */
void TexFile_UploadAll(TexFile *file, s32 tbp, s32 cbp);

/* Uploads texture `index` of a file at its own block offset from `tbp` / `cbp`. */
void TexFile_UploadAt(TexFile *file, s32 index, s32 tbp, s32 cbp);

/* Builds the upload packet of a 256-colour CLUT that the caller fills in afterwards: BITBLTBUF to block `cbp`,
   a 16x16 transfer, 0x400 bytes of image data and a TEXFLUSH, plus the REF / END tags that send it. */
void GfxClut_InitPacket(GfxClutWork *work, u16 cbp);
