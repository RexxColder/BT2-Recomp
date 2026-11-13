
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
M2C_UNK func_002FFB40(s8 *);
M2C_UNK func_003007D0(M2C_UNK, M2C_UNK);
M2C_UNK func_00300890();
M2C_UNK memset(s8 *, M2C_UNK, M2C_UNK);
extern s32 D_00357108 __attribute__((section(".data")));
extern s8 D_00357110 __attribute__((section(".data")));
void func_00300918(void)
{
  s32 temp_v0;
  int new_var;
  s32 var_s1;
  s8 *var_s0;
  temp_v0 = D_00357108 - 1;
  D_00357108 = temp_v0;
  if (temp_v0 == 0)
  {
    var_s0 = &D_00357110;
    new_var = 1;
    var_s1 = 0x1F;
    do
    {
      if ((*var_s0) == new_var)
      {
        func_002FFB40(var_s0);
      }
      var_s1 -= 1;
      var_s0 += 0x238;
    }
    while (var_s1 >= 0);
    memset(&D_00357110, 0, 0x4700);
    func_00300890();
    func_003007D0(0, 0);
  }
}
