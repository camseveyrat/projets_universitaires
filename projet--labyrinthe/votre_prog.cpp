#include <ncurses.h>
#include "labIO.h"
#include <iostream>
#include <fstream>

using namespace std;

void init(Case & c)
{
	c.N=c.S=c.E=c.W=false;
	c.etat=false;
}

void init(laby & L, int p, int q)
{
	L.p=p; L.q=q;
	L.tab=new Case *[p];
	for(int i=0;i<p;i++) L.tab[i]=new Case[q];
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<q;j++) init(L.tab[i][j]);
	}
}

laby *lire_Laby(const char  *filename)
{
	ifstream my_cin;

	my_cin.open(filename);

	laby *L;
	L=new laby;
	my_cin>>(*L).p>>(*L).q;
	init((*L),(*L).p,(*L).q);

	for(int i=0;i<(*L).p;i++)
	{
		for(int j=0;j<(*L).q;j++)
		{
			my_cin>>(*L).tab[i][j].W>>(*L).tab[i][j].N>>(*L).tab[i][j].S>>(*L).tab[i][j].E;
		}
	}
	return L;
}

void ecrire_Laby(const char *fn) 
{
	laby *L;
	L=new laby;
	ofstream my_cout;
	my_cout.open(fn);
	my_cout<<"bonjour";
	for(int i=0;i<(*L).p;i++)
	{
		for(int j=0;j<(*L).q;j++)
		{ 
			my_cout<<(*L).tab[i][j].W<<(*L).tab[i][j].N<<(*L).tab[i][j].S<<(*L).tab[i][j].E;
		}
		
	}
	
}

void deplacement(laby &L)
{
	int i=0; int j=0;
	Mark_Case(i,j);
	L.tab[i][j].etat=true;
	while(true)
	{
		int d=LireCommande();
		if(d==9)
		{
			if(j>0 && L.tab[i][j].W==true)
			{
				j-=1;
				if(L.tab[i][j].etat==false)
				{
					Mark_Case(i,j);
					L.tab[i][j].etat=true;
				}
				else
				{
					UMark_Case(i,j);
					L.tab[i][j].etat=false;
				}
			}
		}
		if(d==6)
		{
			if(i<L.p-1 && L.tab[i][j].S==true)
			{
				i+=1;
				if(L.tab[i][j].etat==false)
				{
					Mark_Case(i,j);
					L.tab[i][j].etat=true;
				}
				else
				{
					UMark_Case(i,j);
					L.tab[i][j].etat=false;
				}
			}
		}
		if(d==3)
		{
			if(j<L.q-1 && L.tab[i][j].E==true)
			{
				j+=1;
				if(L.tab[i][j].etat==false)
				{
					Mark_Case(i,j);
					L.tab[i][j].etat=true;
				}
				else
				{
					UMark_Case(i,j);
					L.tab[i][j].etat=false;
				}
			}
		}
		if(d==12)
		{
			if(i>0 && L.tab[i][j].N==true)
			{
				i-=1;
				if(L.tab[i][j].etat==false)
				{
					Mark_Case(i,j);
					L.tab[i][j].etat=true;
				}
				else
				{
					UMark_Case(i,j);
					L.tab[i][j].etat=false;
				}
			}
		}
		if(d==-1)
		{
			break;
		}
		
	}
}

int main()
{
    laby *L1=lire_Laby("laby.txt");
    InitCurses(); //créer l'interface
	Show_Lab(*L1);
    int ch = wgetch(stdscr) ; 
    deplacement(*L1);
    EndCurses();
    ecrire_Laby("laby2.txt");
   
    
}
