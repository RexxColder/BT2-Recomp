
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
M2C_UNK func_00304618(M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_0037F6F0 __attribute__((section(".data")));
extern M2C_UNK D_0037F740 __attribute__((section(".data")));
void func_003049E8(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  if ((arg0 == 0) || (0 == arg1))
  {
    func_00304618(&D_0037F740, &D_0037F6F0);
    return;
  }
  *((s32 *) (((u8 *) arg0) + 0x1C)) = arg1;
  *((s32 *) (((u8 *) arg0) + 0x20)) = arg2;
  *((s32 *) (((u8 *) arg0) + 0x24)) = arg3;
}
