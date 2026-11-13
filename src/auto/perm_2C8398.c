
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
void func_002C8398(void *arg0, void *arg1)
{
  *((s32 *) (((u8 *) arg1) + 0)) = (s32) (*((s32 *) (((u8 *) arg0) + 0x10)));
  *((s32 *) (((u8 *) arg1) + 4)) = (s32) (*((s32 *) (((u8 *) arg0) + 0x1C)));
  *((s32 *) (((u8 *) arg1) + 8)) = (s32) (*((s32 *) (((u8 *) arg0) + 0x20)));
  *((s32 *) (((u8 *) arg1) + 0xC)) = (s32) (*((s32 *) (((u8 *) arg0) + 0x24)));
  *((s32 *) (((u8 *) arg1) + 0x10)) = (s32) (*((s32 *) (((u8 *) arg0) + 0x28)));
  *((s32 *) (((u8 *) arg1) + 0x14)) = (s32) (*((s32 *) (((u8 *) arg0) + 0x2C)));
  *((s32 *) (((u8 *) arg1) + 0x18)) = (s32) (*((s32 *) (((u8 *) arg0) + 0x14)));
  *((s16 *) (((u8 *) arg1) + 0x1C)) = (s16) ((s8) (*((u8 *) (((u8 *) arg0) + 0x54))));
  *((s16 *) (((u8 *) arg1) + 0x1E)) = 0;
}
