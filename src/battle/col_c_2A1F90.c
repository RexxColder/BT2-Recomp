/*
 * The text printer, whole object: 0x239BB0..0x23C310 (formerly col_b_b.c + col_c.c, merged at integration).
 *
 * First part, 0x239BB0..0x239EA0: the GS packet helpers. Not collision code. Drawing only; nothing here touches
 * the simulation.
 *
 * A packet is written through a CbFontOut (a pointer into the display list). Screen pixel (x, y) becomes the GS
 * primitive coordinate ((x + 0x700) << 4, (y + 0x720) << 4): the window origin is (1792, 1824).
 */
#include "common.h"
#include "battle/col_b.h"

extern u64 *Dma_BeginDirect(void);
extern void Dma_EndDirect(u64 *end);
extern void Gfx_PutDefaultEnv(CbFontOut *out);

/* A rectangle in GS primitive coordinates lies inside the 0..4095 range. */
s32 Font_IsInGsRange(s32 x0, s32 y0, s32 x1, s32 y1);

/* A rectangle in screen pixels overlaps the printer's clip rectangle. */
s32 Font_IsInClip(CbFontClip *clip, s32 x0, s32 y0, s32 x1, s32 y1);

/* Opens a direct packet and writes the text state: the default environment, then CLAMP_1 = 0, TEST_1 = 0,
   TEXA = (0x80, AEM, 0x80), ZBUF_1 (masked) and PRIM = alpha-blended textured sprite with UV coordinates. */
void Font_BeginPacket(CbFontOut *out);

/* Closes the direct packet. */
void Font_EndPacket(CbFontOut *out);

/* Appends one sprite (TEX0, RGBAQ with q = 1.0, two UV / XYZ2 pairs, z = 0xFFFFFF0); dropped when it leaves the
   GS coordinate range. Texel coordinates get the half-texel offset (u * 16 + 8). */
void Font_PutSprite(CbFontOut *out, s32 x0, s32 y0, s32 x1, s32 y1, s32 u0, s32 v0, s32 u1, s32 v1, u32 rgba,
                    u64 tex0);

/* ------------------------------------------------------------------------------------------------------------
 * Second part, 0x239EA0..0x23C310 (the file as its agent wrote it), with its own header and view types. The four
 * packet helpers above that it declared with other parameter types (u64 ** for CbFontOut *, FontCmd * for
 * CbFontClip *) are reached through cast macros (the generated code is the same).
 * ------------------------------------------------------------------------------------------------------------ */
#include "battle/col_c.h"

/*
 * The text printer: 0x239EA0..0x23C310. Text is queued as commands (Font_Print* and friends) with a
 * snapshot of the current style; Font_Flush turns the queue into one GS packet. Drawing only: nothing
 * here is read by the simulation.
 *
 * The original source file starts at 0x239BB0: Font_Flush only matches with Font_BeginPacket and
 * Font_EndPacket defined above it in the same file, which is why the five packet helpers were merged in.
 */

typedef struct FontCommonRes {
    /* 0x00 */ u32 *boot; /* CommonRes.boot: header of byte offsets, +4 / +8 the two fonts, +0x20 the icons */
} FontCommonRes;

extern FontCommonRes *gCommonRes;

extern void *Heap_Alloc(s32 size, u32 align, s32 fromTail, s32 heap);
extern void Heap_Free(void *ptr);
extern void *memset(void *dst, s32 value, u32 size);
extern void Tex_Upload(FontTex *tex, u32 tbp, s32 cbp); /* uploads a texture and its CLUT */
extern void TexFile_UploadAll(void *res, void *tex, void *tex2);

/* 0x239BB0..0x239EA0, defined above with the first part's types. */
#define Font_IsInClip ((s32 (*)(FontCmd *cmd, s32 x0, s32 y0, s32 x1, s32 y1))Font_IsInClip) /* 1 when the box touches the command's clip box */
#define Font_BeginPacket ((void (*)(u64 **pkt))Font_BeginPacket)                                 /* Dma_BeginDirect + the 2D state */
#define Font_EndPacket ((void (*)(u64 **pkt))Font_EndPacket)                                   /* Dma_EndDirect */
#define Font_PutSprite ((void (*)(u64 **pkt, s32 x0, s32 y0, s32 x1, s32 y1, s32 u0, s32 v0, s32 u1, s32 v1, u32 color, u64 tex0))Font_PutSprite)                         /* one textured sprite */

extern FontCursor gFontCursor; /* 0x31C1C0 */
extern FontStyle gFontStyle;   /* 0x31C1D0 */
extern s32 gFontReady;         /* 1 between Font_InitEx and Font_Term */
extern s32 gFontEnabled;
extern s32 gFontGlyphGap;      /* added after every glyph; always 0 */
extern s32 gFontLineHeight;    /* line height of the font set last */
extern FontSlot *gFontSlots;
extern FontCursor *gFontCursorStack;
extern FontStyle *gFontStyleStack;
extern FontCmd *gFontCmds;
extern s32 gFontCursorDepth;
extern s32 gFontStyleDepth;
extern s32 gFontCmdCount;
extern s32 gFontCmdMax;

void Font_InitEx(s32 unused, s32 maxCmds);
void Font_Flush(s32 first);
s32 Font_MeasureWidthEx(void *str, s32 kind, f32 scale);
s32 Font_CountLinesEx(void *str, s32 kind);
s32 Font_GetGlyphHeight(void);
void Font_AddCmd(s32 arg, s32 digits, s32 kind);
FontCmd *Font_AddCmdAt(s32 x, s32 y, s32 arg, s32 digits, s32 kind);
void Font_Home(void);
void Font_DrawCmd(u64 **pkt, FontCmd *cmd);
s32 Font_DrawChar(u64 **pkt, FontCmd *cmd, s32 *x, s32 *y, u16 ch, void *next);
s32 Font_AlignLine(FontCmd *cmd, s32 x, void *str);
s32 Font_MeasureLine(FontCmd *cmd, void *str);
s32 Font_MeasureChar(FontCmd *cmd, s32 *width, u16 ch);
void Font_AdvanceCursor(FontCmd *cmd);
s32 Font_AdvanceChar(FontCmd *cmd, s32 *x, s32 *y, u16 ch);
s32 Font_CharSize(s32 kind);
u16 Font_ReadChar(s32 kind, void *p);
s32 Font_IsNewline(u16 ch);
s32 Font_CountDigits(s32 value);
s32 Font_Pow10(s32 digits);
FontGlyph *Font_FindGlyph(u16 ch, FontSlot **slotOut);
FontGlyph *Font_SearchGlyph(FontSlot *slot, u16 ch);
FontCmd *Font_AllocCmd(void);
void Font_SetCmdCount(s32 count);
FontCmd *Font_NewCmd(s32 arg, s32 digits, s32 x, s32 y, s32 homeX, s32 kind);
void Font_SetFont(s32 slot, FontData *data);
s32 Font_DrawGlyph(u64 **pkt, FontCmd *cmd, s32 x, s32 y, u16 ch);

/* Writes the command's clip box as a GS SCISSOR register. */
void Font_PutScissor(u64 **pkt, FontCmd *cmd);

/* Opens a REGLIST tag of sprites (TEX0_1, RGBAQ, UV, XYZ2, UV, XYZ2 per sprite) and remembers where it is. */
void Font_OpenSpriteTag(u64 **pkt, u64 **tag);

/* Patches the tag opened by Font_OpenSpriteTag with the number of sprites written since. */
void Font_CloseSpriteTag(u64 **pkt, u64 **tag);

/* GS TEX0 value of a font's texture with CLUT number clut (0..3). */
u64 Font_MakeTex0(FontSlot *slot, s32 clut);

/* Uploads a font's texture to its VRAM blocks. */
void Font_UploadTexture(FontSlot *slot);

/* Boot-time init with room for 120 commands. */
void Font_Init(s32 unused);

/* Resets cursor and style, allocates the slots, stacks and command queue, binds the two fonts of the boot file. */
void Font_InitEx(s32 unused, s32 maxCmds);

/* Frees everything Font_InitEx allocated. */
void Font_Term(void);

/*
 * Draws one character into the packet at (*x, *y) unless it is 0 or a line break (used by the "<UB0>" tag).
 * The original returns nothing on the path that does not draw.
 */
s32 Font_DrawCharNow(u64 **pkt, FontCmd *cmd, s32 *x, s32 *y, u16 ch);

/* Draws and empties the whole queue. */
void Font_FlushAll(void);

/* Matches only with Font_BeginPacket and Font_EndPacket DEFINED above it in the same file (otherwise the back
 * branch of the last loop comes out `bnezl` instead of `bnez`): evidence that the object starts at 0x239BB0. */
/* Draws the queued commands from index first on, then truncates the queue to first and homes the cursor. */
void Font_Flush(s32 first);

/* Number of queued commands (callers save it and flush from it). */
s32 Font_GetCmdCount(void);

/* Turns drawing on or off; ignored before init. */
void Font_SetEnabled(s32 enabled);

/* 1 when flushing draws. */
s32 Font_IsEnabled(void);

/* Line height of the font bound last. */
s32 Font_GetLineHeight(void);

/* The same value again (glyph height). */
s32 Font_GetGlyphHeight(void);

/* Width in pixels of the widest line of a string at a scale, with the current style. */
s32 Font_MeasureWidthEx(void *str, s32 kind, f32 scale);

/* Width of a 16-bit string at scale 1. */
s32 Font_GetWidth(u16 *str);

/* Width of an 8-bit string at scale 1. */
s32 Font_GetWidthAscii(char *str);

/* Largest scale, from 1 down in steps of 0.01, at which a 16-bit string is narrower than width. */
f32 Font_FitScale(u16 *str, s32 width);

/* Number of lines of a string. */
s32 Font_CountLinesEx(void *str, s32 kind);

/* Height in pixels of a 16-bit string with the current scale and line spacing. */
s32 Font_GetHeight(u16 *str);

/* Unscaled height of an 8-bit string. */
s32 Font_GetHeightAscii(char *str);

/* Number of lines of a 16-bit string. */
s32 Font_CountLines(u16 *str);

/* Number of lines of an 8-bit string. */
s32 Font_CountLinesAscii(char *str);

/* Queues a command at the cursor and moves the cursor past what it will print. */
void Font_AddCmd(s32 arg, s32 digits, s32 kind);

/* Queues a command at a position; the cursor is not touched. */
FontCmd *Font_AddCmdAt(s32 x, s32 y, s32 arg, s32 digits, s32 kind);

/* Prints a 16-bit string at the cursor. */
void Font_Print(u16 *str);

/* Prints a 16-bit string at a position. */
void Font_PrintAt(s32 x, s32 y, u16 *str);

/* Prints one 16-bit character at the cursor. */
void Font_PutChar(u16 ch);

/* Prints one 16-bit character at a position. */
void Font_PutCharAt(s32 x, s32 y, u16 ch);

/* Prints an 8-bit string at the cursor. */
void Font_PrintAscii(char *str);

/* Prints an 8-bit string at a position. */
void Font_PrintAsciiAt(s32 x, s32 y, char *str);

/* Prints one 8-bit character at the cursor. */
void Font_PutAsciiChar(s8 ch);

/* Prints one 8-bit character at a position. */
void Font_PutAsciiCharAt(s32 x, s32 y, s8 ch);

/* Prints a decimal number at the cursor; digits 0 means as many as the value needs. */
void Font_PrintNum(s32 value, s32 digits);

/* Prints a decimal number at a position. */
void Font_PrintNumAt(s32 x, s32 y, s32 value, s32 digits);

/* Replaces home and cursor. */
void Font_SetCursorState(FontCursor *cursor);

/* Saves home and cursor on the five-deep stack (no bound check). */
void Font_PushCursor(void);

/* Restores home and cursor from the stack. */
void Font_PopCursor(void);

/* Sets the home position and moves the cursor there. */
void Font_SetHome(s32 x, s32 y);

/* Reads the home position. */
void Font_GetHome(s32 *x, s32 *y);

/* Moves the cursor. */
void Font_SetCursor(s32 x, s32 y);

/* Reads the cursor. */
void Font_GetCursor(s32 *x, s32 *y);

/* Moves the cursor to the home position. */
void Font_Home(void);

/* Moves the cursor to the start of the next line. */
void Font_NewLine(void);

/* Replaces the whole style. */
void Font_SetStyle(FontStyle *style);

/* The current style. */
FontStyle *Font_GetStyle(void);

/* Saves the style on the five-deep stack (no bound check). */
void Font_PushStyle(void);

/* Restores the style from the stack. */
void Font_PopStyle(void);

/* Text colour as one RGBA word. */
void Font_SetColor(u32 color);

u32 Font_GetColor(void);

/* Common scale factor. */
void Font_SetScale(f32 scale);

f32 Font_GetScale(void);

/* Horizontal and vertical scale. */
void Font_SetScaleXY(f32 x, f32 y);

void Font_GetScaleXY(f32 *x, f32 *y);

/* Extra pixels between glyphs and between lines. */
void Font_SetSpacing(s32 x, s32 y);

void Font_GetSpacing(s32 *x, s32 *y);

/* Clip box in screen pixels (the scissor of the next commands). */
void Font_SetClip(s32 x0, s32 y0, s32 x1, s32 y1);

void Font_GetClip(s32 *x0, s32 *y0, s32 *x1, s32 *y1);

/* Line alignment: 0 left, 1 centred, 2 right. */
void Font_SetAlign(s32 align);

s32 Font_GetAlign(void);

/* Style flags (bit 0: print only the first line). */
void Font_SetFlags(s32 flags);

s32 Font_GetFlags(void);

/* Shadow mode: 0 none, 1 drop shadow, 2 eight-way outline, 3 four-way outline. */
void Font_SetShadowMode(s32 mode);

s32 Font_GetShadowMode(void);

/* Shadow colour as one RGBA word. */
void Font_SetShadowColor(u32 color);

u32 Font_GetShadowColor(void);

/* Shadow offset in pixels. */
void Font_SetShadowOffset(s32 dx, s32 dy);

void Font_GetShadowOffset(s32 *dx, s32 *dy);

/* Text colour from components. */
void Font_SetColorRGBA(u8 r, u8 g, u8 b, s32 a);

/* Second colour from components (the colour of inline icons). */
void Font_SetColor2RGBA(u8 r, u8 g, u8 b, s32 a);

/* Shadow colour from components. */
void Font_SetShadowColorRGBA(u8 r, u8 g, u8 b, s32 a);

/* Callback run once per command at flush time, before the packet is built. */
void Font_SetBeginCallback(FontBeginFn fn);

/* Callback run in front of every character of a 16-bit string, with its argument. */
void Font_SetTagCallback(FontTagFn fn, void *arg);

/* userFlags = (userFlags & mask) | set. */
void Font_ChangeUserFlags(s32 mask, s32 set);

s32 Font_GetUserFlags(void);

/* Draws one queued command into the packet. */
void Font_DrawCmd(u64 **pkt, FontCmd *cmd);

/* Draws one character and advances (*x, *y); returns 1 at the end of the text. */
s32 Font_DrawChar(u64 **pkt, FontCmd *cmd, s32 *x, s32 *y, u16 ch, void *next);

/* Start x of a line for the command's alignment. */
s32 Font_AlignLine(FontCmd *cmd, s32 x, void *str);

/* Width in pixels of the first line of what a command prints from str on. */
s32 Font_MeasureLine(FontCmd *cmd, void *str);

/* Adds one character's advance to *width; returns 1 at a line break or the end. */
s32 Font_MeasureChar(FontCmd *cmd, s32 *width, u16 ch);

/* Moves the cursor past what a freshly queued command will print. */
void Font_AdvanceCursor(FontCmd *cmd);

/* Advances (*x, *y) by one character without drawing; returns 1 at the end of the text. */
s32 Font_AdvanceChar(FontCmd *cmd, s32 *x, s32 *y, u16 ch);

/* Bytes per character of a string kind. */
s32 Font_CharSize(s32 kind);

/* Reads one character of a string kind (8-bit characters are sign-extended, then cut to 16 bits). */
u16 Font_ReadChar(s32 kind, void *p);

/* 1 for line feed and carriage return. */
s32 Font_IsNewline(u16 ch);

/* Number of decimal digits of a value (1..10). */
s32 Font_CountDigits(s32 value) {
    s32 limit = 10;
    s32 n;

    for (n = 1; n < 10; n++) {
        if (value < limit) {
            break;
        }
        limit *= 10;
    }
    return n;
}

/* 10 to the power digits - 1. */
s32 Font_Pow10(s32 digits) {
    s32 result = 1;
    s32 i;

    for (i = 1; i < digits; i++) {
        result *= 10;
    }
    return result;
}

/* Looks a character up in every bound font, slot 0 first; a no-break space falls back to a space. */
FontGlyph *Font_FindGlyph(u16 ch, FontSlot **slotOut);

/* Binary search of a font's glyph table. */
FontGlyph *Font_SearchGlyph(FontSlot *slot, u16 ch);

/* Takes the next free command (no bound check against gFontCmdMax). */
FontCmd *Font_AllocCmd(void);

/* Truncates the queue. */
void Font_SetCmdCount(s32 count);

/* Queues a command with a snapshot of the current style. */
FontCmd *Font_NewCmd(s32 arg, s32 digits, s32 x, s32 y, s32 homeX, s32 kind);

/* Binds a font file to a slot (fixing its offsets up the first time) and makes its line height current. */
void Font_SetFont(s32 slot, FontData *data);

/* Draws one glyph with its shadow or outline; returns the advance in pixels (0 for an unknown character). */
s32 Font_DrawGlyph(u64 **pkt, FontCmd *cmd, s32 x, s32 y, u16 ch);
