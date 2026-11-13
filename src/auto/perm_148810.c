
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
M2C_UNK BtlScene_Reset(M2C_UNK);
M2C_UNK BtlTask_Kill(s32);
M2C_UNK EftShot_SetCharPool(s32);
extern void *D_00387760;
void func_00148810(s32 arg0)
{
  void *temp_s1;
  temp_s1 = (*((s32 *) (((u8 *) D_00387760) + 4))) + (arg0 * 0x270);
  if ((*((s32 *) (((u8 *) temp_s1) + 0x25C))) != 0)
  {
    BtlScene_Reset((!(arg0 != 0)) ? (2) : (3));
    EftShot_SetCharPool(arg0);
    BtlTask_Kill(*((s32 *) (((u8 *) temp_s1) + 0x25C)));
    *((s32 *) (((u8 *) temp_s1) + 0x25C)) = 0;
  }
}
