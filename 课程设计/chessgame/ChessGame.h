#pragma once
#include "Man.h"
#include "AI.h"
#include "Chess.h"

class ChessGame
{
public:
	//程序控制函数：作用就是开始对局或者是控制对局
	void play();

	/*在c++语言中，最常见的初始化成员变量的方法就是构造函数
	构造函数的名字必须与类名完全相同，这点和Java是非常相似的*/
	ChessGame(Man*man,Chess*chess,AI*ai);

//为了数据成员的安全性，我们将其设置为Private
private:
	Man* man;
	Chess* chess;
	AI* ai;
};

