
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
extern s32 D_00387F2C;
void func_00298460(s32 arg0, s32 arg1, s32 arg2)
{
  s16 *temp_a3_2;
  s32 temp_a0;
  u16 *temp_a3;
  u16 *temp_v1_2;
  s32 var_t0;
  u16 temp_v1;
  int new_var;
  new_var = 2;
  temp_a0 = (arg0 * 4) + 0x1F30;
  temp_a3 = D_00387F2C + temp_a0;
  temp_v1 = *temp_a3;
  if (!((temp_v1 & 1) & 0xFFFF))
  {
    *temp_a3 = temp_v1 | 1;
    temp_v1_2 = D_00387F2C + temp_a0;
    *temp_v1_2 |= new_var;
  }
  var_t0 = 0;
  if (arg2 > 0)
  {
    loop_4:
    temp_a3_2 = (D_00387F2C + new_var) + temp_a0;

    if ((*temp_a3_2) < arg1)
    {
      var_t0 += 1;
      *temp_a3_2 = ((u16) (*temp_a3_2)) + 1;
      if (var_t0 < arg2)
      {
        goto loop_4;
      }
    }
  }
}
