/***************************************************************************

    file				: AI.h
    modified			: 2012-07-11 12:38:13
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/
#ifndef MY_AI
#define MY_AI

#include "Data.h"
#include "Fltk.h"
#include "Gobang.h"

// black ai button callback
void black_ai_cb(Fl_Widget* buttonptr);

// white ai button callback
void white_ai_cb(Fl_Widget* buttonptr);

// AI function. return a position.
Point ai();

int xChange(int);
int yChange(int);

#endif
