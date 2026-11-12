#include "common.h"

void func_002F2108(s32 side);
void func_002F1DD8(s32 side);
void func_002F21A0(s32 side);
void func_002F1E48(s32 side);

/* Clears then sets the control flag of one side: calls func_002F2108, then tail calls func_002F1DD8. */
void func_002BD748(s32 side) {
    func_002F2108(side);
    func_002F1DD8(side);
}

/* Same pair for the other control table: calls func_002F21A0, then tail calls func_002F1E48. */
void func_002BD770(s32 side) {
    func_002F21A0(side);
    func_002F1E48(side);
}
