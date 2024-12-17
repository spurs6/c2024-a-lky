#pragma once
#include "Chess.h"

class Man
{
public:
	void init(Chess* chess);
	void go();
private:
    /*这里用一句非常简单易懂的语言来描述直接定义对象
	和定义对象的指针的区别：如果用的是直接定义，两者就是
	所有关系，棋盘是属于人的，如果是用指针间接定义，两者
	就是合作关系，人只是暂时使用棋盘，但是棋盘并不属于人*/
	Chess* chess;
};

