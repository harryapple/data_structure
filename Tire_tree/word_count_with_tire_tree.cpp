#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
using namespace std;

//总共26个字母
#define WORD_NUM 26

int all=0;


//Tire树的主要结构体
typedef struct Tire
{
	int count; //该单词的数量
	bool isWord;  //节点是否是单词结尾的标志
	struct Tire *parent;  //指向父节点
	struct Tire *son[WORD_NUM];  //单词的下一个字母
}BTire;


//在Tire树中搜索是否已经存在该单词
//参数：T根节点，Word查询单词，p如果查到，则为单词尾节点
//否则，则是查到的最后一个节点，函数返回单词匹配的第几位
//如果匹配到最后一位，则如果p节点还是一个单词标志节点
//则表示该单词在Tire树中已经存在
int searchTire(BTire *T, char *word, BTire *&p)
{
	int i=0;
	int len=strlen(word);
	int index;
	p=T;
	
	while (p!=NULL && i<len)
	{
		index=*(word+i)-'a';
		
		if (p->son[index] == NULL)
		{
			return i;		
		}
		
		p=p->son[index];
		i++;

	}

	return i;
}


//初始化数组
void my_memset(BTire *q)
{
	int i;
	for (i=0; i<WORD_NUM; i++)
	{
		q->son[i]=NULL;		
	}		
}


//向Tire树中添加节点，首先查找，然后根据查找后
//p和i的信息，添加节点
int insertTire(BTire *T, char *word)
{
	BTire *p=NULL;
	BTire *q=NULL;
	int i, j, k;
	int len=strlen(word);
	int index;

	i=searchTire(T, word, p);
	
	if (i==len && p->isWord==true)
	{
		all++;
		cout<<"Find it!"<<word<<endl;
		p->count++;
		return 0;		
	}

	for (j=i; j<len; j++)
	{
		index=*(word+j)-'a';
		q=(BTire *)malloc(sizeof(BTire));
		q->count=0;
		q->parent=NULL;
		q->isWord=false;
		//memset((void *)q->son, NULL, sizeof(q->son));
		my_memset(q);
		p->son[index]=q;
		p=q;		
	}

	p->isWord=true;
	p->count++;
	return 1;
}

//从TUT.txt中解析单词
//‘-’连接两个单词算一个单词
void getword(FILE *p, char buf[])
{
        char ch;
        int j=0;
        int flag=0;
        while (!feof(p))
        {
                ch=fgetc(p);

                if (ch>='A' && ch<='Z')
                {
                        buf[j++] = ch + 32;
                        flag=1;
                }

                else if (ch>='a' && ch<='z')
                {
                        buf[j++] = ch;
                        flag=1;
                }

                else if (ch == '-' && j>0 && buf[j-1] >= 'a' && buf[j-1]<='z')
                {
                        buf[j++] = ch;
                }

                else
                {
                        if (flag==1)
                        {
                                if (buf[j-1]=='-')
                                        buf[j-1]='\0';

                                buf[j]='\0';
                                return ;
                        }
                }
                buf[j]='\0';
        }
}

int main()
{
	BTire *T;
	//char *word="abc";
	FILE *fp;
	char ch;
	char buf[50];
	int j=0;
	fp=fopen("TUT.txt", "r");
	T=(BTire *)malloc(sizeof(BTire));
	T->count=0;
	T->isWord=false;
	T->parent=NULL;
	my_memset(T);
	//memset((void *)T->son, NULL, sizeof(T->son));
	while (!feof(fp))
	{	
		getword(fp, buf);
		insertTire(T, buf);
		j++;
	}
	cout<<"Total: "<<j<<endl;
	cout<<"all: "<<all<<endl;
	fclose(fp);
	return 0;	

			
}
