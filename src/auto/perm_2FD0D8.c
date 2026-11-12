
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
M2C_UNK func_002FCDF0(s8 *);
extern s32 D_003553EC __attribute__((section(".data")));
extern s8 D_003553F0 __attribute__((section(".data")));
void func_002FD0D8(void)
{
  s32 temp_v0;
  s32 var_s1;
  int new_var;
  s8 *var_s0;
  temp_v0 = D_003553EC - 1;
  D_003553EC = temp_v0;
  if (temp_v0 == 0)
  {
    new_var = 1;
    var_s0 = &D_003553F0;
    var_s1 = 0xF;
    do
    {
      if ((*var_s0) == new_var)
      {
        func_002FCDF0(var_s0);
      }
      var_s1 -= new_var;
      var_s0 += 0x44;
    }
    while (var_s1 >= 0);
  }
}
