
///////////////////////////////////////////////////////////////////////////////////
//  This file is part of Sorcerers. Copyright (C) 2020 @salvakantero
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////////////////////////

// Sorcerers v1.0

#include <cpctelera.h>

#include "gfx/tiles.h"			// tiles to compose the map (4x4 px)
#include "gfx/font.h"			// letters and numbers (6x8 px)
#include "gfx/logo.h"			// game logo for the main menu (106x36 px)
#include "gfx/goldframe.h"		// three pieces to create decorative frames (6x6 px) 
#include "gfx/objects.h"		// 16 objects (8x8 px)
#include "gfx/magic.h"			// magic shots; red, blue, green and yellow (8x8 px)

#include "sprites/sorcerer1.h"	// 10 frames for SVEN, the 1st player (10x12 px)
#include "sprites/sorcerer2.h"	// 10 frames for ERIK, the 2nd player (10x12 px)
#include "sprites/sentinel.h"	// 8 frames for the sentinel sprite (10x12 px)
#include "sprites/knight.h"		// 8 frames for the knight sprite (10x12 px)
#include "sprites/ghost.h"		// 8 frames for the ghost sprite (10x12 px)
#include "sprites/bat.h"		// 2 frames for the bat sprite (10x12 px)
#include "sprites/witch.h"		// 4 frames for the witch sprite (10x12 px)
#include "sprites/wizard.h"		// 4 frames for the wizard sprite (10x12 px)
#include "sprites/explosion.h"	// 2 frames for the explosion effect (10x12 px)
#include "sprites/dust.h"		// 2 frames for the dust effect (8x8 px)
#include "sprites/coin.h"		// 3 frames for the coin animation (6x8 px)
#include "sprites/door.h"		// 2 frames for the door (10x12 px)

// compressed game map (40x42 tiles / 160x168 pixels each)
// gardens
#include "map/mappk0.h"
#include "map/mappk1.h"
// cemetery
#include "map/mappk2.h"
#include "map/mappk3.h"
// cellars
#include "map/mappk4.h"
#include "map/mappk5.h"
// castle
#include "map/mappk6.h"
#include "map/mappk7.h"
// tower
#include "map/mappk8.h"
#include "map/mappk9.h"
// library
#include "map/mappk10.h"
#include "map/mappk11.h"

#include "sfx/fx.h"				// sound effects
#include "sfx/start.h"			// start level theme
#include "sfx/end.h"			// game over theme
#include "sfx/menu.h"			// main menu theme
#include "sfx/ingame.h"			// music during game
#include "sfx/completed.h"		// level completed theme










///////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS AND VARIABLES
///////////////////////////////////////////////////////////////////////////////////

#define TRUE	1
#define FALSE	0

#define GLOBAL_MAX_X  80 	// X maximum value for the screen (bytes)
#define GLOBAL_MAX_Y  200	// Y maximun value for the screen (px)

#define FNT_W 3 // width of text characters (bytes)
#define FNT_H 8 // height of text characters (px)

#define SPR_W 5 // sprite width (bytes)
#define SPR_H 12 // sprite height (px)

#define SHT_W 4 // shot width (bytes)
#define SHT_H 8 // shot height (px)

// character types
#define SORCERER1	0
#define SORCERER2	1
#define SENTINEL	2
#define KNIGHT		3
#define GHOST		4
#define BAT			5
#define WITCH		6
#define WIZARD		7
#define NOBODY		9

#define OBJ_W 4 // object width (bytes)
#define OBJ_H 8 // object height (px)

#define TILESET_WELL 38 // the well is detected in this tile number
#define TILESET_DOOR 14 // the door is detected in this tile number
#define TILESET_STORE 39 // in this tile and the next two the store is detected
#define TILESET_BLOCKERS 45 // tile number where the blocking tiles begin

#define BG_COLOR 1 // background color (1 = black)

// maps
#define MAP_W 40 // game screen size in tiles
#define MAP_H 42
#define ORIG_MAP_Y 32 // the map starts at position 32 of the vertical coordinates
#define UNPACKED_MAP_END (u8*)(0x1600) // the program starts at 0x1601
#define UNPACKED_MAP_INI (u8*)(0x0F71)
u8 nMap; // current level number
u8 lastNMap; // has been a level change?
u8 *lName; // text to display on screen for each level

// other global variables
u8 TwoPlayers; 		// if "1" or "TRUE", two players are present
u16 score[2];		// score of both players
u16 highScore;		// maximum score of the entire session
u8 potScore[2];		// current potion score for players 1 and 2
u8 coinScore[2];	// value of the coins collected by players 1 and 2
u8 doorKey[5];		// 5 item key needed to open the exit door
u8 playerKey[5];	// player's 5 item key
u8 storeX;			// X position of the store on the current map (to print objects on it)
u8 storeY;			// Y position of the store on the current map
u8 music;			// "TRUE" = plays the music during the game, "FALSE" = only effects
u8 enemyTurn;		// To avoid flickering sprites, the enemies logic takes turns for each cycle
u8 ctInactivity[2];	// counters to detect inactive players
u8 turboMode;		// disable VSYNC when turboMode = "1" or "TRUE"
u8 nTip;			// control show tips
u8 ctWizardAnim;	// organizes the wizard animation
i16 ctMainLoop; 	// main loop iteration counter

// keyboard / joystick controls
cpct_keyID ctlUp[2];
cpct_keyID ctlDown[2];
cpct_keyID ctlLeft[2];
cpct_keyID ctlRight[2];
cpct_keyID ctlAbort;
cpct_keyID ctlMusic;  
cpct_keyID ctlPause;

// frame of the sprite to print
typedef struct {
	//u8 dir;
	u8* spr;
} TFrm;

// structure to manage sprites (players and enemies)
typedef struct {
	// common properties
	u8 num;		// sprite number (0 to 6; two players and five enemies)
	u8 ident;	// identity; Sorcerer1, Sorcerer2, Sentinel, etc ...
	u8 x, y;	// X, Y coordinates of the sprite
	u8 px, py;	// previous X, Y coordinates of the sprite
	u8 status;	// current status of the sprite; standing, walking, etc ...
	u8 dir;		// sprite direction
	TFrm* frm;	// animation sequence image
	u8 nFrm;	// animation frame number

	// shared properties for players and enemies (saving memory)
	
	// players: lives left
	// enemies: speed
	u8 lives_speed;
	
	// players: number of ingredients purchased
	// enemies: movement type
	u8 objNum_mov;
	
	// players: need to reprint sprite?
	// enemies: minimum value X / Y in linear motion
	u8 print_minV;
	
	// players: powerUp speed*2
	// enemies: maximum value X / Y in linear motion
	u8 power_maxV;
} TSpr;

TSpr spr[7];	// 0) sorcerer #1
				// 1) sorcerer #2
				// 2) enemy #1
				// 3) enemy #2
				// 4) enemy #3
				// 5) enemy #4
				// 6) enemy #5 (wizard)

// structure to manage the shots
typedef struct {
	u8 x, y;	// X, Y coordinates of the shot
	u8 px;		// previous X coordinate of the shot (only has horizontal movement)
	u8 dir;		// firing direction; right or left.
	u8 active;	// the shot is on screen if active = "1" or "TRUE"
} Tsht;

Tsht sht; // witch/wizard shot

// necessary data to control the two objects to collect
i8 nObj[2];	// item number
u8 objX[2];	// X coordinate of item
u8 objY[2];	// Y coordinate of item
i8 nPObj;	// last purchased item number

			// -1) No active object
			// 	0) Coin
			//  1) Coin x5
			//  2) Extra life
			//  3) PowerUp speed*2		
			//	4) Toad snot
			//	5) Diamond dust
			//	6) Newt eye
			//	7) Mammoth poop
			//  8) Kraken ink
			//  9) Mermaid tear
			// 10) Martian mushroom
			// 11) Dragon blood
			// 12) Dodo egg
			// 13) Unicorn blood
			// 14) Troll fat
			// 15) Mordor lava
						
// enumerations
// sprite movement direction
enum {D_up, D_down, D_left, D_right} enum_dir;
// sprite status
enum {S_walkingUp, S_walkingDown, S_walkingLeft, S_walkingRight, S_stopped} enum_sta;
// behavior of sprites controlled by CPU
enum {M_linear_X, M_linear_Y, M_linear_XY, M_chaser} enum_mov;

// 8 frames of Sorcerer1 in motion
const TFrm frmSorcerer1[8] = {
	{g_sorcerer1_00}, // up step 1
	{g_sorcerer1_01}, // up step 2
	{g_sorcerer1_02}, // dows step 1
	{g_sorcerer1_03}, // down step 2
	{g_sorcerer1_04}, // left step 1
	{g_sorcerer1_05}, // left step 2
	{g_sorcerer1_06}, // right step 1
	{g_sorcerer1_07}  // right step 2
};
// Sorcerer1 animation sequences
TFrm* const animUp_Sorcerer1[2] = {&frmSorcerer1[0], &frmSorcerer1[1]};
TFrm* const animDown_Sorcerer1[2] = {&frmSorcerer1[2], &frmSorcerer1[3]};
TFrm* const animLeft_Sorcerer1[2] = {&frmSorcerer1[4], &frmSorcerer1[5]};
TFrm* const animRight_Sorcerer1[2] = {&frmSorcerer1[6], &frmSorcerer1[7]};

// 8 frames of Sorcerer2 in motion
const TFrm frmSorcerer2[8] = {
	{g_sorcerer2_00}, // up step 1
	{g_sorcerer2_01}, // up step 2
	{g_sorcerer2_02}, // down step 1
	{g_sorcerer2_03}, // down step 2
	{g_sorcerer2_04}, // left step 1
	{g_sorcerer2_05}, // left step 2
	{g_sorcerer2_06}, // right step 1
	{g_sorcerer2_07}  // right step 2	
};
// Sorcerer2 animation sequences
TFrm* const animUp_Sorcerer2[2] = {&frmSorcerer2[0], &frmSorcerer2[1]};
TFrm* const animDown_Sorcerer2[2] = {&frmSorcerer2[2], &frmSorcerer2[3]};
TFrm* const animLeft_Sorcerer2[2] = {&frmSorcerer2[4], &frmSorcerer2[5]};
TFrm* const animRight_Sorcerer2[2] = {&frmSorcerer2[6], &frmSorcerer2[7]};

// 8 frames of Sentinel in motion
const TFrm frmSentinel[8] = {
	{g_sentinel_0}, // up step 1
	{g_sentinel_1}, // up step 2
	{g_sentinel_2}, // down step 1
	{g_sentinel_3}, // down step 2	
	{g_sentinel_4}, // left step 1
	{g_sentinel_5}, // left step 2
	{g_sentinel_6}, // right step 1
	{g_sentinel_7}	// right step 2 
};
// Sentinel animation sequences
TFrm* const animUp_Sentinel[2] = {&frmSentinel[0], &frmSentinel[1]};
TFrm* const animDown_Sentinel[2] = {&frmSentinel[2], &frmSentinel[3]};
TFrm* const animLeft_Sentinel[2] = {&frmSentinel[4], &frmSentinel[5]};
TFrm* const animRight_Sentinel[2] = {&frmSentinel[6], &frmSentinel[7]};

// 8 frames of Knight in motion
const TFrm frmKnight[8] = {
	{g_knight_0},	// up step 1 
	{g_knight_1}, 	// up step 2
	{g_knight_2},	// down step 1 
	{g_knight_3}, 	// down step 2
	{g_knight_4}, 	// left step 1
	{g_knight_5},	// left step 2
	{g_knight_6},	// right step 1
	{g_knight_7}	// right step 2
};
// Knight animation sequences
TFrm* const animUp_Knight[2] = {&frmKnight[0], &frmKnight[1]};
TFrm* const animDown_Knight[2] = {&frmKnight[2], &frmKnight[3]};
TFrm* const animLeft_Knight[2] = {&frmKnight[4], &frmKnight[5]};
TFrm* const animRight_Knight[2] = {&frmKnight[6], &frmKnight[7]};

// 8 frames of Ghost in motion
const TFrm frmGhost[8] = {
	{g_ghost_0},	// up step 1 
	{g_ghost_1}, 	// up step 2
	{g_ghost_2},	// down step 1 
	{g_ghost_3}, 	// down step 2
	{g_ghost_4}, 	// left step 1
	{g_ghost_5},	// left step 2
	{g_ghost_6},	// right step 1
	{g_ghost_7}		// right step 2
};
// Ghost animation sequences
TFrm* const animUp_Ghost[2] = {&frmGhost[0], &frmGhost[1]};
TFrm* const animDown_Ghost[2] = {&frmGhost[2], &frmGhost[3]};
TFrm* const animLeft_Ghost[2] = {&frmGhost[4], &frmGhost[5]};
TFrm* const animRight_Ghost[2] = {&frmGhost[6], &frmGhost[7]};

// 2 frames of Bat in motion
const TFrm frmBat[2] = {{g_bat_0}, {g_bat_1}};
// Bat animation sequences
TFrm* const anim_Bat[2] = {&frmBat[0], &frmBat[1]};

// 4 frames of Witch in motion
const TFrm frmWitch[4] = {
	{g_witch_0}, 	// left step 1
	{g_witch_1},	// left step 2
	{g_witch_2},	// right step 1
	{g_witch_3}		// right step 2
};
// Witch animation sequences
TFrm* const animLeft_Witch[2] = {&frmWitch[0], &frmWitch[1]};
TFrm* const animRight_Witch[2] = {&frmWitch[2], &frmWitch[3]};

// Transparency mask table
cpctm_createTransparentMaskTable(g_maskTable, 0x100, M0, 0);










///////////////////////////////////////////////////////////////////////////////////
//  FUNCTION STATEMENTS
///////////////////////////////////////////////////////////////////////////////////

void InitGame();
void GameOver(u8 player);
void PrintObject(u8 nObj, u8 objX, u8 objY);
u8 SpriteCollision(u8 x, u8 y, TSpr *pSpr, u8 marginX);
void PrintSprite(TSpr *pSpr) __z88dk_fastcall;
void MakeDuel();
void ResetData();










///////////////////////////////////////////////////////////////////////////////////
// GENERIC FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////

// returns the absolute value of a number
i16 Abs(i16 number) __z88dk_fastcall {
	if (number < 0)
    	number *= -1;
    return (number);
}


// get the length of a string
u8 Strlen(const unsigned char *str) __z88dk_fastcall {
    const unsigned char *s;
    for (s = str; *s; ++s);
    return (s - str);
}


// converts an integer to ASCII (Lukás Chmela / GPLv3)
char* Itoa(u16 value, char* result, int base) {    
    int tmp_value;
    char* ptr = result, *ptr1 = result, tmp_char;
    
    if (base < 2 || base > 36) { 
        *result = '\0'; 
        return result; 
    }
    
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while (value);
    
    if (tmp_value < 0) 
        *ptr++ = '-';
    *ptr-- = '\0';
    
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    
    return result;
}


// generates a pause
void Pause(u16 value) __z88dk_fastcall {
    u16 i;
    for(i=0; i < value; i++) {
		__asm
			halt
		__endasm;
	}
}


// Arkos tracker music player
void PlayMusic() {
   __asm 
      exx
      .db #0x08
      push af
      push bc
      push de
      push hl
      call _cpct_akp_musicPlay
      pop hl
      pop de
      pop bc
      pop af
      .db #0x08
      exx
   __endasm;
}


// every x calls, plays the music and/or FX and reads the keyboard
void Interrupt() {
   static u8 nInt;

   if (++nInt == 6) {
      PlayMusic();
      cpct_scanKeyboard_if();
      nInt = 0;
   }
}










///////////////////////////////////////////////////////////////////////////////////
// GRAPHICS, TILES AND SCREEN MANAGEMENT FUNCTIONS 
///////////////////////////////////////////////////////////////////////////////////

// cleans the screen with the specified color
void ClearScreen() {
	cpct_memset(CPCT_VMEM_START, cpct_px2byteM0(BG_COLOR, BG_COLOR), 16384);
}


// get the tile number of a certain position XY in the current map
u8* GetTileNum(u8 x, u8 y) {
	return UNPACKED_MAP_INI + (y - ORIG_MAP_Y) / 4 * MAP_W + x / 2;	
}


// returns "1" if the coordinates are placed on the background tiles, "0" if they are blockers
u8 OnBackground(u8 x, u8 y) {
	if (*GetTileNum(x+3, y+8) >= TILESET_BLOCKERS) 
		return FALSE;
	return TRUE;
}


// print the map corresponding to the current map number 
void PrintMap() {
	cpct_etm_drawTilemap2x4(MAP_W, MAP_H, 
							cpctm_screenPtr(CPCT_VMEM_START, 0, ORIG_MAP_Y), 
							UNPACKED_MAP_INI);
}


// print a number as a text string
void PrintNumber(u16 num, u8 len, u8 x, u8 y, u8 prevDel) { 
	u8 txt[6];
	u8 zeros;
	u8 pos = 0;
	u8 nAux;

	Itoa(num, txt, 10);    
	zeros = len - Strlen(txt);
	nAux = txt[pos];

	while(nAux != '\0')	{	
		u8* ptr = cpct_getScreenPtr(CPCT_VMEM_START, (zeros + pos) * FNT_W + x, y);
		if (prevDel) 
			cpct_drawSolidBox(ptr, cpct_px2byteM0(BG_COLOR, BG_COLOR), FNT_W, FNT_H); // previous deletion
		cpct_drawSpriteMaskedAlignedTable(g_font[nAux - 48], ptr, FNT_W, FNT_H, g_maskTable);
		nAux = txt[++pos];
	}
}


// prints a character string at XY coordinates
void PrintText(u8 txt[], u8 x, u8 y, u8 prevDel) {
	u8 pos = 0;
	u8 car = txt[pos];

 	while(car != '\0') { // "@" = blank    ";" = -   ">" = !!   "[" = ,
		u8* ptr = cpct_getScreenPtr(CPCT_VMEM_START, (pos * FNT_W) + x, y);
		if (prevDel) 
			cpct_drawSolidBox(ptr, cpct_px2byteM0(BG_COLOR, BG_COLOR), FNT_W, FNT_H); // previous deletion
		cpct_drawSpriteMaskedAlignedTable(g_font[car - 48], ptr, FNT_W, FNT_H, g_maskTable);
		car = txt[++pos];
	}
}


// print a gold frame
void PrintFrame(u8 xIni, u8 yIni, u8 xEnd, u8 yEnd) {
	int i = xIni+3;	
	// horizontal tiles
	while (i < xEnd) {		
		cpct_drawSpriteMaskedAlignedTable(g_goldframe_2, cpctm_screenPtr(CPCT_VMEM_START, i, yIni), 3, 6, g_maskTable);	
		cpct_drawSpriteMaskedAlignedTable(g_goldframe_2, cpctm_screenPtr(CPCT_VMEM_START, i, yEnd), 3, 6, g_maskTable);	
		i += 3;
	}	
	// vertical tiles	
	i = yIni+6;
	while (i < yEnd) {		
		cpct_drawSpriteMaskedAlignedTable(g_goldframe_1, cpctm_screenPtr(CPCT_VMEM_START, xIni, i), 3, 6, g_maskTable);	
		cpct_drawSpriteMaskedAlignedTable(g_goldframe_1, cpctm_screenPtr(CPCT_VMEM_START, xEnd, i), 3, 6, g_maskTable);	
		i += 6;
	}	
	// gems	
	// upper left corner
	cpct_drawSpriteMaskedAlignedTable(g_goldframe_0, cpctm_screenPtr(CPCT_VMEM_START, xIni, yIni), 3, 6, g_maskTable);
	// upper right corner
	cpct_drawSpriteMaskedAlignedTable(g_goldframe_0, cpctm_screenPtr(CPCT_VMEM_START, xEnd, yIni), 3, 6, g_maskTable);
	// lower left corner				
	cpct_drawSpriteMaskedAlignedTable(g_goldframe_0, cpctm_screenPtr(CPCT_VMEM_START, xIni, yEnd), 3, 6, g_maskTable);
	// lower right corner				
	cpct_drawSpriteMaskedAlignedTable(g_goldframe_0, cpctm_screenPtr(CPCT_VMEM_START, xEnd, yEnd), 3, 6, g_maskTable);									
}










///////////////////////////////////////////////////////////////////////////////////
// ON SCREEN MESSAGES
///////////////////////////////////////////////////////////////////////////////////

void PrintSmallBlueBox() {
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START,  6, 80), cpct_px2byteM0(4, 4), 34, 60);
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 40, 80), cpct_px2byteM0(4, 4), 34, 60);
	PrintFrame(6,80,71,134);
}


// print box with the number and name of the loaded level
void PrintLevelInfo() {
	PrintSmallBlueBox();	
	// if two players, the record is shown in this window, not on the scoreboard
	if (TwoPlayers) {
		PrintText("LEVEL", 13, 95, 0);
		PrintText(lName, 31, 95, 0);
		PrintText("HIGH@SCORE:", 16, 118, 0);
		PrintNumber(highScore, 4, 52, 118, 0);
	}
	else {
		PrintText("LEVEL", 13, 107, 0);
		PrintText(lName, 31, 107, 0);
	}

	cpct_akp_musicInit(g_start); // start level music
	Pause(1150);
	if (music)
		cpct_akp_musicInit(g_ingame); // music ingame
}


void PrintEndGame(u8 player) __z88dk_fastcall {
	// blue background frame
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 5, 40), cpct_px2byteM0(4, 4), 35, 144);
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 40, 40), cpct_px2byteM0(4, 4), 35, 144);	
	PrintFrame(5,40,72,178);

	PrintText("CONGRATULATIONS", 12, 60, 0);
	PrintText("PLAYER@@>", 12, 70, 0);
	PrintNumber(++player, 1, 33, 70, 0);
	PrintText("YOU@FOUND@YOUR", 12, 90, 0);
	PrintText("FATHERS@SPELL@BOOK", 12, 100, 0);
	PrintText("NOW@YOUR@POWER@WILL", 12, 120, 0);
	PrintText("BE@UNSURPASSED", 12, 130, 0);
	PrintText(";THANKS@FOR@PLAYING;", 10, 160, 0);	

	cpct_akp_musicInit(g_completed); // completed level theme
	Pause(1000);
	while (!cpct_isAnyKeyPressed()); // wait for a key press
	InitGame();
}


// novice help tips
void PrintTip() {
	PrintSprite(&spr[0]);
	PrintSmallBlueBox();
	switch (nTip) {
		case 0: {
			PrintText("TIP:@TAKE@THE@EXACT", 11, 95, 0);
			PrintText("COINS@TO@BUY@THE", 16, 105, 0);
			PrintText("REQUIRED@INGREDIENT", 11, 115, 0);
			break;
		}
		case 1: {
			PrintText("TIP:@GO@TO@THE@SHOP", 11, 95, 0);
			PrintText("WHEN@YOU@CAN@GET@THE", 10, 105, 0);
			PrintText("INGREDIENT@YOU@NEED", 11, 115, 0);
			break;
		}
		case 2: {
			PrintText("TIP:@USE@THE@WELL", 14, 95, 0);
			PrintText("WHEN@YOU@TAKE@MORE", 13, 105, 0);
			PrintText("COINS@THAN@YOU@NEED", 11, 115, 0);
			break;
		}
		case 3: {
			PrintText("TIP:@GO@TO@THE@EXIT", 11, 95, 0);
			PrintText("DOOR@WHEN@YOU@HAVE", 13, 105, 0);
			PrintText("THE@RIGHT@POTION", 15, 115, 0);
		}
	}
	Pause(400);
	while (!cpct_isAnyKeyPressed()); // wait for a key press
	nTip++; // next message
	PrintMap();
}










///////////////////////////////////////////////////////////////////////////////////
// KEYBOARD FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////

// returns the key pressed
cpct_keyID ReturnKeyPressed() {
    u8 i = 10, *keys = cpct_keyboardStatusBuffer + 9;
    u16 keypressed;
    // We wait until a key is pressed
    do { cpct_scanKeyboard(); } while ( ! cpct_isAnyKeyPressed() );
    // We detect which key has been pressed
    do {
        keypressed = *keys ^ 0xFF;
        if (keypressed)
            return (keypressed << 8) + (i - 1); 
        keys--;
    } while(--i);    
	return 0;
}


// wait for the full press of a key
// useful to empty the keyboard buffer
void Wait4Key(cpct_keyID key) {
    do cpct_scanKeyboard_f();
    while(!cpct_isKeyPressed(key));
    do cpct_scanKeyboard_f();
    while(cpct_isKeyPressed(key));
}


// asks for a key and returns the key pressed
cpct_keyID RedefineKey(u8 *info) {
    cpct_keyID key; 
    PrintText(info, 28, 120, 1);       
    key = ReturnKeyPressed();
    Wait4Key(key);
	cpct_akp_SFXPlay (1, 12, 59, 0, 0, AY_CHANNEL_A);    
    return key;    
}










///////////////////////////////////////////////////////////////////////////////////
// SCOREBOARD FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////

// update the record
void RefreshHighScore(u8 player) __z88dk_fastcall {
	if (highScore < score[player])
		highScore = score[player];
}


// print the scoreboard
void InitScoreboard() {
	nPObj = 0;
	PrintFrame(0,0,77,24);	

	// player 1
	cpct_drawSpriteMaskedAlignedTable(g_sorcerer1_06, cpct_getScreenPtr(CPCT_VMEM_START,  3, 4), SPR_W, SPR_H, g_maskTable);
	PrintText("0000", 14, 6, 1); // player score
	PrintObject(nPObj, 28, 6); PrintText("00", 32, 6, 1);	// coins score	
	PrintText("<", 28, 15, 1); PrintText("00", 32, 15, 1);	// potion score

	// player 2
	if (TwoPlayers) {
		cpct_drawSpriteMaskedAlignedTable(g_sorcerer2_06, cpct_getScreenPtr(CPCT_VMEM_START, 42, 4), SPR_W, SPR_H, g_maskTable);
		PrintText("0000", 53, 6, 1); // player score
		PrintObject(nPObj, 67, 6); PrintText("00", 71, 6, 1);	// coins score
		PrintText("<", 67, 15, 1); PrintText("00", 71, 15, 1);	// potion score
	}
	else {
		PrintText("HIGH:", 44, 6 , 1);
		PrintText("00000", 61, 6, 1); 
		PrintNumber(highScore, 5, 61, 6, 1); // high score
		cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 60, 16), cpct_px2byteM0(BG_COLOR, BG_COLOR), 16, 8); // key
		PrintText("KEY:", 47, 15, 1);
	}	
}


// refresh data on scoreboard
void RefreshScoreboard() { 
	// player 1
	PrintNumber(spr[0].lives_speed,  1,  8, 6, 1); 		// lives
	PrintNumber(score[0], 4, 14, 6, 1);		 			// current score
	PrintText("0", 32, 6, 1);
	PrintNumber(coinScore[0], 2, 32, 6, 1); 			// coin score
	PrintText("0", 32, 15, 1);
	PrintNumber(potScore[0], 2, 32, 15, 1); 			// potion score
	// player 2
	if (TwoPlayers) {
		PrintNumber(spr[1].lives_speed,  1, 47, 6, 1); 	// lives
		PrintNumber(score[1], 4, 53, 6, 1);		 		// current score
		PrintText("0", 71, 6, 1);
		PrintNumber(coinScore[1], 2, 71, 6, 1); 		// coin score
		PrintText("0", 71, 15, 1);
		PrintNumber(potScore[1], 2, 71, 15, 1); 		// potion score
	}
	else
		PrintNumber(highScore, 5, 61, 6, 1);
}










///////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR OBJECT MANAGEMENT
///////////////////////////////////////////////////////////////////////////////////

// resets the values ​​related to collecting objects
void ResetObjData(u8 player) __z88dk_fastcall {
	spr[player].objNum_mov = 0; // number of objects
	potScore[player] = 0; // potion value
	coinScore[player] = 0; // money
	// clear the scoreboard
	if (player == 0)
		cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 7, 16), cpct_px2byteM0(BG_COLOR, BG_COLOR), 20, 8);
	else
		cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 46, 16), cpct_px2byteM0(BG_COLOR, BG_COLOR), 20, 8);
} 


// the active object is printed at the assigned XY coordinates
void PrintObject(u8 nObj, u8 objX, u8 objY) {
	cpct_drawSpriteMaskedAlignedTable(g_objects[nObj], cpct_getScreenPtr(CPCT_VMEM_START, objX, objY),
									  OBJ_W, OBJ_H, g_maskTable);
}


// a portion of the map is printed at the XY coordinates of the object (to delete it)
void DeleteObject(u8 index) __z88dk_fastcall {
	cpct_etm_drawTileBox2x4(objX[index] / 2, (objY[index] - ORIG_MAP_Y) / 4,
							2 + (objX[index] & 1), 2 + (objY[index] & 3 ? 1 : 0), MAP_W, 
							cpctm_screenPtr(CPCT_VMEM_START, 0, ORIG_MAP_Y), UNPACKED_MAP_INI);	
}


// a frame of the dust effect is printed at the XY coordinates of the object
void PrintDust(u8 nFrame, u8 index) {
	cpct_drawSpriteMaskedAlignedTable(g_dust[nFrame], 
									  cpct_getScreenPtr(CPCT_VMEM_START, objX[index], objY[index]), 
									  OBJ_W, OBJ_H, g_maskTable);
}


// a frame of the coin rotating is printed in the XY coordinates of the object
void PrintCoin(u8 nFrame, u8 index) {
	cpct_drawSpriteMaskedAlignedTable(g_coin[nFrame], 
									  cpct_getScreenPtr(CPCT_VMEM_START, objX[index], objY[index]), 
									  3, OBJ_H, g_maskTable);
}


// delete the object inside the store
void DeleteObjectInStore() {
	if (TwoPlayers) return;
	cpct_etm_drawTileBox2x4(storeX / 2, storeY / 4,
							2 + (storeX & 1), 2 + (storeY & 3 ? 1 : 0),	MAP_W, 
							cpctm_screenPtr(CPCT_VMEM_START, 0, ORIG_MAP_Y), UNPACKED_MAP_INI);	
}


// print the object to buy inside the store
void PrintObjectInStore() {
	if (TwoPlayers) return;
	if (coinScore[0] == 0) return;

	if (coinScore[0] < 13)
		nPObj = coinScore[0] + 3; // assign the corresponding object to the available money
	else // left over money
		nPObj = 15; // assign the most expensive object
						
	PrintObject(nPObj, storeX, storeY + ORIG_MAP_Y);
}


// check if any player has passed over the object
// increase the score and update the scoreboard.
void CheckObject(u8 index) {	
	i8 player = -1;

	if (nObj[index] != -1)	{
		if (SpriteCollision(objX[index], objY[index], &spr[0], 0)) player = 0; // player 1
		else if (TwoPlayers && SpriteCollision(objX[index], objY[index], &spr[1], 0)) player = 1; // player 2
		// collision with object
		if (player >= 0)	{									
			DeleteObject(index);

			// coins
			if (nObj[index] <= 1) {
				cpct_akp_SFXPlay (2, 12, 79, 0, 0, AY_CHANNEL_C); // take an item
				if (nMap == 0 && !TwoPlayers && nTip<2) 
					PrintTip(); // novice help
			}

			switch (nObj[index])
			{
				case 0:	{	// coin
					coinScore[player]++;
					score[player] += 5;
					DeleteObjectInStore();
					PrintObjectInStore();
					break;
				}
				case 1: {	// coin x5
					coinScore[player] += 5;
					score[player] += 20;
					DeleteObjectInStore();
					PrintObjectInStore();
					break;
				}
				case 2: {	// extra life
					cpct_akp_SFXPlay (8, 12, 60, 0, 0, AY_CHANNEL_C); // Prince of Persia tune
					if (spr[player].lives_speed < 9)
						spr[player].lives_speed++;
					score[player] += 30;
					break;
				}	
				case 3: {	// power up speed*2
					cpct_akp_SFXPlay (9, 12, 60, 0, 0, AY_CHANNEL_A); // powerUp
					spr[player].power_maxV = 255;
					score[player] += 25;
				}	
			}
			RefreshHighScore(player);
			RefreshScoreboard();
			nObj[index] = -1; // object not assigned
		}
	}
}


// are there enemies hiding the object?
u8 ObjectCollision(u8 numObj) __z88dk_fastcall {	
	u8 i=2;	// check sprites 2 to 5	
	while(i<=5) {
		if ((spr[i].x + SPR_W >= objX[numObj] && spr[i].x <= objX[numObj] + OBJ_W) && 
			(spr[i].y + SPR_H >= objY[numObj] && spr[i].y <= objY[numObj] + OBJ_H)) {
			return 1;
		}
		i++;
	}
	return 0;
}


// reprints the object on-screen so it doesn't get erased by moving sprites
// animates the "dust effect" when the object appears and disappears
// animates the "rotation effect" when the coin appears
void ReprintObject() {
	// first object
	if (nObj[0] >= 0 && !ObjectCollision(0)) {  // does not print if hidden by enemies
		switch(ctMainLoop) {
			// "dust effect" 1st frame
			case 0:
			case 344:	{ DeleteObject(0); PrintDust(0,0); break; }
			// "dust effect" 2nd frame
			case 8:
			case 336:	{ DeleteObject(0); PrintDust(1,0); break; }
			
			// erase the dust and print the object
			case 16:	{ DeleteObject(0); PrintObject(nObj[0], objX[0], objY[0]); break; }

			// coin animation
			case 24:
			case 56:
			case 88: { if (nObj[0] == 0) {DeleteObject(0); PrintCoin(0,0); break; }}
			case 32:
			case 64:
			case 96: { if (nObj[0] == 0) {DeleteObject(0); PrintCoin(1,0); break; }}
			case 40:
			case 72:
			case 104: { if (nObj[0] == 0) {DeleteObject(0); PrintCoin(2,0); break; }}

			// delete the object
			case 328:	{ DeleteObject(0); }
			// in all other cases print the object
			default:	{ PrintObject(nObj[0], objX[0], objY[0]); }			
		}
	}
	// second object
	if (nObj[1] >= 0 && !ObjectCollision(1)) {
		switch(ctMainLoop) {
			// "dust effect" 1st frame
			case 176:
			case 168:	{ DeleteObject(1); PrintDust(0,1); break; }
			// "dust effect" 2nd frame
			case 184:
			case 160:	{ DeleteObject(1); PrintDust(1,1); break; }
			// delete the dust and print the object
			case 192:	{ DeleteObject(1); PrintObject(nObj[1], objX[1], objY[1]); break; }

			// coin animation
			case 200:
			case 232:
			case 264: { if (nObj[1] == 0) {DeleteObject(1); PrintCoin(0,1); break; }}
			case 208:
			case 240:
			case 272: { if (nObj[1] == 0) {DeleteObject(1); PrintCoin(1,1); break; }}
			case 216:
			case 248:
			case 280: { if (nObj[1] == 0) {DeleteObject(1); PrintCoin(2,1); break; }}

			// delete the object
			case 154:	{ DeleteObject(1); }
			// in all other cases print the object
			default:	{ PrintObject(nObj[1], objX[1], objY[1]); }			
		}
	}
}


void SetObject(u8 index) __z88dk_fastcall {
	u8 tile;
	// if there is any active object, delete it
	if (nObj[index] >= 0) DeleteObject(index); 
	// generates a new object
	nObj[index] = cpct_getRandom_lcg_u8(0) / 11;	// obj = 0 a 22

	do {
		objX[index] = 4 + (cpct_getRandom_lcg_u8(0)*10/36); 	// x = 4 a 74
		objY[index] = 40 + (cpct_getRandom_lcg_u8(0)*10/17);	// y = 40 a 190	
		tile = *GetTileNum(objX[index]+2, objY[index]+8);	
	}
	// the XY of the object will only be valid on background tiles and away from other sprites
	while (tile > 34 || tile == TILESET_DOOR || // tile is a blocker
			Abs(objX[0] - objX[1]) < 12 || // near the other object
			SpriteCollision(objX[index], objY[index], &spr[0], 12) || // near player 1
			SpriteCollision(objX[index], objY[index], &spr[1], 12)); // near player 2

	if (nObj[index] == 22) nObj[index] = 1; // slightly more chance of showing 5 coins
	else if (nObj[index] == 21) nObj[index] = 3; // slightly more chance of powerUps showing up
	else if (nObj[index] > 3) nObj[index] = 0; // only PowerUps and coins, others are purchased

	cpct_akp_SFXPlay(1, 12, 65, 0, 0, AY_CHANNEL_A); // new item
}


// print the purchased item on the player scoreboard in the XY coordinates 
// that correspond according to the player and the number of accumulated objects
void AddObjectToScoreboard(u8 player) __z88dk_fastcall {
	u8 x = spr[player].objNum_mov * 3 + 7;
	if (player == 1) x += 39;		
	PrintObject(nPObj, x, 16);
}


// prints the objects that make up the opening key on the scoreboard
void PrintKey() {
	u8 i = 0;	
	u8 x = 60;
	while (i<=4) {
		PrintObject(doorKey[i], x, 16);
		i++;
		x+=3;
	}
}


// Compare the objects the player is carrying with the key on the current map
u8 CompareKeys() {
	if (doorKey[0] == playerKey[0] && 
		doorKey[1] == playerKey[1] &&
		doorKey[2] == playerKey[2] && 
		doorKey[3] == playerKey[3] &&
		doorKey[4] == playerKey[4]) 
		return 1;
		
	return 0;
}


// check if any player has stepped on a special tile; shop, well, exit door
void CheckActiveTile(u8 player) {	
	u8 currentTile = *GetTileNum(spr[player].x+3, spr[player].y+8);	
	u8 i = 0;
	
	// collision with the store?
	if (currentTile >= TILESET_STORE && currentTile <= TILESET_STORE + 5) {
		// money to buy? Is there room to carry more objects?
		while (coinScore[player] > 0 && spr[player].objNum_mov < 5) {
			cpct_akp_SFXPlay (7, 12, 65, 0, 0, AY_CHANNEL_A);
			if (coinScore[player] < 13) // no money left
				nPObj = coinScore[player] + 3; // assign the corresponding object to the available money
			else // excess of money
				nPObj = 15; // assign the most expensive object
			spr[player].objNum_mov++; // increases the number of objects the player carries
			potScore[player] += coinScore[player]; // increase the potion score
			score[player] += coinScore[player] * 2; // increase the player score
			RefreshHighScore(player);
			coinScore[player] -= nPObj - 3; // decrease the coin score
			if (!TwoPlayers) {
				playerKey[spr[player].objNum_mov-1] = nPObj; // add object to key
				// novice tip
				if (nMap == 0 && (nTip<3 || (nTip<4 && spr[0].objNum_mov >= 5)))
					PrintTip();
			}
			DeleteObjectInStore();
			AddObjectToScoreboard(player); 
			RefreshScoreboard();
		}
	}

	// collision with the well. Do we have objects or coins?
	else if (currentTile == TILESET_WELL && (potScore[player] > 0 || coinScore[player] > 0)) {	
		// it sounds like we dropped something
		cpct_akp_SFXPlay (3, 12, 57, 0, 0, AY_CHANNEL_C);
		// clear P1 or P2 scoreboard
		if (player == 0)
			cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 7, 16), 
							  cpct_px2byteM0(BG_COLOR, BG_COLOR), 20, 8);
		else
			cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 46, 16), 
							  cpct_px2byteM0(BG_COLOR, BG_COLOR), 20, 8);
				
		coinScore[player] = 0; 		// throwing money
		spr[player].objNum_mov = 0;	// throwing objects
		potScore[player] = 0;		// potion value to zero
		
		if (!TwoPlayers) { // search for valid objects to retrieve them (only 1 player game)			
			while (i<5) {
				if (playerKey[i] == doorKey[i] ) {
					potScore[0] += playerKey[i] - 3; // increases potion value
					spr[0].objNum_mov++; // increases the number of objects		
					// reprint the object in the scoreboard					
					PrintObject(playerKey[i++], spr[0].objNum_mov * 3 + 7, 16);					
				}
				else // wrong object. Delete the rest of the sequence
					while (i<5)	
						playerKey[i++] = 0;					
			}
			DeleteObjectInStore();
		}
		RefreshScoreboard();
	}

	// collision with the exit door and we have 5 objects?
	else if ((currentTile == TILESET_DOOR || currentTile == 30) && 
			spr[0].objNum_mov == 5 && CompareKeys()) {
		MakeDuel();	
	}
}










///////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR SPRITES MANAGEMENT
///////////////////////////////////////////////////////////////////////////////////

// prints the sprite and its mask at the current XY coordinates
void PrintSprite(TSpr *pSpr) __z88dk_fastcall {
	cpct_drawSpriteMaskedAlignedTable(pSpr->frm->spr, 
									  cpct_getScreenPtr(CPCT_VMEM_START, pSpr->x, pSpr->y), 
									  SPR_W, SPR_H, g_maskTable);
}


// print a portion of the map in the coordinates of the sprite (to delete it)
void DeleteSprite(TSpr *pSpr) __z88dk_fastcall {	
	cpct_etm_drawTileBox2x4(pSpr->px / 2, (pSpr->py - ORIG_MAP_Y) / 4, 
							3 + (pSpr->px & 1), 3 + (pSpr->py & 3 ? 1 : 0),	
							MAP_W, cpctm_screenPtr(CPCT_VMEM_START, 0, ORIG_MAP_Y), UNPACKED_MAP_INI);
}


// next frame of the animation sequence
void AssignFrame(TSpr *pSpr, TFrm **anim) {
	u8 animPause = 2;
	if (pSpr->num > 3) animPause = 1; // slow enemies (4 and 5) have no pause in animation
	pSpr->frm = anim[pSpr->nFrm / animPause];	
}


// we assign a frame or sequence of frames to each state
void SelectFrame(TSpr *pSpr) __z88dk_fastcall {
	// player 1
	if(pSpr->ident == SORCERER1) {
		switch(pSpr->status) {
			case S_walkingUp: 		{AssignFrame(&spr[0], animUp_Sorcerer1); break;}
			case S_walkingDown:		{AssignFrame(&spr[0], animDown_Sorcerer1); break;}
			case S_walkingLeft:		{AssignFrame(&spr[0], animLeft_Sorcerer1); break;}
			case S_walkingRight:	{AssignFrame(&spr[0], animRight_Sorcerer1); break;}
			case S_stopped:			{spr[0].frm = &frmSorcerer1[spr[0].dir*2];}		
		}
	}
	// player 2
	else if(pSpr->ident == SORCERER2) {
		switch(pSpr->status) {
			case S_walkingUp: 		{AssignFrame(&spr[1], animUp_Sorcerer2); break;}
			case S_walkingDown:		{AssignFrame(&spr[1], animDown_Sorcerer2); break;}
			case S_walkingLeft:		{AssignFrame(&spr[1], animLeft_Sorcerer2); break;}
			case S_walkingRight:	{AssignFrame(&spr[1], animRight_Sorcerer2); break;}
			case S_stopped:			{spr[1].frm = &frmSorcerer2[spr[1].dir*2];}	
		}
	}
	// sentinel
	else if(pSpr->ident == SENTINEL) {
		switch(pSpr->dir) {
			case D_up:				{AssignFrame(pSpr, animUp_Sentinel); break;}
			case D_down:			{AssignFrame(pSpr, animDown_Sentinel); break;}
			case D_left:			{AssignFrame(pSpr, animLeft_Sentinel); break;}
			case D_right:			{AssignFrame(pSpr, animRight_Sentinel);}
		}
	}
	// knight
	else if(pSpr->ident == KNIGHT) {
		switch(pSpr->dir) {
			case D_up:				{AssignFrame(pSpr, animUp_Knight); break;}
			case D_down:			{AssignFrame(pSpr, animDown_Knight); break;}
			case D_left:			{AssignFrame(pSpr, animLeft_Knight); break;}
			case D_right:			{AssignFrame(pSpr, animRight_Knight);}
		}
	}
	// ghost
	else if(pSpr->ident == GHOST) {
		switch(pSpr->dir) {
			case D_up:				{AssignFrame(pSpr, animUp_Ghost); break;}
			case D_down:			{AssignFrame(pSpr, animDown_Ghost); break;}
			case D_left:			{AssignFrame(pSpr, animLeft_Ghost); break;}
			case D_right:			{AssignFrame(pSpr, animRight_Ghost);}
		}
	}
	// witch
	else if(pSpr->ident == WITCH) {
		switch(pSpr->dir) {
			case D_left:			{AssignFrame(pSpr, animLeft_Witch); break;}
			case D_right:			{AssignFrame(pSpr, animRight_Witch);}
		}
	}
	// bat
	else if(pSpr->ident == BAT)	AssignFrame(pSpr, anim_Bat);
}


// prints an explosion frame at the XY coordinates of the sprite
void PrintExplosion(TSpr *pSpr, u8 nFrame)
{
	cpct_drawSpriteMaskedAlignedTable(g_explosion[nFrame], 
									  cpct_getScreenPtr(CPCT_VMEM_START, pSpr->x, pSpr->y), 
									  SPR_W, SPR_H, g_maskTable);
}


// Eliminate the player touched by an explosion
void ExplodeSprite(u8 player, u8 deleteSpr)
{
	u8 ct = 0;
	u8 i = 0;
	cpct_akp_SFXPlay (4, 12, 48, 0, 0, AY_CHANNEL_B); // explosion
	while (ct++ < 2) {	
		PrintExplosion(&spr[player], 0); Pause(40);
		PrintExplosion(&spr[player], 1); Pause(40);
		if (deleteSpr > FALSE) {
			DeleteSprite(&spr[player]); // delete player
			PrintSprite(&spr[deleteSpr]); // reprint enemy, which may have been partially erased
		}
	}
	PrintExplosion(&spr[player], 0); Pause(40);
	if (deleteSpr > FALSE) {
		DeleteSprite(&spr[player]);
		PrintSprite(&spr[deleteSpr]);
	}
}


// return "1" or "TRUE" if the coordinates match those of the sprite + the supplied margin
u8 SpriteCollision(u8 x, u8 y, TSpr *pSpr, u8 marginX) {
	u8 marginY = marginX+marginX;	
	if (x+OBJ_W > pSpr->x-marginX && x-marginX < pSpr->x+SPR_W) // check the X coordinate with the sprite		
		if (y+OBJ_H > pSpr->y-marginY && y-marginY < pSpr->y+SPR_H) // check the Y coordinate with the sprite
			return TRUE;	
	return FALSE;
}










///////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR CONTROLLING PLAYERS
///////////////////////////////////////////////////////////////////////////////////

void MoveUp(TSpr *pSpr) __z88dk_fastcall { 
	// move the sprite up if there is space and there are no barriers
	if (pSpr->y > ORIG_MAP_Y && OnBackground(pSpr->x-1, pSpr->y-2)) {
		pSpr->y -= 2;
		if (pSpr->power_maxV > 0 && OnBackground(pSpr->x-1, pSpr->y-2))
			pSpr->y -= 2; // powerUp speed*2
		
		pSpr->dir = D_up;
		pSpr->status = S_walkingUp;
	}
}


void MoveDown(TSpr *pSpr) __z88dk_fastcall {
	// move the sprite down if there is space and there are no barriers
	if (pSpr->y + SPR_H < GLOBAL_MAX_Y && OnBackground(pSpr->x-1, pSpr->y+4)) {
		pSpr->y += 2;
		if (pSpr->power_maxV > 0 && OnBackground(pSpr->x-1, pSpr->y+4))
			pSpr->y += 2; // powerUp speed*2
		
		pSpr->dir = D_down;
		pSpr->status = S_walkingDown;
	}
}


void MoveLeft(TSpr *pSpr) __z88dk_fastcall {
	// move the sprite to the left if there is space and there are no barriers
	if (OnBackground(pSpr->x-3, pSpr->y+1)) {
		pSpr->x--;
		if (pSpr->power_maxV > 0 && OnBackground(pSpr->x-3, pSpr->y+1))
			pSpr->x--; // powerUp speed*2
		
		pSpr->dir = D_left;
		pSpr->status = S_walkingLeft;
	} 
}


void MoveRight(TSpr *pSpr) __z88dk_fastcall { 
	// move the sprite to the right if there is space and there are no barriers
	if (OnBackground(pSpr->x+1, pSpr->y+1)) {
		pSpr->x++;
		if (pSpr->power_maxV > 0 && OnBackground(pSpr->x+1, pSpr->y+1)) 
			pSpr->x++; // powerUp speed*2
		
		pSpr->dir = D_right;
		pSpr->status = S_walkingRight;
	}
}


// prepare the movement
void WalkIn(TSpr *pSpr, u8 dir) {
	pSpr->nFrm = 0;
	pSpr->dir = dir;
	pSpr->status = dir;
	pSpr->print_minV = TRUE; // the sprite must be printed, it will move
}


// stands still
void Stop(TSpr *pSpr) __z88dk_fastcall {
	cpct_scanKeyboard_f(); // check the pressed keys
	if(cpct_isKeyPressed(ctlUp[pSpr->ident]))			WalkIn(pSpr, D_up);
	else if(cpct_isKeyPressed(ctlDown[pSpr->ident]))	WalkIn(pSpr, D_down);
	else if(cpct_isKeyPressed(ctlLeft[pSpr->ident]))	WalkIn(pSpr, D_left);
	else if(cpct_isKeyPressed(ctlRight[pSpr->ident]))	WalkIn(pSpr, D_right);	
	// leave the game
	else if(cpct_isKeyPressed(ctlAbort)) {
		spr[0].lives_speed = 0;
		spr[1].lives_speed = 0;
		GameOver(2);
	}
	// mute music TRUE/FALSE
	else if(cpct_isKeyPressed(ctlMusic)) {
		Wait4Key(ctlMusic);
		if (music == TRUE) { // if the music is playing ...
			music = FALSE;
			cpct_akp_musicInit(g_fx);
		}
		else { // if there was no music playing ...
			music = TRUE;			
			cpct_akp_musicInit(g_ingame); // music ingame
		}
	}
	// pause
	else if(cpct_isKeyPressed(ctlPause)) {
		Wait4Key(ctlPause);
		cpct_akp_musicInit(g_fx);
		while (!cpct_isAnyKeyPressed());
		Wait4Key(ctlPause);
		if (music)
			cpct_akp_musicInit(g_ingame); // music ingame
	}

	
	/*
	// beta testing helper /////////////////////////////////////////
	else if(cpct_isKeyPressed(Key_Space)) {
		if (nMap < 11) 
			nMap++; // go to the next screen on the map
		else
			nMap = 0;
		
		// reset data related to object collection
		ResetObjData(0);
		ResetObjData(1);		
		InitScoreboard();
		ResetData();
	}
	////////////////////////////////////////////////////////////////
	*/
}


// assign the frame corresponding to the animation sequence of the sprite
void WalkAnim(TSpr *pSpr, u8 dir) {
	u8 animPause = 2;
	if (pSpr->num > 3) animPause = 1; // slow enemies (4 and 5) have no pause in animation
	pSpr->dir = dir;
	if(++pSpr->nFrm == animPause*2) pSpr->nFrm = 0;
}


// walking
void Walk(TSpr *pSpr) __z88dk_fastcall {
	cpct_scanKeyboard_f(); // check the pressed keys
	// possible movements to the right
	if(cpct_isKeyPressed(ctlRight[pSpr->ident])) {	
		if (cpct_isKeyPressed(ctlUp[pSpr->ident])) 			MoveUp(pSpr);  // diagonal derecha-arriba
		else if(cpct_isKeyPressed(ctlDown[pSpr->ident]))	MoveDown(pSpr); // diagonal derecha-abajo
		MoveRight(pSpr);
		WalkAnim(pSpr, D_right);
	}
	// possible movements to the left
	else if(cpct_isKeyPressed(ctlLeft[pSpr->ident])) {	
		if (cpct_isKeyPressed(ctlUp[pSpr->ident])) 			MoveUp(pSpr); // diagonal izda-arriba
		else if(cpct_isKeyPressed(ctlDown[pSpr->ident]))	MoveDown(pSpr); // diagonal izda-abajo
		MoveLeft(pSpr); 
		WalkAnim(pSpr, D_left);
	}
	// only up
	else if(cpct_isKeyPressed(ctlUp[pSpr->ident])) {
		MoveUp(pSpr); 
		WalkAnim(pSpr, D_up);
	}
	// only down
	else if(cpct_isKeyPressed(ctlDown[pSpr->ident])) {
		MoveDown(pSpr); 
		WalkAnim(pSpr, D_down);
	}
	else
		pSpr->status = S_stopped;
}


// calls the appropriate function based on the status of the main sprites
void RunStatus(TSpr *pSpr) __z88dk_fastcall {
	if (pSpr->status == S_stopped)
		Stop(pSpr);
	else
		Walk(pSpr);	
}


// player logic inside the main loop
void PlayerLoop(TSpr *pSpr) __z88dk_fastcall {
	RunStatus(pSpr); // calls the appropriate function based on the status of the main sprites
	if (pSpr->print_minV) { // does the sprite have to be reprinted?
		SelectFrame(pSpr); // we assign the next frame of the animation to the sprite
		DeleteSprite(pSpr); // delete the sprite
		pSpr->px = pSpr->x; // save the current X coordinate
		pSpr->py = pSpr->y; // save the current Y coordinate
		PrintSprite(pSpr); // paint the sprite in the new XY position
		ctInactivity[pSpr->num] = 0; // on the move
		if (pSpr->status == S_stopped) 
			pSpr->print_minV = FALSE; // if it is stopped it is no longer necessary to continue printing the sprite
	}
	// sometimes reprint, in case they have been deleted between both players
	else if (ctMainLoop % 5 == 0)
		PrintSprite(pSpr);
}	










///////////////////////////////////////////////////////////////////////////////////
// DUEL SEQUENCE BETWEEN BOTH PLAYERS
///////////////////////////////////////////////////////////////////////////////////

// Eliminate the player with an explosion inside the duel sequence
void ExplodePlayerInDuel(u8 player) __z88dk_fastcall {
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, spr[player].x, 122), cpct_px2byteM0(4, 4), SPR_W, SPR_H);
	ExplodeSprite(player, FALSE);
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, spr[player].x, 122), cpct_px2byteM0(4, 4), SPR_W, SPR_H);
}


// duel window animations
void MakeDuel() {
	u8 loser;
	// print a frame with blue background
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 18, 80), cpct_px2byteM0(4, 4), 45, 60);
	PrintFrame(18,80,60,134);
	// print player 1
	spr[0].x = 23; spr[0].y = 122;
	cpct_drawSpriteMaskedAlignedTable(g_sorcerer1_06,
		cpct_getScreenPtr(CPCT_VMEM_START, spr[0].x, spr[0].y), SPR_W, SPR_H, g_maskTable);
	// print player 2 if there are two players
	spr[1].x = 53; spr[1].y = 122;
	if (TwoPlayers) {
		cpct_drawSpriteMaskedAlignedTable(g_sorcerer2_04, 
			cpct_getScreenPtr(CPCT_VMEM_START, spr[1].x, spr[1].y), SPR_W, SPR_H, g_maskTable);
	}
	// print a door if there are not two players
	else {
		cpct_drawSpriteMaskedAlignedTable(g_door_0, 
			cpct_getScreenPtr(CPCT_VMEM_START, spr[1].x, spr[1].y), SPR_W, SPR_H, g_maskTable);
	}
	Pause(400);

	// print both players shooting
	cpct_drawSpriteMaskedAlignedTable(g_sorcerer1_08, 
		cpct_getScreenPtr(CPCT_VMEM_START, spr[0].x, spr[0].y), SPR_W, SPR_H, g_maskTable);
	spr[0].x += OBJ_W;
	if (TwoPlayers) {
		cpct_drawSpriteMaskedAlignedTable(g_sorcerer2_08, 
			cpct_getScreenPtr(CPCT_VMEM_START, spr[1].x, spr[1].y), SPR_W, SPR_H, g_maskTable);
		spr[1].x -= OBJ_W;
	}
	cpct_akp_SFXPlay (5, 12, 60, 0, 0, AY_CHANNEL_B); // shot sound

	// print/delete both magic shots on the move
	while (spr[0].x < 50)
	{						
		// print
		spr[0].x ++;
		cpct_drawSpriteMaskedAlignedTable(g_magic_0, 
			cpct_getScreenPtr(CPCT_VMEM_START, spr[0].x, 125), SHT_W, SHT_H, g_maskTable);
		if (TwoPlayers) {
			spr[1].x --;
			cpct_drawSpriteMaskedAlignedTable(g_magic_1, 
				cpct_getScreenPtr(CPCT_VMEM_START, spr[1].x, 125), SHT_W, SHT_H, g_maskTable);
		}
		Pause(12);
		// delete
		cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, spr[0].x, 125), 
			cpct_px2byteM0(4, 4), OBJ_W, OBJ_H);
		if (TwoPlayers)
			cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, spr[1].x, 125), 
				cpct_px2byteM0(4, 4), OBJ_W, OBJ_H);
	}
	
	// player 1 recovers the resting posture
	spr[0].x = 23;
	cpct_drawSpriteMaskedAlignedTable(g_sorcerer1_06, 
		cpct_getScreenPtr(CPCT_VMEM_START, spr[0].x, spr[0].y), SPR_W, SPR_H, g_maskTable);
	spr[1].x = 53;
	// player 2 recovers the posture of rest if there are two players
	if (TwoPlayers) {
		cpct_drawSpriteMaskedAlignedTable(g_sorcerer2_04, 
			cpct_getScreenPtr(CPCT_VMEM_START, spr[1].x, spr[1].y), SPR_W, SPR_H, g_maskTable);
	}

	// player 1 wins?
	if (potScore[0] > potScore[1]) {
		loser = 1;
		ExplodePlayerInDuel(loser);
		if (TwoPlayers) {
			// print player 2 looking bad
			cpct_drawSpriteMaskedAlignedTable(g_sorcerer2_09, 
				cpct_getScreenPtr(CPCT_VMEM_START, spr[1].x, spr[1].y), SPR_W, SPR_H, g_maskTable);
			PrintText("PLAYER1", 30, 90, 0);
			// the player who wins a duel wins a life
			// that way they may reach the last screen
			if (spr[0].lives_speed < 9) spr[0].lives_speed++;
		}
		else {
			// print the door open
			cpct_drawSpriteMaskedAlignedTable(g_door_1, 
				cpct_getScreenPtr(CPCT_VMEM_START, spr[1].x, spr[1].y), SPR_W, SPR_H, g_maskTable);
			PrintText("LEVEL", 33, 90, 0);
		}
	}
	// player 2 wins?
	else if (potScore[0] < potScore[1]) {
		loser = 0;
		ExplodePlayerInDuel(loser);
		// print player 1 looking bad
		cpct_drawSpriteMaskedAlignedTable(g_sorcerer1_09, 
			cpct_getScreenPtr(CPCT_VMEM_START, spr[0].x, spr[0].y), SPR_W, SPR_H, g_maskTable);
		PrintText("PLAYER2", 30, 90, 0);
		// the player who wins a duel wins a life
		// that way they may reach the last screen
		if (spr[1].lives_speed < 9) spr[1].lives_speed++;
	}
	// tie
	else {		
		PrintText("NOBODY", 32, 90, 0);
		loser = 2;
	}
	if (TwoPlayers)
		PrintText("WINS>", 33, 101, 0);
	else
		PrintText("COMPLETED", 27, 101, 0);	
	
	cpct_akp_musicInit(g_completed); // level completed music
	Pause(1000);

	if (loser < 2) // if there is no tie
		nMap++; // go to the next screen on the map

	if (nMap == 12) { // screens are over. End of the game
		if (loser == 0)		
			PrintEndGame(1); // player 2 wins
		else
			PrintEndGame(0); // player 1 wins
	}

	// reset data related to object collection
	ResetObjData(0);
	ResetObjData(1);
	InitScoreboard();

	if (loser < 2 && TwoPlayers)
		GameOver(loser); // the player who loses a duel loses a life
	else
		ResetData();
}


// check conditions to create a duel
void CheckDuel() {
	if ((spr[0].objNum_mov == 5 || spr[1].objNum_mov == 5) && 
		SpriteCollision(spr[0].x, spr[0].y, &spr[1], 0)) {				
		// clean the screen, deleting players, enemies and objects
		for(u8 i=0;i<6;i++)
			DeleteSprite(&spr[i]);
		DeleteObject(0);
		DeleteObject(1);

		MakeDuel();
	}
}










///////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR FIRE MANAGEMENT
///////////////////////////////////////////////////////////////////////////////////

// generates the shot
void MakeShot(u8 x, u8 y, u8 dir) {	
	if (sht.active == FALSE) { // if there is no active shot...
		sht.active = TRUE; // activate it
		sht.dir = dir; // the direction of the shot is that of the sprite that shoots
		sht.y = y + 5; // adjusts to the height of the gun (hand)
		// gives the shot the X coordinate of the main sprite
		if (sht.dir == D_right) sht.x = x + SPR_W;
		else sht.x = x - SHT_W;
		cpct_akp_SFXPlay (6, 12, 65, 0, 0, AY_CHANNEL_B); // shot sound
	}  
}


// print a map portion in the shot coordinates (to delete it)
void DeleteShot() {
	cpct_etm_drawTileBox2x4(sht.px / 2, (sht.y - ORIG_MAP_Y) / 4, 
							2 + (sht.px & 1), 2 + (sht.y & 3 ? 1 : 0), 
							MAP_W, cpctm_screenPtr(CPCT_VMEM_START, 0, ORIG_MAP_Y), UNPACKED_MAP_INI);							
}


void PrintShot(u8* magic) __z88dk_fastcall {
	DeleteShot(); // delete the previous shot
	if (!sht.active) return; // outside the margins. no need to print
	cpct_drawSpriteMaskedAlignedTable(magic, cpct_getScreenPtr(CPCT_VMEM_START, sht.x, sht.y), 
									  SHT_W, SHT_H, g_maskTable);
}


// move shot to corresponding XY position
void MoveShot() {
	sht.px = sht.x; // save the current X coordinate
	// change X for the next redrawn
	if (sht.dir == D_right)	sht.x++; else sht.x--;
	// check if we should continue drawing the shot (it has reached the extremes)
	if (sht.x + SHT_W >= GLOBAL_MAX_X || sht.x <= 0) {
		sht.active = FALSE;
		DeleteShot();
	}
}









///////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR THE WIZARD
///////////////////////////////////////////////////////////////////////////////////

// print the wizard sprite
void PrintWizard(u8 shooting) __z88dk_fastcall {
	u8* wizard;
	u8 x = 0;

	if (spr[6].dir == D_left) { // on the right bank facing left
		if (shooting) wizard = g_wizard_1;
		else wizard = g_wizard_0;
		x = 75;
	}
	else { // on the left bank facing right
		if (shooting) wizard = g_wizard_3; 
		else wizard = g_wizard_2;
	}
	
	cpct_drawSpriteMaskedAlignedTable(wizard, cpct_getScreenPtr(CPCT_VMEM_START, x, spr[6].y), 
									  SPR_W, SPR_H, g_maskTable); 							
}


// animation of the wizard shooting the player
void WizardAnim() {
	if (ctWizardAnim > 0) {
		switch(ctWizardAnim++) {			
			// different phases of the initial explosion
			case 1:
			case 29:	{ PrintExplosion(&spr[6], 0); break; }
			case 2:	
			case 30:	{ PrintExplosion(&spr[6], 1); break; }
			case 3:	
			case 31:	{ DeleteSprite(&spr[6]); PrintExplosion(&spr[6], 0); break; }						
			// print the wizard shooting, deleting the previous explosion
			case 4:		{ DeleteSprite(&spr[6]); PrintWizard(TRUE); break; }		
			// activate the shot
			case 5:		{ MakeShot(spr[6].x, spr[6].y-3, spr[6].dir); break; }			
			// do nothing
			case 6:			
			case 7:	
			case 8:
			case 9:
			case 10:			
			case 11:	{break;}
			// print the wizard, deleting the previous sprite shooting
			case 12:    { DeleteSprite(&spr[6]); PrintWizard(FALSE); break;}
			// makes the wizard disappear
			case 32:    { DeleteSprite(&spr[6]); ctWizardAnim = 0; return; }
			// reprint the witcher in case he is deleted
			default:	{ PrintWizard(FALSE); break;	}			
		}		
	}
}


// brings up the wizard
void MakeWizardAnim(u8 player) __z88dk_fastcall {
	if (ctInactivity[player]++ == 80 && !sht.active) {	
		spr[6].y = spr[6].py = spr[player].y;

		if (spr[player].x < 40) {
			spr[6].x = spr[6].px = 74;		
			spr[6].dir = D_left;
		}
		else {
			spr[6].x = spr[6].px = 1;
			spr[6].dir = D_right;
		}
		ctWizardAnim++; // makes the wizard shooting animation start
	}
}










///////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR THE ENEMIES CONTROL
///////////////////////////////////////////////////////////////////////////////////

// updates the XY coordinates of the sprites based on their movement type
void MoveEnemy(TSpr *pSpr) {
	u8 z = 255;	// multipurpose variable
	switch(pSpr->objNum_mov) {
		// linear motion on the X axis
		case M_linear_X:
			if (pSpr->dir == D_right) {
				// if it has not exceeded the maximum X, moves the sprite to the right
				if (pSpr->x < pSpr->power_maxV) 
					pSpr->x = pSpr->x + pSpr->lives_speed;
				else // if there is no place change the direction
					pSpr->dir = D_left;
			}
			else {
				// if it has not exceeded the minimum X, moves the sprite to the left
				if (pSpr->x > pSpr->print_minV)  
					pSpr->x = pSpr->x - pSpr->lives_speed;
				else // if there is no place change the direction
					pSpr->dir = D_right; 
			}
			// WITCH! activates shooting when the Y position coincides with the players
			if (pSpr->ident == WITCH) {
				if (pSpr->y > (spr[0].y - SHT_H) && pSpr->y < (spr[0].y + SHT_H)) z = 0; // P1
				else if (pSpr->y > (spr[1].y - SHT_H) && pSpr->y < (spr[1].y + SHT_H)) z = 1; // P2
				if (z < 255) {
					if (spr[z].x > pSpr->x) pSpr->dir = D_right; 
					else pSpr->dir = D_left;
					MakeShot(pSpr->x, pSpr->y, pSpr->dir);
				}
			}				
			break;

		// linear motion on the Y axis
		case M_linear_Y:
			if (pSpr->dir == D_down) {
				// if it has not exceeded the maximum y, moves the sprite down
				if (pSpr->y < pSpr->power_maxV)
					pSpr->y = pSpr->y + (pSpr->lives_speed*2);
				else // if there is no place change the direction
					pSpr->dir = D_up;
			}
			else {
				// if it has not exceeded the minimum y, moves the sprite up
				if (pSpr->y > pSpr->print_minV) 
					pSpr->y = pSpr->y - (pSpr->lives_speed*2);
				else // if there is no place change the direction
					pSpr->dir = D_down; 
			}
			break;

		// automatic linear movement depending on the terrain
		case M_linear_XY:		
			// continue up (adjust y + 8)
			if (pSpr->dir == D_up && OnBackground(pSpr->x, pSpr->y - (pSpr->lives_speed*2)-8))
				pSpr->y = pSpr->y - (pSpr->lives_speed*2);			
			// continue down
			else if (pSpr->dir == D_down && OnBackground(pSpr->x, pSpr->y + (pSpr->lives_speed*2)+2))
				pSpr->y = pSpr->y + (pSpr->lives_speed*2);
			// continue to the left (adjust x + 3)
			else if (pSpr->dir == D_left && OnBackground((pSpr->x - pSpr->lives_speed)-3, pSpr->y))
				pSpr->x = pSpr->x - pSpr->lives_speed;
			// continue to the right (adjust x - 1)
			else if (pSpr->dir == D_right && OnBackground((pSpr->x + pSpr->lives_speed)+1, pSpr->y))
				pSpr->x = pSpr->x + pSpr->lives_speed;
			// search for a new random address for the next move
			else pSpr->dir = cpct_getRandom_lcg_u8(0) / 65; // 0-1-2-3			
			break;

		// flying chaser
		case M_chaser:
			if (ctMainLoop % pSpr->lives_speed == 0) {
				z = 0;
				// select the closest player				
				if (TwoPlayers)
					z = Abs(pSpr->x - spr[1].x)*2 + Abs(pSpr->y - spr[1].y) <
						Abs(pSpr->x - spr[0].x)*2 + Abs(pSpr->y - spr[0].y);
				// if it's to the left of the target sprite it goes to the right
				if (pSpr->x < spr[z].x) {
						pSpr->x++;
						pSpr->dir = D_right;
				}
				// if it is to the right of the target sprite it goes to the left
				else if (pSpr->x > spr[z].x) {
						pSpr->x--;
						pSpr->dir = D_left;
				}
				// if it is above the target sprite it goes down
				if (pSpr->y < spr[z].y) {
					pSpr->y+=2;
				}
				// if it is below the target sprite it goes up
				else if (pSpr->y > spr[z].y) {
					pSpr->y-=2;
				}
			}
			break;
	}
}


// assign properties to enemy sprites
void SetEnemyParams(u8 i, u8 ident, u8 mov, u8 dir, u8 speed, u8 x, u8 y, u8 minV, u8 maxV) {
	spr[i].num = i;
	spr[i].ident = ident; 
	spr[i].objNum_mov = mov;	 
	spr[i].dir = dir; 
	spr[i].lives_speed = speed;
	spr[i].x = spr[i].px = x;
	spr[i].y = spr[i].py = y;
	spr[i].print_minV = minV;
	spr[i].power_maxV = maxV;
}


// values ​​enemy properties based on current map
// coordinate calculation: x=TILED(x)*2  y=(TILED(y)*4)+ORIG_MAP_Y  [ORIG_MAP_Y=32]
// for "linear" movements, the higher SPEED value, the higher speed
// for "chaser" movements, the lower SPEED value, the higher speed
// to avoid flickering assigning enemies 2 and 3 to those with the highest Y and putting a minimum Y
// enemies 2 and 3 are processed in each iteration of the loop (fast)
void SetEnemies() {
	switch (nMap) {
		// gardens #1
		case 0: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, SENTINEL,	M_linear_X, 	D_left,     1, 73, 158,   2,  73);						
			SetEnemyParams(3, SENTINEL,	M_linear_X, 	D_right,    1,  3, 110,   2,  73);
			SetEnemyParams(4, SENTINEL,	M_linear_X, 	D_left,     1, 73,  62,  40,  73);
			SetEnemyParams(5, SENTINEL,	M_linear_X, 	D_right,    1,  2,  62,   2,  35);
			// player 1 starting position
			spr[0].x = spr[0].px = 6; 
			spr[0].y = spr[0].py = 178;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk0_end);
			// screen title
			lName = "1;1@@GARDENS";
			// exit door key
			doorKey[0] = 4;	// toad snot
			doorKey[1] = 5;	// diamond dust
			doorKey[2] = 4;	// toad snot
			doorKey[3] = 5;	// diamond dust
			doorKey[4] = 4; // toad snot
			// store
			storeX = 51;
			storeY = 11;
			break;
		}
		// gardens #2
		case 1: {
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, NOBODY,	M_linear_X, 	D_left,     1,  0,   0,   0,   0);
			SetEnemyParams(3, SENTINEL,	M_linear_X, 	D_right,    1,  2, 114,   2,  73);						
			SetEnemyParams(4, KNIGHT, 	M_linear_XY,    D_right,    1, 10,  62,   0,   0);
			SetEnemyParams(5, KNIGHT,	M_linear_XY,	D_down,     1,  2,  38,   0,   0);
			// player 1 starting position
			spr[0].x = spr[0].px = 58; 
			spr[0].y = spr[0].py = 178;	
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk1_end);
			// screen title
			lName = "1;2@@GARDENS";
			// exit door key
			doorKey[0] = 4;	// toad snot
			doorKey[1] = 6;	// newt eye
			doorKey[2] = 5; // diamond dust
			doorKey[3] = 6; // newt eye
			doorKey[4] = 4; // toad snot
			// store
			storeX = 51;
			storeY = 55;
			break;
		}
		// cemetery #1
		case 2: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, GHOST,	M_linear_XY, 	D_right,    1,  3, 120,   0,   0);						
			SetEnemyParams(3, GHOST,	M_linear_XY, 	D_left,     1, 73,  99,   0,   0);
			SetEnemyParams(4, BAT,	 	M_linear_X,    	D_right,    1, 22,  58,  22,  60);																		
			SetEnemyParams(5, WITCH,	M_linear_X,		D_left,     1,  3,  78,   2,  73);
			// player 1 starting position
			spr[0].x = spr[0].px = 58; 
			spr[0].y = spr[0].py = 178;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk2_end);
			// screen title
			lName = "2;1@CEMETERY";
			// exit door key
			doorKey[0] = 4;	// toad snot
			doorKey[1] = 5;	// diamond dust
			doorKey[2] = 6; // newt eye
			doorKey[3] = 7;	// mammoth poop
			doorKey[4] = 8; // kraken ink
			// store
			storeX = 3;
			storeY = 11;
			break;
		}
		// cemetery #2
		case 3: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, GHOST,	M_linear_XY, 	D_left,     1,  2, 180,   0,   0);
			SetEnemyParams(3, GHOST,	M_linear_XY, 	D_right,    1,  2, 136,   0,   0);
			SetEnemyParams(4, GHOST,	M_linear_XY, 	D_left,     1, 70,  40,   0,   0);
			SetEnemyParams(5, GHOST,	M_linear_XY,	D_left,     1,  2,  40,   0,   0);
			// player 1 starting position
			spr[0].x = spr[0].px = 36; 
			spr[0].y = spr[0].py = 178;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk3_end);
			// screen title
			lName = "2;2@CEMETERY";
			// exit door key
			doorKey[0] = 5;	// diamond dust
			doorKey[1] = 7; // mammooth poop
			doorKey[2] = 6; // newt eye
			doorKey[3] = 7; // mammooth poop
			doorKey[4] = 5; // diamond dust
			// store
			storeX = 41;
			storeY = 71;
			break;
		}		
		// cellars #1
		case 4: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, BAT,		M_linear_X, 	D_left,     1, 73, 134,  16,  73);							
			SetEnemyParams(3, BAT,		M_linear_X, 	D_right,    1,  3,  94,   2,  73);		
			SetEnemyParams(4, KNIGHT,	M_linear_XY, 	D_down,    	1, 17,  50,   0,   0);
			SetEnemyParams(5, KNIGHT,	M_linear_XY, 	D_up,     	1, 57, 156,   0,   0);
			// player 1 starting position
			spr[0].x = spr[0].px = 6; 
			spr[0].y = spr[0].py = 175;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk4_end);
			// screen title
			lName = "3;1@@CELLARS";	
			// exit door key
			doorKey[0] = 4; // toad snot
			doorKey[1] = 9; // mermaid tear
			doorKey[2] = 10;// martian mushroom
			doorKey[3] = 9; // mermaid tear
			doorKey[4] = 4; // toad snot
			// store
			storeX = 5;
			storeY = 103;		
			break;
		}
		// cellars #2
		case 5: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, SENTINEL,	M_linear_X, 	D_left,     1,  3, 142,   2,  73);
			SetEnemyParams(3, SENTINEL,	M_linear_X, 	D_right,    1, 73, 102,   2,  73);						
			SetEnemyParams(4, KNIGHT,	M_linear_Y, 	D_down,     1, 38,  50,  50, 178);
			SetEnemyParams(5, WITCH,	M_linear_X,		D_left,     1,  3,  62,   2,  73);
			// player 1 starting position
			spr[0].x = spr[0].px = 34; 
			spr[0].y = spr[0].py = 176;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk5_end);
			// screen title
			lName = "3;2@@CELLARS";
			// exit door key
			doorKey[0] = 7; // mammooth poop
			doorKey[1] = 8; // kraken ink
			doorKey[2] = 9; // mermaid tear
			doorKey[3] = 6; // newt eye
			doorKey[4] = 5; // diamond dust
			// store
			storeX = 3;
			storeY = 143;
			break;
		}
		// castle #1
		case 6: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, KNIGHT,	M_linear_XY, 	D_up,     	1,  2, 174,   0,   0);
			SetEnemyParams(3, KNIGHT,	M_linear_XY, 	D_left,    	1, 60, 116,   0,   0);
			SetEnemyParams(4, SENTINEL,	M_linear_XY, 	D_left,     1, 73,  96,   0,   0);
			SetEnemyParams(5, WITCH,	M_linear_X,		D_left,     1,  3,  60,   2,  73);
			// player 1 starting position
			spr[0].x = spr[0].px = 67; 
			spr[0].y = spr[0].py = 176;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk6_end);
			// screen title
			lName = "4;1@@@CASTLE";	
			// exit door key
			doorKey[0] = 10; // martian mushroom
			doorKey[1] = 6; // newt eye
			doorKey[2] = 11; // dragon blood
			doorKey[3] = 6; // newt eye
			doorKey[4] = 10; // martian mushroom
			// store
			storeX = 3;
			storeY = 11;		
			break;
		}
		// castle #2
		case 7: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, NOBODY,	M_linear_XY, 	D_left,     1,  0,   0,   0,   0);
			SetEnemyParams(3, GHOST,	M_linear_XY, 	D_up,       1,  3, 176,   0,   0);
			SetEnemyParams(4, KNIGHT,	M_linear_XY, 	D_right,    1,  3,  44,   0,   0);
			SetEnemyParams(5, KNIGHT,	M_linear_XY, 	D_down,     1, 73,  44,   0,   0);
			// player 1 starting position
			spr[0].x = spr[0].px = 36; 
			spr[0].y = spr[0].py = 176;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk7_end);
			// screen title
			lName = "4;2@@@CASTLE";
			// exit door key
			doorKey[0] = 5; // diamond dust
			doorKey[1] = 11; // dragon blood
			doorKey[2] = 7; // mammooth poop
			doorKey[3] = 11; // dragon blood
			doorKey[4] = 5; // diamond dust
			// store
			storeX = 33;
			storeY = 95;
			break;
		}
		// tower #1
		case 8: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, NOBODY,	M_linear_X, 	D_left,     1,  0,   0,   0,   0);
			SetEnemyParams(3, GHOST,	M_chaser,		D_right,    7,  2, 114,   0,   0);						
			SetEnemyParams(4, KNIGHT, 	M_linear_XY,    D_right,    1, 10,  68,   0,   0);
			SetEnemyParams(5, KNIGHT,	M_linear_XY,	D_down,     1,  2,  38,   0,   0);
			// player 1 starting position
			spr[0].x = spr[0].px = 34; 
			spr[0].y = spr[0].py = 176;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk8_end);
			// screen title
			lName = "5;1@@@TOWER";	
			// exit door key
			doorKey[0] = 8; // kraken ink
			doorKey[1] = 9; // mermaid tear
			doorKey[2] = 10; // martian mushroom
			doorKey[3] = 11; // dragon blood
			doorKey[4] = 12; // dodo egg
			// store
			storeX = 25;
			storeY = 95;		
			break;
		}
		// tower #2
		case 9: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX	
			SetEnemyParams(2, BAT,		M_linear_X, 	D_left,     1, 73, 111,  41,  73);
			SetEnemyParams(3, BAT,		M_linear_X,		D_right,    1,  2, 111,   2,  34);				
			SetEnemyParams(4, SENTINEL, M_linear_Y,    	D_down,     1, 27,  44,  44, 175);
			SetEnemyParams(5, SENTINEL,	M_linear_Y,		D_up,       1, 49, 160,  44, 175);
			// player 1 starting position
			spr[0].x = spr[0].px = 34; 
			spr[0].y = spr[0].py = 176;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk9_end);
			// screen title
			lName = "5;2@@@TOWER";	
			// exit door key
			doorKey[0] = 10; // martian mushroom
			doorKey[1] = 5; // diamond dust
			doorKey[2] = 12; // dodo egg
			doorKey[3] = 4; // toad snot
			doorKey[4] = 13; // unicorn blood
			// store
			storeX = 41;
			storeY = 43;		
			break;
		}			
		// library #1
		case 10: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, SENTINEL,	M_linear_X, 	D_left,     1,  2, 156,   2,  73);
			SetEnemyParams(3, GHOST,	M_chaser, 		D_right,    4,  2, 114,   0,   0);
			SetEnemyParams(4, KNIGHT,	M_linear_Y, 	D_right,    1, 17,  40,  40, 145);
			SetEnemyParams(5, KNIGHT,	M_linear_Y, 	D_left,     1, 59,  40,  40, 145);
			// player 1 starting position
			spr[0].x = spr[0].px = 54; 
			spr[0].y = spr[0].py = 176;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk10_end);
			// screen title
			lName = "6;1@@LIBRARY";
			// exit door key
			doorKey[0] = 11; // dragon blood
			doorKey[1] = 8; // kraken ink
			doorKey[2] = 9; // dodo egg
			doorKey[3] = 10; // martian mushroom
			doorKey[4] = 15; // mordor lava
			// store
			storeX = 3;
			storeY = 143;
			break;
		}
		// library #2
		case 11: {			 
						//SPR IDENTITY	MOVEMENT		DIR     SPEED   X    Y  MIN  MAX
			SetEnemyParams(2, GHOST,	M_linear_X, 	D_left,     1,  2, 132,   2,  72);
			SetEnemyParams(3, GHOST,	M_chaser, 		D_right,    5,  2, 114,   0,   0);
			SetEnemyParams(4, KNIGHT,	M_linear_XY, 	D_down,     1, 21,  38,   0,   0);
			SetEnemyParams(5, KNIGHT,	M_linear_XY, 	D_down,     1, 55,  38,   0,   0);
			// player 1 starting position
			spr[0].x = spr[0].px = 34; 
			spr[0].y = spr[0].py = 176;			
			// unzip the map
			cpct_zx7b_decrunch_s(UNPACKED_MAP_END, mappk11_end);
			// screen title
			lName = "6;2@@LIBRARY";
			// exit door key
			doorKey[0] = 13; // unicorn blood
			doorKey[1] = 15; // mordor lava
			doorKey[2] = 14; // troll fat
			doorKey[3] = 15; // mordor lava
			doorKey[4] = 13; // unicorn blood
			// store
			storeX = 73;
			storeY = 11;
			break;
		}		
	}
	// player 2's starting position is always relative to player 1's
	if (TwoPlayers) {
		spr[1].x = spr[1].px = spr[0].x + 6; 
		spr[1].y = spr[1].py = spr[0].y;
	}
}


// check if there has been any collision of the players with the enemies
void CheckEnemyCollision(u8 player, TSpr *pSpr) 
{ 
	if ((spr[player].x + SPR_W) > pSpr->x && spr[player].x < (pSpr->x + SPR_W) &&
		(spr[player].y + SPR_H) > pSpr->y && spr[player].y < (pSpr->y + SPR_H)) {
		//an enemy has touched player 1 or 2
		ExplodeSprite(player, pSpr->num);			
		GameOver(player);
	}
	// collision shot with sprites
	else if (sht.active) {
		if ((sht.x + SHT_W) > (spr[player].x) && sht.x < (spr[player].x + SPR_W))
			if ((sht.y + SHT_H) > (spr[player].y) && (sht.y) < (spr[player].y + SPR_H))	{
				// a shot has touched player 1 or 2
				DeleteShot();
				ExplodeSprite(player, pSpr->num);			
				GameOver(player);
			}
	}
}


// logic of enemy sprites within the main loop
void EnemyLoop(TSpr *pSpr) __z88dk_fastcall {
	if (pSpr->ident == NOBODY) 
		return; 
	// update the XY coordinates of the sprite
	MoveEnemy(pSpr);
	// select the animation frame and apply it
	SelectFrame(pSpr); 
	WalkAnim(pSpr, pSpr->dir);
	// delete the sprite from the previous position and paint in the current one
	DeleteSprite(pSpr);
	pSpr->px = pSpr->x; // save the current X coordinate
	pSpr->py = pSpr->y; // save the current Y coordinate
	PrintSprite(pSpr);
	// check if any collision has occurred
	CheckEnemyCollision(0, pSpr);
	if (TwoPlayers)
		CheckEnemyCollision(1, pSpr);
}










///////////////////////////////////////////////////////////////////////////////////
// MAIN MENU
///////////////////////////////////////////////////////////////////////////////////

void PrintStartMenu() {
	ClearScreen();

    // "SORCERERS" logo
	cpct_drawSprite(g_logo_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 0), G_LOGO_0_W, G_LOGO_0_H);
	cpct_drawSprite(g_logo_1, cpctm_screenPtr(CPCT_VMEM_START, G_LOGO_0_W, 0), G_LOGO_0_W, G_LOGO_0_H);

	PrintText("1@@1@PLAYER@GAME", 10, 50, 0);
	PrintText("2@@2@PLAYER@GAME", 10, 60, 0);
    PrintText("3@@REDEFINE@CONTROLS", 10, 70, 0);
	if (turboMode)
		PrintText("4@@TURBO@MODE:@ON", 10, 80, 0);
	else
		PrintText("4@@TURBO@MODE:@OFF", 10, 80, 0);

	// Sven y Erik
	cpct_drawSpriteMaskedAlignedTable(g_sorcerer1_06, 
		cpct_getScreenPtr(CPCT_VMEM_START, 6, 187), SPR_W, SPR_H, g_maskTable);
	cpct_drawSpriteMaskedAlignedTable(g_sorcerer2_04, 
		cpct_getScreenPtr(CPCT_VMEM_START, 68, 187), SPR_W, SPR_H, g_maskTable);

    PrintText("CODE@=@GFX", 25, 110, 0);
    PrintText("SALVAKANTERO", 22, 120, 0);
    PrintText("MUSIC@=@FX", 25, 135, 0);
    PrintText("MCKLAIN", 30, 145, 0);
    PrintText("BETA@TESTING", 22, 160, 0);
    PrintText("BLACKMORES", 25, 170, 0);

    PrintText("PLAY@ON@RETRO@2020", 13, 190, 0);
}


// ingredients info table
void PrintObjInfo() {
	u8 obj;
	u8 yPos = 25;
	ClearScreen();
	PrintText("INGREDIENT@VALUES", 13, 0, 0);
	// blue background frame
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 3, 12), cpct_px2byteM0(4, 4), 37, 188);
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 40, 12), cpct_px2byteM0(4, 4), 35, 188);	
	PrintFrame(3,12,72,194);
	// object graphic and value
	for (obj=4; obj<16; obj++) {
		PrintObject(obj, 7, yPos);
		PrintNumber(obj-3, 2, 62, yPos, 0); PrintText("<", 68, yPos, 0);
		yPos += 14;
	}
	// object names
	PrintText("TOAD@SNOT", 14, 25, 0);
	PrintText("DIAMOND@DUST", 14, 39, 0);
	PrintText("NEWT@EYE", 14, 53, 0);
	PrintText("MAMMOTH@POOP", 14, 67, 0);
	PrintText("KRAKEN@INK", 14, 81, 0); 
	PrintText("MERMAID@TEAR", 14, 95, 0);
	PrintText("MARTIAN@MUSHROOM", 14, 109, 0);
	PrintText("DRAGON@BLOOD", 14, 123, 0);
	PrintText("DODO@EGG", 14, 137, 0); 
	PrintText("UNICORN@BLOOD", 14, 151, 0);
	PrintText("TROLL@FAT", 14, 165, 0); 
	PrintText("MORDOR@LAVA", 14, 179, 0);
}

/*
// introductory help (dismissed; not enough memory)
void PrintGameInfo() {
	ClearScreen();
	PrintText("THE@STORY", 26, 0, 0);
	// blue background frame
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 1, 12), cpct_px2byteM0(4, 4), 39, 180);
	cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 40, 12), cpct_px2byteM0(4, 4), 37, 180);	
	PrintFrame(1,12,74,186);

	PrintText("EINAR@IS@DEAD>", 17, 30, 0);
	PrintText("THE@OLD@AND@WISE", 14, 45, 0);
	PrintText("SORCERER", 26, 60, 0);

	PrintText("GUIDE@SVEN@AND@ERIK[", 11, 90, 0);
	PrintText("SONS@OF@EINAR@AND", 14, 105, 0);
	PrintText("SORCERERS@APPRENTICES[", 8, 120, 0);
	PrintText("TO@THE@CASTLE@LIBRARY", 8, 135, 0);
	PrintText("TO@GAIN@THE@KNOWLEDGE", 8, 150, 0);	
	PrintText("OF@EINAR>", 26, 165, 0);
}*/


void StartMenu() {
	u8 randSeed = 254;
	u8 page = 0;
	cpct_akp_musicInit(g_menu); // initialize music. Main theme

	while(1) {
		// get the seed of randomness based on the time it takes to press a key
		// switches between menu and help after 256 cycles
		if (++randSeed == 255) {					
			if (page == 0) 		PrintStartMenu();	// page 1; menu
			else if(page == 4)	PrintObjInfo();		// page 2; ingredients info
			//else if(page == 8)	PrintGameInfo();	// page 3; introductory help
			randSeed = 0;
			if (++page == 8) //12
				page = 0;		
		}
		// get keystrokes from menu options
		cpct_scanKeyboard_f();
		if(cpct_isKeyPressed(Key_1)) { // 1 player
			TwoPlayers = FALSE;	
        	break;
    	}
   		else if(cpct_isKeyPressed(Key_2)) {	// 2 players
			TwoPlayers = TRUE;
        	break;
    	}
   		else if(cpct_isKeyPressed(Key_3)){ // redefine keys
			Wait4Key(Key_3);
			randSeed = 0; page = 1;
			PrintStartMenu();
			// hide credits
			cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 22, 110), cpct_px2byteM0(1, 1), 45, 70);

			// player 1
			ctlUp[0] = 		RedefineKey("@P1@UP");
			ctlDown[0] = 	RedefineKey("P1@DOWN");
			ctlLeft[0] = 	RedefineKey("P1@LEFT");
			ctlRight[0] = 	RedefineKey("P1@RIGHT");
			// player 2
			ctlUp[1] = 		RedefineKey("@P2@UP@@");
			ctlDown[1] = 	RedefineKey("P2@DOWN");
			ctlLeft[1] = 	RedefineKey("P2@LEFT");
			ctlRight[1] = 	RedefineKey("P2@RIGHT");	
			// common
			ctlAbort = 		RedefineKey("@ABORT@@");
			ctlMusic = 		RedefineKey("@MUSIC");
			ctlPause =		RedefineKey("@PAUSE");		
			PrintStartMenu();
    	}
		else if(cpct_isKeyPressed(Key_4)) {	// turbo mode
			turboMode = !turboMode;
			randSeed = 0; page = 1;
			PrintStartMenu();
    	}
		Pause(3);
	}	
	cpct_setSeed_lcg_u8(randSeed); // set the seed
	cpct_akp_musicInit(g_fx); // mute the music
	ClearScreen();
}










///////////////////////////////////////////////////////////////////////////////////
// MAIN LOOP
///////////////////////////////////////////////////////////////////////////////////

// assigns default values ​​that do not vary between games
void InitValues() {	
	// default key mapping
	// player 1
	ctlUp[0] = Key_W;
	ctlDown[0] = Key_S;
	ctlLeft[0] = Key_A;
	ctlRight[0] = Key_D;
	// player 2
	ctlUp[1] = Key_F5;
	ctlDown[1] = Key_F2;
	ctlLeft[1] = Key_F1;
	ctlRight[1] = Key_F3;
	// common
	ctlAbort = Key_X;
	ctlMusic = Key_M;
	ctlPause = Key_H;	

	turboMode = FALSE;
	nTip = 0;
}


// InitGame() and gameOver() common values
void ResetData() {
	ctMainLoop = 0;
	nObj[0] = -1;
	nObj[1] = -1;
	sht.active = FALSE;
	ctWizardAnim = 0;
	
	// reset player data
	spr[0].dir = D_right; 
	spr[0].status = S_stopped;
	spr[0].print_minV = TRUE; // the first time must be printed on screen
	spr[0].power_maxV = 0;
	ctInactivity[0] = 0;

	spr[1].dir = D_left; 
	spr[1].status = S_stopped;	
	spr[1].print_minV = TRUE; // the first time must be printed on screen
	spr[1].power_maxV = 0;
	ctInactivity[1] = 0;
	
	SetEnemies();
	PrintMap();
	RefreshScoreboard();
	DeleteObjectInStore();

	// prints level information if it is the first map load
	if (nMap != lastNMap) {
		if (!TwoPlayers) {
			PrintKey();
			// reset player1's key only if it's a new map
			playerKey[0] = 0;
			playerKey[1] = 0;
			playerKey[2] = 0;
			playerKey[3] = 0;
			playerKey[4] = 0;
		}
		PrintLevelInfo();	
		PrintMap();	
		lastNMap = nMap;
	}
}


// initialization of some variables
void InitGame() {
	StartMenu(); // run the start menu
	music = TRUE;
	nMap = 0; // initial map number
	lastNMap = 255;
	
	// initial player 1 data
	spr[0].num = 0; // sprite number
	spr[0].ident = SORCERER1; // identity
	spr[0].lives_speed = 3; // lives
	score[0] = 0; // score
	ResetObjData(0);
	
	// initial player 2 data
	spr[1].num = 1; // sprite number
	spr[1].ident = SORCERER2; // identity
	spr[1].lives_speed = 3; // lives
	score[1] = 0; // score
	ResetObjData(1);

	// initial wizard data
	spr[6].num = 6; // sprite number
	spr[6].ident = WIZARD; // identity

	InitScoreboard();		
	ResetData();
}


// Players 1 or 2 lose a life, some variables are reset
void GameOver(u8 player) {
	// if there are lives left
	if (spr[player].lives_speed > 1 && player != 2) {
		spr[player].lives_speed--;
		ResetData();
	}
	else { // prepare a new game
		cpct_akp_musicInit(g_end); // game over music
		// puts 0 life on the scoreboard of the losing player
		spr[player].lives_speed = 0;
		RefreshScoreboard();
		// print a GAME OVER in the center of the play area
		cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START,  6, 80), cpct_px2byteM0(4, 4), 34, 60);
		cpct_drawSolidBox(cpctm_screenPtr(CPCT_VMEM_START, 40, 80), cpct_px2byteM0(4, 4), 34, 60);
		PrintFrame(6,80,71,134);
		if (TwoPlayers) {
			PrintText("G@A@M@E@@O@V@E@R", 16, 91, 0);
			if (player == 0) PrintText("PLAYER@2@WINS>", 19, 106, 0);
			else if (player == 1) PrintText("PLAYER@1@WINS>", 19, 106, 0);
			PrintText("HIGH@SCORE:", 16, 122, 0);
			PrintNumber(highScore, 4, 52, 122, 0);			
		}
		else
			PrintText("G@A@M@E@@O@V@E@R", 16, 107, 0);
		Pause(500);	
		// wait for a key press
		while (!cpct_isAnyKeyPressed());
		InitGame();
	}
}


void main(void) {
	// disable firmware
	cpct_disableFirmware();
	// initialize sound effects
	cpct_akp_SFXInit(g_fx);
	// initialize the interrupt manager (keyboard and sound)
	cpct_setInterruptHandler(Interrupt); 
	// activate mode 0; 160 * 200 16 colors
	cpct_setVideoMode(0);
	// assign palette
	cpct_setPalette(g_palette, 16);
	// print border (black)
	cpct_setBorder(g_palette[BG_COLOR]);
	// keep in memory the tiles for the maps (4 * 4)
	cpct_etm_setTileset2x4(g_tileset);	
	// assigns default values ​​that do not vary between games
	InitValues();
	// initial value assignment for each item
	InitGame();

	// main loop
	while (1) {
		// every 8 passes of the loop ...
		if (ctMainLoop % 8 == 0) {
			ReprintObject(); // reprint the active object
			PrintObjectInStore(); // reprint the object into the store
			CheckObject(0); // verify collection of object 1
			CheckObject(1); // verify collection of object 2
			MakeWizardAnim(0); // activates the wizard's shot if the player 1 is inactive		
			if (spr[0].print_minV) CheckActiveTile(0); // check entry into store, door or well of player 1

			if (TwoPlayers) {
				CheckDuel(); // check that both players collide and have potions
				MakeWizardAnim(1); // activates the wizard's shot if the player 2 is inactive		
				if (spr[1].print_minV) CheckActiveTile(1); // check entry into store, door or well of player 2
			}
			WizardAnim(); // print the wizard if active
		}		
		
		if (!turboMode) cpct_waitVSYNC(); // wait for vertical retrace	

		// shift system to avoid double video buffer
		switch (ctMainLoop % 3) {
			// turn 1
			case 0: {							
				PlayerLoop(&spr[0]); // player 1
				EnemyLoop(&spr[2]);	 // enemy sprite 2 is always processed (fast)
				break;
			}
			// turn 2
			case 1:	{			
				if (TwoPlayers) {
					PlayerLoop(&spr[1]); // player 2
					if (!turboMode) cpct_waitVSYNC(); // additional wait for vertical retrace (avoid flickering)
				}
				EnemyLoop(&spr[3]);	 // enemy sprite 3 is always processed (fast)
				break;
			}			
			// turn 3			
			case 2:	{
				EnemyLoop(&spr[enemyTurn+4]); // enemy sprites 4 and 5 take turns processing (slow)				
				if (++enemyTurn > 1) enemyTurn = 0;
				
				// process active shot
				if (sht.active) {				
					MoveShot(); // update the shot's XY coordinates	
					
					// delete the shot and reprint it on the new XY	
					if (ctWizardAnim > 0) 	
						PrintShot(g_magic_3);	// wizard
					else
						PrintShot(g_magic_2);	// witch
				}

				// decrease the powerUp value of the players
				if (spr[0].power_maxV > 0) spr[0].power_maxV--;
				if (spr[1].power_maxV > 0) spr[1].power_maxV--;			
			}
		}
		
		if (ctMainLoop == 174) {
			ctMainLoop++;
			SetObject(1); // set the second object

			if (nMap == 0 && !TwoPlayers && nTip<1) 
				PrintTip(); // novice help
		}
		else if (ctMainLoop++ == 350) {			
			SetObject(0); // set the first object			
			ctMainLoop = 0; // reset counter
		}		

		// DEBUG					
		//PrintNumber(spr[3].dir, 2, 72, 185, 1); 
	}
}
