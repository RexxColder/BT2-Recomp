
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
void *BtlObjVis_GetView_207EA0(s32);
extern void *D_00387A40;
void func_0020CB20(void)
{
  s32 var_a0;
  void *temp_v0;
  var_a0 = 0;
  if ((*((s32 *) (((u8 *) D_00387A40) + 4))) > 0)
  {
    var_a0 = 0;
    do
    {
      temp_v0 = BtlObjVis_GetView_207EA0(var_a0);
      var_a0 += 1;
      if (temp_v0 != 0)
      {
        *((s32 *) (((u8 *) temp_v0) + 0xAF0)) = (s32) ((*((s32 *) (((u8 *) temp_v0) + 0xAF0))) | 2);
      }
      var_a0 = var_a0;
    }
    while (var_a0 < (*((s32 *) (((u8 *) D_00387A40) + 4))));
  }
}
