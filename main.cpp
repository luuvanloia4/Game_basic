#include <iostream>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

int i,j,score;
bool born_bm;
//Khu vuc ham:

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

//Khu vuc class


class Map
{
	private:
	int dai = 29;
	int rong = 119;
	public:
		int m[29][119];
		void reset()
		{
			//Ve map = 0
			for(i=1;i<=dai-2;i++)
			{
				for(j=2;j<=rong-3;j++)
				{
					m[i][j]=0;
				}
			}
			//Ke vien map
			for(j=1;j<rong-1;j++)
			{
				m[0][j]=9;
				m[dai-1][j]=9;
			}
			for(i=0;i<dai;i++)
			{
				m[i][1]=9;
				m[i][rong-2]=9;
			}
		}
		void show()
		{
		    char ex=3;
			for(i=0;i<dai;i++)
			{
				for(j=0;j<rong;j++)
				{
					//Ve Ran:
					if(m[i][j]==1)
					{
						gotoxy(j,i);
						cout << ex;
					}
					if(m[i][j]==2)
					{
						gotoxy(j,i);
						cout << "@";
					}
					//Ve Moi:
					if(m[i][j]==3)
					{
						gotoxy(j,i);
						cout << "A";
					}
					//Ve Big_moi:
					if(m[i][j]==4)
                    {
                        gotoxy(j,i);
                        cout << "B";
                    }
					//Ve vien:
					if(m[i][j]==9)
					{
						gotoxy(j,i);
						cout << "+";
					}
				}
			}
		}
		void test()
		{
			for(i=0;i<dai;i++)
			{
				for(j=0;j<rong;j++)
				{
					cout << m[i][j];
				}
				cout << endl;
			}

		}
		int getd()
		{
			return dai;
		}
		int getr()
		{
			return rong;
		}

};
//Khai bao doi tuong map1::Map
Map map1;

class Moi
{
	private:
		int a;
		int b;
	public:
		void random()
		{
        a=0;
        b=0;
			while
			(
				(a <=0)||(a >= map1.getr()-1)||
				(b <= 0)||(b >= map1.getd()-1)||
				(map1.m[b][a]==1)
			)
			{
				srand(time(NULL));
				a = 2*(rand() % (map1.getr()/2));
				b = (rand() % map1.getd())-1;
			}
        }
        void random_1()
		{
			if
			(
				(a <=0)||(a >= map1.getr()-1)||
				(b <= 0)||(b >= map1.getd()-1)||
				(map1.m[b][a]==1)
			)
			{
				srand(time(NULL));
				a = 2*(rand() % (map1.getr()/2));
				b = (rand() % map1.getd())-1;
			}
        }

		void show()
		{
			map1.m[b][a]=3;
		}
		int getx()
		{
		    return a;
		}
		int gety()
		{
            return b;
		}
};
//Khai bao doi tuong moi1::Moi
Moi moi1;
class Big_moi
{
private:
    struct vi_tri
    {
        int doc,ngang;
    };
    struct vi_tri vt[2][2];
public:
    void born()
    {
        vt[0][0].doc=0;
        vt[0][0].ngang=0;
        while
			(
				(vt[0][0].ngang <=0)||(vt[0][0].ngang >= map1.getr()-3)||
				(vt[0][0].doc <= 0)||(vt[0][0].doc >= map1.getd()-3)||
				(map1.m[vt[0][0].doc][vt[0][0].ngang]==1)||
                (map1.m[vt[0][0].doc][vt[0][0].ngang]==2)||
                (map1.m[vt[0][0].doc][vt[0][0].ngang]==3)
			)
			{
				srand(time(NULL));
				vt[0][0].ngang = 2*(rand() % (map1.getr()/2));
				vt[0][0].doc = (rand() % map1.getd())-3;
			}
			vt[0][1].doc = vt[0][0].doc;
			vt[0][1].ngang = vt[0][0].ngang + 2;
			vt[1][0].doc = vt[0][0].doc + 1;
			vt[1][0].ngang = vt[0][0].ngang;
			vt[1][1].doc = vt[1][0].doc;
			vt[1][1].ngang = vt[0][1].ngang;
			born_bm=true;
    }
    void show()
    {
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
            {
                map1.m[vt[i][j].doc][vt[i][j].ngang]=4;
            }
        }
    }
};
//Khai bao doi tuong bm::Big_moi:
Big_moi bm;
class Ran
{
	private:
		int do_dai;
		int huong;
		bool chay;
		struct d
		{
			int x,y;
		};
		struct d dot[29*117];

	public:
		void start()
		{
			//Khoi tao gia tri cho Ran
			do_dai=20;
			i=0;
			for(j=do_dai*2;j>0;j-=2)
            {
                dot[i].x = j;
                dot[i].y = 1;
                i++;
            }
			huong=2;
			chay=true;
		}

		void show()
		{
			for(i=1;i<do_dai;i++)
			{
				map1.m[dot[i].y][dot[i].x]=1;
			}
			map1.m[dot[0].y][dot[0].x]=2;
		}
		//Khu vuc ham lien quan den kbhit
		void right_click()
		{
			if (huong != 4) huong = 2;
		}
		void left_click()
		{
			if(huong != 2) huong = 4;
		}
		void up_click()
		{
			if(huong != 3) huong = 1;
		}
		void down_click()
		{
			if(huong != 1) huong = 3;
		}
		void ran_kbhit()
		{
			if(kbhit())
			{
				int phim = getch();
				switch(phim)
				{
					case 77:
						{
							right_click();
							break;
						}
					case 72:
						{
							up_click();
							break;
						}
					case 75:
						{
							left_click();
							break;
						}
					case 80:
						{
							down_click();
							break;
						}
				}
			}
		}
		//Khu vuc ham lien quan den di chuyen Ran
		void run()
		{
			while(chay)
			{
				struct d dottg;
				//Cac dot nam trong khoang (0;do_dai-1) lan luot lay data tu cac dot trc no:
				dottg=dot[do_dai-1];
				for(i=do_dai-1;i>0;i--)
				{
					dot[i]=dot[i-1];
				}
				ran_kbhit();
				//Dot dau tien dich chuyen theo bien huong:
				switch (huong)
				{
					case 1:
						{
							dot[0].y-=1;
							break;
						}
					case 2:
						{
							dot[0].x+=2;
							break;
						}
					case 3:
						{
							dot[0].y+=1;
							break;
						}
					case 4:
						{
							dot[0].x-=2;
							break;
						}
				}
				//Dot cuoi cung trong 2 truong hop:
				if(
                    (dot[0].x <1)||(dot[0].x>(map1.getr()-3))||
                    (dot[0].y==0)||(dot[0].y >= (map1.getd()-1))||
                    (map1.m[dot[0].y][dot[0].x] == 1)
                    )
				{
					break;
					chay=false;
				}
				if(map1.m[dot[0].y][dot[0].x] == 3)
				{
					do_dai+=1;
					dot[do_dai-1]=dottg;
					moi1.random();
					moi1.show();
				}
				else
                {
                    moi1.show();
                }
                //An Big_moi:
                bool an = false;
                if(map1.m[dot[0].y][dot[0].x] == 4)
                {
                    an=true;
                }
				//Ve Ran ra Map:
				show();
				map1.show();
				Sleep(100);
				system("cls");
				if(an)
                {
					do_dai+=3;
					dot[do_dai-3]=dottg;
					dot[do_dai-2]=dottg;
					dot[do_dai-1]=dottg;
					map1.reset();
					born_bm = false;
				}
				else
                {
                    map1.reset();
                }
				//Hien thi diem:
				gotoxy(2,map1.getd());
				cout << "Score: " << do_dai;
				if(
                    (do_dai>10)&&(do_dai%5==0)&&(!born_bm)
                    )
                {
                    bm.born();
                }
                if(born_bm)
                {
                    bm.show();
                }

                show();
                moi1.show();
				map1.show();
				ran_kbhit();
				system("cls");
			}
			//Khi vong while ket thuc (nguoi choi thua):
			for(i=1;i<=15;i++) cout << endl;
			cout << setw(58) << "So diem: " << setw(5) << do_dai << endl;
			cout << setw(60) << "NGU VL!!!" << endl;
			getch();
		}

};
//Khai bao doi tuong ran1::Ran
Ran ran1;
//Than chuong trinh
int main()
{
    Nocursortype();
    system("cls");
    bool chay = true;
    while (chay)
   {
        map1.reset();
        ran1.start();
        moi1.random();
        moi1.show();
        map1.show();
        ran1.run();
        for(i=10;i>=0;i--)
        {
            system("cls");
            gotoxy(40,14);
            cout << "Press any key to restart!!! (" << i << ")";
            int phim = 0;

            for(j=1;j<=10;j++)
            {
                if(kbhit())
                {
                    phim = getch();
                }
                 if(phim != 0)
                {
                    //Thoat khoi vong lap hien tai:
                    break;
                }
                Sleep(100);
            }
            if(phim != 0)
                {
                    break;
                }
            if(i == 0)
            {
                chay = false;
            }

        }
   }
	return 0;
}












