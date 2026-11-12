#include "m2c_macros.h"

M2C_UNK (*Gsc_FindHandler(u16))(M2C_UNK, void *);   /* extern */
M2C_UNK Gsc_ResetOperands();                        /* extern */
void *List_GetHead(M2C_UNK *);                      /* extern */
void *List_GetNext(void *);                         /* extern */
extern u8 D_00387DB4;
extern void *gGscCurTask;
extern M2C_UNK gGscTaskList __attribute__((section(".data")));

void func_0029F2B0(void) {
    M2C_UNK (*temp_s0)(M2C_UNK, void *);
    void *temp_v1;
    void *var_s1;

    if (D_00387DB4 != 0) {
        var_s1 = List_GetHead(&gGscTaskList);
        if (var_s1 != NULL) {
            do {
                gGscCurTask = var_s1;
                temp_v1 = M2C_FIELD(var_s1, void **, 0x18);
                if ((M2C_FIELD(temp_v1, s32 *, 0) & 0xF) == 1) {
                    temp_s0 = Gsc_FindHandler(M2C_FIELD(temp_v1, u16 *, 2));
                    Gsc_ResetOperands();
                    temp_s0(3, var_s1 + 0x2C);
                }
                var_s1 = List_GetNext(var_s1);
            } while (var_s1 != NULL);
        }
        gGscCurTask = NULL;
    }
}
