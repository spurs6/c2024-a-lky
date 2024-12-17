#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->GradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row(size, 0);
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	Chesspos pos = think();
	Sleep(1000); //��װ˼��
	chess->ChessDown(&pos, CHESS_WHITE);
}

void AI::calculate()
{
	int personNum = 0; //���ַ��ж��ٸ���������
	int aiNum = 0; //AI�ж��ٸ���������
	int emptyNum = 1;//�÷����Ͽհ�λ�ĸ���         



	//����������������
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;

		}
	}

	int size = chess->GradeSize();
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {

			//��ÿ������м���
			if (chess->Chessgetdata(row, col)) continue;
			//ֻ�Կհ׵�����

			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					//���������
					personNum = 0;
					aiNum = 0;
					emptyNum = 1;
					if (y == 0 && x == 0) continue;

					//��������ڸ�λ������
					for (int i = 1; i <= 4; i++) {//i���ܴ�0��ʼ�жϣ���Ϊ0���ǿհף�Ȼ���ֱ��break��
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->Chessgetdata(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->Chessgetdata(curRow, curCol) == 0) {
							emptyNum++;
							break;
							//���屻��������ж�
						}
						else {//����ǰ���ֱ��break
							break;
						}
					}

					if (personNum == 1) {//��2
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptyNum == 1) {//����
							//��
							//  ��
							//    ��
							//      �жϵ�
							//
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4) {
						scoreMap[row][col] += 20000;
					}

					// ��������ڸ�λ������
					emptyNum = 1;                        
					for (int i = 1; i <= 4; ++i) {        
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->Chessgetdata(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->Chessgetdata(curRow, curCol == 0)) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}

					if (aiNum == 0) {
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 25;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 50;
						}
					}
					else if (aiNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 55;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum >= 4) {
						scoreMap[row][col] += 30000;
					}


				}
			}
		}
	}
}

Chesspos AI::think()
{
	calculate();

	int maxScore = 0;

	vector<Chesspos> maxPoints;

	int size = chess->GradeSize();
	//size = scoreMap.size();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->Chessgetdata(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(Chesspos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxPoints.push_back(Chesspos(row, col));
				}
			}
		}
	}

	int index = rand() % maxPoints.size();
	return maxPoints[index];
}