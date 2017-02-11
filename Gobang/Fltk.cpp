/***************************************************************************

    file				: Fltk.cpp
    modified			: 2012-07-12 16:56:53
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#include "AI.h"
#include "Fltk.h"
#include "Gobang.h"
#include <time.h>

extern int reply_step;
extern Gobang *game;
extern time_t s_time, e_time;
extern bool black_ai, white_ai, ai_work;

extern MyWindow *window;
extern MyBox *chesspiece[MAX_NUM][MAX_NUM];
extern MyBox *player[2];
extern MyOutput *tip_message;
extern MyButton *button[8];
extern MyOutput *reply_step_msg;
extern MyButton *player_ai[2];

extern MyImage Black_piece_jpg;
extern MyImage White_piece_jpg;
extern MyImage Black_last_jpg;
extern MyImage White_last_jpg;
extern MyImage Black_player_jpg;
extern MyImage White_player_jpg;
extern MyImage Flower_jpg;

MyWindow::MyWindow(int x, int y, int w, int h):Fl_Double_Window(x, y, w, h, " Gobang") {}

int MyWindow::handle(int e) {
	if(game->reply)	return Fl_Window::handle(e);		// ignore reply mode
	if(game->over)	return Fl_Window::handle(e);		// ignore game over
	// is AI turn
	if(!ai_work && ((game->player == Black && black_ai) || (game->player == White && white_ai))) {
		ai_work = true;
		if(game->add_step(ai())) { // add ai step successfully
			time(&s_time);
			player_reset();
			board_change();
			if(game->is_win())	{
				tip_message->value(game->player_msg().c_str());
				fl_message(game->player_msg().c_str());
			}
		}
		ai_work = false;
	}
	// is time out
	else {
		time(&e_time);
		// if blank time > 15s, show message
		if(difftime(e_time, s_time) > 15) {
			if(game->get_player() == Black)	{
				tip_message->value("  Black player hurry up! You think too long.");
				player[1]->image(Flower_jpg);
				player[1]->hide();player[1]->show();
			}
			else {
				tip_message->value("  White player hurry up! You think too long.");
				player[0]->image(Flower_jpg);
				player[0]->hide();player[0]->show();
			}
		}
		// if blank time > 30s, AI work
		if(difftime(e_time, s_time) > 30) {
			ai_work = true;
			if(game->add_step(ai())) { // add ai step successfully
				time(&s_time);
				player_reset();
				board_change();
				if(game->is_win())	{
					tip_message->value(game->player_msg().c_str());
					fl_message(game->player_msg().c_str());
				}
			}
			ai_work = false;
		}
	}
	return Fl_Window::handle(e);
}

MyBoard::MyBoard(int x, int y, int w, int h) : Fl_Box(FL_NO_BOX, x, y, w, h, "") {}

int MyBoard::handle(int e) {
	if(game->reply)	return Fl_Box::handle(e);		// ignore reply mode
	if(game->over)	return Fl_Box::handle(e);		// ignore game over
	Point p;
	if(e == FL_PUSH) {
		// get mouse position
		p.x = game->get_x_pos(Fl::event_x());
		p.y = game->get_y_pos(Fl::event_y());

		// add step fail
		if(game->player == Black && black_ai)	return Fl_Box::handle(e);
		if(game->player == White && white_ai)	return Fl_Box::handle(e);
		if(!game->add_step(p))					return Fl_Box::handle(e);

		// reset start time
		time(&s_time);
		player_reset();

		// Show changes in chessboard.
		board_change();

		// if game over
		if(game->is_win()) {
			tip_message->value(game->player_msg().c_str());
			fl_message(game->player_msg().c_str());
		}
		return 1;
	}
	else
		return Fl_Box::handle(e);
}

MyImage::MyImage(const char *filename) : Fl_JPEG_Image(filename) {}

MyBox::MyBox(int x, int y, int w, int h) : Fl_Box(FL_NO_BOX, x, y, w, h, "") {}

void MyBox::refresh() {
	show(); hide(); show();
}

MyOutput::MyOutput(int x, int y, int w, int h, const char *l) : Fl_Output(x, y, w, h, l) {}

MyButton::MyButton(int x, int y, int w, int h, const char *l) : Fl_Button(x, y, w, h, l) {}

void MyButton::refresh() {
	show(); hide(); show();
}

MyText::MyText(int x, int y, int w, int h, const char *l) : Fl_Text_Display(x, y, w, h, l) {}

MyText::MyText(int x, int y, const char *l) : Fl_Text_Display(x, y,0, 0, l) {}

MyFile::MyFile(const char *d, const char *p, int t, const char *title) : Fl_File_Chooser(d, p, t, title) {}

void retract_cb(Fl_Widget* buttonptr) {
	if(game->is_rep())	return ;	// ignore reply mode
	if(game->is_win()) return ;		// ignore game over
	time(&s_time);
	player_reset();
	int s = game->get_step();
	if(black_ai || white_ai)	// AI mode delete two steps
	{
		ai_work = true;
		if(s < 1)	{ai_work = false; return ;}
		Point p = game->get_step(s - 1);
		chesspiece[p.x][p.y]->hide();
		game->del_step();
		if(s > 1)
			board_change();
		else
			tip_message->value(game->player_msg().c_str());
	}
	s = game->get_step();
	if(s < 1)	{ai_work = false; return ;}
	Point p = game->get_step(s - 1);
	chesspiece[p.x][p.y]->hide();
	game->del_step();
	if(s > 1)
		board_change();
	else
		tip_message->value(game->player_msg().c_str());
	ai_work = false;
}

void restart_cb(Fl_Widget* buttonptr) {
	delete game;
	game = new Gobang();
	time(&s_time);
	player_reset();
	black_ai = false;
	white_ai = false;
	ai_work = false;
	player_ai[0]->box(FL_NO_BOX);
	player_ai[1]->box(FL_NO_BOX);
	for(int i=0; i<MAX_NUM; i++)
		for(int j=0; j<MAX_NUM; j++)
			chesspiece[i][j]->hide();
	button[6]->hide();
	button[7]->hide();
	reply_step_msg->hide();
	tip_message->value("  Game begin!");
}

void skin_cb(Fl_Widget* buttonptr) {
	int color = window->color();
	do{
		color ++;
		color %= 256;
	}while(color < 60);
	window->color(color);
	for(color=0; color<6; color++) {
		button[color]->color(window->color());
		button[color]->refresh();
	}
}

void save_cb(Fl_Widget* buttonptr) {
	MyFile file("", "*.dat", 2, "Save");
	file.show();
	while(file.shown()) Fl::wait();
	// cancel save
	if(file.value() == NULL) return ;
	// save data
	if(game->save(file.value()))
		fl_message(" Data saved successfully!");
	else
		fl_message(" Data save failed!");
}

void load_cb(Fl_Widget* buttonptr) {
	MyFile file("", "*.dat", 0, "Load");
	file.show();
	while(file.shown()) Fl::wait();
	// cancel load
	if(file.value() == NULL) return ;
	// load data
	if(game->load(file.value())) {	// Data loaded successfully!
		fl_message(" Data loaded successfully!");
		// turn on reply mode
		tip_message->value("  Reply mode.");
		// clean chessboard
		for(int i=0; i<MAX_NUM; i++)
			for(int j=0; j<MAX_NUM; j++)
				chesspiece[i][j]->hide();
		player_ai[0]->box(FL_NO_BOX);
		player_ai[0]->refresh();
		player_ai[1]->box(FL_NO_BOX);
		player_ai[1]->refresh();
		black_ai = false;
		white_ai = false;
		// show reply
		for(int i=0, j=game->get_step(), k=0; i<j; i++, k^=1) {
			Point p = game->get_step(i);
			if(k == 0)
				chesspiece[p.x][p.y]->image(Black_piece_jpg);
			else
				chesspiece[p.x][p.y]->image(White_piece_jpg);
			chesspiece[p.x][p.y]->refresh();
		}
		// display button
		button[6]->refresh();	// pre step
		button[7]->refresh();	// next step
		reply_step = game->get_step();
		reply_step_msg->value(int_to_str(reply_step).c_str());
		reply_step_msg->show();
	}
	else	// Data failed to load
		fl_message(" Data failed to load!");
}

void quit_cb(Fl_Widget* buttonptr) {
	window->hide();
}

void board_change() {
	// get player
	Player player = game->get_player();

	// get step
	int s = game->get_step();
	
	// get point
	Point p = game->get_step(s - 1);
	
	// show new step
	if(player == Black)
		chesspiece[p.x][p.y]->image(White_last_jpg);
	else
		chesspiece[p.x][p.y]->image(Black_last_jpg);
	chesspiece[p.x][p.y]->refresh();
	
	// change last step
	if(s > 1) {
		p = game->get_step(s - 2);
		if(player == Black)
			chesspiece[p.x][p.y]->image(Black_piece_jpg);
		else
			chesspiece[p.x][p.y]->image(White_piece_jpg);
		chesspiece[p.x][p.y]->refresh();
	}
	
	// change tip message
	tip_message->value(game->player_msg().c_str());
}

void pre_step_cb(Fl_Widget* buttonptr) {
	if(reply_step > 0) {
		Point p = game->get_step(--reply_step);
		chesspiece[p.x][p.y]->hide();
		reply_step_msg->value(int_to_str(reply_step).c_str());
	}
}

void next_step_cb(Fl_Widget* buttonptr) {
	if(reply_step < game->get_step()) {
		Point p = game->get_step(reply_step++);
		chesspiece[p.x][p.y]->refresh();
		reply_step_msg->value(int_to_str(reply_step).c_str());
	}
}

string int_to_str(int n) {
	char t_ch[4] = {0};
	sprintf(t_ch, "%d", n);
	string re = "";
	re = t_ch;
	return re;
}

void player_reset()
{
	player[0]->image(Black_player_jpg);
	player[0]->hide();player[0]->show();
	player[1]->image(White_player_jpg);
	player[1]->hide();player[1]->show();
}