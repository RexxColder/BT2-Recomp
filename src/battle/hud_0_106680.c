#include "common.h"
#include "battle/hud_0.h"
#include "battle/battle.h"
#include "sys/pad.h"

/*
 * Battle pause menu, part 1. Source range 0x2129C8-0x213238.
 *
 * The first three functions are the end of the battle-level wrappers of btl_tech_b.c (BtlGame_*). The rest is
 * the pause menu proper: it owns no state of its own except gPauseMenuWhich; the menu trees are data
 * (0x2C4E70-0x2C6070) and the engine that runs them is hud_0_b.c (BtlMenu_*).
 *
 * PauseMenu_Update(pad, which) is called by the battle sequence: with which = 0 from the fight state while
 * BATTLE_FLAG_PAUSE_MENU is set (the pause menu), with which = 1 from the end state in battle mode 0 (the
 * result menu). It returns 0 once the menu has closed itself (only the pause menu can: triangle / start on its
 * top level); it clears BATTLE_FLAG_PAUSE itself in that case. A picked item of type "result" ends the battle
 * through BattleResult_Set(BTL_RESULT_ABORT, reason); the reason bit is chosen by the item id:
 *
 *   id 0x0C, 0x13  0x8000      id 0x0D  0x10       id 0x0E  0x80      id 0x0F  0x08      id 0x10  0x100
 *   id 0x11        0x400       id 0x12  0x200      id 0x14  0x40 (pad 0: 0x20)            id 0x15  0x20
 *   id 0x16        nothing     id 0x17  0x1000     id 0x18, 0x19  0x10000                 id 0x1A  0x20
 *
 * (0x8000 / 0x10000 are the two restart bits, BTL_REASON_RESTART.)
 */

extern s32 gBtlGameReplayActive;
extern s32 gPauseMenuWhich;

extern BtlMenu gPauseMenuVersus;
extern BtlMenu gPauseMenuResultVersus;
extern BtlMenu gPauseMenuReplayRec;
extern BtlMenu gPauseMenuResultReplayRec;
extern BtlMenu gPauseMenuReplayPlay;
extern BtlMenu gPauseMenuResultReplayPlay;
extern BtlMenu gPauseMenuMode1;
extern BtlMenu gPauseMenuResultMode1;
extern BtlMenu gPauseMenuMode2;
extern BtlMenu gPauseMenuMode3;
extern BtlMenu gPauseMenuMode4;
extern BtlMenu gPauseMenuMode5;
extern BtlMenu gPauseMenuMode6;
extern BtlMenu gPauseMenuMode7;
/* The cursor words (BtlMenu + 0x18) of the yes / no box at 0x2C4F00 and of the CPU level menu at 0x2C5158. */
extern s32 gPauseMenuConfirmCursor[8];
extern s32 gPauseMenuCpuLevelCursor[8];

/* Local view of the battle object: only the skill-list script pointer is used. */
typedef struct PauseMenuObj {
    /* 0x00 */ u8 unk0[0xBC];
    /* 0xBC */ u16 *skillText;
} PauseMenuObj;

extern void Hud_Draw(void); /* Hud_Draw (config/symbols/hud_a.txt, not linked yet) */
extern void BtlScript_UpdateView(void);
extern s32 BtlSeq_IsFighting(void);
extern s32 Battle_GetMode(void);
extern s32 BattleReplay_IsActive(void);
extern s32 BattleReplay_IsLoaded(void);
extern s32 BattleSide_GetObjId(s32 side);
extern PauseMenuObj *BtlObj_Get(s32 id);
extern void BattleResult_Set(s32 flags, s32 reason);
extern s32 Snd_PlaySe(u32 mask, s32 id);
extern void Adx_ResumeSeVoice(void);
extern void FontIcon_ResetAnim(void);
extern s32 BtlAiMgr_GetLevel(s32 side);
extern void BtlAiMgr_SetLevel(s32 side, s32 level);
extern s32 CpuLevel_ToSetting(s32 level);   /* internal CPU level -> menu difficulty 0..4, -1 when off */
extern s32 CpuLevel_FromSetting(s32 setting); /* menu difficulty 0..4 -> internal CPU level 0, 6, 13, 21, 29 */

/* Draws the battle's 2D layers: the HUD, the script's view update, then the pause menu. */
void BtlGame_Draw(void);

/* 1 while the battle sequence is in the fight state. */
s32 BtlGame_IsFighting(void);

/* 1 when the battle is a replay being played (latched by BtlGame_Reset). */
s32 BtlGame_IsReplay(void);

/* Returns the menu tree for the battle: which = 0 the pause menu, 1 the result menu (modes 0 and 1 only). */
BtlMenu *PauseMenu_GetMenu(s32 which);

/* Item callback of the yes / no box: when the item is confirmed, clears the values of items 1 and 0 and puts
   the box's cursor on its third line. */
s32 PauseMenu_ConfirmFunc(BtlMenuEvent *ev);

/* Item callback of the skill list: left / right change the page (wrapping), up / down move the entry cursor
   (clamped) and scroll the 7-line window. Reads the owner pad's repeat word. */
s32 PauseMenu_SkillListFunc(BtlMenuEvent *ev);

/* Item callback of the CPU level menu: on confirm, clears its six lines and puts the cursor on the current
   level of side 1 (line 1 = off); while the menu is active, writes the cursor's level back every frame. */
s32 PauseMenu_CpuLevelFunc(BtlMenuEvent *ev);

/* Round reset: closes both trees. */
void PauseMenu_Reset(void) {
    BtlMenu_Reset(PauseMenu_GetMenu(0));
    BtlMenu_Reset(PauseMenu_GetMenu(1));
    gPauseMenuWhich = 0;
}

/* Battle start: allocates the menu work. */
void PauseMenu_Init(void);

/* Battle end: frees it. */
void PauseMenu_Term(void);

/* One frame of the pause menu (which = 0) or the result menu (which = 1) for controller port `pad`.
   Returns 0 when the menu closed (pause flag cleared, voices resumed), else 1. */
s32 PauseMenu_Update(s32 pad, s32 which);

/* Draws the menu when it is shown. */
void PauseMenu_Draw(void);
