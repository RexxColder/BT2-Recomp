
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
extern M2C_UNK D_003B0F7C __attribute__((section(".data")));
s32 func_002A72C8(s32 arg0)
{
  s32 var_v1;
  u8 *new_var;
  if (arg0 == 0)
  {
    var_v1 = 0x1F;
    new_var = &D_003B0F7C;
    do
    {
      var_v1 -= 1;
      *((new_var = (u8 *) new_var) + 0xC) = 0;
      new_var += 0x68;
    }
    while (var_v1 >= 0);
  }
  return 1;
}
