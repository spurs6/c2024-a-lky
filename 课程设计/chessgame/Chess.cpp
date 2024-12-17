#include "Chess.h"
#include <math.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


/// </summary>
/// <param name="x">
void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
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

	/*���͵�c++��������Ķ�ά�����ʼ���Ĳ��裬
	����vector�����涨���˲����й����鴦��ĺ���
	��push_back(),pop_back(),��һ���Ĳ����б��Ҫ���������
	�൱��python�����׷��append�������ڶ��������б����治��
	�κ����ݣ�ֱ��ɾ���б��������һ��Ԫ�أ��൱��python����
	��pop����*/
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
	//�������ǵ���Ϸ����
	/*�������漰������ʹ��easyxͼ�ο�����֪ʶ
	��һ�����ȴ���һ����߶��Ĵ��ڣ�ʹ��initgraph����
	�ڶ���������ͼƬ��Ĭ�ϴ��ڣ�ʹ��loadimage����һ��������0���ڶ���������ͼƬ��
	*/
	
	initgraph(897,895);
	//�����һ��������0,˵��Ĭ�ϼ��ص���ǰ������
	loadimage(0, "res/res/����2.jpg");

	mciSendString("play res/res/start.wav", 0, 0, 0);
	//��������ڲ�����ͼƬ��ʾ���������ö���õ�ͼƬ����������������
	//�����������ݾ������ͼƬ�Ĵ�С�ͺ����趨�Ĵ�С��ͬ����Ҫ������Ԫ�ص�
	//��Ⱥ͸�Ԫ�صĿ����ȫ��ͬ��ԭ���js���һ��
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
	/*����ΪʲôҪ��ȥ���ӳߴ��һ���أ�ԭ�����easyx�����ڻ���ͼƬ��ʱ��
	�ǽ������б������������Ϊ����ͼƬ��ʾ�����Ͻǣ������������ģ�
	����������Ҫ������������ֱ����ƺ���������һ��ĳ�����ʵ��Ч��*/
	/*���Ҳ��js�е�img��ǩ���ͼƬ��ԭ��ǳ����ƣ�ͬ���������ǴӺ���
	�����Ͻǿ�ʼ��ʾͼƬ�ģ�ͼƬ������ӵĲ��ֲ�����ʾ��Ȼ�������ֿ�����
	background-position��������ʾͼƬ�Ĳ��֣������Ǿ���ͼ�Ĺ���ԭ��*/
	int x = margin_x + pos->col * chessSize-0.5*chessSize;
	int y = margin_y + pos->row * chessSize-0.5*chessSize;
	
	//�ж����µ����ӵ�����
	if (kind == CHESS_BLACK) {
		/*ʹ�û���ͼ����putimage����������ɴ�����IMAGE���������ͼƬ��ʾ*/
		putimagePNG(x, y, &blackchess);
	}
	else {
		putimagePNG(x, y, & whitechess);
	}

	updateMap(pos);
}



/*�ж�����λ�õ�ԭ��
�������֮��,GetMouseMsg�᷵���������x�����y����
Ȼ���ؼ���������Χ�ĸ���ľ��룬������Ҫ����һ����ֵ�ĸ���
��������λ�ú͵�ľ�����С����ֵ�ģ���λ��ȷ����������
��ֵ����������ߵ�����ݴ��ʵģ�һ��С�����ӳߴ��һ�붼���ԣ�
����ȡ���ӳߴ��0.4*/
bool Chess::ClickBoard(int x, int y, Chesspos* pos)
{ 
	int x10 = 0;
	double offset=chessSize*0.4;
    double length;
	bool ret = false;
	do {
		//���Ͻ�
		int x1 = (x - margin_x) / chessSize;
		int y1 = (y - margin_y) / chessSize;

		double lefttopposX = margin_x + x1 * chessSize;
		double lefttopposY = margin_y + y1 * chessSize;

		length = sqrt((x - lefttopposX) * (x - lefttopposX) +
			(y - lefttopposY) * (y - lefttopposY));
		if (length < offset) {
			pos->col = x1;
			pos->row = y1;
			/*���ｫ��ά��̬�����ʼ����0Ҳ��ʮ�������
			ԭ�����Ѿ���ö�ٶ����˺�����1��������-1���ո�
			Ϊ0������������ȫ���������ߵ������*/
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
				break;//��ʡʱ��
			}
		}

		//���Ͻ�
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

		//���½�
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

		//���½�
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
			/*playerFlag�������ж�˭�����һ�������ͱ���
			��updateMap�����ÿ�β���֮ǰ��Ҫ�Ƚ��б���
			ֵ�ķ�ת*/
			/*���playerflagΪ�٣�˵����ʱ�������AI������
			�Ѿ������ˣ�˵�������ֻ�ʤ*/
			loadimage(0, "res/res/ʤ��.jpg");
			mciSendString("play res/res/����.mp3", 0, 0, 0);
		}
		else {
			loadimage(0, "res/res/ʧ��.jpg");
			mciSendString("play res/res/ʧ��.mp3",0,0,0);
		}

		//����һ����ͣ���������÷���getchar���в�ͬ
		/*getchar�Ǳ���Ҫ��ȡ��һ���ַ����͵����ݲ���
		�س�����Ż�������У�_getch�����ⰴ��һ����
		����ͻ��������*/
		_getch();
		return true;
	}
    return false;
}

/*������������þ��ǽ��Ѿ��ºõ����Ӵ����ڶ�ά����chessMap����*/
void Chess::updateMap(Chesspos* pos)
{
	/*��������ֻ�ж̶����д��룬ҲҪ����������˼��
	* �����߼���������ԣ���ֻ����������ֵ���Ƿ���ֵ
	* �������ֵ��ʹ���߼��������֮��ͱ����
	* ����Ƿ���ֵ��ʹ���߼��������֮��ͱ�ɼ�
	* ���ǲ���ʵ�ֽ�һ������ת����һ��������Ч����
	*/
	/*
	* ����֮ǰplayerflag�Ѿ��洢һ������ֵCHESS_BLACK
	* ���߼��ж�ʱ��ֻҪ�Ƿǿշ��㶼���棬�������º���
	* ����Ҫ��������˳������ʹ���߼�����������´���
	* �����������ʽ��ʱ���µľ��ǰ����ˣ��������ܽ�
	* �ºõ����Ӱ�������ֵ�Ĳ�ͬ�����ڶ�ά�������棬
	* ��������AI��������ж�
	*/
	lastpos = *pos;//�����һ�����������и���
	chessMap[pos->row][pos->col] = (playerFlag ? CHESS_BLACK : CHESS_WHITE);
	playerFlag = !playerFlag;
}


bool Chess::checkWin()
{
	//������ӵ��λ��
	int row = lastpos.row;
	int col = lastpos.col;

	//���ӵ��ˮƽ����
	for (int i = 0; i < 5; i++) {
		 //���ڵ�i��,
		 //��������������λ��
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

	//��ֱ����
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

	//"/"����
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

	//"\"����
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
