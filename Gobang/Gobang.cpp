/***************************************************************************

    file				: Gobang.cpp
    modified			: 2012-07-13 20:43:39
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#include "Gobang.h"
#include <fstream>

extern bool black_ai, white_ai;

Gobang::Gobang()
{
	step = 0;
	memset(pos, 0, sizeof(pos));
	memset(map, 0, sizeof(map));
	player = Black;
	over = false;
	reply = false;
}

bool Gobang::add_step(Point p)
{
	if(over)	return false;
	if(reply)	return false;
	if(!VALID(p.x))	return false;
	if(!VALID(p.y))	return false;
	if(map[p.x][p.y] != 0)	return false;
	
	char color = (char)(step % 2);
	map[p.x][p.y] = color + 1;
	pos[step++] = p;
	player = (Player)(step % 2);
	return true;
}

void Gobang::del_step()
{
	if(over)	return ;
	if(step < 1) return ;
	Point p = pos[--step] ;
	map[p.x][p.y] = 0;
	player = (Player)(step % 2);
}

int Gobang::get_step() {
	return step;
}

Point Gobang::get_step(int s) {
	return pos[s];
}

Player Gobang::get_player() {
	return player;
}

int Gobang::get_x_pos(int p)
{
	int i, j;
	for(i=0; i<MAX_NUM; i++)
	{
		j = p - 35 - (CELL_LENGTH * i);
		if(-17 <= j && j <= 17)
			return i;
	}
	return -1;
}

int Gobang::get_y_pos(int p)
{
	int i, j;
	for(i=0; i<MAX_NUM; i++)
	{
		j = p - 30 - (CELL_LENGTH * i);
		if(-17 <= j && j <= 17)
			return i;
	}
	return -1;
}

bool Gobang::is_win()
{
	if(over) return over;
	Point p;
	if(step < 1) return false;
	p = pos[step - 1];
	int l, r, t;
	// 1)
	for(l = 0;0 <= p.x-l && map[p.x-l][p.y] == map[p.x][p.y]; l++) {}
	t = l;
	for(r = 0;MAX_NUM > p.x+r && map[p.x+r][p.y] == map[p.x][p.y]; r++) {}
	t += r;
	if(t > 5) {
		over = true;
		return over;
	}
	// 2)
	for(l = 0;0 <= p.y-l && map[p.x][p.y-l] == map[p.x][p.y]; l++) {}
	t = l;
	for(r = 0;MAX_NUM > p.y+r && map[p.x][p.y+r] == map[p.x][p.y]; r++) {}
	t += r;
	if(t > 5) {
		over = true;
		return over;
	}
	// 3)
	for(l = 0;0 <= p.x-l && 0 <= p.y-l && map[p.x-l][p.y-l] == map[p.x][p.y]; l++) {}
	t = l;
	for(r = 0;MAX_NUM > p.x+r && MAX_NUM > p.y+r && map[p.x+r][p.y+r] == map[p.x][p.y]; r++) {}
	t += r;
	if(t > 5) {
		over = true;
		return over;
	}
	// 4)
	for(l = 0;0 <= p.x-l && MAX_NUM > p.y+l && map[p.x-l][p.y+l] == map[p.x][p.y]; l++) {}
	t = l;
	for(r = 0;MAX_NUM > p.x+r && 0 <= p.y-r && map[p.x+r][p.y-r] == map[p.x][p.y]; r++) {}
	t += r;
	if(t > 5) {
		over = true;
		return over;
	}
	// 5）平局，游戏结束
	if(step == 361) over = true;
	return over;
}

bool Gobang::is_rep() {
	return reply;
}

string Gobang::player_msg()
{
	if(over) {
		if(player == Black)
			return "  Congratulations! White player win the game!";
		else
			return "  Congratulations! Black player win the game!";
	}
	else {
		if(player == Black)
			return "  Black player please place a black stone.";
		else
			return "  White player please place a white stone.";
	}
}

bool Gobang::save(string f) {
	if(black_ai) black_ai = false;
	if(white_ai) white_ai = false;
	ofstream savefile;
	savefile.open(f.c_str(), ios::out);
	if(savefile == NULL)
		return false;
	savefile << step << endl;
	for(int i=0; i<step; i++)
		savefile << pos[i].x << " " << pos[i].y << endl;
	savefile.close();
	return true;
}

bool Gobang::load(string f) {
	if(black_ai) black_ai = false;
	if(white_ai) white_ai = false;
	ifstream loadfile;
	loadfile.open(f.c_str(), ios::in);
	if(loadfile == NULL)
		return false;
	Gobang *temp;
	temp = new Gobang();
	int t_step;
	Point t_pos;
	loadfile >> t_step;
	while(loadfile >> t_pos.x >> t_pos.y) {
		temp->add_step(t_pos);
	}
	if(temp->get_step() != t_step)
		return false;
	// clean current data
	step = 0;
	memset(pos, 0, sizeof(pos));
	memset(map, 0, sizeof(map));
	player = Black;
	over = false;
	reply = false;
	// add load data
	for(int i=0; i<t_step; i++)
		add_step(temp->get_step(i));
	delete temp;
	loadfile.close();
	reply = true;
	return true;
}