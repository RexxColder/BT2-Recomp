
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
s32 func_002C3210(s32);
M2C_UNK func_002CCFB0(s32);
M2C_UNK func_002CDE80();
extern s32 D_00346E2C __attribute__((section(".data")));
void func_002CCF58(void)
{
  s32 *var_s0;
  s32 var_s1;
  int new_var;
  var_s0 = &D_00346E2C;
  var_s1 = 7;
  do
  {
    if (func_002C3210(*var_s0) == 0)
    {
      func_002CCFB0(*var_s0);
    }
    new_var = 4;
    var_s1 -= (new_var = 1);
    var_s0 += new_var;
  }
  while (var_s1 >= 0);
  func_002CDE80();
}
