#ifndef __PYTHON_API_H__
#define __PYTHON_API_H__

extern "C" {
int JudgeAPIDoJudge(int board[15][15], int x,int y, int count);
int AIAPIGetBestSet(int board[15][15], int count);
}
#endif