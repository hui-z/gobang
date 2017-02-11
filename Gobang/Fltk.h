/***************************************************************************

    file				: Fltk.h
    modified			: 2012-07-12 16:56:45
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#ifndef MY_FLTK
#define MY_FLTK

#include <Fl/Fl.H>
#include <Fl/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_message.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_File_Chooser.H>
#include "Data.h"
#include <string>
using std::string;

class MyWindow: public Fl_Double_Window {
public:
	MyWindow(int x, int y, int w, int h);
	int handle(int e);
};

class MyBoard: public Fl_Box {
public:
	MyBoard(int x, int y, int w, int h);
	int handle(int e);
};

class MyImage: public Fl_JPEG_Image {
public:
	MyImage(const char *filename);
};

class MyBox: public Fl_Box {
public:
	MyBox(int x, int y, int w, int h);
	void refresh();
};

class MyOutput: public Fl_Output {
public:
	MyOutput(int x, int y, int w, int h, const char *l);
};

class MyButton: public Fl_Button {
public:
	MyButton(int x, int y, int w, int h, const char *l);
	void refresh();
};

class MyText: public Fl_Text_Display {
public:
	MyText(int x, int y, const char *l);
	MyText(int x, int y, int w, int h, const char *l);
};

class MyFile: public Fl_File_Chooser {
public:
	MyFile(const char *d, const char *p, int t, const char *title);
};

void retract_cb(Fl_Widget* buttonptr);
void restart_cb(Fl_Widget* buttonptr);
void skin_cb(Fl_Widget* buttonptr);
void save_cb(Fl_Widget* buttonptr);
void load_cb(Fl_Widget* buttonptr);
void quit_cb(Fl_Widget* buttonptr);
void board_change();
void pre_step_cb(Fl_Widget* buttonptr);
void next_step_cb(Fl_Widget* buttonptr);
string int_to_str(int n);
void player_reset();

#endif