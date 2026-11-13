
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
M2C_UNK func_0025BA28(u8, s32);
extern u8 D_003876A8;
void func_0025B860(s32 arg0)
{
  int new_var;
  func_0025BA28(D_003876A8, arg0 & (0xFFFF ^ 0));
  if (0 != D_003876A8)
  {
    new_var = 0;
    D_003876A8 = (float) new_var;
  }
}
