#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

/*实现用户的走棋功能*/
void Man::go()
{
	/*首先我们先定义一个esayx库里面的一个结构体MOSUEMSG的对象,
	里面定义了许多与鼠标信息相关的成员变量，然后用getmosuemsg来
	获取鼠标点击信息，这里的信息包括很多：例如下面要用到的
	当前鼠标的x值和y值，直角坐标系是在窗口里面建立的*/
	MOUSEMSG msg;
    Chesspos pos;
	/*我们想要检测鼠标点击是否有效，如果有效将他存入二维数组里面
	此时我们想到要使用chess类里面的函数clickBoard,但是在调用其他类
	的对象之前，我们先要添加数据成员*/

	/*这里使用while循环就是为了防止无效点击的出现，
	因此允许人们错误点击多次，只要点对即可跳出循环*/
	while (1) {
		msg = GetMouseMsg();
		/*uMSG是MOUSEMG结构体里面定义的一种成员变量，
		其作用就是获取页面上发生的事件类型*/
        if (msg.uMsg == WM_LBUTTONDOWN && chess->ClickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	//已经确定落子位置正确，实现真正的落子功能
	chess->ChessDown(&pos, CHESS_BLACK);
}
