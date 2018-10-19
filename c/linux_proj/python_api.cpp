#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"
#include "python_api.h"


class JudgeAPI
{
  private:
    Judge judgewhite;
    Judge judgeblack;

  public:
    JudgeAPI(void);
    int DoJudge(Table &table, int x, int y, int count);
};

JudgeAPI::JudgeAPI(void): judgewhite(1), judgeblack(2)
{

}

int JudgeAPI::DoJudge(Table &table, int x, int y, int count)
{
  if(count % 2){
    if(judgeblack.longlink(table)){
      // cout << "黑棋长连禁手，白棋胜" << endl;
      return 2;
    }
    if(judgeblack.fivelink(table)){
      // cout<<"黑棋五连，黑棋胜"<<endl;
      return 1;
    }
    if(judgeblack.huosan(table, y, x) > 1 ){
      // cout<<"黑棋三三禁手，白棋胜"<<endl;
      return 2;
    }
    if(judgeblack.si(table, y, x) > 1){
      // cout<<"黑棋四四禁手，白棋胜"<<endl;
      return 2;
    }
  }
  else{
    if(judgewhite.fivelink(table) ){
      // cout<<"白棋五连，白棋胜"<<endl;
      return 2;
    }
  }
  if(count == 225){
    // cout <<"和棋"<<endl;
    return 3;
  }
  return 0;
}


class AIAPI
{
  private:
    Ai aiwhite;
    Ai aiblack;

  public:
    AIAPI(void);
    int GetBestSet(Table &table, int count);
};

AIAPI::AIAPI(void):aiwhite(1), aiblack(2)
{

}

int AIAPI::GetBestSet(Table &table, int count)
{
  if(count % 2){
    return aiwhite.xiazi(table);
  }
  else{
    return aiblack.xiazi(table);
  }
}

extern "C" {

int input[15][15] = {0};

JudgeAPI judge_api;
AIAPI ai_api;

int JudgeAPIDoJudge(int board[15][15], int x,int y, int count)
{
  Table table(board);
  return judge_api.DoJudge(table, x, y, count);
}

int AIAPIGetBestSet(int board[15][15], int count)
{
  Table table(board);
  return ai_api.GetBestSet(table, count);
}

}
