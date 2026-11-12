
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
inline u8 *inline_fn(s32 arg0, s32 arg1)
{
  return ((u8 *) (arg0 + (arg1 * 0x74))) + 0x1318;
}

void func_002C0E10(s32 arg0, s32 arg1, s32 arg2)
{
  if (arg1 != 8)
  {
    *((s32 *) inline_fn(arg0, arg1)) = arg2;
  }
}
