#include "Chess.h"
#include <math.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


/// </summary>
/// <param name="x">
void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

Chess::Chess(int gradeSize, int marginX, int marginY, int chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;

	/*典型的c++语言里面的二维数组初始化的步骤，
	由于vector库里面定义了不少有关数组处理的函数
	如push_back(),pop_back(),第一个的参数列表加要加入的数据
	相当于python里面的追加append函数，第二个参数列表里面不加
	任何内容，直接删除列表后面的最后一个元素，相当于python里面
	的pop函数*/
	for (int i = 0; i < gradeSize; i++) {
		vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}

	playerFlag =CHESS_BLACK;
}

void Chess::init()
{
	//创建我们的游戏窗口
	/*这里又涉及到关于使用easyx图形库的相关知识
	第一步：先创建一个多高多宽的窗口，使用initgraph函数
	第二步：加载图片到默认窗口，使用loadimage，第一个参数是0，第二个参数是图片名
	*/
	
	initgraph(897,895);
	//如果第一个参数是0,说明默认加载到当前窗口上
	loadimage(0, "res/res/棋盘2.jpg");

	mciSendString("play res/res/start.wav", 0, 0, 0);
	//如果我现在不想让图片显示，可以先用定义好的图片变量将他储存起来
	//后面三个数据就是如果图片的大小和盒子设定的大小不同，需要设置子元素的
	//宽度和父元素的宽度完全相同，原理和js如出一辙
	loadimage(&blackchess, "res/res/black.png", chessSize, chessSize, true);
	loadimage(&whitechess, "res/res/white.png", chessSize, chessSize, true);

	
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}
}

void Chess::ChessDown(Chesspos* pos, chess_kind_t kind)
{

	mciSendString("play res/res/down7.WAV", 0, 0, 0);
	/*这里为什么要减去棋子尺寸的一半呢，原因就是easyx库他在绘制图片的时候
	是将参数列表里面的坐标作为整个图片显示的左上角，而不是正中心，
	所以我们需要将这个点的坐标分别上移和左移棋子一半的长度来实现效果*/
	/*这点也与js中的img标签添加图片的原理非常类似，同样编译器是从盒子
	的左上角开始显示图片的，图片溢出盒子的部分不会显示，然后我们又可以用
	background-position来控制显示图片的部分，这又是精灵图的工作原理*/
	int x = margin_x + pos->col * chessSize-0.5*chessSize;
	int y = margin_y + pos->row * chessSize-0.5*chessSize;
	
	//判断所下的棋子的种类
	if (kind == CHESS_BLACK) {
		/*使用绘制图像函数putimage，将加载完成储存在IMAGE变量里面的图片显示*/
		putimagePNG(x, y, &blackchess);
	}
	else {
		putimagePNG(x, y, & whitechess);
	}

	updateMap(pos);
}



/*判断落子位置的原理：
当鼠标点击之后,GetMouseMsg会返回鼠标点击的x坐标和y坐标
然后呢计算他到周围四个点的距离，这里需要引入一个阈值的概念
如果鼠标点击位置和点的距离是小于阈值的，则位置确定，本质上
阈值就是用来提高点击的容错率的，一般小于棋子尺寸的一半都可以，
这里取棋子尺寸的0.4*/
bool Chess::ClickBoard(int x, int y, Chesspos* pos)
{ 
	int x10 = 0;
	double offset=chessSize*0.4;
    double length;
	bool ret = false;
	do {
		//左上角
		int x1 = (x - margin_x) / chessSize;
		int y1 = (y - margin_y) / chessSize;

		double lefttopposX = margin_x + x1 * chessSize;
		double lefttopposY = margin_y + y1 * chessSize;

		length = sqrt((x - lefttopposX) * (x - lefttopposX) +
			(y - lefttopposY) * (y - lefttopposY));
		if (length < offset) {
			pos->col = x1;
			pos->row = y1;
			/*这里将二维动态数组初始化成0也是十分巧妙的
			原因是已经用枚举定义了黑棋是1，白棋是-1，空格
			为0，这样就能完全区分这三者的情况啊*/
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
				break;//节省时间
			}
		}

		//右上角
		int x2 = (x - margin_x) / chessSize + 1;
		int y2 = (y - margin_y) / chessSize;
		double righttopposX = margin_x + x2 * chessSize;
		double righttopposY = margin_y + y2 * chessSize;

		length = sqrt((x - righttopposX) * (x - righttopposX) +
			(y - righttopposY) + (y - righttopposY));
		if (length < offset) {
			pos->col = x2;
			pos->row = y2;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
				break;
			}
		}

		//左下角
		int x3 = (x - margin_x) / chessSize;
		int y3 = (y - margin_y) / chessSize+1;
		double leftbottomposX = margin_x + chessSize * x3;
		double leftbottomposY = margin_y + chessSize * y3;

		length = sqrt((x-leftbottomposX) * (x-leftbottomposX) + 
			(y-leftbottomposY) * (y-leftbottomposY));
		if (length < offset) {
			pos->col = x3;
			pos->row = y3;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
				break;
			}
		}

		//右下角
		int x4 = (x - margin_x) / chessSize + 1;
		int y4 = (y - margin_y) / chessSize + 1;
		double rightbottomposX = margin_x + chessSize * x4;
		double rightbottomposY = margin_y + chessSize * y4;

		length = sqrt((x - rightbottomposX) * (x - rightbottomposX) +
			(y - rightbottomposY) * (y - rightbottomposY));
		if (length < offset) {
			pos->col = x4;
			pos->row = y4;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
				break;
			}
		}


	} while (0);

	return ret;
}

int Chess::GradeSize()
{
	return gradeSize;
}



int Chess::Chessgetdata(Chesspos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::Chessgetdata(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkover()
{
	if (checkWin()) {
		Sleep(2000);
		if (playerFlag == false) {
			/*playerFlag是用来判断谁走棋的一个布尔型变量
			在updateMap函数里，每次操作之前都要先进行变量
			值的反转*/
			/*如果playerflag为假，说明此时下棋的是AI，但是
			已经结束了，说明是棋手获胜*/
			loadimage(0, "res/res/胜利.jpg");
			mciSendString("play res/res/不错.mp3", 0, 0, 0);
		}
		else {
			loadimage(0, "res/res/失败.jpg");
			mciSendString("play res/res/失败.mp3",0,0,0);
		}

		//这是一个暂停函数，其用法与getchar稍有不同
		/*getchar是必须要获取到一个字符类型的数据并且
		回车程序才会继续进行，_getch是任意按下一个键
		程序就会继续进行*/
		_getch();
		return true;
	}
    return false;
}

/*这个函数的作用就是将已经下好的棋子储存在二维数组chessMap里面*/
void Chess::updateMap(Chesspos* pos)
{
	/*别看这里面只有短短两行代码，也要理解里面的意思：
	* 对于逻辑运算符而言，他只关心你是零值还是非零值
	* 如果是零值，使用逻辑非运算符之后就变成真
	* 如果是非零值，使用逻辑非运算符之后就变成假
	* 他是不能实现将一个正数转化成一个负数的效果的
	*/
	/*
	* 由于之前playerflag已经存储一个整数值CHESS_BLACK
	* 做逻辑判断时，只要是非空非零都是真，所以先下黑棋
	* 下面要交换落子顺序，于是使用逻辑非运算符，下次在
	* 遇到条件表达式的时候下的就是白棋了，这样就能将
	* 下好的棋子按照整数值的不同储存在二维数组里面，
	* 方便后面的AI进行棋局判断
	*/
	lastpos = *pos;//对最后一个点的坐标进行更新
	chessMap[pos->row][pos->col] = (playerFlag ? CHESS_BLACK : CHESS_WHITE);
	playerFlag = !playerFlag;
}


bool Chess::checkWin()
{
	//最近落子点的位置
	int row = lastpos.row;
	int col = lastpos.col;

	//落子点的水平方向
	for (int i = 0; i < 5; i++) {
		 //对于第i次,
		 //五子连珠的最左侧位置
		 //i = 0: (row,col) (row,col+1) (row,col+2) (row,col+3) (row,col+4)  
		 //i = 1: (row,col-1) (row,col-1+1) (row,col-1+2) (row,col-1+3) (row,col-1+4)
		// i = 2: ()
		if (col - i > 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4]) {
			return true;

		}

	}

	//垂直方向
	for (int i = 0; i < 5; i++) {
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}

	//"/"方向
	for (int i = 0; i < 5; i++) {
		if (row + i < gradeSize && row + i - 4 >= 0 &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]) {
			return true;
		}
	}

	//"\"方向
	for (int i = 0; i < 5; i++) {
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]) {
			return true;
		}
	}

	return false;
}
