#pragma once
#include "Man.h"
#include "AI.h"
#include "Chess.h"

class ChessGame
{
public:
	//������ƺ��������þ��ǿ�ʼ�Ծֻ����ǿ��ƶԾ�
	void play();

	/*��c++�����У�����ĳ�ʼ����Ա�����ķ������ǹ��캯��
	���캯�������ֱ�����������ȫ��ͬ������Java�Ƿǳ����Ƶ�*/
	ChessGame(Man*man,Chess*chess,AI*ai);

//Ϊ�����ݳ�Ա�İ�ȫ�ԣ����ǽ�������ΪPrivate
private:
	Man* man;
	Chess* chess;
	AI* ai;
};

