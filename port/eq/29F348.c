#include "common.h"

s32 Gsc_CallAction(s32 arg0, s32 arg1);
s32 (*Gsc_FindHandler(u16 arg0, s32 arg1))(s32, u8 *);
void Gsc_FreeTask(u8 *arg0, s32 arg1);
u8 *Gsc_NextCommand(u8 *arg0);
void Gsc_ResetOperands();
s32 func_0029F6F8(s32 arg0);
extern void *gGscCurTask;

void Gsc_StepTask(u8 *arg0) {
    s32 (*s2)(s32, u8 *);
    u8 *pc;
    u8 *s1;
    s32 opcode;
    s32 s3;
    s32 s4;

    gGscCurTask = arg0;
    s4 = 1;
    while (s4 != 0) {
        pc = *(u8 **)(arg0 + 0x18);
        opcode = *(s32 *)pc & 0xF;
        switch (opcode) {
        case 0:
            s4 = 0;
            Gsc_FreeTask(arg0, opcode);
            break;
        case 3:
            if (!(*(s32 *)(arg0 + 0x20) & 1)) {
                *(s32 *)(arg0 + 0x28) = Gsc_CallAction(*(s16 *)(pc + 2), 3);
                *(s32 *)(arg0 + 0x20) = *(s32 *)(arg0 + 0x20) | 1;
            }
            if (func_0029F6F8(*(s32 *)(arg0 + 0x28)) != 0) {
                s4 = 0;
            } else {
                *(s32 *)(arg0 + 0x20) = 0;
                *(s32 *)(arg0 + 0x24) = 0;
                *(u8 **)(arg0 + 0x18) = pc + 4;
            }
            break;
        case 2:
            Gsc_CallAction(*(s16 *)(pc + 2), 2);
            *(s32 *)(arg0 + 0x20) = 0;
            *(s32 *)(arg0 + 0x24) = 0;
            *(u8 **)(arg0 + 0x18) = pc + 4;
            break;
        case 1:
            s3 = 0;
            s2 = Gsc_FindHandler((u16)*(u16 *)(pc + 2), 1);
            s1 = arg0 + 0x2C;
            if (!(*(s32 *)(arg0 + 0x20) & 1)) {
                Gsc_ResetOperands();
                s3 = s2(0, s1);
                *(s32 *)(arg0 + 0x20) = *(s32 *)(arg0 + 0x20) | 1;
            }
            if (s3 == 0) {
                Gsc_ResetOperands();
                if (s2(2, s1) == 0) {
                    s4 = 0;
                    *(s32 *)(arg0 + 0x24) = *(s32 *)(arg0 + 0x24) + 0xA;
                    break;
                }
            }
            Gsc_ResetOperands();
            s2(1, s1);
            pc = Gsc_NextCommand(*(u8 **)(arg0 + 0x18));
            *(s32 *)(arg0 + 0x20) = 0;
            *(u8 **)(arg0 + 0x18) = pc;
            *(s32 *)(arg0 + 0x24) = 0;
            break;
        }
    }
}
