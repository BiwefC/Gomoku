#include "decision.h"

char* GetPos(char pos[], char WorB)  //���߽ӿ�
{
	if (WorB == 'b')
	{
		// ���ӻغ�
		// ��ChessLog.txt�õ���ǰ������Ϣ
		// ʹ����ľ����㷨�������һ��Ҫ�ߵ�x��y����
		// ��[x��y] = decision(ChessLog.txt)
		// ����pos��Ϊ��������ֵ

		// ������������
		int x, y;

		cin >> x >> y;
		cin.clear();
		cin.ignore(10, '\n');
		pos[0] = x;
		pos[1] = y;

		return pos;
	}
	else if (WorB == 'w')
	{
		// ���ӻغ�
		// ��ChessLog.txt�õ���ǰ������Ϣ
		// ʹ����ľ����㷨�������һ��Ҫ�ߵ�x��y����
		// [x��y] = decision()
		// ����pos��Ϊ��������ֵ

		// ������������
		int x, y;
		
		cin >> x >> y;
		cin.clear();
		cin.ignore(10, '\n');
		pos[0] = x;
		pos[1] = y;

		return pos;
	}
	else
	{
		pos[0] = 0;
		pos[1] = 0;

		return pos;
	}
}