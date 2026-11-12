
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
M2C_UNK func_003053C8(M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_0037F898 __attribute__((section(".data")));
extern M2C_UNK D_0037F8C8 __attribute__((section(".data")));
extern M2C_UNK D_0037F908 __attribute__((section(".data")));
extern M2C_UNK D_0037F918 __attribute__((section(".data")));
void func_003057E8(void *arg0, s32 arg1, s32 arg2)
{
  if (arg0 == 0)
  {
    func_003053C8(&D_0037F908, &D_0037F898);
    return;
  }
  if ((*((s8 *) (((u8 *) arg0) + 4))) == 0)
  {
    func_003053C8(&D_0037F918, &D_0037F8C8);
    return;
  }
  *((s32 *) (((u8 *) arg0) + 0x28)) = arg1;
  *((s32 *) (((u8 *) arg0) + 0x2C)) = arg2;
}
