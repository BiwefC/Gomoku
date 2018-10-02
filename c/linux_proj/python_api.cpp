#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"
#include "python_api.h"

class TableAPI
{
  public:
    TableAPI(int input[15][15]);
    void TableReset(void);
    void Set(int x, int y, int color);
    
    Table fivetable;
    int count;
};

TableAPI::TableAPI(int input[15][15]):fivetable(input), count(0)
{

}

void TableAPI::TableReset(void)
{
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 15; j++){
      fivetable.set(i, j, 0);
    }
  }
  count = 0;
}

inline void TableAPI::Set(int x, int y, int color)
{
  fivetable.set(x, y, color);
  count++;
}

class JudgeAPI
{
  private:
    Judge judgewhite;
    Judge judgeblack;
    TableAPI &gomoku_table;

  public:
    JudgeAPI(TableAPI &input_table);
    int DoJudge(int x, int y,int color);
};

JudgeAPI::JudgeAPI(TableAPI &input_table): judgewhite(1), judgeblack(2), gomoku_table(input_table)
{

}

int JudgeAPI::DoJudge(int x, int y, int color)
{
  if(gomoku_table.count % 2){
    if(judgeblack.longlink(gomoku_table.fivetable) ){
      cout << "黑棋长连禁手，白棋胜" << endl;
      return 2;
    }
    if(judgeblack.fivelink(gomoku_table.fivetable)){
      cout<<"黑棋五连，黑棋胜"<<endl;
      return 1;
    }
    if(judgeblack.huosan(gomoku_table.fivetable, x, y) > 1 ){
      cout<<"黑棋三三禁手，白棋胜"<<endl;
      return 2;
    }
    if(judgeblack.si(gomoku_table.fivetable, x, y) > 1){
      cout<<"黑棋四四禁手，白棋胜"<<endl;
      return 2;
    }
  }
  else{
    if(judgewhite.fivelink(gomoku_table.fivetable) ){
      cout<<"白棋五连，白棋胜"<<endl;
      return 1;
    }
  }
  if(gomoku_table.count == 225){
    cout <<"和棋"<<endl;
    return 3;
  }
  return 0;
}


class AIAPI
{
  private:
    Ai aiwhite;
    Ai aiblack;
    TableAPI &gomoku_table;

  public:
    AIAPI(TableAPI &input_table);
    int GetBestSet(void);
};

AIAPI::AIAPI(TableAPI &input_table):aiwhite(1), aiblack(2), gomoku_table(input_table)
{

}

int AIAPI::GetBestSet(void)
{
  if(gomoku_table.count % 2){
    return aiblack.xiazi(gomoku_table.fivetable);
  }
  else{
    return aiwhite.xiazi(gomoku_table.fivetable);
  }
}

extern "C" {

int input[15][15] = {0};

TableAPI table_api(input);
JudgeAPI judge_api(table_api);
AIAPI ai_api(table_api);

void TableAPITableReset(void)
{
  table_api.TableReset();
}

void TableAPISet(int x, int y, int color)
{
  table_api.Set(x, y, color);
}

int JudgeAPIDoJudge(int x,int y, int color)
{
  judge_api.DoJudge(x, y, color);
}

int AIAPIGetBestSet(void)
{
  return ai_api.GetBestSet();
}

}
