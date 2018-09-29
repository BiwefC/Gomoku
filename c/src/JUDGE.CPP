#include "TABLE.H"
#include "JUDGE.H"
#include "AI.H"

/////////////////////////////////////////////////////////////////////////////////////////

Judge::Judge( int k )           //    构造函数
{
	color = k ;
	if( k == 1 ) anticolor = 2 ;
	else anticolor = 1 ;
}

/////////////////////////////////////////////////////////////////////////////////////////

bool Judge::longlink( Table T )      // 判断长连
{
	int i, j ;
	for( i = 0 ; i < 15 ; i++ ){        //判断黑棋横向长连
		for( j = 0 ; j < 10 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i][j+1] == 2 && T.data[i][j+2] == 2 && T.data[i][j+3] == 2 && T.data[i][j+4] == 2 && T.data[i][j+5] == 2){
				return 1 ;
			}
		}
	}

	for( i = 0 ; i < 10 ; i++ ){          //判断黑棋纵向长连
		for( j = 0 ; j < 15 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i+1][j] == 2 && T.data[i+2][j] == 2 && T.data[i+3][j] == 2 && T.data[i+4][j] == 2 && T.data[i+5][j] == 2){
				return 1 ;
			}
		}
	}

	for( i = 0 ; i < 10 ; i++ ){              //判断黑棋“\”向长连
		for( j = 0 ; j < 10 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i+1][j+1] == 2 && T.data[i+2][j+2] == 2 && T.data[i+3][j+3] == 2 && T.data[i+4][j+4] == 2 && T.data[i+5][j+5] == 2){
				return 1 ;
			}
		}
	}

	for( i = 0 ; i < 10 ; i++ ){              //判断黑棋“/”向长连
		for( j = 5 ; j < 15 ; j++ ){
			if( T.data[i][j] == 2 && T.data[i+1][j-1] == 2 && T.data[i+2][j-2] == 2 && T.data[i+3][j-3] == 2 && T.data[i+4][j-4] == 2 && T.data[i+5][j-5] == 2){
				return 1 ;
			}
		}
	}
	
	return 0 ;
}

/////////////////////////////////////////////////////////////////////////////////////////


int Judge::fivelink( Table T )            // 判断五连
{
	int i, j ;
	if( color == 1 ){            //判断横向五连
		for( i = 0 ; i < 15 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i][j+1] == 1 && T.data[i][j+2] == 1 && T.data[i][j+3] == 1 && T.data[i][j+4] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 15 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i][j+1] == 2 && T.data[i][j+2] == 2 && T.data[i][j+3] == 2 && T.data[i][j+4] == 2){
					return 2 ;
				}
			}
		}
	}

	if( color == 1 ){            //判断纵向五连
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 15 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i+1][j] == 1 && T.data[i+2][j] == 1 && T.data[i+3][j] == 1 && T.data[i+4][j] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 15 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i+1][j] == 2 && T.data[i+2][j] == 2 && T.data[i+3][j] == 2 && T.data[i+4][j] == 2){
					return 2 ;
				}
			}
		}
	}

	if( color == 1 ){            //判断“\”向五连
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i+1][j+1] == 1 && T.data[i+2][j+2] == 1 && T.data[i+3][j+3] == 1 && T.data[i+4][j+4] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 0 ; j < 11 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i+1][j+1] == 2 && T.data[i+2][j+2] == 2 && T.data[i+3][j+3] == 2 && T.data[i+4][j+4] == 2){
					return 2 ;
				}
			}
		}
	}

	if( color == 1 ){            //判断“/”向五连
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 4 ; j < 15 ; j++ ){
				if( T.data[i][j] == 1 && T.data[i+1][j-1] == 1 && T.data[i+2][j-2] == 1 && T.data[i+3][j-3] == 1 && T.data[i+4][j-4] == 1){
					return 1 ;
				}
			}
		}
	}
	else{
		for( i = 0 ; i < 11 ; i++ ){
			for( j = 4 ; j < 15 ; j++ ){
				if( T.data[i][j] == 2 && T.data[i+1][j-1] == 2 && T.data[i+2][j-2] == 2 && T.data[i+3][j-3] == 2 && T.data[i+4][j-4] == 2){
					return 2 ;
				}
			}
		}
	}
	return 0 ;
}

/////////////////////////////////////////////////////////////////////////////////////////


int Judge::si(Table T, char line, char column)            // 判断四（包括冲四、活四），并返回棋盘中“四”的个数
{
	siArr1.clear();
	siArr2.clear();
	siArr3.clear();
	siArr4.clear();

	int i , j , pi = 22 , pj = 22 , count = 0 ;
	for( i = 0 ; i < 15 ; i++ ){        //判断横向四
		for( j = 0 ; j < 11 ; j++ ){
			if((i != pi || j != pj+1 ) && T.data[i][j] != anticolor && T.data[i][j+1] != anticolor && T.data[i][j+2] != anticolor && T.data[i][j+3] != anticolor && T.data[i][j+4] != anticolor && ( T.data[i][j] + T.data[i][j+1] + T.data[i][j+2] + T.data[i][j+3] + T.data[i][j+4] ) == 4*color ){
				//count ++ ;
				pi = i ; pj = j ;
				//cout << "i j " << i << " " << j << endl;
				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i, j };
				p_tmp p2 = { i, j + 1 };
				p_tmp p3 = { i, j + 2 };
				p_tmp p4 = { i, j + 3 };
				p_tmp p5 = { i, j + 4 };
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i][j] != 0)
						siArr1.push_back(p1);
					if (T.data[i][j + 1] != 0)
						siArr1.push_back(p2);
					if (T.data[i][j + 2] != 0)
						siArr1.push_back(p3);
					if (T.data[i][j + 3] != 0)
						siArr1.push_back(p4);
					if (T.data[i][j + 4] != 0)
						siArr1.push_back(p5);
				}	
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < siArr1.size(); i++)
	{
		//cout << "Si Arr1  " << siArr1[i].i << " " << siArr1[i].j << endl;
	}

	//-----------------------------------------------------------------------------------

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 11 ; i++ ){   //判断纵向四
		for( j = 0 ; j < 15 ; j++ ){
			if((i != pi+1 || j != pj ) && T.data[i][j] != anticolor && T.data[i+1][j] != anticolor && T.data[i+2][j] != anticolor && T.data[i+3][j] != anticolor && T.data[i+4][j] != anticolor && ( T.data[i][j] + T.data[i+1][j] + T.data[i+2][j] + T.data[i+3][j] + T.data[i+4][j] ) == 4*color ){
				//count ++ ;
				pi = i ; pj = j ;

				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i , j };
				p_tmp p2 = { i + 1, j };
				p_tmp p3 = { i + 2, j };
				p_tmp p4 = { i + 3, j };
				p_tmp p5 = { i + 4, j };
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i][j] != 0)
						siArr2.push_back(p1);
					if (T.data[i + 1][j] != 0)
						siArr2.push_back(p2);
					if (T.data[i + 2][j] != 0)
						siArr2.push_back(p3);
					if (T.data[i + 3][j] != 0)
						siArr2.push_back(p4);
					if (T.data[i + 4][j] != 0)
						siArr2.push_back(p5);
				}
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < siArr2.size(); i++)
	{
		//cout << "Si Arr2  " << siArr2[i].i << " " << siArr2[i].j << endl;
	}

	//-----------------------------------------------------------------------------------

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 11 ; i++ ){    //判断“\”向四
		for( j = 0 ; j < 11 ; j++ ){
			if((i != pi+1 || j != pj+1 ) && T.data[i][j] != anticolor && T.data[i+1][j+1] != anticolor && T.data[i+2][j+2] != anticolor && T.data[i+3][j+3] != anticolor && T.data[i+4][j+4] != anticolor && ( T.data[i][j] + T.data[i+1][j+1] + T.data[i+2][j+2] + T.data[i+3][j+3] + T.data[i+4][j+4] ) == 4*color ){
				//count ++ ;
				pi = i ; pj = j ;

				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i + 0, j + 0 };
				p_tmp p2 = { i + 1, j + 1 };
				p_tmp p3 = { i + 2, j + 2 };
				p_tmp p4 = { i + 3, j + 3 };
				p_tmp p5 = { i + 4, j + 4 };
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i + 0][j + 0] != 0)
						siArr3.push_back(p1);
					if (T.data[i + 1][j + 1] != 0)
						siArr3.push_back(p2);
					if (T.data[i + 2][j + 2] != 0)
						siArr3.push_back(p3);
					if (T.data[i + 3][j + 3] != 0)
						siArr3.push_back(p4);
					if (T.data[i + 4][j + 4] != 0)
						siArr3.push_back(p5);
				}
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < siArr3.size(); i++)
	{
		//cout << "Si Arr3  " << siArr3[i].i << " " << siArr3[i].j << endl;
	}

	//-----------------------------------------------------------------------------------

	pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 11 ; i++ ){    //判断“/”向四
		for( j = 4 ; j < 15 ; j++ ){
			if((i != pi+1 || j != pj-1 ) && T.data[i][j] != anticolor && T.data[i+1][j-1] != anticolor && T.data[i+2][j-2] != anticolor && T.data[i+3][j-3] != anticolor && T.data[i+4][j-4] != anticolor && ( T.data[i][j] + T.data[i+1][j-1] + T.data[i+2][j-2] + T.data[i+3][j-3] + T.data[i+4][j-4] ) == 4*color ){
				//count ++ ;
				pi = i ; pj = j ;

				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i + 0, j - 0 };
				p_tmp p2 = { i + 1, j - 1 };
				p_tmp p3 = { i + 2, j - 2 };
				p_tmp p4 = { i + 3, j - 3 };
				p_tmp p5 = { i + 4, j - 4 };
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i + 0][j - 0] != 0)
						siArr4.push_back(p1);
					if (T.data[i + 1][j - 1] != 0)
						siArr4.push_back(p2);
					if (T.data[i + 2][j - 2] != 0)
						siArr4.push_back(p3);
					if (T.data[i + 3][j - 3] != 0)
						siArr4.push_back(p4);
					if (T.data[i + 4][j - 4] != 0)
						siArr4.push_back(p5);
				}
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < siArr4.size(); i++)
	{
		//cout << "Si Arr4  " << siArr4[i].i << " " << siArr4[i].j << endl;
	}

	//-----------------------------------------------------------------------------------

	//judge four four forbidden
	for (unsigned int i = 0; i < siArr1.size(); i++)
	{
		p_tmp compare_elem = siArr1[i];
		
		for (unsigned int j = 0; j < siArr2.size(); j++)
		{
			if (compare_elem.i == siArr2[j].i && compare_elem.j == siArr2[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
		for (unsigned int j = 0; j < siArr3.size(); j++)
		{
			if (compare_elem.i == siArr3[j].i && compare_elem.j == siArr3[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
		for (unsigned int j = 0; j < siArr4.size(); j++)
		{
			if (compare_elem.i == siArr4[j].i && compare_elem.j == siArr4[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
	}

	for (unsigned int i = 0; i < siArr2.size(); i++)
	{
		p_tmp compare_elem = siArr2[i];

		for (unsigned int j = 0; j < siArr3.size(); j++)
		{
			if (compare_elem.i == siArr3[j].i && compare_elem.j == siArr3[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
		for (unsigned int j = 0; j < siArr4.size(); j++)
		{
			if (compare_elem.i == siArr4[j].i && compare_elem.j == siArr4[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
	}

	for (unsigned int i = 0; i < siArr3.size(); i++)
	{
		p_tmp compare_elem = siArr3[i];

		for (unsigned int j = 0; j < siArr4.size(); j++)
		{
			if (compare_elem.i == siArr4[j].i && compare_elem.j == siArr4[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
	}

	count = 0;
	return count ;
}

/////////////////////////////////////////////////////////////////////////////////////////


int Judge::huosan( Table T, char line, char column)          //    判断“活三”，并返回棋盘中“活三”的个数
{
	sanArr1.clear();
	sanArr2.clear();
	sanArr3.clear();
	sanArr4.clear();

	int i, j , pi=22 , pj=22 , count = 0 ;
	for( i = 0 ; i < 15 ; i++ ){        //判断横向“活三”
		for( j = 0 ; j < 10 ; j++ ){
			if ((i != pi || j != pj + 1) && T.data[i][j] == 0 && T.data[i][j + 1] != anticolor && T.data[i][j + 2] != anticolor && T.data[i][j + 3] != anticolor && T.data[i][j + 4] != anticolor && T.data[i][j + 5] == 0 && (T.data[i][j + 1] + T.data[i][j + 2] + T.data[i][j + 3] + T.data[i][j + 4]) == 3 * color){
				//count ++ ;
				pi = i ; pj = j ;	

				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i, j + 1};
				p_tmp p2 = { i, j + 2};
				p_tmp p3 = { i, j + 3};
				p_tmp p4 = { i, j + 4};
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i][j + 1] != 0)   //忽略[0] 和 [5] ，因为必须是0
						sanArr1.push_back(p1);
					if (T.data[i][j + 2] != 0)
						sanArr1.push_back(p2);
					if (T.data[i][j + 3] != 0)
						sanArr1.push_back(p3);
					if (T.data[i][j + 4] != 0)
						sanArr1.push_back(p4);
				}
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < sanArr1.size(); i++)
	{
		//cout << "San Arr1  " << sanArr1[i].i << " " << sanArr1[i].j << endl;
	}

	//-----------------------------------------------------------------------------------
    
	pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 10 ; i++ ){          //判断纵向“活三”
		for( j = 0 ; j < 15 ; j++ ){
			if ((i != pi + 1 || j != pj) && T.data[i][j] == 0 && T.data[i + 1][j] != anticolor && T.data[i + 2][j] != anticolor && T.data[i + 3][j] != anticolor && T.data[i + 4][j] != anticolor && T.data[i + 5][j] == 0 && (T.data[i + 1][j] + T.data[i + 2][j] + T.data[i + 3][j] + T.data[i + 4][j]) == 3 * color){
				//count ++ ;
				pi = i ; pj = j ;

				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i + 1, j };
				p_tmp p2 = { i + 2, j };
				p_tmp p3 = { i + 3, j };
				p_tmp p4 = { i + 4, j };
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i + 1][j] != 0)
						sanArr2.push_back(p1);
					if (T.data[i + 2][j] != 0)
						sanArr2.push_back(p2);
					if (T.data[i + 3][j] != 0)
						sanArr2.push_back(p3);
					if (T.data[i + 4][j] != 0)
						sanArr2.push_back(p4);
				}
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < sanArr2.size(); i++)
	{
		//cout << "San Arr2  " << sanArr2[i].i << " " << sanArr2[i].j << endl;
	}

	//-----------------------------------------------------------------------------------

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 10 ; i++ ){              //判断“\”向“活三”
		for( j = 0 ; j < 10 ; j++ ){
			if ((i != pi + 1 || j != pj + 1) && T.data[i][j] == 0 && T.data[i + 1][j + 1] != anticolor && T.data[i + 2][j + 2] != anticolor && T.data[i + 3][j + 3] != anticolor && T.data[i + 4][j + 4] != anticolor && T.data[i + 5][j + 5] == 0 && (T.data[i + 1][j + 1] + T.data[i + 2][j + 2] + T.data[i + 3][j + 3] + T.data[i + 4][j + 4]) == 3 * color){
				//count ++ ;
				pi = i ; pj = j ;

				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i + 1, j + 1};
				p_tmp p2 = { i + 2, j + 2};
				p_tmp p3 = { i + 3, j + 3};
				p_tmp p4 = { i + 4, j + 4};
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i + 1][j + 1] != 0)
						sanArr3.push_back(p1);
					if (T.data[i + 2][j + 2] != 0)
						sanArr3.push_back(p2);
					if (T.data[i + 3][j + 3] != 0)
						sanArr3.push_back(p3);
					if (T.data[i + 4][j + 4] != 0)
						sanArr3.push_back(p4);
				}
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < sanArr3.size(); i++)
	{
		//cout << "San Arr3  " << sanArr3[i].i << " " << sanArr3[i].j << endl;
	}

	//-----------------------------------------------------------------------------------

    pi = 22 ; pj = 22 ;
	for( i = 0 ; i < 10 ; i++ ){              //判断“/”向“活三”
		for( j = 5 ; j < 15 ; j++ ){
			if ((i != pi + 1 || j != pj - 1) && T.data[i][j] == 0 && T.data[i + 1][j - 1] != anticolor && T.data[i + 2][j - 2] != anticolor && T.data[i + 3][j - 3] != anticolor && T.data[i + 4][j - 4] != anticolor && T.data[i + 5][j - 5] == 0 && (T.data[i + 1][j - 1] + T.data[i + 2][j - 2] + T.data[i + 3][j - 3] + T.data[i + 4][j - 4]) == 3 * color){
				//count ++ ;
				pi = i ; pj = j ;

				static p_tmp temp = { 22, 22 };
				p_tmp p1 = { i + 1, j - 1 };
				p_tmp p2 = { i + 2, j - 2 };
				p_tmp p3 = { i + 3, j - 3 };
				p_tmp p4 = { i + 4, j - 4 };
				//if (temp.i != p1.i && temp.j != p1.j)
				if (1)
				{
					if (T.data[i + 1][j - 1] != 0)
						sanArr4.push_back(p1);
					if (T.data[i + 2][j - 2] != 0)
						sanArr4.push_back(p2);
					if (T.data[i + 3][j - 3] != 0)
						sanArr4.push_back(p3);
					if (T.data[i + 4][j - 4] != 0)
						sanArr4.push_back(p4);
				}
				temp = p1;
			}
		}
	}
	//test
	for (unsigned int i = 0; i < sanArr4.size(); i++)
	{
		//cout << "San Arr4  " << sanArr4[i].i << " " << sanArr4[i].j << endl;
	}

	//-----------------------------------------------------------------------------------
	
	//judge three three forbidden
	for (unsigned int i = 0; i < sanArr1.size(); i++)
	{
		p_tmp compare_elem = sanArr1[i];

		for (unsigned int j = 0; j < sanArr2.size(); j++)
		{
			if (compare_elem.i == sanArr2[j].i && compare_elem.j == sanArr2[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
		for (unsigned int j = 0; j < sanArr3.size(); j++)
		{
			if (compare_elem.i == sanArr3[j].i && compare_elem.j == sanArr3[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
		for (unsigned int j = 0; j < sanArr4.size(); j++)
		{
			if (compare_elem.i == sanArr4[j].i && compare_elem.j == sanArr4[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
	}

	for (unsigned int i = 0; i < sanArr2.size(); i++)
	{
		p_tmp compare_elem = sanArr2[i];

		for (unsigned int j = 0; j < sanArr3.size(); j++)
		{
			if (compare_elem.i == sanArr3[j].i && compare_elem.j == sanArr3[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
		for (unsigned int j = 0; j < sanArr4.size(); j++)
		{
			if (compare_elem.i == sanArr4[j].i && compare_elem.j == sanArr4[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
	}

	for (unsigned int i = 0; i < sanArr3.size(); i++)
	{
		p_tmp compare_elem = sanArr3[i];

		for (unsigned int j = 0; j < sanArr4.size(); j++)
		{
			if (compare_elem.i == sanArr4[j].i && compare_elem.j == sanArr4[j].j)
				if (compare_elem.i == line && compare_elem.j == column)
					return 2;
		}
	}

	count = 0;
	return count ;
}

/////////////////////////////////////////////////////////////////////////////////////////









