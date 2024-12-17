#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

/*ʵ���û������幦��*/
void Man::go()
{
	/*���������ȶ���һ��esayx�������һ���ṹ��MOSUEMSG�Ķ���,
	���涨��������������Ϣ��صĳ�Ա������Ȼ����getmosuemsg��
	��ȡ�������Ϣ���������Ϣ�����ࣺܶ��������Ҫ�õ���
	��ǰ����xֵ��yֵ��ֱ������ϵ���ڴ������潨����*/
	MOUSEMSG msg;
    Chesspos pos;
	/*������Ҫ���������Ƿ���Ч�������Ч���������ά��������
	��ʱ�����뵽Ҫʹ��chess������ĺ���clickBoard,�����ڵ���������
	�Ķ���֮ǰ��������Ҫ������ݳ�Ա*/

	/*����ʹ��whileѭ������Ϊ�˷�ֹ��Ч����ĳ��֣�
	����������Ǵ�������Σ�ֻҪ��Լ�������ѭ��*/
	while (1) {
		msg = GetMouseMsg();
		/*uMSG��MOUSEMG�ṹ�����涨���һ�ֳ�Ա������
		�����þ��ǻ�ȡҳ���Ϸ������¼�����*/
        if (msg.uMsg == WM_LBUTTONDOWN && chess->ClickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	//�Ѿ�ȷ������λ����ȷ��ʵ�����������ӹ���
	chess->ChessDown(&pos, CHESS_BLACK);
}
