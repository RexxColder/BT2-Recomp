#include "common.h"

/* Walks the 4-byte words after the first until one has bit 3 clear; returns that word. */
s32 Gsc_DumpCommand(s32 *words) {
    s32 word;

    do {
        words++;
        word = *words;
    } while (word & 8);
    return word;
}
