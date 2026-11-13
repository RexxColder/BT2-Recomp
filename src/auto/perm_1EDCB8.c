
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
M2C_UNK func_003126C8(s32, s32);
extern void *D_00387A40;
void func_001EDCB8(s32 arg0, s32 arg1)
{
  func_003126C8(*((s32 *) (((u8 *) D_00387A40) + 8)) + (arg0 * 0x1520) + 0x9A0, arg1);
}
