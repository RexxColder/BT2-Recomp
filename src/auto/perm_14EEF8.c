
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
M2C_UNK FlashShapePool_Term(s32);
M2C_UNK func_001817D0(s32);
void func_0014EEF8(u8 **arg0, s32 arg1)
{
  s32 var_a0;
  s32 var_s0;
  s32 var_s1;
  s32 var_s2;
  s32 var_s4;
  var_s2 = arg1;
  var_s4 = 1;
  do
  {
    if ((*((u8 *) (((u8 *) (*arg0)) + 0))) != 0)
    {
      func_001817D0(var_s2 + 0x324);
    }
    var_s1 = 0;
    if ((*((u8 *) (((u8 *) (*arg0)) + 0x550))) != 0)
    {
      var_s0 = var_s2 + 0x370;
      var_a0 = var_s0;
      do
      {
        FlashShapePool_Term(var_a0);
        var_s1 += 1;
        var_s0 += 4;
        var_a0 = var_s0;
      }
      while (var_s1 < ((s32) (*((u8 *) (((u8 *) (*arg0)) + 0x550)))));
    }
    var_s4 -= 1;
    var_s2 += 0x364;
  }
  while (var_s4 >= 0);
}
