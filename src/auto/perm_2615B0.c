
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
void *func_00261060(s32);
extern s32 D_003B2654 __attribute__((section(".data")));
s32 func_002615B0(s32 arg0)
{
  s32 var_v0;
  var_v0 = 0;
  if (!(D_003B2654 & 0x100))
  {
    var_v0 = *((s32 *) (((u8 *) func_00261060(arg0 & 0xFFFF)) + 0xBD0));
    var_v0 = var_v0 != 0;
  }
  return var_v0;
}
