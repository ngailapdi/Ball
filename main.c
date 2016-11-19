// Name: NGOC ANH THAI

#include "NA1.h"
#include "NA4.h"
#include "myLib.h"
#include "NA2.h"
#include "NA3.h"
#include "NA5.h"
#include <stdio.h>
#include <stdlib.h>
#define CAPAC 18

DIAMOND diamond[CAPAC];
LOG wlog;
BALL ball;

// State enum definition
enum GBAState {
	START,
	START_NODRAW,
	STATE1,
	STATE2,
	GAMEOVER,
};

int main() {

	REG_DISPCTL = MODE_3 | BG2_EN;

	char buffer2[1];
	char buffer3[1];
	int score = 0;
	int mode = 0;
	int rd = 1;
	int cd = 1;
	int waitSTART = 0;
	int waitSELECT = 0;
	int change = 0;
	int times = 0;
	int lives = 5;

	int delay = 0;
	int capac = 15;
	int numErase = 0;
	int oldrow = ball.row;
	int oldcol = ball.col;

	int cDiamond = 1;
	ball.row = 80;
	ball.col = 120;
	ball.height = 5;
	ball.width = 5;
	ball.color = RED;
	wlog.color = WHITE;
	wlog.row = 130;
	wlog.col = 95;
	wlog.height = 10;
	wlog.width = 50;

	for (int i = 0; i < capac; i++) {
		if (i < 10) {
			diamond[i].row = 10;
			diamond[i].col = 5 + i*20;
		} else if (i < 15) {
			diamond[i].row = 30;
			diamond[i].col = -155 + i*20;
		}
		diamond[i].isActive = 1;
	}

	while(1) {
		waitForVBlank();




		// Gameboy screen

		if (mode == 0) {
			score = 0;
			lives = 5;
			numErase = 0;
			if (change < 30) {
				drawScreen(0, NA2_data);
				drawString(100, 100, "(ENTER)", BLACK);
				change++;
			} else {
				drawString(85, 87, "PRESS START", ORANGE);
				change++;
				if (change >= 60) {
					change = 0;
				}
			}

			for (int i = 0; i < capac; i++) {
				if (i < 10) {
					diamond[i].row = 10;
					diamond[i].col = 5 + i*20;
				} else if (i < 15) {
					diamond[i].row = 30;
					diamond[i].col = -155 + i*20;
				}
				diamond[i].isActive = 1;
			}
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				fillScreen(BLACK);
				mode = 6;
				waitSTART = 1;
				drawScreen(0, NA1_data);
			}
		}



		// Playing screen
		if (mode == 1) {


			drawString(150, 40, buffer2, BLACK);
			sprintf(buffer2, "%d", score);
			drawString(150, 2, "SCORE:", BLUE);
			drawString(150, 40, buffer2, ORANGE);

			drawString(150, 100, buffer3, BLACK);
			sprintf(buffer3, "%d", times);
			drawString(150, 70, "TIME:", BLUE);
			drawString(150, 100, buffer3, ORANGE);

			drawString(150, 148, "LIVES: ", BLUE);
			for (int i = 1; i <= lives; i++) {
				drawImage(148, 175 + i*10, 10, 10, NA5_data);
			}
			
			int random = rand() % 30 + 40;
			int rand2 = rand() % 2;
			//Draw ball
			if(ball.row < 0)
			{
				ball.row = 0;
				rd =-rd;
			}
			if (ball.row > 129) {
				for (int i = 1; i <= lives; i++) {
					drawImage(148, 180 + i*10, 10, 10, BLACK);
				}
				lives--;
				if (lives == 0) mode = 3;
				for (int i = 1; i <= lives; i++) {
					drawImage(148, 175 + i*10, 10, 10, NA5_data);
				}
				ball.row = random;
				if (rand2 == 0) cd = 1;
				else cd = -1;
			}
			
			if(hitLog(wlog,ball))
			{
				ball.row = ball.row;
				rd = -rd;
			}
			if(ball.col < 0)
			{
				ball.col = 0;
				cd =-cd;
			}
			if(ball.col >= 239-ball.width)
			{
				ball.col = 239-ball.width;
				cd = -cd;
			}
			drawRect(oldrow, oldcol, ball.width, ball.width, BLACK);
			drawRect(ball.row, ball.col, ball.height, ball.width, ball.color);
			oldrow = ball.row;
			oldcol = ball.col;

			//Draw log
			drawRect(wlog.row,wlog.col,wlog.height,wlog.width,wlog.color);

			if(KEY_DOWN_NOW(BUTTON_LEFT))
			{
				drawRect(wlog.row, wlog.col,wlog.height,wlog.width,BLACK);
				wlog.col = wlog.col - 1;
				if(wlog.col < 0) wlog.col = 0;
				drawRect(wlog.row,wlog.col,wlog.height,wlog.width,wlog.color);
			}

			if(KEY_DOWN_NOW(BUTTON_RIGHT))
			{
				drawRect(wlog.row, wlog.col,wlog.height,wlog.width,BLACK);	
				wlog.col = wlog.col + 1;
				if(wlog.col > 190) wlog.col = 190;
				drawRect(wlog.row,wlog.col,wlog.height,wlog.width,wlog.color);
			}
		
	
			ball.row += rd;
			ball.col += cd;



			//Draw diamond
			int startcol = diamond[0].col;
			if (startcol < 0 || startcol > 40) {
				cDiamond = -cDiamond;
			}
			for (int i = 0; i < capac; i++) {
				if (diamond[i].isActive == 1) {
					drawDiamond(diamond[i].row, diamond[i].col, 15, 15, YELLOW);
				}
				if (delay % 3 == 0) {
					drawRect(diamond[i].row, diamond[i].col, 16, 17, BLACK);
					drawRect(oldrow, oldcol, ball.width, ball.width, BLACK);
					drawRect(ball.row, ball.col, ball.height, ball.width, ball.color);
					oldrow = ball.row;
					oldcol = ball.col;
					diamond[i].col += cDiamond;
					if (diamond[i].isActive == 1) {
						drawDiamond(diamond[i].row, diamond[i].col, 15, 15, YELLOW);
					}
				}
			}
			delay++;
			for (int i = 0; i < capac; i++) {
				if (diamond[i].isActive == 1) {
					if (hitDiamond(ball, diamond[i])) {

						score+=10;
						if (score == capac * 10) mode = 4;
						diamond[i].isActive = 0;
						cd = -cd;
					}
				}
			}
			if (delay % 30 == 0) {
				times++;
			}



			

			// Reset key
			if (KEY_DOWN_NOW(BUTTON_SELECT) && waitSELECT == 0) {
				mode = 0;
				waitSELECT = 1;
				score = 0;
				lives = 5;
			}

			// Pause key
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				mode = 5;
				waitSTART = 1;
			}

		}



		if (mode == 2) {
			fillScreen(BLACK);
			mode = 1;
		}





		// Game over

		if (mode == 3) {
			if (change < 30) {
				drawScreen(0, NA3_data);
				change++;
			} else {
				drawString(100, 87, "PRESS START", RED);
				change++;
				if (change >= 60) {
					change = 0;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				mode = 0;
				waitSTART = 1;
			}
		}





		// Win screen

		if (mode == 4) {
			if (change < 30) {
				drawScreen(0, NA4_data);
				change++;
			} else {
				drawString(85, 87, "PRESS START", BLUE);
				change++;
				if (change >= 60) {
					change = 0;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				mode = 0;
				waitSTART = 1;
			}
		}





		// Pause screen
		if (mode == 5) {
			drawString(70, 100, "PAUSE", GREY);
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				drawString(70, 100, "PAUSE", BLACK);
				mode = 1;
				waitSTART = 1;
			}
		}




		// Start screen
		if (mode == 6) {
			if (change < 30) {
				drawScreen(0, NA1_data);
				drawString(105, 90, "(to start)", WHITE);
				change++;
			} else {
				drawString(85, 87, "PRESS START", YELLOW);
				change++;
				if (change >= 60) {
					change = 0;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				mode = 2;
				waitSTART = 1;
			}
		}



		if (!KEY_DOWN_NOW(BUTTON_SELECT) && waitSELECT == 1) {
			waitSELECT = 0;
		}

		if (!KEY_DOWN_NOW(BUTTON_START) && waitSTART == 1) {
			waitSTART = 0;
		}



	}

	return 0;
}
