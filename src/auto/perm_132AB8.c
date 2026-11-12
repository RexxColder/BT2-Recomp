
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
M2C_UNK BtlTaskList_AddTail(s32, s32, M2C_UNK);
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK);
s32 func_00132B50(s32);
extern M2C_UNK D_00340088 __attribute__((section(".data")));
extern void *gEftStage;
void func_00132AB8(void)
{
  s32 var_s1;
  u8 *new_var;
  if ((*((s32 *) (((u8 *) gEftStage) + 0))) == 0)
  {
    var_s1 = 0xA;
    *((s32 *) (((u8 *) gEftStage) + 0)) = BtlTask_CreateChildList(*((s32 *) (((u8 *) gEftStage) + 4)), 0xB, 0);
    new_var = &D_00340088;
    new_var = (u8 *) new_var;
    do
    {
      if (((*((s32 *) (new_var + 0))) != 0) && (func_00132B50(*((s32 *) (((u8 *) new_var) + 4))) != 0))
      {
        BtlTaskList_AddTail(*((s32 *) (((u8 *) gEftStage) + 0)), *((s32 *) (((u8 *) new_var) + 0)), 0);
      }
      var_s1 -= 1;
      new_var += 8;
    }
    while (var_s1 >= 0);
  }
}
