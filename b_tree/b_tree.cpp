#include <iostream>
#include <ctime>
#include <queue>
#include <cstdlib>

using namespace std;

//定义B-tree的阶数，一般是根据磁盘磁盘页的大小而定
#define M 5

//节点数据结构的定义
typedef struct BTNode
{
	int keynum;             //节点信息的数量，不包含key[0]节点
	struct BTNode *parent;  //父节点
	int key[M+1];           //节点信息数组，第一个节点没用。
	struct BTNode *ptr[M+1];//子节点信息		
}BTNode;

//B-tree的搜索函数
//参数T：B-Tree的根节点，K：要查找的信息
//p：如果找到K，则p为所在的节点，如果没有找，则p为最后一次查找的节点
//p传的是指针的引用
//返回值为0，为未找到；为其他值，为在节点中的位置
int BT_search(BTNode *T, int K, BTNode *&p)
{
	BTNode *q;
	int i;

	p=q=T;
	
	while (q!=NULL)
	{
		p=q;
		
		//在节点内查找，此处可以用二分法查找
		for (i=1; i<=q->keynum; i++)
		{
			if (q->key[i]==K)
			{
				cout<<"find it! :"<<K<<endl;
				return i;
			}
			else if (K > q->key[i])
				continue;
			else
				break;		
		}

		q=q->ptr[i-1];

	}
	return 0;
}

//分裂函数，当一个节点中信息数过多
//需要分裂节点
// 参数p为传引用
//拆分后，分为p和返回值q两个节点
BTNode *split(BTNode *&p)
{
	BTNode *q;
	int mid;

	int j, k;

	q=(BTNode *)malloc(sizeof(BTNode));
	mid=(M+1)/2;
	q->ptr[0]=p->ptr[mid];
	if (q->ptr[0] != NULL)
		q->ptr[0]->parent=q;

	// 从mid位置拆分，mid值上调到父节点
	// mid后为一部分，mid前为一部分
	for (j=1, k=mid+1; k<=M; k++)
	{
		q->key[j]=p->key[k];
		q->ptr[j]=p->ptr[k];
		if (q->ptr[j] != NULL)
			q->ptr[j]->parent=q; //注意此处拆分后，要修改父节点信息。
		j++;
				
	}

	q->keynum=M-mid;
	p->keynum=mid-1;
	q->parent=p->parent;

	return q;
}


//插入节点，参数T为父节点，K为插入信息
void insert_BTree(BTNode *&T, int K)
{
	int i;
	BTNode *p=NULL, *s1=NULL, *s2=NULL;
	if (!BT_search(T, K, p))
	{
		while (p!=NULL)
		{
			p->key[0]=K;
			for (i=p->keynum; K<p->key[i]; i--)
			{
				p->key[i+1]=p->key[i];
				p->ptr[i+1]=p->ptr[i];
			}
			i+=1;
			p->key[i]=K;
			p->ptr[i]=s2;
			p->ptr[i-1]=s1;
			
			if (++(p->keynum) < M)
				break;
			else
			{
				s2=split(p);
				s1=p;
				K=p->key[p->keynum+1];
				p=p->parent;		
			}

			if (p==NULL)
			{
				p=(BTNode *)malloc(sizeof(BTNode));
				p->keynum=1;
				p->key[1]=K;
				p->ptr[0]=s1;
				s1->parent=p;
				p->ptr[1]=s2;
				s2->parent=p;
				p->parent=NULL;
				T=p;
				break;		
			}
		}
	}
}

// 深度遍历函数，用于检验b-tree正确性。
void mid_order(BTNode *T)
{
	cout<<"The tree is: "<<endl;
	int i;
	queue<BTNode *> q;
	BTNode *p=T;
	
	if (p!=NULL)
	{
		q.push(p);
		while (!q.empty())
		{
			p=q.front();
			
			for (i=0; i<=p->keynum; i++)
			{
				if (p->ptr[i] != NULL)
					q.push(p->ptr[i]);
				
				if (i!=p->keynum)
					cout<<p->key[i+1]<<" ";		
			}

			q.pop();
			cout<<endl;
		}
	}
}

int MoveKey(BTNode *&p)
{
	int k, j;
	BTNode *f = p->parent, *b;
	for (j=0; f->ptr[j] != p; j++);
	
	if (j>0) //说明有左兄弟节点
	{
		b=f->ptr[j-1];
		if (b->keynum>(M-1)/2)
		{
			for (k=p->keynum; k>=0; k--)
			{
				p->key[k+1]=p->key[k];
				p->ptr[k+1]=p->ptr[k];		
			}

			p->key[1]=f->key[j];
			f->key[j]=b->key[b->keynum];

			p->ptr[0]=b->ptr[b->keynum];
			if (p->ptr[0] != NULL)
				p->ptr[0]->parent = p;

			p->keynum++;
			b->keynum--;

			return (1);
		}
				
	}

	if (j<f->keynum)
	{
		b=f->ptr[j+1];
		if (b->keynum > (M-1)/2)
		{
			p->key[p->keynum+1]=f->key[j+1];
			f->key[j+1]=b->key[1];
			p->ptr[p->keynum+1] = b->ptr[0];
			if (p->ptr[p->keynum+1] != NULL)
				p->ptr[p->keynum+1]->parent=p;


			for (k=0; k<b->keynum; k++)
			{
				b->key[k]=b->key[k+1];
				b->ptr[k]=b->ptr[k+1];
			}

			p->keynum++;
			b->keynum--;
			
			return (1);
		}
	}
	return 0;
}

BTNode *MergeNode(BTNode *&p)
{
	BTNode *b, *f=p->parent;
	int j, k;
	for (j=0; f->ptr[j]!=p; j++);
	
	if (j>0)
	{
		b=f->ptr[j-1];		
	}
	else
	{
		b=p;
		p=f->ptr[j+1];		
	}

	b->key[++b->keynum]=f->key[j+1];
	b->ptr[b->keynum]=p->ptr[0];

	for (k=1; k<=p->keynum; k++)
	{
		b->key[++b->keynum]=p->key[k];
		b->ptr[b->keynum]=p->ptr[k];		
	}

	free(p);

	for (k=j+2; k<=f->keynum; k++)
	{
		f->key[k-1]=f->key[k];
		f->ptr[k-1]=f->ptr[k];		
	}

	f->keynum--;

	return b;
}

void DeleteBTNode(BTNode *&T, int K)
{
	BTNode *p, *S;
	int j, n;
	j=BT_search(T, K, p);
	
	if (j==0)
	{
		cout<<K<<" is not one node of the tree"<<endl;
		return;		
	}

	if (p->ptr[j-1])
	{
		S=p->ptr[j-1];
		while (S->ptr[S->keynum])
			S=S->ptr[S->keynum];
		
		p->key[j]=S->key[S->keynum];
		p=S;
		j=S->keynum;		
	}

	for (n=j+1; n<=p->keynum; n++)
	{
		p->key[n-1]=p->key[n];
		p->ptr[n-1]=p->ptr[n];		
	}

	p->keynum--;

	while (p->keynum < (M-1)/2 && p->parent)
	{
		if (!MoveKey(p))
			p=MergeNode(p);
		p=p->parent;		
	}

	if (p==T && T->keynum==0)
	{
		if (T->ptr[0])
		{
			T=T->ptr[0];
			free(p);
		}
	}
}

void menu()
{
	cout<<endl;
	cout<<"************menu***************"<<endl;
	cout<<"**  "<<"(i): input a value;"<<endl;
	cout<<"**  "<<"(d): delete a value;"<<endl;
	cout<<"**  "<<"(q): quit"<<endl;
	cout<<"*******************************"<<endl;
	cout<<endl;		
}

int main()
{
	int n;
	BTNode *T=NULL;
	BTNode *p;
	menu();
	char choose;
	while( cin>>choose && choose!='q')
	{
		switch(choose)
		{
			case 'i':
				cin>>n;
				if (T==NULL)
				{
					T=(BTNode *)malloc(sizeof(BTNode));
					T->keynum=1;
					T->key[1]=n;
					T->ptr[0]=NULL;
					T->ptr[1]=NULL;
					T->parent=NULL;		
				}
				else
				{
					insert_BTree(T, n);		
				}
				mid_order(T);
				break;
			case 'd':
				cin>>n;
				DeleteBTNode(T, n);
				mid_order(T);
				break;
			default:
				menu();
		}
	}
	/*
	while (cin>>n)
	{
		if (T==NULL)
		{
			T=(BTNode *)malloc(sizeof(BTNode));
			T->keynum=1;
			T->key[1]=n;
			T->ptr[0]=NULL;
			T->ptr[1]=NULL;
			T->parent=NULL;		
		}

		else
		{
			insert_BTree(T, n);		
		}
	}
	*/
}

/*
int main()
{
	int n;
	cin>>n;
	
	int i;
	int num;
	
	BTNode *T=NULL;
	BTNode *p;
	
	for (i=0; i<n; i++)
	{
		if (T==NULL)
		{
			T=(BTNode *)malloc(sizeof(BTNode));
			T->keynum=1;
			T->key[1]=i;
			T->ptr[0]=NULL;
			T->ptr[1]=NULL;
			T->parent=NULL;		
		}
		else
		{
			insert_BTree(T, i);		
		}
	}
	
	

		
	cout<<"test: "<<T->keynum<<endl;
	mid_order(T);
	cin>>n;
	insert_BTree(T, n-1);

	cout<<"test: "<<T->keynum<<endl;
	mid_order(T);
	
	return 0;
}
*/
