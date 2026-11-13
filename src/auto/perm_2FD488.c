
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
M2C_UNK func_002FD3C0(s8 *);
s32 func_00307B90(s32 *);
extern s32 D_00356010 __attribute__((section(".data")));
extern s8 D_00356080 __attribute__((section(".data")));
void func_002FD488(void)
{
  int new_var;
  s32 var_s1;
  s8 *var_s0;
  if (func_00307B90(&D_00356010) != 0)
  {
    var_s0 = &D_00356080;
    new_var = 1;
    var_s1 = 0x27;
    do
    {
      if ((*var_s0) == new_var)
      {
        func_002FD3C0(var_s0);
      }
      var_s1 -= 1;
      var_s0 += 0x48;
    }
    while (var_s1 >= 0);
    D_00356010 = 0;
  }
}
