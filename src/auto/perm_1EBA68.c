
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
extern M2C_UNK func_001EB270 __attribute__((section(".data")));

#ifdef __mips__
#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)&func_001EB270)
#else
#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
#endif

void func_001EBA68(void *arg0, s32 arg1, s32 arg2)
{
  void *temp_a0;
  if ((arg0 != 0) && LOOP_IS_UPDATE((*(*((s32 **) (((u8 *) arg0) + 0x28))))))
  {
    temp_a0 = *((void **) (((u8 *) arg0) + 0x38));
    if (((*((void **) (((u8 *) arg0) + 0x38))) != 0) && (((*((u16 *) (((u8 *) (*((void **) (((u8 *) arg0) + 0x38)))) + 0x60))) & 1) & 0xFFFF))
    {
      *((s32 *) (((u8 *) temp_a0) + 0)) = arg1;
      *((s32 *) (((u8 *) temp_a0) + 0x38)) = arg2;
    }
  }
}
