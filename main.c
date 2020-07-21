#include <gb/gb.h>
#include <gb/cgb.h>

#include "tiles/all_s.h"

#define ROTPAL		0
#define BLAUPAL		1
#define GRUENPAL	2

UWORD spritePalette[] = {
	0,RGB(31,0,0),RGB(22,0,0),RGB(15,0,0),
	0,RGB(0,31,0),RGB(0,22,0),RGB(0,15,0),
	0,RGB(0,0,31),RGB(0,0,22),RGB(0,0,15),
};

void main() {
	//position vars
	UINT8 x = 75;
	UINT8 y = 75;
	UINT8 xdir = 1;

	//palette selector
	UINT8 palSelector = ROTPAL;

	//sprite frame selector
	UINT8 spriteFrameSelector = 8;
	UINT8 frameCounter = 0;

	//use 8x16 sprites
	SPRITES_8x16;

	//load sprite data
	set_sprite_data(0,48,all_s);

	//load palettes
	set_sprite_palette(0,3,spritePalette);

	//main game loop
	while (1) {
		palSelector = ROTPAL;
		//joypad state check
		switch (joypad()) {
			case J_UP:
				palSelector = BLAUPAL;
				break;

			case J_DOWN:
				palSelector = GRUENPAL;
				break;

			case J_LEFT:
				x -= xdir;
				break;

			case J_RIGHT:
				x += xdir;
				break;
		}
		
		//set sprite tile
		set_sprite_tile(0,spriteFrameSelector);
		set_sprite_tile(1,spriteFrameSelector+2);

		//put sprite on screen
		move_sprite(0,x,y);
		move_sprite(1,x+8,y);

		//set sprite palette for CGB
		set_sprite_prop(0,palSelector);
		set_sprite_prop(1,palSelector);

		//display sprites
		SHOW_SPRITES;

		//wait for vblank
		wait_vbl_done();

		//increment sprite frame selector
		if (frameCounter % 8 == 0)
			spriteFrameSelector+=(spriteFrameSelector <= 32 ? 4 : -spriteFrameSelector);
		frameCounter++;
	}

}
