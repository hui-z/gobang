/***************************************************************************

    file				: Gobang.h
    modified			: 2012-07-13 20:43:34
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#ifndef GOBANG
#define GOBANG

#include "Data.h"
#include "Fltk.h"
#include <string>
using namespace std;

class Gobang
{
private:
	Point pos[400];					// the position of chess
	int step;						// The current number of steps
	char map[MAX_NUM][MAX_NUM];		// chessboard
	Player player;					// current player.
	bool over;						// is game over
	bool reply;						// is reply mode
public:
	// 添加友元
	friend class MyWindow;
	friend class MyBoard;
	friend Point ai();
	// 构造函数
	Gobang();
	// 功能函数
	bool add_step(Point point);		// 添加棋子
	void del_step();				// 删除棋子
	int get_step();					// 获得当前总步数
	Point get_step(int s);			// 获得指定步数棋子的位置
	Player get_player();			// 获得当前玩家
	int get_x_pos(int p);			// 将像素横坐标转换成棋盘位置
	int get_y_pos(int p);			// 将像素纵坐标转换成棋盘位置
	bool is_win();					// 检查游戏是否结束
	bool is_rep();					// 检查是否是录像模式
	string player_msg();			// 返回提示信息
	bool save(string f);			// 保存游戏信息
	bool load(string f);			// 载入游戏信息
};

#endif