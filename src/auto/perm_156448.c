
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
M2C_UNK func_00195900(s32);
void func_00156448(void *arg0)
{
  s32 *new_var;
  s32 temp_v0;
  s32 var_s2;
  void *temp_s1;
  temp_s1 = *((void **) (((u8 *) arg0) + 0x38));
  var_s2 = 0;
  if ((*((s32 *) (((u8 *) temp_s1) + 0xAA0))) > 0)
  {
    arg0 = temp_s1 + 0xAA4;
    do
    {
      new_var = arg0;
      temp_v0 = *new_var;
      if (temp_v0 != 0)
      {
        func_00195900(temp_v0);
        *new_var = 0;
      }
      var_s2 += 1;
      arg0 += 4;
    }
    while (var_s2 < (*((s32 *) (((u8 *) temp_s1) + 0xAA0))));
  }
}
