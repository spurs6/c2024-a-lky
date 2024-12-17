#pragma once
#include "Chess.h"
#include <vector>

class AI
{
public:
	//无论是AI下棋还是人下棋之前，都必须先对整个棋盘进行初始化
	void init(Chess* chess);
	void go();
private:
	Chess* chess;

	/*这个名字就起的非常本质了：
	AI下棋的原理就是快速计算棋盘上每个点对应的分数
	生成一张棋盘点的分数图，然后来决定下在哪里*/
	vector<vector<int>> scoreMap;

    /*私有的成员属性和接口通常是分开的，即将属性和方法分在
	两个不同private属性里面*/
private:
	void calculate();
	Chesspos think();
};

