#ifndef __PYTHON_API_H__
#define __PYTHON_API_H__

extern "C" {  
int JudgeAPIInit(void);
int JudgeAPIUpdateAndJudge(int x,int y, int color);
}
#endif