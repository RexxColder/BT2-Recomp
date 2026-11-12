#include "common.h"

void func_00191238(void);

/*
 * The class table (D_00342018 and friends) is original data: its first word is the PS2 address of the update
 * (0x00191238), while func_00191238 here is the PC address of the ported C version. Comparing them directly
 * always fails, so every blast looked dead: the shot cleared its slot (task = 0), its manager returned
 * "no blast alive", and the shot killed itself while the blast task kept running (B28: the ultimate orb stayed
 * anchored at the firing point, with its hitbox). Same workaround as IS_PTCL in src/battle/xc_1BC010.c.
 */
#ifdef __mips__
#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_00191238)
#else
#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00191238u)
#endif

s32 func_00191728(u8 *arg0) {
    u8 *v1;

    if (arg0 == NULL) {
        return 0;
    }
    v1 = *(u8 **)(arg0 + 0x28);
    if (!BLAST_IS_UPDATE(*(void **)v1)) {
        return 0;
    }
    v1 = *(u8 **)(arg0 + 0x38);
    return (*(s32 *)(v1 + 0x30) & 1) != 0;
}
