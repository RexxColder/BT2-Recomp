#include "common.h"

void func_0026EBC0(s32 arg0, s32 arg1, s32 arg2);
void func_0024A350(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2, s32 t3, s32 st0, s32 st8);
void func_0024A6D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2, s32 t3, s32 st0);
void func_0026EA58(s32 arg0);
void BattleSetup_Finish(void);
extern u8 *D_003879B0;
extern u8 D_00375C80[] __attribute__((section(".data")));
extern u8 D_00375C98[] __attribute__((section(".data")));
extern u8 D_00375CB0[] __attribute__((section(".data")));
extern u8 D_00375CC8[] __attribute__((section(".data")));
extern u8 D_00375CE0[] __attribute__((section(".data")));
extern u8 D_00375CF8[] __attribute__((section(".data")));
extern u8 D_00375D10[] __attribute__((section(".data")));

void func_00250DC0(s32 arg0) {
    u8 buf[16];
    s32 base;

    func_0026EBC0((s32)(D_003879B0 + 0x1C), (s32)D_00375C80, (s32)buf);
    func_0024A350((s32)(D_003879B0 + 0x1C), (s32)buf, 0, 0, *(s32 *)(D_003879B0 + 0x04), arg0 + 1, 1, 0x17C, -0x80, 0x40);
    func_0026EBC0((s32)(D_003879B0 + 0x1C), (s32)D_00375C98, (s32)buf);
    func_0024A6D8((s32)(D_003879B0 + 0x1C), (s32)buf, 0, 0, *(s32 *)(D_003879B0 + 0x08), 1, 0, (s32)0xFFFF0080, 0x40);
    func_0026EBC0((s32)(D_003879B0 + 0x1C), (s32)D_00375CB0, (s32)buf);
    func_0024A6D8((s32)(D_003879B0 + 0x1C), (s32)buf, 0, 0, *(s32 *)(D_003879B0 + 0x08), 2, 0, (s32)0xFFFF0080, 0x40);
    func_0026EBC0((s32)(D_003879B0 + 0x1C), (s32)D_00375CC8, (s32)buf);
    func_0024A6D8((s32)(D_003879B0 + 0x1C), (s32)buf, 0, 0, *(s32 *)(D_003879B0 + 0x08), 3, 0, (s32)0xFFFF0080, 0x40);
    func_0026EBC0((s32)(D_003879B0 + 0x1C), (s32)D_00375CE0, (s32)buf);
    func_0024A6D8((s32)(D_003879B0 + 0x1C), (s32)buf, 0, 0, *(s32 *)(D_003879B0 + 0x0C), arg0 + 1, 0, -0x80, 0x6040);
    func_0026EBC0((s32)(D_003879B0 + 0x1C), (s32)D_00375CF8, (s32)buf);

    base = (arg0 * 3) * 16;
    base = base + *(s32 *)(D_003879B0 + 0x18);
    func_0024A6D8((s32)(D_003879B0 + 0x1C), (s32)buf, 0, 0, *(s32 *)(D_003879B0 + 0x10), *(s32 *)(base + 0x20) + 1, 0, -0x80, 0x6040);
    func_0026EBC0((s32)(D_003879B0 + 0x1C), (s32)D_00375D10, (s32)buf);

    base = (arg0 * 3) * 16;
    base = base + *(s32 *)(D_003879B0 + 0x18);
    func_0024A6D8((s32)(D_003879B0 + 0x1C), (s32)buf, 0, 0, *(s32 *)(D_003879B0 + 0x14), *(s32 *)(base + 0x24) + 1, 0, -0x80, 0x6040);
    func_0026EA58((s32)(D_003879B0 + 0x1C));
    BattleSetup_Finish();
}
