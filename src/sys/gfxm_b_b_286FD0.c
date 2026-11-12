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
void TexChain_WriteTags(TexChain chain);

/* The round-up of the end offset to 64 bytes is INSIDE the `if (next == 0)` that leaves the walk. The compiler
   copies the loop's exit test, body of the `if` included, in front of the loop, so each exit path has its own
   copy of the round-up until cross-jumping merges them after register allocation. With the round-up behind the
   loop, 3 instructions differ: cse then knows the offset is still 0x10 on the first-chunk path
   (`addiu s0,v0,16` for the original's `addu s0,v0,s0`) and the temporary of the alignment test is alone in its
   block and takes v0 (v1 in the original, where it shares a block with the size load). */
/* Builds the chunk list and the DMA chain of a whole chunked file, in the free space behind its chunks. */
TexChain TexChain_Build(u8 *file);

/* TexChain_Build, then moves every chunk's destination by `cbp` blocks. */
TexChain TexChain_BuildAt(u8 *file, s32 unused, s32 cbp);

/* Same walk as TexChain_Build. The pair count is a local set once at the top (the constant is then loaded behind
   the call's argument and the result copy avoids v0), and ONE counter serves the skip loop and the pair loop, a
   plain `for` (both counters are a3 in the original). */
/* Builds the list and chain of one pair of chunks (`index`-th pixel + CLUT pair) of a chunked file. Every pair has
   its own 0x20-byte list and 0x40-byte tag area behind the chunks. */
TexChain TexChain_BuildPair(u8 *file, s32 index);

/* Builds the chains of the first `count` pairs of a chunked file and moves each one's destination by `cbp`. */
void TexChain_BuildPairs(TexChain *out, u8 *file, s32 cbp, s32 count);

/* Adds `add` to the destination block pointer (word 9 of the packet) of every chunk of a chain. */
void TexChain_AddCbp(TexChain chain, s32 add);

/* Returns the GS size exponent (TW / TH) for a texture dimension; the screen sizes 112, 224, 448 and 640 round up. */
s32 Tex_Log2Size(s32 size);

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
void GfxClut_InitPacket(GfxClutWork *work, u16 cbp) {
    u32 *w = (u32 *)work;
    u64 blt = (u64)cbp << 32;
    u32 endTag = DMA_TAG_END; /* a local set at the top, while the REF tag is a constant in the last statement:
                                 with the constant written at its store, a2 and v1 are exchanged */

    work->cbp = cbp;
    w[0] = 0;
    w[1] = 0;
    w[2] = 0;
    w[3] = VIF_DIRECT | 0x48;
    w[4] = GIF_EOP | 4;
    w[5] = 0x10000000;
    w[6] = GIF_REG_AD;
    w[7] = 0;
    w[8] = blt;
    w[9] = blt >> 32;
    w[10] = 0x50;
    w[11] = 0;
    w[12] = 0;
    w[13] = 0;
    w[14] = 0x51;
    w[15] = 0;
    w[16] = 16;
    w[17] = 16;
    w[18] = 0x52;
    w[19] = 0;
    w[20] = 0;
    w[21] = 0;
    w[22] = 0x53;
    w[23] = 0;
    w[24] = GIF_EOP | 0x40;
    w[25] = 0x08000000;
    w[26] = 0;
    w[27] = 0;
    w[0x470 / 4] = GIF_EOP | 1;
    w[0x474 / 4] = 0x10000000;
    w[0x478 / 4] = GIF_REG_AD;
    w[0x47C / 4] = 0;
    w[0x480 / 4] = 0;
    w[0x484 / 4] = 0;
    work->clut = (u8 *)&w[28];
    w[0x488 / 4] = GS_TEXFLUSH;
    w[0x48C / 4] = 0;
    work->ref[1] = (u32)work;
    work->ref[2] = 0;
    work->ref[3] = 0;
    work->end[0] = endTag;
    work->end[1] = 0;
    work->end[2] = 0;
    work->end[3] = 0;
    work->ref[0] = DMA_TAG_REF | 0x49;
}
