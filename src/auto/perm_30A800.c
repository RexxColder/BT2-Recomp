
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
M2C_UNK func_00307968(s32);
M2C_UNK func_00307980();
M2C_UNK func_00307998();
M2C_UNK func_003079B0();
M2C_UNK func_003079E0();
s32 func_0030A9B0(s32);
extern s32 D_00367418 __attribute__((section(".data")));
s32 func_0030A800(void)
{
  s32 temp_a0;
  s32 temp_v0;
  temp_v0 = func_0030A9B0(D_00367418);
  temp_a0 = temp_v0 < 2;
  if (temp_v0 != 1)
  {
    if (temp_a0 == 0)
    {
      switch (temp_v0)
      {
        case 2:
          func_00307968(temp_a0);
          goto block_8;

        case 3:
          func_00307968(temp_a0);
          func_00307980();
          func_00307998();
          func_003079B0();
          func_003079E0();

        default:
          goto block_8;
          return 0;

      }

    }
    else
    {
      goto block_9;
    }
  }
  else
  {
    block_8:
    block_9:
    return 0;


  }
}
