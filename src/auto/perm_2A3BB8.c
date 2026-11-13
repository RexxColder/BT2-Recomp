
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
s32 func_00100ED0(M2C_UNK, M2C_UNK, s32);
extern u8 D_003876A8;
extern M2C_UNK D_003B0F44 __attribute__((section(".data")));
void func_002A3BB8(s32 arg0, M2C_UNK arg1)
{
  int new_var;
  new_var = arg0;
  *((&D_003B0F44) + new_var) = func_00100ED0(arg1, 0, D_003876A8 != 0);
  new_var = new_var * 4;
  if (D_003876A8 != 0)
  {
    D_003876A8 = 0;
  }
}
