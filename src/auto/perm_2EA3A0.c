
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
inline int inline_fn(s32 arg0)
{
  return arg0 != 0;
}

void func_002EA3A0(void)
{
  s32 var_v0;
  var_v0 = 0xC350;
  do
  {
    var_v0 -= 1;
  }
  while (inline_fn(var_v0));
}
