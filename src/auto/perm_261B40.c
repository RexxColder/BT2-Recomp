
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
M2C_UNK func_0028BB60(s32);
extern M2C_UNK D_00388A48 __attribute__((section(".data")));
void func_00261B40(void)
{
  s32 temp_v0_3;
  u8 *new_var;
  s32 temp_v0_2;
  s32 var_s1;
  s32 temp_v0;
  new_var = &D_00388A48;
  var_s1 = 0xF;
  do
  {
    if ((*((s32 *) (((u8 *) new_var) + 0))) & 1)
    {
      temp_v0 = *((s32 *) (((u8 *) new_var) + 0x24));
      if (temp_v0 != 0)
      {
        func_0028BB60(temp_v0);
        *((s32 *) (((u8 *) new_var) + 0x24)) = 0;
      }
      temp_v0_2 = *((s32 *) (((u8 *) new_var) + 0x28));
      if (temp_v0_2 != 0)
      {
        func_0028BB60(temp_v0_2);
        *((s32 *) (((u8 *) new_var) + 0x28)) = 0;
      }
      temp_v0_3 = *((s32 *) (((u8 *) new_var) + 0x2C));
      if (temp_v0_3 != 0)
      {
        func_0028BB60(temp_v0_3);
        new_var = (u8 *) new_var;
        *((s32 *) (new_var + 0x2C)) = 0;
      }
      *((s32 *) (((u8 *) new_var) + 0)) = (s32) ((*((s32 *) (((u8 *) new_var) + 0))) & (~1));
    }
    var_s1 -= 1;
    new_var += 0x30;
  }
  while (var_s1 >= 0);
}
