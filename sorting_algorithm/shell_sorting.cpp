#include "common.h"
#include <cstdlib>
#include <cmath>
using namespace std;

void shell_pass(Sqlist *L, int d)
{
	int j,k;
	
	for (j=d+1; j<=L->length; j++)
	{
		L->R[0].key=L->R[j].key;
		k=j-d;
		while(k>0 && L->R[0].key < L->R[k].key)
		{
			L->R[k+d].key=L->R[k].key;
			k=k-d;		
		}
		
		L->R[k+d].key=L->R[0].key;		
	}
}

void shell_sort(Sqlist *L)
{
	int i=sqrt(L->length);
	while(i>0)
	{
		shell_pass(L, i);
		i=i/2;		
	}
	//shell_pass(L,1);
}

int main()
{
	Sqlist *L=(Sqlist *)malloc(sizeof(Sqlist));
	initial(L);
	print(L);
	shell_sort(L);
	print(L);
	return 0;	
}
