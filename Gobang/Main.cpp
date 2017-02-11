/***************************************************************************

    file				: Mian.cpp
    modified			: 2012-07-13 20:50:56
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#include "AI.h"
#include "Data.h"
#include "Fltk.h"
#include "Gobang.h"
#include <time.h>

// Globel definition
int reply_step;
Gobang *game;
time_t s_time, e_time;
bool black_ai, white_ai, ai_work;

MyWindow *window;
MyBoard *chessboard;
MyOutput *tip_message;
MyBox *chesspiece[MAX_NUM][MAX_NUM];
MyBox *player[2];
MyButton *player_ai[2];
MyBox *logo;
MyText *author;
MyButton *button[8];
MyOutput *reply_step_msg;

MyImage chess_board_jpg("1_Chessboard.jpg");
MyImage Black_piece_jpg("2_Black_piece.jpg");
MyImage White_piece_jpg("3_White_piece.jpg");
MyImage Black_last_jpg("4_Black_last.jpg");
MyImage White_last_jpg("5_White_last.jpg");
MyImage Black_player_jpg("6_Black_player.jpg");
MyImage White_player_jpg("7_White_player.jpg");
MyImage Logo_jpg("8_Logo.jpg");
MyImage Flower_jpg("9_Flower.jpg");

int main() {
	game = new Gobang();
	time(&s_time);
	black_ai = false;
	white_ai = false;
	ai_work = false;

	// creat a window
	window = new MyWindow(100, 40, CHESSBOARD_W + 400, CHESSBOARD_H);
	window->color(FL_WHITE);
	window->begin();

	// add chessboard to window
	chessboard = new MyBoard(0, BOX_BIAS, CHESSBOARD_W, CHESSBOARD_H - BOX_BIAS);
	chessboard->image(chess_board_jpg);
	
	// add chesspiece to window
	for(int i=0; i<MAX_NUM; i++)
		for(int j=0; j<MAX_NUM; j++)
			chesspiece[i][j] = new MyBox(18+i*CELL_LENGTH, 30+j*CELL_LENGTH, 34, 34-BOX_BIAS);

	// add tip message to window
	tip_message = new MyOutput(CHESSBOARD_W, 230, 400, 35, "");
		//tip_message->box(FL_NO_BOX); // this line may cause a display bug and I don't konw the reason.
	tip_message->textsize(19);
	tip_message->value("  Game begin!");

	// add player to window
		// 0) black player
	player[0] = new MyBox(CHESSBOARD_W + 50, BOX_BIAS, 200, 200-BOX_BIAS);
	player[0]->image(Black_player_jpg);
	player_ai[0] = new MyButton(CHESSBOARD_W + 100, 200, 110, 30, "Black Player");
	player_ai[0]->labelsize(20);
	player_ai[0]->labelfont(FL_TIMES);
	player_ai[0]->box(FL_NO_BOX);
	player_ai[0]->callback(black_ai_cb);
		// 1) white player
	player[1] = new MyBox(CHESSBOARD_W + 150, 270 + BOX_BIAS, 200, 200-BOX_BIAS);
	player[1]->image(White_player_jpg);
	player_ai[1] = new MyButton(CHESSBOARD_W + 200, 470, 110, 30, "White Player");
	player_ai[1]->labelsize(20);
	player_ai[1]->labelfont(FL_TIMES);
	player_ai[1]->box(FL_NO_BOX);
	player_ai[1]->callback(white_ai_cb);
	
	// add logo & author to window
	logo = new MyBox(CHESSBOARD_W, CHESSBOARD_H - 97 + BOX_BIAS, 97, 97-BOX_BIAS);
	logo->image(Logo_jpg);
	author = new MyText(CHESSBOARD_W + 240, CHESSBOARD_H - 5, AUTHOR);
	author->labelsize(17);
	author->labelfont(FL_COURIER);

	// add button to window
		// 0) retract
	button[0] = new MyButton(CHESSBOARD_W + 25, 510, 110, 40, "Retract");
	button[0]->labelsize(20);
	button[0]->labelfont(FL_COURIER);
	button[0]->color(window->color());
	button[0]->callback(retract_cb);
		// 1) restart
	button[1] = new MyButton(CHESSBOARD_W + 145, 510, 110, 40, "Restart");
	button[1]->labelsize(20);
	button[1]->labelfont(FL_COURIER);
	button[1]->color(window->color());
	button[1]->callback(restart_cb);
		// 2) change skin
	button[2] = new MyButton(CHESSBOARD_W + 265, 510, 110, 40, "Skin");
	button[2]->labelsize(20);
	button[2]->labelfont(FL_COURIER);
	button[2]->color(window->color());
	button[2]->callback(skin_cb);
		// 3) save
	button[3] = new MyButton(CHESSBOARD_W + 25, 555, 110, 40, "Save");
	button[3]->labelsize(20);
	button[3]->labelfont(FL_COURIER);
	button[3]->color(window->color());
	button[3]->callback(save_cb);
		// 4) load
	button[4] = new MyButton(CHESSBOARD_W + 145, 555, 110, 40, "Load");
	button[4]->labelsize(20);
	button[4]->labelfont(FL_COURIER);
	button[4]->color(window->color());
	button[4]->callback(load_cb);
		// 5) quit
	button[5] = new MyButton(CHESSBOARD_W + 265, 555, 110, 40, "Quit");
	button[5]->labelsize(20);
	button[5]->labelfont(FL_COURIER);
	button[5]->color(window->color());
	button[5]->callback(quit_cb);
		// 6) load -> Pre step
	button[6] = new MyButton(CHESSBOARD_W + 25, 280, 110, 40, "Pre step");
	button[6]->labelsize(20);
	button[6]->callback(pre_step_cb);
	button[6]->hide();
		// 7) load -> Next step
	button[7] = new MyButton(CHESSBOARD_W + 25, 340, 110, 40, "Next step");
	button[7]->labelsize(20);
	button[7]->callback(next_step_cb);
	button[7]->hide();

	// reply step message
	reply_step_msg = new MyOutput(CHESSBOARD_W + 85, 400, 80, 40, "Step : ");
	reply_step_msg->labelsize(20);
	reply_step_msg->box(FL_NO_BOX);
	reply_step_msg->textsize(20);
	reply_step_msg->hide();

	window->end();
	window->show();
	return Fl::run();
}
