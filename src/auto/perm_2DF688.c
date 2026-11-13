
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
M2C_UNK func_002DFBC8();
M2C_UNK func_003061A8();
inline int inline_fn(s32 arg0, s32 arg1)
{
  return arg0 + arg1;
}

s32 func_002DF688(void *arg0, void **arg1)
{
  s32 sp[4];
  s32 temp_a1;
  s32 temp_s1;
  s32 temp_v1;
  temp_s1 = arg0 + 0x38C;
  (*((M2C_UNK (**)(void **, M2C_UNK, M2C_UNK, s32)) (((u8 *) (*arg1)) + 0x18)))(arg1, 1, 0x7FFFFFFF, temp_s1);
  temp_v1 = *((s32 *) (((u8 *) arg0) + 0x38C));
  temp_a1 = temp_v1 & (~3);
  func_003061A8(temp_s1, inline_fn(inline_fn(temp_a1, ((s32) ((temp_v1 - temp_a1) * 8)) >> 3), 4) - temp_v1, temp_s1, sp);
  (*((M2C_UNK (**)(void **, M2C_UNK, s32)) (((u8 *) (*arg1)) + 0x20)))(arg1, 0, temp_s1);
  (*((M2C_UNK (**)(void **, M2C_UNK, void *)) (((u8 *) (*arg1)) + 0x1C)))(arg1, 1, sp);
  func_002DFBC8(arg1);
  return 0;
}
