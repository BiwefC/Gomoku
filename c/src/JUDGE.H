#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

struct p_tmp 
{
	int i;
	int j;
};

class Judge
{
public:
	Judge( int k );
	bool longlink( Table T );
	int fivelink( Table T );
	int si(Table T, char line, char column);
	int huosan(Table T, char line, char column);
/*	int chongsan( Table T );
	int huoer( Table T );
	int chonger( Table T );
	int huoyi( Table T );
	int chongyi( Table T );*/
	friend class Table ;
	friend class Ai ;
private:
	int color ;
	int anticolor ;

	vector<p_tmp> sanArr1;  // -
	vector<p_tmp> sanArr2;  // |
	vector<p_tmp> sanArr3;  // \ 
	
	vector<p_tmp> sanArr4;  // /

	vector<p_tmp> siArr1;
	vector<p_tmp> siArr2;
	vector<p_tmp> siArr3;
	vector<p_tmp> siArr4;
};