//============================================================================
// Name        : 印出魯蛇.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <fstream>
#include <string>

using namespace std;
using std::getline;
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]) {
	std::list<int>List1;//宣告List1儲存數字(玩家)
	std::list<string>List2;//List2儲存字串(各玩家喊的字)
	std::ifstream fin;
	std::ofstream fout;

	fin.open(argv[1]);
	fout.open(argv[2]);

	int FirstPerson;
	fin >> FirstPerson; //找出誰先開始
	int PerNum = 0;
	while(fin >> PerNum)
	{
		if(PerNum < 0)
			break;
		List1.push_back(PerNum); //將串流出的數字存進List1的後面直到讀到負數
	}
	List2.resize(List1.size()); //List2的大小將會跟List1相同

	string Space; //換行
	string Text; //儲存每行文字
	getline(fin, Space, '\n');
	do //調整List1以確保讓內定開始的人講第一個字
	{
		List1.push_back(List1.front());
		List1.pop_front();
	}while(List1.front() != FirstPerson);

	int c=0; //控制變數,偶數順時針,奇數逆時針
	while(getline(fin, Text, '\n'))
	{
		std::list<string>::iterator ite2=List2.begin(); //List2起始iterator
		std::list<int>::iterator ite1=List1.begin(); //List1起始iterator
		int TextLength = Text.length(); //沒這個會有黃三角驚嘆號
		if(c % 2 == 0) //順時針
		{
			for(int i=0; i<TextLength; i++)
			{
				if( List2.end() == ite2 ) //List到終點,開始reverse
				{
					ite2= --List2.end();
					ite1= --List1.end();
					ite2--;
					ite1--; //把iterator定位在終點前一點
					*ite2 = *ite2 + Text[i];  //字母放入最後
					List2.reverse();
					List1.reverse();
					ite2++;
					ite1++;
				}
				else //一般情況
				{
					*ite2 =*ite2 + Text[i]; //字母放入最後
					ite2++;
					ite1++;
				}
			}
		}
		else //逆時針
		{
			for(int i=0; i<TextLength; i++)
			{
				if( List2.end() == ite2 ) //list到終點,開始reverse
				{
					ite2 = --List2.end();
					ite1 = --List1.end();
					ite2--;
					ite1--; //把iterator定位在終點前一點
					*ite2 = Text[i] + *ite2; //字母從前放入
					List2.reverse();
					List1.reverse();
					ite2++;
					ite1++;
				}
				else //一般情況
				{
					*ite2 = Text[i] + *ite2; //字母從前放入
					ite2++;
					ite1++;
				}
			}
		}
		ite2--;
		ite1--; //把迴圈最後多加的iterator扣掉
		fout<< *ite1 << ' ' << *ite2 <<endl;; //想想魯蛇講過的話和號碼
		List2.erase(ite2);
		List1.erase(ite1); //魯蛇掰掰

		//最後一個字為子音就換方向
		if(Text[TextLength-1] != 'a' && Text[TextLength-1] != 'e' && Text[TextLength-1] != 'i'
				&& Text[TextLength-1] != 'o' && Text[TextLength-1] != 'u')
		{
			List2.reverse();
			List1.reverse();
			c++;
		}

	}

	fout << List1.front() << " " << List2.front() << endl; //溫拿

	fin.close();
	fout.close();
	return 0;
}
