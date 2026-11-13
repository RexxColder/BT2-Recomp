
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
s32 func_002B61E0();
M2C_UNK func_002BB530(s32);
s32 func_002BC550(s32);
M2C_UNK func_002BD180(M2C_UNK);
s32 func_002BD3A8();
extern s32 D_00345344 __attribute__((section(".data")));
void func_002BD3C8(void)
{
  s32 temp_v0;
  s32 temp_s2;
  s32 temp_v0_2;
  s32 var_s0;
  s32 var_s1;
  temp_s2 = D_00345344;
  if (temp_s2 == 1)
  {
    temp_v0 = func_002B61E0();
    temp_v0_2 = func_002BC550(temp_v0 + 0x58);
    if (temp_v0_2 == temp_s2)
    {
      if (func_002BD3A8() != temp_v0_2)
      {
        var_s1 = 7;
        var_s0 = temp_v0 + 0x6C;
        do
        {
          if (var_s0 != 0)
          {
            func_002BB530(var_s0);
          }
          var_s1 -= 1;
          var_s0 += 0x304;
        }
        while (var_s1 >= 0);
      }
      func_002BD180(0);
    }
  }
}
