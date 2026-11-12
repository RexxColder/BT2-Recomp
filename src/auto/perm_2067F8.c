
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
s32 BtlChar_GetPos(void *);
s32 BtlObjAnim_GetEventArg(s32, M2C_UNK);
s32 BtlObjAnim_MaskToNode(s32);
s32 BtlObjAnim_QueryEvent(s32, M2C_UNK, M2C_UNK, M2C_UNK);
s32 BtlObjXf_Update();
M2C_UNK func_0019B4A0(s32, s32, s32, s32);
M2C_UNK func_0019B598(s32);
f32 func_001FA308(void *);
s32 func_001FA3A8(s32);
M2C_UNK func_0020FC38(void *, M2C_UNK);
s32 func_00210D98(void *);
s32 func_0023F430(void *);
s32 func_0025FBE8(s32, M2C_UNK);
s32 func_00269A40(s32, s32);
void func_002067F8(void *arg0)
{
  f32 var_f20;
  s32 var_s0;
  s32 var_s1;
  void *var_s2;
  var_s2 = arg0;
  if ((func_001FA3A8(BtlObjXf_Update(arg0)) & 8) && (!(func_00210D98(var_s2) & 0x80)))
  {
    if (func_0025FBE8(*((s32 *) (((u8 *) var_s2) + 0x1530)), 0x20000) != 0)
    {
      var_s1 = func_00269A40(*((s32 *) (((u8 *) var_s2) + 0x1530)), BtlObjAnim_MaskToNode(BtlObjAnim_GetEventArg(*((s32 *) (((u8 *) var_s2) + 0x1530)), 0x20000)));
      var_s0 = func_0023F430(var_s2) & 0x80;
      var_s0 = var_s0 == 0;
      func_0019B4A0(var_s1 + 0x30, BtlChar_GetPos(var_s2) + 0x20, var_s0, *((s32 *) (((u8 *) var_s2) + 0x1534)));
    }
 do { var_f20 = func_001FA308(var_s2); if (((f32) BtlObjAnim_QueryEvent(*((s32 *) (((u8 *) var_s2) + 0x1530)), 0x20000, 0, 0)) < var_f20) { var_f20 = func_001FA308(var_s2); if (var_f20 < ((f32) BtlObjAnim_QueryEvent(*((s32 *) (((u8 *) var_s2) + 0x1530)), 0x40000, 0, 1))) { func_0020FC38(var_s2, 0x51); } } if (func_0025FBE8(*((s32 *) (((u8 *) var_s2) + 0x1530)), 0x40000) != 0) { func_0019B598(*((s32 *) (((u8 *) var_s2) + 0x1534))); func_0020FC38(var_s2, 0x52); } } while (0);
  }
}
