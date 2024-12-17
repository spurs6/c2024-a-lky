#include "ChessGame.h"

/*������ʵ�����������Ļ�������
 ���������ж���ĺ����ӿڶ��޷�ʵ��
 ԭ��������ǻ�û�ж������
 ���������֮�������Ϸ����ѭ���ͺܼ���
 1.�������ߣ�����������
 2.�������˻������֣�ÿ����һ����Ҫ�������Ƿ����
 3.���������ʼ������ͼ���û����棬Ȼ��continue����ѭ������
*/

ChessGame::ChessGame(Man* man, Chess* chess, AI* ai)
{
	this->man = man;
	this->chess = chess;
	this-> ai = ai;

	man->init(chess);
	ai->init(chess);
}
//��������thisָ��һ���ǳ���Ҫ�����ã������ڹ��캯�������ʼ����Ա����
//thisָ�����ʵprivate�����еĳ�Ա������������ֵ�ǲ����б�����ľֲ�����
//�����дthisָ�룬man�ͻ�Ĭ�ϳɲ����б������man�����Ǿͽ�ԭ���µ�

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

