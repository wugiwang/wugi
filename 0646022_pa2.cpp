//============================================================================
// Name        : �L�X�|�D.cpp
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
	std::list<int>List1;//�ŧiList1�x�s�Ʀr(���a)
	std::list<string>List2;//List2�x�s�r��(�U���a�۪��r)
	std::ifstream fin;
	std::ofstream fout;

	fin.open(argv[1]);
	fout.open(argv[2]);

	int FirstPerson;
	fin >> FirstPerson; //��X�֥��}�l
	int PerNum = 0;
	while(fin >> PerNum)
	{
		if(PerNum < 0)
			break;
		List1.push_back(PerNum); //�N��y�X���Ʀr�s�iList1���᭱����Ū��t��
	}
	List2.resize(List1.size()); //List2���j�p�N�|��List1�ۦP

	string Space; //����
	string Text; //�x�s�C���r
	getline(fin, Space, '\n');
	do //�վ�List1�H�T�O�����w�}�l���H���Ĥ@�Ӧr
	{
		List1.push_back(List1.front());
		List1.pop_front();
	}while(List1.front() != FirstPerson);

	int c=0; //�����ܼ�,���ƶ��ɰw,�_�ưf�ɰw
	while(getline(fin, Text, '\n'))
	{
		std::list<string>::iterator ite2=List2.begin(); //List2�_�literator
		std::list<int>::iterator ite1=List1.begin(); //List1�_�literator
		int TextLength = Text.length(); //�S�o�ӷ|�����T����ĸ�
		if(c % 2 == 0) //���ɰw
		{
			for(int i=0; i<TextLength; i++)
			{
				if( List2.end() == ite2 ) //List����I,�}�lreverse
				{
					ite2= --List2.end();
					ite1= --List1.end();
					ite2--;
					ite1--; //��iterator�w��b���I�e�@�I
					*ite2 = *ite2 + Text[i];  //�r����J�̫�
					List2.reverse();
					List1.reverse();
					ite2++;
					ite1++;
				}
				else //�@�뱡�p
				{
					*ite2 =*ite2 + Text[i]; //�r����J�̫�
					ite2++;
					ite1++;
				}
			}
		}
		else //�f�ɰw
		{
			for(int i=0; i<TextLength; i++)
			{
				if( List2.end() == ite2 ) //list����I,�}�lreverse
				{
					ite2 = --List2.end();
					ite1 = --List1.end();
					ite2--;
					ite1--; //��iterator�w��b���I�e�@�I
					*ite2 = Text[i] + *ite2; //�r���q�e��J
					List2.reverse();
					List1.reverse();
					ite2++;
					ite1++;
				}
				else //�@�뱡�p
				{
					*ite2 = Text[i] + *ite2; //�r���q�e��J
					ite2++;
					ite1++;
				}
			}
		}
		ite2--;
		ite1--; //��j��̫�h�[��iterator����
		fout<< *ite1 << ' ' << *ite2 <<endl;; //�Q�Q�|�D���L���ܩM���X
		List2.erase(ite2);
		List1.erase(ite1); //�|�D�T�T

		//�̫�@�Ӧr���l���N����V
		if(Text[TextLength-1] != 'a' && Text[TextLength-1] != 'e' && Text[TextLength-1] != 'i'
				&& Text[TextLength-1] != 'o' && Text[TextLength-1] != 'u')
		{
			List2.reverse();
			List1.reverse();
			c++;
		}

	}

	fout << List1.front() << " " << List2.front() << endl; //�Ů�

	fin.close();
	fout.close();
	return 0;
}
