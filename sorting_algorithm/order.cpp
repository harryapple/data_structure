#include "common.h"

void print(Sqlist *L)
{
	int i;
	for (i=1; i<=L->length; i++)
	{
		cout<<L->R[i].key<<" ";		
	}
	cout<<endl;
}

void initial(Sqlist *L)
{
	L->length=7;
	L->R[0].key=0;
	L->R[1].key=5;
	L->R[2].key=1;
	L->R[3].key=3;
	L->R[4].key=5;
	L->R[5].key=9;
	L->R[6].key=7;
	L->R[7].key=2;		
}

void radix_init(RList *&head)
{
	int num[6]={1039, 2121, 355, 1382, 66, 118};
	//int num[2]={10, 1};
	int i;
	RList *p, *q;

	for (i=0; i<6; i++)
	{
		p=(RList *)malloc(sizeof(RList));
		p->next=NULL;
		p->value=num[i];
		
		if (head==NULL)
		{
			head=p;		
		}
		else
		{
			q->next=p;		
		}
		q=p;		
	}
	
}
