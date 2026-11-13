
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
u32 func_002F4590();
s32 func_002BE878(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
  int new_var;
  new_var = 0;
  return ((float) (func_002F4590(r_a0) < 2U)) == new_var;
}
