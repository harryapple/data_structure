#include "common.h"

//获得从各位开始数，第几位的数字
int ord(int num, int bit)
{
	int i, factor=1;
	int result;
	for (i=0; i<bit; i++)
		factor=factor*10;
	result=num%factor;
	result=result/(factor/10);
	return result;
			
}

void radix_sort(RList *&head)
{
	RList *p, *f[RADIX], *e[RADIX];
	int i,j,k;
	int flag=0;

	for (i=0; i<BIT_KEY; i++)
	{
		p=head;
		flag=0;

		for (j=0; j<RADIX; j++)
		{
			f[j]=NULL;
			e[j]=NULL;		
		}

		while (p!=NULL)
		{
			k=ord(p->value, (i+1));
			if (k!=0)
				flag=1;

			if (f[k]==NULL)
			{
				f[k]=p;		
			}
			else
			{
				e[k]->next=p;		
			}
			e[k]=p;
			p=p->next;
		}

		for (j=0; j<RADIX; j++)
		{
			if (f[j]!=NULL)
			{
				if (p==NULL)
				{
					head=f[j];
					p=e[j];		
				}
				else
				{
					p->next=f[j];
					p=e[j];		
				}		
			}
		}

		p->next=NULL;

		if (flag==0)
			break;
	}
}

void order(RList *head)
{
	while(head!=NULL)
	{
		cout<<head->value<<" ";
		head=head->next;		
	}
	cout<<endl;		
}

int main()
{
	RList *head=NULL;
	radix_init(head);
	order(head);
	radix_sort(head);
	order(head);	
	return 0;	
}
