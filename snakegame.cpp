#include<iostream>
#include<windows.h>
#include<conio.h>
int height=25;
int width=100;
int gameover=0,score=0,choice;
short fcount;
using namespace std;
class SnakeGame
{	
    int x,y,fx,fy;
    char dir;
	char playername[50];
	struct node
	{
		int nx,ny;
		struct node *next;
		struct node *back;
	};
	struct node *head=NULL;
	void gotoxy(int x,int y)
	{
		COORD pos={x,y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}
	void Name_Score()
	{
		gotoxy(0,26);
		textcolour(10);
		cout<<"MADE BY:MARYAM_AKBAR";
		textcolour(6);
		gotoxy(0,28);
		cout<<playername<<"'s SCORE = "<<score*100;
	}
	void textcolour(int k)
	{
		HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,k);	
	}	
	public:	
	SnakeGame()
	{
		dir='n';
	}
	void change_dir(char direction)
	{
	dir=direction;
    }
	void walls()
	{
		textcolour(8);
			for(int i=0;i<=width;i++)
		{
			gotoxy(i,0);
			cout<<"|";
			gotoxy(i,height);
			cout<<"|";
		}
	     for(int i=0;i<=height;i++)
		{
			gotoxy(0,i);
			cout<<"|";
			gotoxy(width,i);
			cout<<"|";
		}
	}	
	void snake_pos()
	{
		score=0;
		gameover=0;
		head=new node;
		head->nx=width/2;
		head->ny=height/2;
		head->next=NULL;
		head->back=NULL;
		x=width/2;
		y=height/2;
	}
	void food_pos()
	{
		label1:
		fx=rand()%width;
		if(fx==0||fx==width)
		goto label1;
		label2:
		fy=rand()%height;
		if(fy==0||fy==height)
		goto label2;
	}
	void snake_body(struct node *h)
	{
		textcolour(4);
		struct node *ptr=h;
		while(ptr!=NULL)
		{
			gotoxy(ptr->nx,ptr->ny);
			cout<<"@";
			ptr=ptr->next;
		}
	}
	void remove_snake(struct node *h)
	{
		struct node *ptr=h;
		while(ptr!=NULL)
		{
			gotoxy(ptr->nx,ptr->ny);
			cout<<" ";
			ptr=ptr->next;
		}
	}
	void gen_food()
	{
	    snake_body(head);
		gotoxy(fx,fy);
		textcolour(3);
		cout<<"o";
		Sleep(70);
		remove_snake(head);
	}
	void play()
	{
		move_snake();
		int h;
		char ch;
		if(kbhit())
		{	
			ch=getch();
			h=ch;
			switch(h)
			{
					case 72:
					{
						change_dir('u');
						break;
					}
				    case 75:
					{
      					change_dir('l');
						break;
					}
				case 80:
					{
						change_dir('d');
						break;
					}
				case 77:
					{
						change_dir('r');
						break;
					}
			}
		}
	}
	
	void box(int m1,int n1,int m2,int n2)
	{
			for(int i=m1;i<=m2;i++)
		{
			gotoxy(i,n1);
			cout<<"//";
			gotoxy(i,n2);
			cout<<"//";
		}
		
		for(int i=n1;i<=n2;i++)
		{
			gotoxy(m1,i);
			cout<<"//";
			gotoxy(m2,i);
			cout<<"//";
		}	
	}
	void welcome()
	{
		textcolour(3);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		textcolour(10);
		gotoxy(width/2-20,height/2-10);
		cout<<"*** WELCOME TO SNAKE GAME BY MARYAM AKBAR *** ";
		textcolour(8);
		gotoxy(width/2-13,height/2);
		cout<<"ENTER YOUR NAME: ";
		cin>>playername;
		system("cls");
    }
    char replay()
	{
		char c;
		gotoxy(width/2-5,height/2-4);
		cout<<"GAME OVER \n";
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		
		textcolour(1);
		gotoxy(width/2-15,height/2-2);
		cout<<playername<<" You Scored : "<<score*100;
		textcolour(6);
		gotoxy(width/2-15,height/2+4);
		cout<<"Want To Play Again ? (Y/N) : ";
		cin>>c;
		system("cls");
		return c;
		
	}
	void move_snake()
	{
		switch(dir)
		{
		
		case 'u':
			{
				y--;
				break;
			}
		case 'd':
			{
				y++;
				break;
			}
		case 'l':
			{
				x--;
				break;
			}
		case 'r':
			{
				x++;
				break;
			}
		}
	}
	void dolist(struct node *h,int pp,int qq)
	{
		struct node *ptr,*prev;
		ptr=h;
		prev=h;
	
		 while(ptr->next!=NULL)
		{
			prev=ptr;
			ptr=ptr->next;
		}
		while(prev!=h)
		{
			ptr->nx=prev->nx;
			ptr->ny=prev->ny;
			prev=prev->back;
			ptr=ptr->back;
		}
		ptr->nx=prev->nx;
		ptr->ny=prev->ny;
		prev->nx=pp;
		prev->ny=qq;
	}
	void drawagain()
	{
		if(x==width)
		{
			x=1;
		}
		if(x==0)
		{
			x=width-1;
		}
		if(y==0)
		{
			y=height-1;
		}
		if(y==height)
		{
			y=1;
		}
	}
	void checkfcount()
	{
		if(fcount==0)
		{
			gameover=1;
		}
	}
	void snake_collided()
	{
			if(x==width||x==0)
			gameover=1;	
			if(y==height||y==0)
			gameover=1;
		   drawagain();
		
		struct node *h;
		h=head->next;
		while(h!=NULL)
 		{
			if(x==h->nx&&y==h->ny)
			{
				gameover=1;
				break;
			}
			h=h->next;
		}
	
		if(x==fx&&y==fy)
		{
				fcount--;
				checkfcount();
			    struct node *t,*ptr,*prev;
			    t=new node;
			    t->next=NULL;
			    t->back=NULL;
				ptr=head;
				prev=head;
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;		
				}
				ptr->next=t;
				t->back=ptr;
				food_pos();
			score++;
			Name_Score();
		}
			dolist(head,x,y);
		}
	void Game()
	{
		char ch;
		welcome();
		do{
			walls();
			Name_Score();
			snake_pos();
			food_pos();
			while(gameover!=1)
			{
				gen_food();
				play();
				snake_collided();
			}
			ch=replay();
			}while(ch=='y'||ch=='Y');
	}
};
int main()
{
	SnakeGame snake;
	snake.Game();
	system("exit");
}

