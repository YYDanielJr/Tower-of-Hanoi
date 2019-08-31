//汉诺塔 Tower of Hanoi
//Producted by DYYSB 
//Written in C++
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdio>

using namespace std;

//========================================================================

void startscreen();
void choosescreen();
bool movement(int, int);
void graphic(char);
void process();
void makelog(int, int, double);
int how_many_numbers(int);
void viewlog();
void datascreen();
void delete_data(int);

//========================================================================

int hanoi[4][65];

//========================================================================

int main()
{
	system("cls");
	startscreen();
	int choice;
	while (1)
	{
		system("cls");
		choosescreen();
		cin >> choice;
		switch(choice)
		{
	    	case 1: process(); break;
			case 2: viewlog(); break;
	    	case 3: return 0; 
	    	default: cout << "Illegal choice. Please choose again." << endl;
		}
	}
	return 0;
}

//=========================================================================

void startscreen()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                     Tower of Hanoi                        |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                   Producted by DYYSB                      |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                     Written in C++                        |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                                                           |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	system("pause");
}

void choosescreen()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                      < 1.开始游戏 >                       |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                    < 2.查看游戏记录 >                     |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                        < 3.退出 >                         |" << endl;
	cout << "|                                                           |" << endl;
	cout << "|                                                           |" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << endl << "你想做什么？" << endl;
}

void datascreen()
{
	cout << "1、按照移动盘数单独查找" << endl;
	cout << "2、删除一条游戏记录" << endl;
	cout << "3、删除所有游戏记录" << endl;
	cout << "你想做什么？" << endl;
}

bool movement(int aim, int to)		//hanoi[x][y] 代表的是 在第x根柱子上的第y个盘，其值为盘的大小。 
{
	if (hanoi[aim][0] == 0)
	{
		cout << "非法移动。" << endl;
		return false;
	}
	else if (hanoi[to][0] == 0)
	{
		hanoi[to][hanoi[to][0] + 1] = hanoi[aim][hanoi[aim][0]];
		hanoi[aim][hanoi[aim][0]] = 0;
		hanoi[aim][0]--;
		hanoi[to][0]++;
		cout << endl;
		return true;
	}
	else if (hanoi[to][hanoi[to][0]] > hanoi[aim][hanoi[aim][0]])
	{
		hanoi[to][hanoi[to][0] + 1] = hanoi[aim][hanoi[aim][0]];
		hanoi[aim][hanoi[aim][0]] = 0;
		hanoi[aim][0]--;
		hanoi[to][0]++;
		cout << endl;
		return true;
	}
	else
	{
		cout << "非法移动。" << endl;
		return false;
	}
}

void graphic(char a)
{
	int i, j, k;
	for (j = 10; j >= 1; j--)
	{
		for (i = 1; i <= 3; i++)
		{
			int temp = hanoi[i][j];
			for (k = 0; k < temp; k++)
				cout << a;
			for (k = 0; k < 10 - temp; k++)
				cout << " ";
		}
		cout << endl;
	}
}

void makelog(int disk, int step, double time)
{
	fstream log;
	log.open("data.dyy", ios::out | ios::app);
	if (!log)
	{
        ofstream create("data.dyy");
		create.close();
	}
	log << ' ' << disk << ' ' << step << ' ' << time;
	log.close();
}

void process()
{
	char chara;
	system("cls");
	int aim, to, usernum;
	cout << "你想移动几个盘子？" << endl;
    cin >> usernum;
	cout << "请输入你想用于图形输出的半角字符：" << endl;
	cin >> chara;
    hanoi[1][0] = usernum;
	hanoi[2][0] = 0;
	hanoi[3][0] = 0;
    int i, j, num, x = 0;

    for (i = 1; i <= 3; i++)
    	for (j = 1; j <= 64; j++)
    		hanoi[i][j] = 0;

	for (i = 1, num = usernum; i <= usernum; i++, num--)
    	hanoi[1][i] = num;

	long dur;
	clock_t start, finish;

	system("cls");
    graphic(chara);
	start = clock();
	
    while (hanoi[1][0] != 0 || hanoi[2][0] != 0)
    {
    	cin >> aim >> to;
    	if (movement(aim, to))
    	{
    		system("cls");
    		graphic(chara);
			x++;
    	}
    }
	finish = clock();
	dur = (finish - start);
	cout << "成功!" << endl;
    cout << "你在" << x << "步内完成了操作。" << endl;
	cout << "你在" << (double)dur / 1000 << "秒内完成了操作。" << endl;
	makelog(usernum, x, (double)dur / 1000);
    system("pause");
}

void viewlog()
{
	system("cls");
	ifstream fin("data.dyy");
	if (!fin.is_open())
	{
		cout << "没有可用的游戏数据。" << endl;
		system("pause");
		return;
	}

	int steps[1000], disks[1000];
	double times[1000];
	int count = 0;
	for (int i = 1; !fin.eof(); i++)
	{
		fin >> disks[i] >> steps[i] >> times[i];
		count++;
	}
	cout << "你的游戏数据：" << endl;
	cout << "    盘子：" << "      " << "步数：" << "      " << "时间：" << endl;
	for (int i = 1; i <= count; i++)
	{
		cout << i << ".";
		for (int j = 0; j < 3 - how_many_numbers(i); j++)
			cout << ' ';
		cout << disks[i];
		for (int j = 0; j < 12 - how_many_numbers(disks[i]); j++)
			cout << ' ';
		cout << steps[i];
        for (int j = 0; j < 12 - how_many_numbers(steps[i]); j++)
			cout << ' ';
		cout << times[i] << "s" << endl;
	}
	cout << endl << endl;
	fin.close();
	datascreen();
	int choice;

	while (1)
	{
		cin >> choice;
		if (choice == 1)
		{
			datascreen();
		}
		else if (choice == 2)
		{
			int b;
			cout << "你想要删除哪一行数据？" << endl;
			while (1)
			{
                cin >> b;
		    	if (b <= count)
			    {
				    delete_data(b);
    			    datascreen();
	    		}
		    	else
    			{
	    			cout << "该行不存在。请重新输入：" << endl;
    			}
			}
			
		}
		else if (choice == 3)
		{
			char a;
			cout << "确定删除数据文件？这不可恢复。[y/n]" << endl;
			cin >> a;
			if (a == 'y')
				remove("data.dyy");
			return;
		}
	    else
			cout << "无法识别您输入的序号。请重新输入一个在列表内的序号：" << endl;	    
	}
	
}

void delete_data(int line)
{
	ifstream read("data.dyy");
	int steps[1000] = { 0 }, disks[1000] = { 0 };
	double times[1000] = { 0 };
	int count = 0;
	for (int i = 1; !read.eof(); i++)
	{
		read >> disks[i] >> steps[i] >> times[i];
		count++;
	}

	for (int i = line; i <= count; i++)
	{
		disks[i] = disks[i + 1];
		steps[i] = steps[i + 1];
		times[i] = times[i + 1];
	}
	read.close();
	remove("data.dyy");
	for (int i = 1; i <= count - 1; i++)
	{
		makelog(disks[i], steps[i], times[i]);
	}
}

int how_many_numbers(int x)
{
	int i = 1;
	while (x >= 10)
	{
		x /= 10;
		i++;
	}
	return i;
}