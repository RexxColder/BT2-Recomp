
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
extern void *D_00387A40;
extern s32 D_003B2654 __attribute__((section(".data")));
void func_00261A08(unsigned short arg0)
{
  void *temp_v1;
  if (!(D_003B2654 & 0x100))
  {
    temp_v1 = (*((s32 *) (((u8 *) D_00387A40) + 8))) + ((arg0 & 0xFFFF) * 0x1520);
    *((s32 *) (((u8 *) temp_v1) + 0xAF0)) = (s32) ((*((s32 *) (((u8 *) temp_v1) + 0xAF0))) | 0x04000000);
  }
}
