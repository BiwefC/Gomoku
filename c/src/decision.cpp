#include "decision.h"

char* GetPos(char pos[], char WorB)  //决策接口
{
	if (WorB == 'b')
	{
		// 黑子回合
		// 从ChessLog.txt得到当前棋盘信息
		// 使用你的决策算法，获得下一步要走的x，y坐标
		// 如[x，y] = decision(ChessLog.txt)
		// 放入pos作为函数返回值

		// 键盘输入例子
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
		// 白子回合
		// 从ChessLog.txt得到当前棋盘信息
		// 使用你的决策算法，获得下一步要走的x，y坐标
		// [x，y] = decision()
		// 放入pos作为函数返回值

		// 键盘输入例子
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