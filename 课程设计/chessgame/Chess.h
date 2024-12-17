#pragma once
#include <graphics.h>
#include <vector>
using namespace std;
/*添加一个动态数组库，并且使用标准库的命名空间std*/

/*在c++里面，结构体和类是有着很大相似之处的，
* 两者均能进行继承和多态，唯一的不同就是类的
* 成员访问权限默认是private，而结构体的成员默认
* 访问权限是public，这也解释了为什么在类里面有时
* 需要手动设置public和private，来调整不同范围的接口
* 
*/

struct Chesspos {
	int row;
	int col;

	/*这种结构体的构造函数在实际开发应用过程中非常
	普遍，首先构造函数与类名相同，参数列表给x和y设了
	一个默认值0，意思就是如果参数列表为空就自动
	赋值0和0，这也是个非常重要的小技巧，防止在代码太多
	调用参数列表时候出错*/
	/*然后关键就是冒号和后面的部分，这叫做成员初始化列表
	将x的值赋值给成员变量row，将Y的值赋值给成员变量col,这样
	在创建对象的时候就能自动初始化，非常方便*/
	Chesspos(int x=0,int y=0):row(x),col(y){}
};

/*枚举作为一种特殊的整型类型的用法：
* 其实本质上和变量的定义是相同的，只不过是不加数据类型
* ，原因是enum定义的变量默认数据类型是Int,同时可能会对等号产生疑惑，
* 其实不要有疑惑，这不是css里面的修饰，用属性名加：再加属性值
* 中间用逗号隔开，这个还是要记住的
* 
* enum的使用方法主要有两种：显式定义和隐式定义
* 如果使用显式定义，就是在枚举类型里面每个都加上数值
* 但现在通常用的都是隐式类型，默认是从0开始赋值
* 同时在c++里面允许省略enum关键字，直接枚举名来定义枚举成员这种行为
*/

typedef enum {
	CHESS_WHITE=-1,
    CHESS_BLACK=1,
}chess_kind_t;

/*
c++中相较于c的一个优势，直接将bool类型函数作为内置函数
*/
class Chess
{
public:
	//添加完数据成员之后，自然就要用构造函数给数据成员初始化
	Chess(int gradeSize,int marginX,int marginY,int chessSize);
	//先初始化整个游戏界面
	void init();
	//记录落子的位置，并确定是黑棋还是白棋
	void ChessDown(Chesspos* pos, chess_kind_t kind);
	//判断落子是否有效
	bool ClickBoard(int x, int y, Chesspos* pos);
	//获取棋盘的大小(13,15,17)
	int GradeSize();
	//获取位置上是黑棋，白棋，还是空白
	int Chessgetdata(Chesspos* pos);
	int Chessgetdata(int row, int col);
	//检查棋局是否结束
	bool checkover();
	
private:
	/*这里为什么要定义两个图像类型的变量呢
	原因和c++中开始变量出现的原因基本相同
	就是因为在程序执行的过程中，需要多次使
	用到黑棋和白棋这两种图片*/
	IMAGE blackchess;
	IMAGE whitechess;

	int gradeSize;//获取棋盘的大小
	int margin_x;//获取棋盘左边距的长度
	int margin_y;//获取棋盘上边距的长度
	float chessSize;//获取棋子的大小（本质上就是棋盘上一个空格的长度）

	//定义一个可变长度的数组，用来存储当前棋盘棋子的信息
	//1代表黑棋，-1代表白棋，0代表空格
	vector <vector<int>> chessMap;

	bool playerFlag;//确定到底是黑棋下还是白棋下

	Chesspos lastpos;//记录最近落子点的位置

private:
	void updateMap(Chesspos*pos);
	//检查棋局是否有一方胜利
	bool checkWin();
};

