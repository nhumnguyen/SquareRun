// Make a simple GBA state machine
// Name: Quynh-Nhu Nguyen

#include "startscreen.h"
#include "winscreen.h"
#include "myLib.h"
#include "gameboy.h"
#include "gameover.h"
#include "lives.h"
#include <stdio.h>
#include <stdlib.h>
#include "inky.h"
#include "me.h"
#include "ball.h"
#include "wall.h"




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

	char buffer1[1];
	char buffer2[1];
	// char buffer3[1];
	

//-----------------------------------------------


	int waitSTART = 0;
	// int waitSELECTE = 0;

	int enemySIZE = 17;


//-----------------------------------------------

	int mode = 0;
	int change = 0; //change is the times we loop throuugh the while //30 changes is about 1 sec
	
	// int times = 0;
	int lives = 10;
	int bananCount = 0;


	//Drawing my square
	ME me;
	me.col = 5;
	me.row = 5;
	me.width = 9;
	me.height = 9;
	me.dead = 1;


	//initialize banana's position
	WALL banana;
	banana.row = 50;
	banana.col = 50;
	banana.height = 10;
	banana.width = 10;

	//initialize 17 balls
	BALL enemyRectOld[enemySIZE];
	BALL enemyRectCurr[enemySIZE];
	

	

	while(1) {
		waitForVBlank();

		//
		//
		// Start screen
		//
		//
		if (mode == 0) {
			lives = 10;
			bananCount = 0;
		
			if (change < 30) {
				//drawScreen(0, gameboy_data);
				
				fillScreen(GREY);
				drawString(60, 70, "WORLD HARDEST GAME!", BLACK);
				drawString(100, 100, "<ENTER>", RED);
			
				change++;
		

			} else { //this else if is just for the blinking
				drawString(80, 60, "PRESS ENTER TO START", ORANGE);
				drawObject(80, 190, 9, 9, me_data);

				change++;
				if (change >= 60) {
					change = 0;
				}
			}


			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				fillScreen(BLACK);
				mode = 10;
				waitSTART = 1;
				drawScreen(0, startscreen_data);
			}
		}




		if (mode == 10) { // set up enemies

			waitForVBlank();
			fillScreen(BLACK);

			drawRect(140, 0, 20, 240, BLUE); //Border line at bottom
			

			//initiallize enemies 
			for (int i = 0; i <= enemySIZE; i++) {
				enemyRectCurr[i].row = 5;
				enemyRectCurr[i].col = 5;
			} 

			for (int i = 0; i < enemySIZE; i++) {
				enemyRectCurr[i].width = 10;
				enemyRectCurr[i].height = 10;
			} 
		
			for (int i = 0; i <= 3; i++) {
				enemyRectCurr[i].col += 20 + (50 * i);
				enemyRectCurr[i + 4].col += 20 + (50 * i);
				enemyRectCurr[i + 8].col += 20 + (50 * i);
				enemyRectCurr[i].direction = -3; //moving down
			}

			for (int i = 4; i <= 7; i++) {
				enemyRectCurr[i].row += 55;
				enemyRectCurr[i + 4].row += 110;
				enemyRectCurr[i].direction = 2; //moving right
			}

		
			for (int i = 12; i <= 14; i++) {
				enemyRectCurr[i].row = 30;
				enemyRectCurr[i].col = (45 * (i - 11)) + 5;
				enemyRectCurr[i].direction = 2; //moving left
			}
			

			for (int i = 15; i <= 17; i++) {
				enemyRectCurr[i].row = 85;
				enemyRectCurr[i].col = (45 * (i - 14)) + 15;
				enemyRectCurr[i].direction = -3; //moving up
			}

			//set up initial position of red square
			me.col = 5;
			me.row = 5;
			me.width = 9;
			me.height = 9;
			me.dead = 0;

			mode = 2; //go to draw banana
			
		}



		//
		//
		// Playing screen
		//
		//
		if (mode == 1) { //level 1

			//sdrawObject(me.row, me.col, me.width, me.height, me_data);
			
			if (me.dead == 1) { //get back to initial position
				me.col = 5;
				me.row = 5;
				me.width = 9;
				me.height = 9;
				me.dead = 0;
			}


			
				// Draw enemy
				for (int i = 0; i <= enemySIZE; i++) { //SAVING OLd position to erase later
					enemyRectOld[i].col = enemyRectCurr[i].col;
					enemyRectOld[i].row = enemyRectCurr[i].row;
				}


				for (int i = 0; i < 5; i++) {
					if (enemyRectCurr[i].col + enemyRectCurr[i].direction >= 230 
						|| enemyRectCurr[i].col + enemyRectCurr[i].direction <= 20) {
						enemyRectCurr[i].direction = -1 * enemyRectCurr[i].direction; //change direction
					}

					enemyRectCurr[i].col += enemyRectCurr[i].direction;
				}


				for (int i = 5; i < 10; i++) {

					if (enemyRectCurr[i].row + enemyRectCurr[i].direction >= 130 
							|| enemyRectCurr[i].row + enemyRectCurr[i].direction <= 1) {
						enemyRectCurr[i].direction = -1 * enemyRectCurr[i].direction; //change direction
					}

					enemyRectCurr[i].row += enemyRectCurr[i].direction;
				}

				for (int i = 10; i < 14; i++) {
					if (enemyRectCurr[i].col + enemyRectCurr[i].direction >= 230 
							|| enemyRectCurr[i].col + enemyRectCurr[i].direction <= 20) {
						enemyRectCurr[i].direction = -1 * enemyRectCurr[i].direction; //change direction
					}

					enemyRectCurr[i].col += enemyRectCurr[i].direction;
				}

				for (int i = 14; i <= 17; i++) {
					if (enemyRectCurr[i].row + enemyRectCurr[i].direction >= 130 
							|| enemyRectCurr[i].row + enemyRectCurr[i].direction <= 1) {
						enemyRectCurr[i].direction = -1 * enemyRectCurr[i].direction; //change direction
					}
					enemyRectCurr[i].row += enemyRectCurr[i].direction;
				}
			


			// Draw the controllable rectangle (moving 4 directions)
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				drawRect(me.row, me.col,  me.width, me.height, BLACK);
				me.col -= 3;
				if (me.col <= 0) {
					me.col = 0;
				}
			}


			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				drawRect(me.row, me.col, me.width, me.height, BLACK);
				me.col += 3;
				if (me.col >= 220) {
					me.col = 220;
				}
			}


			if (KEY_DOWN_NOW(BUTTON_UP)) {
				drawRect(me.row, me.col, me.width, me.height, BLACK);
				me.row -= 3;
				if (me.row <= 0) {
					me.row = 0;
				}
			}


			if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				drawRect(me.row, me.col, me.width, me.height, BLACK);
				me.row += 3;
				if (me.row >= 130) {
					me.row = 130;
				}
			}
			drawObject(me.row, me.col, me.width, me.height, me_data);

			if (bananCount >= 5) {
				mode = 4; //go to winner page

			} else if (lives < 0) {
				mode = 3; //go to lost page
			}

			
			waitForVBlank();
			drawObject(banana.row, banana.col, 10, 10, wall_data); 


			for (int i = 0; i <= enemySIZE; i++) { //all enemies moving 
				drawObject(enemyRectOld[i].row, enemyRectOld[i].col, 10, 10, BLACK);
				drawObject(enemyRectCurr[i].row, enemyRectCurr[i].col, 10, 10, ball_data);
			}
			
		 

		


		//draw information at bottom
		drawString(150, 40, buffer1, BLUE);  
		sprintf(buffer1, "%d", lives);
		drawString(150, 2, "Lives-", GREEN);
		drawString(150, 40, buffer1, RED);//

		drawString(150, 123, buffer2, BLUE); //rewrite the buffer again in BLLUE is like erasing it
		sprintf(buffer2, "%d", bananCount);
		drawString(150, 72, "Banana#-", GREEN);
		drawString(150, 123, buffer2, RED);

 

			for (int i = 0; i <= enemySIZE; i++) {
					// collision 
					if (collision(me, enemyRectCurr[i]) == 1) {
						drawRect(me.row, me.col,  me.width, me.height, BLACK);
						lives--;
						me.dead = 1;
					}
			}



			if (eatFruit(me, banana) == 1) { //eat banana
					drawRect(banana.row, banana.col, 10, 10, BLACK);
					bananCount++;
					mode = 2;
			}
			

			// Reset key
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				mode = 0;
				// waitSELECTE = 1;
				lives = 5;
				
			}


			// Pause key
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				mode = 5;
				waitSTART = 0;
			}
		}

		




		//
		//
		// BANANA position
		//
		//
		if (mode == 2) { 
			
			banana.col = rand() % 230 + 20 ; //column from 20 - 230
			banana.row = rand() % 130 + 2 ; //row from 2s - 130
		

			waitForVBlank();
			drawObject(banana.row , banana.col, 10, 10, wall_data);
			
		
			mode = 1;

			
		}




		//
		//
		// Lost screen
		//
		//
		if (mode == 3) {
			if (change < 30) {
				drawScreen(0, gameover_data);
				change++;
			} else {
				drawString(100, 87, "PRESS START", ORANGE);
				change++;
				if (change >= 60) {
					change = 0;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_START)) {
				mode = 0;
				// waitSTART = 1;
			}
		}




		//
		//
		// Win screen
		//
		//
		if (mode == 4) {
			if (change < 30) {
				drawScreen(0, winscreen_data);
				change++;
			} else {
				drawString(85, 87, "PRESS START", GREY);
				change++;
				if (change >= 60) {
					change = 0;
				}
			}
			if (KEY_DOWN_NOW(BUTTON_START) ) {
				mode = 0;
				// waitSTART = 1;
			}
		}




		//
		//
		// Pause screen
		//
		//
		if (mode == 5) {
			drawString(70, 100, "PAUSE", GREY);
			if (KEY_DOWN_NOW(BUTTON_START) && waitSTART == 0) {
				drawString(70, 100, "PAUSE", BLACK);
				mode = 1;
				waitSTART = 1;
			}
		}



		// if (!KEY_DOWN_NOW(BUTTON_SELECT) && waitSELECTE == 1) {
		// 	waitSELECTE = 0;
		// }

		if (!KEY_DOWN_NOW(BUTTON_START) && waitSTART == 1) { //reset waitSTART???		
			waitSTART = 0;
		}
	}



	return 0;
}
