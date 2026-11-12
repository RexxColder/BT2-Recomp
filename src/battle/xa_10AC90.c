#include "common.h"

/* Winner side of the battle (BattleResult_GetWinnerSide, battle result module). */
extern s32 BattleResult_GetWinnerSide(void);
/* Flag test of the original's func_0028C648 (0 when clear). */
extern s32 func_0028C648(void);

/* Sets word +4 of obj to the winning side, or 0 when word +0 is 1; does nothing while func_0028C648 is set.
 * Always returns 0. */
s32 BtlResult_SetWinnerSide(void *obj) {
    if (func_0028C648() != 0) {
        return 0;
    }
    if (*(s32 *)obj == 1) {
        *(s32 *)((u8 *)obj + 4) = 0;
    } else {
        *(s32 *)((u8 *)obj + 4) = BattleResult_GetWinnerSide();
    }
    return 0;
}
