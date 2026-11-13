
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
M2C_UNK func_002C32B0();
M2C_UNK func_002C32C8();
s32 func_002CCB08();
s32 func_002CD700();
s32 func_002CD880();
s32 func_002CD650(s32 arg0)
{
  s32 sp[4];
  s32 var_s2;
  s32 var_v0;
  void *temp_s1;
  temp_s1 = arg0 + 0x950;
  func_002C32B0(sp);
  var_s2 = 0;
  var_v0 = *((s32 *) (((u8 *) temp_s1) + 0x20));
  if (var_v0 == 0)
  {
    if (func_002CD700(arg0) != 0)
    {
      *((s32 *) (((u8 *) temp_s1) + 0x20)) = 1;
      *((s32 *) (((u8 *) temp_s1) + 0x24)) = (s32) ((*((s32 *) (((u8 *) temp_s1) + 0x24))) + 1);
      var_v0 = func_002CCB08(arg0, 1);
      goto block_5;
    }
  }
  else
    if (func_002CD880(arg0) != 0)
  {
    *((s32 *) (((u8 *) temp_s1) + 0x20)) = 0;
    var_v0 = func_002CCB08(arg0, 0);
    block_5:
    var_s2 = var_v0;

  }
  func_002C32C8(sp);
  return var_s2;
}
