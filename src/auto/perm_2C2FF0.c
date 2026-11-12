
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
M2C_UNK func_002C3060(M2C_UNK *);
extern M2C_UNK D_00346DC4 __attribute__((section(".data")));
inline int inline_fn(void *arg0, int arg1)
{
  return arg0 == arg1;
}

s32 func_002C2FF0(void *arg0, s32 arg1)
{
  s32 temp_v0;
  s32 var_v0;
  var_v0 = 0;
  if (arg1 != 0)
  {
    if (inline_fn(arg0, 0))
    {
      func_002C3060(&D_00346DC4);
    }
    else
    {
      func_002C3060(arg0 + 0x9F8);
      temp_v0 = *((s32 *) (((u8 *) arg0) + 0x48));
      var_v0 = temp_v0;
      if (temp_v0 > 0)
      {
        *((s32 *) (((u8 *) arg0) + 0x48)) = (s32) (-var_v0);
      }
    }
    var_v0 = arg1;
  }
  return var_v0;
}
