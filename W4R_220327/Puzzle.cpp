//#include<stdio.h>
#include<bangtal.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<string>
using namespace std;



SceneID scene1;
ObjectID game_board[16],init_board[16], blank, start, restart, restart2;
TimerID timer;;
int mixCount = -1;

time_t time_st, time_ed;
int time_d;
string time_s;
const char* time_f;


const char* board_image[16]{
	"images/1.png",
	"images/2.png",
	"images/3.png",
	"images/4.png",
	"images/5.png",
	"images/6.png",
	"images/7.png",
	"images/8.png",
	"images/9.png",
	"images/10.png",
	"images/11.png",
	"images/12.png",
	"images/13.png",
	"images/14.png",
	"images/15.png",
	"images/16.png",

};
const int board_X[16] = { 0,150,300,450,0,150,300,450,0,150,300,450,0,150,300,450 };
const int board_Y[16] = { 450,450,450,450,300,300,300,300,150,150,150,150,0,0,0,0 };

int board_index(ObjectID object) {
	for (int i = 0; i < 16; i++) {
		if (game_board[i] == object) return i;
	}
	return -1;
}

void board_move(int index) {
	ObjectID t = game_board[blank];
	game_board[blank] = game_board[index];
	game_board[index] = t;

	locateObject(game_board[blank], scene1, board_X[blank], board_Y[blank]);
	locateObject(game_board[index], scene1, board_X[index], board_Y[index]);

	blank = index ;
}

bool movable(int index)
{

	if (blank < 0 or blank >15) return false;
	if (blank % 4 != 0 and blank - 1 == index) return true;
	if	(blank % 4 != 3 and blank + 1 == index) return true;
	if (blank / 4 != 0 and blank - 4 == index) return true;
	if	(blank / 4 != 3 and blank + 4 == index) return true;


	return false;
}

void board_mix() {
		int index ;
			do {
			switch (rand() % 4) {
			case 0:	index = blank - 1;break;
			case 1:	index = blank + 1;break;
			case 2:	index = blank - 4;break;
			case 3:	index = blank + 4;break;
			}		
			} while (!movable(index));
			board_move(index);

	}

bool completed() {
	for (int i = 0; i < 16; i++) {
		if (game_board[i]!=init_board[i]) return false;
}
return true;
}

void timerCallback(TimerID timer)
{

	if (mixCount > 0) {
		mixCount--;

		board_mix();

		setTimer(timer, 0.05f);
		startTimer(timer);
	}
	else if(mixCount == 0) {
		time_st = time(NULL);
		showObject(restart);
	}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == start) {
		mixCount = 200;
		setTimer(timer, 0.05f);
		startTimer(timer);
		hideObject(start);
		blank = 15;
		hideObject(game_board[15]);
	}
	else if(object == restart) {
		mixCount = 200;
		setTimer(timer, 0.05f);
		startTimer(timer);
	}
	else if (object == restart2) {
		mixCount = 200;
		setTimer(timer, 0.05f);
		startTimer(timer);
		hideObject(restart2);
		blank = 15;
		hideObject(game_board[15]);
	}
	else {
		int index = board_index(object);
		if (movable(index)) {
			board_move(index);

			if(completed()) {
				time_ed = time(NULL);
				int time_d = (time_ed - time_st);
				time_s = std::to_string(time_d);
				time_f = time_s.c_str();
				showMessage(time_f);
				hideObject(restart);
				showObject(game_board[blank]);
				showObject(restart2);

			}
		}
	}
}

int main() {
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	scene1 = createScene("ÆÛÁñ¸ÂÃß±â", "images/600x600.png");
	



	for (int i = 0; i < 16; i++) {
		game_board[i] = createObject(board_image[i]);
		init_board[i] = game_board[i];

		locateObject(game_board[i], scene1, board_X[i], board_Y[i]);
		showObject(game_board[i]);
	}
//	blank = 15;
//	hideObject(game_board[15]);

	start = createObject("images/start.png");
	locateObject(start, scene1, 300, 300);
	showObject(start);

	restart = createObject("images/restart.png");
	locateObject(restart, scene1, 500, 600);
	hideObject(restart);

	restart2 = createObject("images/restart.png");
	locateObject(restart2, scene1, 300, 300);
	hideObject(restart2);

	timer = createTimer(1.f);
	startTimer(timer);

	/*
	ObjectID board1 = createObject("images/1.png");
	locateObject(board1, scene1, 0, 450);
	showObject(board1);

	ObjectID board2 = createObject("images/2.png");
	locateObject(board2, scene1, 150, 450);
	showObject(board2);

	ObjectID board3 = createObject("images/3.png");
	locateObject(board3, scene1, 300, 450);
	showObject(board3);

	ObjectID board4 = createObject("images/4.png");
	locateObject(board4, scene1, 450, 450);
	showObject(board4);

	ObjectID board5 = createObject("images/5.png");
	locateObject(board5, scene1, 0, 300);
	showObject(board5);

	ObjectID board6 = createObject("images/6.png");
	locateObject(board6, scene1, 150, 300);
	showObject(board6);

	ObjectID board7 = createObject("images/7.png");
	locateObject(board7, scene1, 300, 300);
	showObject(board7);

	ObjectID board8 = createObject("images/8.png");
	locateObject(board8, scene1, 450, 300);
	showObject(board8);

	ObjectID board9 = createObject("images/9.png");
	locateObject(board9, scene1, 0, 150);
	showObject(board9);

	ObjectID board10 = createObject("images/10.png");
	locateObject(board10, scene1, 150, 150);
	showObject(board10);

	ObjectID board11 = createObject("images/11.png");
	locateObject(board11, scene1, 300, 150);
	showObject(board11);

	ObjectID board12 = createObject("images/12.png");
	locateObject(board12, scene1, 450, 150);
	showObject(board12);

	ObjectID board13 = createObject("images/13.png");
	locateObject(board13, scene1, 0, 0);
	showObject(board13);

	ObjectID board14 = createObject("images/14.png");
	locateObject(board14, scene1, 150, 0);
	showObject(board14);

	ObjectID board15 = createObject("images/15.png");
	locateObject(board15, scene1, 300, 0);
	showObject(board15);

	ObjectID board16 = createObject("images/16.png");
	locateObject(board16, scene1, 450, 0);
	//showObject(board16);

	*/
	startGame(scene1);
}