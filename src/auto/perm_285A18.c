
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
void GfxDepthFog_BuildClut(s32 arg0)
{
  s32 temp_v0;
  s32 temp_v1;
  s32 var_a1;
  s8 temp_a0;
  void *temp_v1_2;
  var_a1 = 0;
  do
  {
    temp_v1 = (var_a1 & 0xE7) | ((var_a1 & 8) * 2);
    temp_a0 = (-1) - var_a1;
    temp_v0 = ((s32) (var_a1 & 0x10)) >> 1;
    var_a1 += 1;
    temp_v1_2 = arg0 + ((temp_v1 | temp_v0) * 4);
    *((s8 *) (((u8 *) temp_v1_2) + 3)) = temp_a0;
    *((s8 *) (((u8 *) temp_v1_2) + 1)) = 0;
    *((s8 *) (((u8 *) temp_v1_2) + 2)) = 0;
    *((s8 *) (((u8 *) temp_v1_2) + 0)) = 0;
  }
  while (var_a1 < 0x100);
}
