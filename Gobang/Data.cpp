/***************************************************************************

    file				: Data.cpp
    modified			: 2012-07-11 15:12:42
    copyright			: (C) 2012 Zhou Cheng
    email				: c.zhou@live.com

 ***************************************************************************/

#include "Data.h"

bool operator==(Point &p1, Point &p2) {
	return (p1.x == p2.x)&&(p1.y == p2.y);
}

bool operator!=(Point &p1, Point &p2) {
	return !(p1 == p2);
}