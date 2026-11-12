#include "common.h"

void func_0026EB78(s32 arg0, s32 arg1);
void func_002711A0(void);
void func_002711E8(void);
s32 func_00284DE0(s32 arg0);
void func_00284E68(s32 arg0, s32 arg1, f32 farg0);
void func_0028B090(void);
void func_0028B218(s32 arg0, s32 arg1);
void func_0028BDA0(void);
void func_00298158(s32 arg0);
void func_002987A0(void);
void func_00298A20(void);
void func_00299110(void);
void func_00299380(void);
s32 func_002A8678(void);
extern u8 D_00387D98[] __attribute__((section(".data")));
extern u8 D_0038B058[] __attribute__((section(".data")));

void func_002998D8(void) {
    u8 *p = D_0038B058;
    s32 temp_s0;
    s32 var_a1;
    s32 var_a2;
    s32 temp_v0;
    u8 *var_v1;

    func_00298158(1);
    func_002987A0();
    if (func_00284DE0(0) != 0) {
        func_00284E68(0, 1, 1.0f);
    }
    do {
loop_3:
        func_002711A0();
        temp_s0 = func_002A8678();
        func_0028B090();
        func_0028BDA0();
        func_00298A20();
        func_00299380();
        func_002711E8();
        func_00299110();
        *(s32 *)(p + 4) = *(s32 *)(p + 4) + 1;
        if (temp_s0 == 0) {
            if (!(*(u8 *)(p + 0) & 1)) {
                func_0026EB78(*(s32 *)(p + 8), (s32)D_00387D98);
                *(u8 *)(p + 1) = 0x25;
                *(u8 *)(p + 0) = *(u8 *)(p + 0) | 2;
                var_v1 = p + 0x28;
                var_a2 = 0;
                var_a1 = 6;
                do {
                    *(s16 *)(var_v1 - 4) = 3;
                    var_a1 -= 1;
                    *(s16 *)(var_v1 + 0) = 1;
                    var_v1 += 6;
                    *(s32 *)((u8 *)(var_a2 + *(s32 *)(p + 0x20)) + 0xA4) = 0x80;
                    var_a2 += 0x38;
                } while (var_a1 >= 0);
            }
            *(u8 *)(p + 0) = *(u8 *)(p + 0) | 1;
        }
        if (!(*(u8 *)(p + 0) & 1)) {
            goto loop_3;
        }
        temp_v0 = *(u8 *)(p + 1) - 1;
        *(u8 *)(p + 1) = (u8)temp_v0;
    } while ((s8)temp_v0 != -1);
    func_0028B218(-1, (s32)D_0038B058);
    func_00298158(0);
}
