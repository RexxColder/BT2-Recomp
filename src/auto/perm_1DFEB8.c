
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
M2C_UNK func_001E1550(f32, void *, s32, s32, s32);
void func_001DFEB8(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 var_s2;
  f32 new_var;
  s32 var_s3;
  s32 var_s4;
  s32 var_s5;
  void *new_var2;
  void *var_s0;
  void *var_s1;
  var_s0 = arg0;
  var_s3 = arg3;
  var_s3 = var_s3 & 0xFF;
  var_s4 = arg2;
  var_s5 = arg1;
  if ((*((u8 *) (((u8 *) var_s0) + 0x21DA))) != 0)
  {
    var_s2 = 0;
    if ((*((u8 *) (((u8 *) var_s0) + 0x21CC))) != 0)
    {
      new_var2 = var_s0;
      var_s1 = new_var2;
      do
      {
        new_var = *((f32 *) (0x21D0 + ((u8 *) new_var2)));
        var_s2 += 1;
        func_001E1550(new_var, var_s1, var_s5, var_s4, var_s3);
        var_s1 = var_s1 + 0x1B0;
 do { } while (0);
      }
      while (var_s2 < ((s32) (*((u8 *) (((u8 *) var_s0) + 0x21CC)))));
    }
  }
}
