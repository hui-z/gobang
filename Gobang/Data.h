/***************************************************************************

    file				: Data.h
    modified			: 2012-07-11 15:12:42
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#ifndef MY_DATA
#define MY_DATA

#define CHESSBOARD_W 697
#define CHESSBOARD_H 692
#define BOX_BIAS 15
#define CELL_LENGTH 35
#define MAX_NUM 19
#define AUTHOR "ZHOU Cheng \n e-mail: c.zhou AT live.com \n School of Software, \n Shanghai Jiao Tong University"
#define VALID(n) (0 <= (n) && (n) < MAX_NUM)

struct Point {
    int x, y;
    Point(int xx, int yy) : x(xx), y(yy) { }
    Point() :x(0), y(0) { }
};

bool operator==(Point &p1, Point &p2);
bool operator!=(Point &p1, Point &p2);

enum Player{Black,White};

#endif