#include "common.h"

extern s32 D_0038768C;
extern s32 D_00387690;
extern s32 D_00387694;
extern s32 func_002EB648();
extern s32 func_002EC6B0();
extern s32 func_0028BAA8();
extern void func_002EC0C8();
extern s32 func_002EC990();
extern void func_002EF218();
extern void func_002EBB08();

s32 func_00101220(s32 arg0) {
    s32 status;

    D_0038768C = func_002EB648(arg0, 0);
    D_00387690 = func_002EC6B0(D_0038768C);
    D_00387694 = func_0028BAA8(D_00387690 << 11);
    func_002EC0C8(D_0038768C, D_00387690, D_00387694);
    do {
        status = func_002EC990(D_0038768C);
        func_002EF218();
    } while (status != 3);
    func_002EBB08(D_0038768C);
    D_0038768C = 0;
    return D_00387694;
}
