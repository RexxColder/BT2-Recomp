
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
extern M2C_UNK D_00344BD0 __attribute__((section(".data")));
void func_002998B0(s32 arg0, s32 arg1, s32 arg2)
{
  s32 *p = &D_00344BD0 + (arg0 & 0xFF);
  p[0] = arg1;
  p[2] = arg2;
}
