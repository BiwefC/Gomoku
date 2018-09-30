#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"
#include "python_api.h"

class JudgeAPI
{
  private:
    Judge judgewhite;
    Judge judgeblack;
    Table fivetable;
    int count;

  public:
    JudgeAPI(int input[15][15]);
    void Init(void);
    int UpdateAndJudge(int x, int y,int color);
};

JudgeAPI::JudgeAPI(int input[15][15]): judgewhite(1), judgeblack(2), fivetable(input)
{

}

void JudgeAPI::Init(void)
{
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 15; j++){
      fivetable.set(i, j, 0);
    }
  }
  count = 0;
}

int JudgeAPI::UpdateAndJudge(int x, int y, int color)
{
  fivetable.set(x, y, color);
  count++;
  if(count % 2){
    if(judgeblack.longlink(fivetable) ){
      cout << "黑棋长连禁手，白棋胜" << endl;
      return 2;
    }
    if(judgeblack.fivelink(fivetable)){
      cout<<"黑棋五连，黑棋胜"<<endl;
      return 1;
    }
    if(judgeblack.huosan(fivetable, x, y) > 1 ){
      cout<<"黑棋三三禁手，白棋胜"<<endl;
      return 2;
    }
    if(judgeblack.si(fivetable, x, y) > 1){
      cout<<"黑棋四四禁手，白棋胜"<<endl;
      return 2;
    }
  }
  else{
    if(judgewhite.fivelink(fivetable) ){
      cout<<"白棋五连，白棋胜"<<endl;
      return 1;
    }
  }
  if(count == 225){
    cout <<"和棋"<<endl;
    return 3;
  }
  return 0;
}


extern "C" {

int input[15][15] = {0};

JudgeAPI judge_api(input);

int JudgeAPIInit(void)
{
  judge_api.Init();
}

int JudgeAPIUpdateAndJudge(int x,int y, int color)
{
  judge_api.UpdateAndJudge(x, y, color);
}
}
