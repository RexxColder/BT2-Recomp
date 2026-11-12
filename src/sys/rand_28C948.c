#include "common.h"
#include "sys/rand.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void srand(u32 seed);
extern s32 rand(void);
extern long func_00339410(void);

extern u32 gRandState[RAND_N];
extern s32 gRandIndex;
extern u32 gRandMag01[2];

/* Seeds the twister state from one 32-bit value (MT19937 init_genrand). */
void Rand_Seed(u32 seed) {
    gRandState[0] = seed;
    for (gRandIndex = 1; gRandIndex < RAND_N; gRandIndex++) {
        gRandState[gRandIndex] =
            1812433253ULL * (gRandState[gRandIndex - 1] ^ (gRandState[gRandIndex - 1] >> 30)) + gRandIndex;
    }
}

/* Seeds the twister state from an array of words (MT19937 init_by_array). */
void Rand_SeedByArray(u32 *key, s32 keyLen);

/* Returns the next 32-bit random number (MT19937 genrand_int32).
 * The refill lacks the reference code's second loop (kk = N-M .. N-2), so words 227..622 of the state
 * are never regenerated: this is not a true MT19937 sequence. */
u32 Rand_Next(void);

/* Seeds libc rand from the hardware timer, then seeds the twister with four rand() words. */
void Rand_Init(void);

/* Returns a random number in [0, n), or 0 when n is 0. */
u32 Rand_Range(u32 n);
