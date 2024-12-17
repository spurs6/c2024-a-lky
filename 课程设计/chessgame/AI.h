#pragma once
#include "Chess.h"
#include <vector>

class AI
{
public:
	//������AI���廹��������֮ǰ���������ȶ��������̽��г�ʼ��
	void init(Chess* chess);
	void go();
private:
	Chess* chess;

	/*������־���ķǳ������ˣ�
	AI�����ԭ����ǿ��ټ���������ÿ�����Ӧ�ķ���
	����һ�����̵�ķ���ͼ��Ȼ����������������*/
	vector<vector<int>> scoreMap;

    /*˽�еĳ�Ա���Ժͽӿ�ͨ���Ƿֿ��ģ��������Ժͷ�������
	������ͬprivate��������*/
private:
	void calculate();
	Chesspos think();
};

