
asm(".include \"labels.inc\"\n");;
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long u64;
typedef float f32;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
M2C_UNK memset(s32, M2C_UNK, s32);
void func_002CF2C8(void *arg0, s32 arg1, s32 arg2)
{
  s32 var_s0;
  void *var_s2;
  s32 var_s1;
  var_s1 = arg1 + 7;
  var_s1 &= ~7;
  var_s0 = arg2 - (var_s1 - arg1);
  var_s2 = arg0;
  memset(var_s1, 0, var_s0);
  var_s0 = (var_s0 < 0) ? (var_s0 + 0xF) : (var_s0);
  *((s32 *) (((u8 *) var_s2) + 0)) = var_s1;
  var_s0 = var_s0 >> 4;
  *((s32 *) (((u8 *) var_s2) + 0x10)) = 0;
  *((s32 *) (((u8 *) var_s2) + 8)) = 0;
  *((s32 *) (((u8 *) var_s2) + 0xC)) = 0;
  *((s32 *) (((u8 *) var_s2) + 4)) = var_s0;
}
