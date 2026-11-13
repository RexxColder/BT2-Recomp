
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
extern void *gEftDisc;
void func_00191B80(void *arg0)
{
  void *temp_a0;
  void *temp_a0_2;
  void *var_a1;
  temp_a0 = *((void **) (((u8 *) arg0) + 0));
  if (temp_a0 != 0)
  {
    var_a1 = temp_a0;
    do
    {
      *((s32 *) (((u8 *) var_a1) + 0)) = 0;
      *((s32 *) (((u8 *) gEftDisc) + 8)) = (s32) ((*((s32 *) (((u8 *) gEftDisc) + 8))) - 1);
      temp_a0_2 = *((void **) (((u8 *) var_a1) + 0x140));
      var_a1 = temp_a0_2;
    }
    while (temp_a0_2 != 0);
  }
  *((s32 *) (((u8 *) arg0) + 4)) = (*((void **) (((u8 *) arg0) + 0)) = 0);
}
