#include "common.h"
#include "battle/hud_0.h"
#include "sys/pad.h"
#include "sys/heap.h"

/*
 * Battle pause menu, part 2: the menu engine. Source range 0x213238-0x215010.
 *
 * A menu is a BtlMenu with an array of BtlMenuItem; an item may open a sub menu. One tree is shown at a time
 * (BtlMenuWork.top). Each frame PauseMenu_Update calls BtlMenu_Update on the top menu, which recurses into the
 * open sub menu; only the deepest open menu takes input. PauseMenu_Draw draws the deepest open menu only.
 *
 * Input (game button words of the owner's pad, gPad[pad]):
 *   up / down       pressed word: move the cursor (wraps, steps over disabled items); sound 0
 *   cross           pressed word (PADG_CROSS): confirm the item under the cursor
 *   triangle        pressed word: close the menu (state 2); the top menu also closes on start, and only
 *                   when `which` is 0 (the result menu cannot be closed)
 *   the skill list reads the repeat word itself (PauseMenu_SkillListFunc)
 *
 * Opening and closing take 6 frames each: the box grows from / shrinks to the parent's size in equal steps.
 * A menu's box is centred on the 512 x 448 screen.
 *
 * Drawing uses one sprite sheet (a texture file inside the common file) uploaded at TBP 0x2A40 / CBP 0x2A00
 * each frame the menu is shown, and the font module for the item texts.
 *
 * The engine reads the pad (game button words, Pad_GetLastStatus) and writes only menu state; it draws no
 * random numbers and reads no clock or camera. What a menu does to the battle is in the item callbacks and
 * in PauseMenu_Update (hud_0.c). It runs only while the battle is paused or over.
 *
 * Original quirks: `pad` may be -1 for "nobody" (the input tests are skipped), but gPad[pad], text[pad] and
 * Pad_GetLastStatus(pad) are still evaluated with it; BtlMenu_CallItem stores a leaf callback's result in the
 * "menu shown" word (no leaf item of the shipped menus has a callback); the controls page always asks for
 * pad type 0.
 */

extern BtlMenuWork *gBtlMenu;
extern void *gCommonRes;

extern void *memset(void *dst, s32 c, u32 n);
extern u64 *Dma_BeginDirect(void);
extern void Dma_EndDirect(u64 *end);
extern void Gfx_PutDefaultEnv(u64 **pkt);
extern void TexFile_UploadAll(BtlMenuTexFile *file, s32 tbp, s32 cbp); /* TexFile_UploadAll (gfxm_b.txt, not linked yet) */
extern void Res_RelocateOffsets(BtlMenuTexFile **out, BtlMenuTexFile *base, BtlMenuTexFile *hdr);
extern s32 Battle_GetMode(void);
extern s32 Pad_GetLastStatus(s32 pad);
extern s32 Snd_PlaySe(u32 mask, s32 id);
extern s32 Font_GetCmdCount(void);
extern void Font_Flush(s32 first);
extern s32 Font_GetGlyphHeight(void);
extern s32 Font_GetWidth(u16 *str);
extern void Font_Print(u16 *str);
extern void Font_NewLine(void);
extern void Font_PushStyle(void);
extern void Font_PopStyle(void);
extern void Font_PushCursor(void);
extern void Font_PopCursor(void);
extern void Font_SetHome(s32 x, s32 y);
extern void Font_SetScale(f32 scale);
extern void Font_SetSpacing(s32 x, s32 y);
extern void Font_SetAlign(s32 align);
extern void Font_SetShadowMode(s32 mode);
extern void Font_SetShadowOffset(s32 x, s32 y);
extern void Font_SetColorRGBA(s32 r, s32 g, s32 b, s32 a);
extern void Font_SetShadowColorRGBA(s32 r, s32 g, s32 b, s32 a);
extern void FontIcon_SetPadType(s32 type);
extern void FontIcon_ResetAnim(void);
extern void BtlText_DrawList(u64 **pkt, s32 x0, s32 x1, s32 y0, s32 y1, s32 mode);
extern void BtlText_DrawScrollBar(u64 **pkt, s32 unused, s32 x, s32 y0, s32 y1);
extern void BtlText_CountEntries(void);

/* Starts a direct packet with the default 2D state, then two A+D registers: TEST_1 = 0 (no alpha / depth
   test) and ZBUF_1 = 0x1310000E0 (depth writes masked). */
void BtlMenu_BeginDraw(u64 **pkt);

/* Sends the packet. */
void BtlMenu_EndDraw(u64 **pkt);

/* Writes one textured sprite: corners in screen pixels, UV in texels, pixels of sheet entry `tex` with the
   CLUT of entry `clut`. REGLIST GIF tag with 8 registers (PRIM, NOP, TEX0_1, RGBAQ, UV, XYZ2, UV, XYZ2);
   PRIM 0x156 = sprite, textured, blended, UV coordinates; Q = 1.0f; Z = 0xFFFFFFF0; screen offset (0x700, 0x720). */
void BtlMenu_PutSprite(u64 **pkt, s32 x0, s32 y0, s32 x1, s32 y1, s32 u0, s32 v0, s32 u1, s32 v1, u32 color,
                       s32 tex, s32 clut);

/* Fills a box with mirrored copies of one texture around the box centre: halves = 1 gives a left and a right
   copy (texture drawn at double size), anything else four quarter copies. */
void BtlMenu_PutMirrored(u64 **pkt, s32 x0, s32 x1, s32 y0, s32 y1, u32 color, s32 tex, s32 clut, s32 halves);

/* TEX0 for the pixels of sheet entry `tex` and the CLUT of entry `clut` (TCC on). */
u64 BtlMenu_GetTex0(s32 tex, s32 clut);

/* Uploads the sprite sheet. */
void BtlMenu_UploadTex(void);

/* The pad type used in battle mode 5. */
s32 BtlMenu_GetDefaultPadType(void);

/* 1 when the menu is the skill-list page. */
s32 BtlMenu_IsSkillList(BtlMenu *menu) {
    return menu->items->type == BTL_MENU_ITEM_SKILLS;
}

/* 1 when the menu is the controls page. */
s32 BtlMenu_IsControls(BtlMenu *menu) {
    return menu->items->type == BTL_MENU_ITEM_CONTROLS;
}

/* String n of the common file's offset table. */
u16 *BtlMenu_GetText(s32 n);

/* Text of a menu item. */
u16 *BtlMenu_GetItemText(s32 n);

/* Text of the controls page for a pad type and a control configuration. */
u16 *BtlMenu_GetControlsText(s32 padType, s32 config);

/* Finds the item with an id in a menu or its sub menus (depth first). */
BtlMenuItem *BtlMenu_FindItem(BtlMenu *menu, s32 id);

/* Finds the menu that holds the item with an id. */
BtlMenu *BtlMenu_FindOwner(BtlMenu *menu, s32 id);

/* Box width: 20 / 22 glyph heights for the two special pages, else the widest item text (at least 128),
   times the scale, plus the margins. */
s32 BtlMenu_GetWidth(BtlMenu *menu);

/* Box height: 18 / 15 glyph heights for the two special pages, else 28 per item, times the scale, plus margins. */
s32 BtlMenu_GetHeight(BtlMenu *menu);

/* 1 when the open index points at an item that has a sub menu. */
s32 BtlMenu_HasOpenSub(BtlMenu *menu);

/* Draws row `part` (h texels high) of sheet entry `tex`, w x h pixels, with (x, y) its top-left corner or,
   when `centered`, its centre. */
void BtlMenu_DrawPart(u64 **pkt, s32 x, s32 y, s32 w, s32 h, s32 tex, s32 part, s32 centered);

/* Draws a box with sheet entry kind + 1. */
void BtlMenu_DrawFrame(u64 **pkt, s32 x0, s32 x1, s32 y0, s32 y1, s32 kind);

/* Draws the skill list's page bar: sheet entry 4 with the CLUT of entry 0x26 + page. */
void BtlMenu_DrawPageBar(u64 **pkt, s32 x0, s32 x1, s32 y0, s32 y1, s32 page);

/* Draws the tab of a skill-list page: sheet entry 3 with the CLUT of entry 0x26 + page, 50 pixels per tab. */
void BtlMenu_DrawPageTab(u64 **pkt, s32 x, s32 y, s32 page);

/* Draws a menu: the growing box while it opens or closes; when active, the deepest open menu's box and
   contents (skill list, controls page, or the item texts). */
void BtlMenu_Draw(u64 **pkt, BtlMenu *menu);

/* Calls the callback of an active item. A non-zero result ends the item's activity; for a leaf item the
   result also becomes the "menu shown" word. */
void BtlMenu_CallItem(BtlMenu *menu, s32 idx, s32 leaf);

/* Wraps the cursor into range and moves it forward to an item that is not disabled (not on the two special
   pages). */
void BtlMenu_FixCursor(BtlMenu *menu);

/* Marks the menu as shown. */
void BtlMenu_SetActive(void);

/* Marks the menu as hidden. */
void BtlMenu_ClearActive(void);

/* Allocates the work (0x120 bytes, heap 2) and binds the sprite sheet: entry 7 of the common file's table. */
void BtlMenu_Init(void);

/* Frees the work. */
void BtlMenu_Term(void);

/* Draws the shown tree: uploads the sheet, builds one direct packet, then flushes the font commands added. */
void BtlMenu_DrawAll(void);

/* Returns the work. */
BtlMenuWork *BtlMenu_GetWork(void);

/* Sets the tree to draw. */
void BtlMenu_SetTop(BtlMenu *menu);

/* One frame of a menu for controller port `pad` (parent = the menu it was opened from, NULL for the top).
   Returns 1 when the menu has finished closing. */
s32 BtlMenu_Update(s32 which, BtlMenu *parent, BtlMenu *menu, s32 pad);

/* Value of the item with an id (0 when there is none). */
s32 BtlMenu_GetValue(BtlMenu *menu, s32 id);

/* Sets the value of the item with an id. */
void BtlMenu_SetValue(BtlMenu *menu, s32 id, s32 value);

/* The "confirmed once" word of the item with an id. */
s32 BtlMenu_GetPicked(BtlMenu *menu, s32 id);

/* Sets it. */
void BtlMenu_SetPicked(BtlMenu *menu, s32 id, s32 picked);

/* Enables / disables the item with an id. */
void BtlMenu_SetDisabled(BtlMenu *menu, s32 id, s32 disabled);

/* Closes a tree: no open sub menu, cursor 0, state "open", every item's active / value / picked cleared. */
void BtlMenu_Reset(BtlMenu *menu);

/* Looks for a picked item of type "result" in a tree. Found in the top menu, the item itself is returned;
   found deeper, the top menu's item under the cursor is (the entry the box was opened from). */
BtlMenuItem *BtlMenu_FindResult(BtlMenu *top, BtlMenu *menu);

/* 1 when the item with an id has a sub menu and that sub menu is the open one of its menu. */
s32 BtlMenu_IsSubOpen(BtlMenu *menu, s32 id);

/* Sets the skill-list script. */
void BtlMenu_SetScript(u16 *text);

/* Sets the second script. */
void BtlMenu_SetScript2(u16 *text);

/* Returns the skill-list script. */
u16 *BtlMenu_GetScript(void);

/* Returns the second script. */
u16 *BtlMenu_GetScript2(void);

/* 1 while the menu is shown. */
s32 BtlMenu_IsActive(void);
