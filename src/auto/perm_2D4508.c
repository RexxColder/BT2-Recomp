
asm(".include \"labels.inc\"\n");;
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
M2C_UNK IVec4_SetZero();
extern M2C_UNK D_00399D50 __attribute__((section(".data")));
void func_002D4508(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
  M2C_UNK *new_var;
  IVec4_SetZero(r_a0);
  new_var = &D_00399D50;
  *((s32 *) (((u8 *) new_var) + 4)) = (s32) ((*((s32 *) (((u8 *) new_var) + 4))) - 1);
}
