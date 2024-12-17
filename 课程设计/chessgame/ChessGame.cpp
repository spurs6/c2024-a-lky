#include "ChessGame.h"

/*现在想实现启动函数的基本功能
 但发现所有定义的函数接口都无法实现
 原因就是我们还没有定义对象
 创建完对象之后，设计游戏主体循环就很简单了
 1.先由人走，再由棋手走
 2.无论是人还是棋手，每走完一步都要检查棋局是否结束
 3.如果结束初始化整个图形用户界面，然后continue跳出循环即可
*/

ChessGame::ChessGame(Man* man, Chess* chess, AI* ai)
{
	this->man = man;
	this->chess = chess;
	this-> ai = ai;

	man->init(chess);
	ai->init(chess);
}
//这里体现this指针一个非常重要的作用，就是在构造函数里面初始化成员变量
//this指向的其实private属性中的成员变量，所赋的值是参数列表里面的局部变量
//如果不写this指针，man就会默认成参数列表里面的man，这是就近原则导致的

void ChessGame::play()
{
	chess->init();
	while (1) {
		man->go();
		if (chess->checkover()) {
			chess->init();
			continue;
		}
		ai->go();
		if (chess->checkover()) {
			chess->init();
			continue;
		}
	}
}

