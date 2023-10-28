
#define SAFE_INT_ADDRESS 	23297
unsigned int asm_int 	@ SAFE_INT_ADDRESS;

#include <spritepack.h>
#include "my_sprites.h"
#include "my_levels.h"

#include "aplib.h"
#include "beeper.h"

#pragma output STACKPTR=61440

extern struct sp_Rect *sp_ClipStruct;

#asm
LIB SPCClipStruct
._sp_ClipStruct         defw SPCClipStruct
#endasm

extern uchar *sp_NullSprPtr;
#asm
LIB SPNullSprPtr
._sp_NullSprPtr         defw SPNullSprPtr
#endasm 

uchar hash[] = {0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa};

struct sp_UDK keys;

/* Create memory allocator for sprite routines */

void *my_malloc(uint bytes)
{
   return sp_BlockAlloc(0);
}

void *u_malloc = my_malloc;
void *u_free = sp_FreeBlock;
 
extern uchar * level_curr[] = NULL;
struct sp_SS * s_player = NULL;
struct sp_SS * s_key  	= NULL;
struct sp_SS * s_door  	= NULL;
struct sp_SS * s_boat  	= NULL;
 
struct sp_SS * s_level[110] = {NULL};
uchar s_level_count = 0;

uchar current_level = 0;

uchar player_x = 1;
uchar player_y = 3;

uchar key_x = 4;
uchar key_y = 5;

uchar door_x = 5;
uchar door_y = 3;

uchar has_key = 0;

uchar level_off_x = 0;
uchar level_off_y = 0;

uchar hasBlock(uchar x, uchar y){
	uchar sub = x >> 3;
	uchar fra = x % 8;
	return ((*level_curr)[(y<<2)+sub] >> ( 7-fra )) & 0x01;	
}

uchar hasHitKey(uchar x, uchar y){
	if(x == key_x && y == key_y) {
		return has_key = 1;
	}
	return 0;
}

uchar hasHitDoor(uchar x, uchar y){
	if(x == door_x && y == door_y) {
		return  1;
	}
	return 0;
}


void moveKey(uchar x, uchar y){
	key_y = y;
	key_x = x;
	 
	sp_MoveSprAbs(s_key, sp_ClipStruct, 0, key_y + level_off_y, key_x + level_off_x , 0, 0);
}

void moveDoor(uchar x, uchar y){
	door_y = y;
	door_x = x;
	sp_MoveSprAbs(s_door, sp_ClipStruct, 0, door_y + level_off_y, door_x + level_off_x, 0, 0);
}

void movePlayer(uchar x, uchar y){
	player_y = y;
	player_x = x;
	 
	sp_MoveSprAbs(s_player, sp_ClipStruct, 0, player_y + level_off_y, player_x + level_off_x, 0, 0);
}

void moveBoat(uchar x, uchar y){
	sp_MoveSprAbs(s_boat, sp_ClipStruct, 0, y + level_off_y, x + level_off_x, 0, 0);
}

void hideBoat(){
	moveBoat(40,0);
}

void hideDoor(){
	moveDoor(28,0);
}

void hideKey(){
	moveKey(31,0);
}


void clearLevel(){
	for(uchar i = 0;i<s_level_count;i++){
		sp_MoveSprAbs(s_level[i], sp_ClipStruct, 0, 40, 40, 0, 0);
		sp_DeleteSpr(s_level[i]);
		s_level[i] = NULL;
	}
	
	s_level_count = 0;
}

void load_level(int width, int height){
	struct sp_SS *tmp;
	// Mover Jogador, Chave e Porta para os sitios certos.
	sp_MoveSprAbs(s_key, sp_ClipStruct, 0, level_off_y + key_y, level_off_x + key_x, 0, 0);
	sp_MoveSprAbs(s_player, sp_ClipStruct, 0, level_off_y + player_y, level_off_x + player_x, 0, 0);
		sp_MoveSprAbs(s_door, sp_ClipStruct, 0, level_off_y + door_y, level_off_x +door_x, 0, 0);
		
	// Iniciar o nivel.
	for(uchar x = 0; x < width; x++){
		for(uchar y= 0; y < height; y++){
			if(hasBlock(x,y) == 1){
				if(hasBlock(x,y+1) == 1){
					tmp = sp_CreateSpr(sp_MASK_SPRITE, 2, wall_block);
					sp_MoveSprAbs(tmp, sp_ClipStruct, 0, level_off_y + y, level_off_x + x, 0, 0);
					
					s_level[s_level_count++] = tmp;
					
					y++;
				} else if(hasBlock(x+1,y) == 0 && hasBlock(x-1,y) == 0){
					tmp = sp_CreateSpr(sp_MASK_SPRITE, 1, wall_square);
					sp_MoveSprAbs(tmp, sp_ClipStruct, 0, level_off_y + y, level_off_x + x, 0, 0);
					s_level[s_level_count++] = tmp;
				}
				
			}
		}
	}

	for(uchar y = 0; y < height; y++){
		for(uchar x = 0; x < width; x++){
			if(hasBlock(x,y) == 1){
				if(hasBlock(x+1,y) == 1){
					tmp = sp_CreateSpr(sp_MASK_SPRITE, 1, wall_square);
					sp_AddColSpr(tmp, wall_square);
					sp_MoveSprAbs(tmp, sp_ClipStruct, 0, level_off_y + y, level_off_x + x, 0, 0);
					
					s_level[s_level_count++] = tmp;
					x++;
				} else if(hasBlock(x,y+1) == 0 && hasBlock(x,y-1) == 0){
					tmp = sp_CreateSpr(sp_MASK_SPRITE, 1, wall_square);
					sp_MoveSprAbs(tmp, sp_ClipStruct, 0, level_off_y + y, level_off_x + x, 0, 0);
					s_level[s_level_count++] = tmp;
				}
			}
		}
	}
}

void load_level_0(){
	level_off_x = 12;
	level_off_y = 8;
	
	(*level_curr) = level_0;
	load_level(8,8);
	
	hideBoat();
	moveKey(4,5);
	moveDoor(5,3);
	movePlayer(1,3);
}

void load_level_1(){
	level_off_x = 8;
	level_off_y = 4;
	
	(*level_curr) = level_1;
	load_level(32, 16);
	
	moveKey(11,1);
	moveDoor(1,8);
	movePlayer(6,8);
}

void load_level_2(){
	level_off_x = 4;
	level_off_y = 6;
	
	(*level_curr) = level_2;
	load_level(32, 16);
	
	moveKey(18,1);
	moveDoor(18,7);
	movePlayer(4,8);
}

void load_level_3(){
	level_off_x = 4;
	level_off_y = 5;
	
	(*level_curr) = level_3;
	load_level(32, 16);
	
	moveKey(12,13);
	moveDoor(18,10);
	movePlayer(4,10);
}

void load_level_4(){
	level_off_x = 6;
	level_off_y = 6;
	
	(*level_curr) = level_4;
	load_level(32, 16);
	
	moveKey(4,6);
	moveDoor(8,3);
	movePlayer(7,9);
}

void load_level_5(){
	level_off_x = 8;
	level_off_y = 8;
	
	(*level_curr) = level_5;
	load_level(32, 8);
	
	moveBoat(15,1);
	moveKey(1,2);
	moveDoor(13,1);
	movePlayer(1,5);
}

// Level 0
// 8, 7

// Level 1
// 32, 16

main()
{
	uint reset;
	char dx, dy, i;

	#asm
	di
	#endasm

	sp_Initialize (0, 0);
	sp_Border (BLACK);

	sp_AddMemory(0, 255, 14, 0xb000);

	//sp_Initialize (0, 0);
	//sp_Border (BLACK);
	// Reserve memory blocks for sprites
	//sp_AddMemory(0, NUMBLOCKS, 14, AD_FREE);


	keys.up    = sp_LookupKey('w');
	keys.down  = sp_LookupKey('s');
	keys.left  = sp_LookupKey('a');
	keys.right = sp_LookupKey('d');
	keys.fire  = sp_LookupKey(' ');
	reset      = sp_LookupKey('r');

	while(1){
		sp_UpdateNow();
		unpack ((unsigned int) (s_title), 16384);
			
		while(1) {
			i = sp_JoyKeyboard(&keys);
			if(sp_KeyPressed(keys.fire))
			  break;
		}

		sp_TileArray(' ', hash);
		sp_Initialize(INK_WHITE | PAPER_BLACK, ' ');
		sp_Border(BLACK);

		// Iniciar a srite da chave
		if(s_key == NULL) 
			s_key = sp_CreateSpr(sp_MASK_SPRITE, 2, chave);

		if(s_player == NULL){
			// Iniciar a sprite do jogador
			s_player = sp_CreateSpr(sp_MASK_SPRITE, 2, player_l);
			sp_AddColSpr(s_player, player_r); // Colar a parte da esquerda do jogador
		}

		if(s_door == NULL){
			// Iniciar a sprite da porta.
			s_door = sp_CreateSpr(sp_MASK_SPRITE, 2, porta_l);
			sp_AddColSpr(s_door, porta_r); // Colar o resto da porta.
		}
	
		if(s_boat == NULL){
			s_boat = sp_CreateSpr(sp_MASK_SPRITE, 2, barco_0);
			sp_AddColSpr(s_boat, barco_1);
			sp_AddColSpr(s_boat, barco_2);
			sp_AddColSpr(s_boat, barco_3);
			sp_MoveSprAbs(s_boat, sp_ClipStruct, 0, 40, 0, 0, 0);
		}
		
		beep_fx(2);
		load_level_0();
		
		while(1) {
			uchar had_key = has_key;
			
			sp_UpdateNow();
			i = sp_JoyKeyboard(&keys);
			
			uchar next_level = 0;
			
			if (sp_KeyPressed(keys.left))
			{
				uchar tx = player_x;
				while(tx > 0){
					if(hasHitKey(tx-1, player_y)) 
						hideKey();
					
					if(hasHitDoor(tx-1, player_y) && has_key)
						next_level = 1;
						//hideDoor();
					
					if(hasBlock(tx-1, player_y) != 1)
						tx --;
					else{
						if(player_x != tx) beep_fx(1);
						break;
					}
				}
				player_x = tx;
			}
			else if  (sp_KeyPressed(keys.right))
			{
				uchar tx = player_x;
				while(tx < 25){
					if(hasHitKey(tx+1, player_y)) 
						hideKey();
					
					if(hasHitDoor(tx+1, player_y) && has_key)
						next_level = 1;
									
					if(hasBlock(tx+1,player_y) != 1)
						tx ++;
					else{
						if(player_x != tx-1) beep_fx(1);
						break;
					}
				}
				player_x = tx-1;
			}
			else if (sp_KeyPressed(keys.up))
			{
				uchar ty = player_y;
				while(ty > 0){
					if(hasHitKey(player_x, ty-1)) 
						hideKey();
					
					if(hasHitDoor(player_x, ty-1) && has_key)
						next_level = 1;
						
					if(hasBlock(player_x, ty-1) != 1)
						ty --;
					else{
						if(player_y != ty) beep_fx(1);
						break;
					}
				}
				player_y = ty;
			}
			else if  (sp_KeyPressed(keys.down))
			{
				uchar ty = player_y;
				while(ty < 16){
					if(hasHitKey(player_x, ty+1)) 
						hideKey();
					
					if(hasHitDoor(player_x, ty+1) && has_key)
						next_level = 1;
					
					if(hasBlock(player_x, ty+1) != 1)
						ty ++;
					else{
						if(player_y != ty-1) beep_fx(1);
						break;
					}
				}
				player_y = ty-1;
			}
			

			if(next_level == 1){
				beep_fx(2);
				
				clearLevel();
				
				next_level = 0;
				has_key = 0;
				
				if(current_level == 0){
					load_level_1();
					current_level = 1;
				} else if(current_level == 1){
					load_level_2();
					current_level = 2;
				} else if(current_level == 2){
					load_level_3();
					current_level = 3;
				} else if(current_level == 3){
					load_level_4();
					current_level= 4;
				} else if(current_level == 4){
					load_level_5();
					current_level= 5;
				} else if(current_level == 5){
					current_level= 0;
					break;
				}
			}
		
			
			if(had_key == 0 && has_key == 1){
				beep_fx(6);
			}
			

			sp_MoveSprAbs(s_player, sp_ClipStruct, 0, level_off_y + player_y, level_off_x + player_x, 0, 0);
		
		}
	}
}
 