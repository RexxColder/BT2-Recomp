
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
extern M2C_UNK D_0035D260 __attribute__((section(".data")));
s32 func_003029C8(u32 arg0)
{
  if (arg0 < 2U) {
    return *(&D_0035D260 + arg0);
  }
  return 0;
}
