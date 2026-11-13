
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
void func_0029DEB8(void *arg0, void *arg1, void *arg2)
{
  f32 temp_f5;
  f32 temp_f5_2;
  f32 temp_f5_3;
  f32 temp_f5_4;
  temp_f5 = *((f32 *) (((u8 *) arg1) + 0x30));
  *((f32 *) (((u8 *) arg0) + 0)) = (f32) ((((((*((f32 *) (((u8 *) arg2) + 0))) * (*((f32 *) (((u8 *) arg1) + 0)))) + ((*((f32 *) (((u8 *) arg2) + 4))) * (*((f32 *) (((u8 *) arg1) + 0x10))))) + ((*((f32 *) (((u8 *) arg2) + 8))) * (*((f32 *) (((u8 *) arg1) + 0x20))))) + ((*((f32 *) (((u8 *) arg2) + 0xC))) * temp_f5)) + temp_f5);
  temp_f5_2 = *((f32 *) (((u8 *) arg1) + 0x34));
  *((f32 *) (((u8 *) arg0) + 4)) = (f32) ((((((*((f32 *) (((u8 *) arg2) + 0))) * (*((f32 *) (((u8 *) arg1) + 4)))) + ((*((f32 *) (((u8 *) arg2) + 4))) * (*((f32 *) (((u8 *) arg1) + 0x14))))) + ((*((f32 *) (((u8 *) arg2) + 8))) * (*((f32 *) (((u8 *) arg1) + 0x24))))) + ((*((f32 *) (((u8 *) arg2) + 0xC))) * temp_f5_2)) + temp_f5_2);
  temp_f5_3 = *((f32 *) (((u8 *) arg1) + 0x38));
  *((f32 *) (((u8 *) arg0) + 8)) = (f32) ((((((*((f32 *) (((u8 *) arg2) + 0))) * (*((f32 *) (((u8 *) arg1) + 8)))) + ((*((f32 *) (((u8 *) arg2) + 4))) * (*((f32 *) (((u8 *) arg1) + 0x18))))) + ((*((f32 *) (((u8 *) arg2) + 8))) * (*((f32 *) (((u8 *) arg1) + 0x28))))) + ((*((f32 *) (((u8 *) arg2) + 0xC))) * temp_f5_3)) + temp_f5_3);
  ;
  *((f32 *) (((u8 *) arg0) + 0xC)) = (f32) ((((((*((f32 *) (((u8 *) arg2) + 0))) * (*((f32 *) (((u8 *) arg1) + 0xC)))) + ((*((f32 *) (((u8 *) arg2) + 4))) * (*((f32 *) (((u8 *) arg1) + 0x1C))))) + ((*((f32 *) (((u8 *) arg2) + 8))) * (*((f32 *) (((u8 *) arg1) + 0x2C))))) + ((*((f32 *) (((u8 *) arg2) + 0xC))) * (*((f32 *) (((u8 *) arg1) + 0x3C))))) + (*((f32 *) (((u8 *) arg1) + 0x3C))));
}
