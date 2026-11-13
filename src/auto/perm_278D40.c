
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
M2C_UNK func_00279288();
M2C_UNK func_0028BB60(void *);
extern void *gOt;
void func_00278D40(void)
{
  func_00279288();
  func_0028BB60(*((void **) (((u8 *) gOt) + 0x28)));
  func_0028BB60(gOt);
  gOt = 0;
}
