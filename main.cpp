#include<stdio.h>
#include <stdlib.h>

#define MAX 10000
typedef struct 
{
	int row;			//����Ԫ��������
	int col;			//����Ԫ������
	int value;			//����Ԫ��ֵ
}TNode;					//��Ԫ������

typedef struct 
{
	int r;				//����
	int c;				//����
	int v;				//����Ԫ����
	TNode data[MAX+1];		//��Ԫ���data�±��1��ʼ
}TSMatrix;					//��Ԫ�������

void CreatM(TSMatrix *M);
void CreatMat(TSMatrix *M,int a[10][10]);
void Out(TSMatrix *M);
void Print(TSMatrix M);
void Trans(TSMatrix M,TSMatrix *N);
void CPot(TSMatrix M,int pot[MAX]);
void FastTrans(TSMatrix M,TSMatrix *N);
int Multi(TSMatrix M,TSMatrix N,TSMatrix *Q);
void menu();


int main()
{
	int i,sel;
	int a[10][10]={{3,0,0,2,0,0,9,0,0,0},{0,0,0,0,4,0,0,0,10,0},{0,0,0,0,0,0,8,0,0,0},
	{0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,12,2,0,10},
	{0,3,0,0,0,2,0,0,0,0},{0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,8,0,0,0}};	
	int b[10][10]={{0,0,1,0,0,0,0,0,2,0},{0,0,0,0,0,2,0,0,1,0},{0,0,8,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0},{0,0,0,0,5,0,0,0,0,0},{0,0,0,0,0,0,0,0,12,0},{0,0,2,0,0,0,0,12,0,10},
	{0,3,0,0,0,0,0,2,0,0},{0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,2}};	
	TSMatrix M,N,Q;
	printf("\nϡ�����a����:\n");
	CreatMat(&M,a);
	Out(&M);
	printf("\n\t����aѹ���洢:\n");
	Print(M);
	printf("\na��ת�þ���Ϊ:\n");
	FastTrans(M,&Q);
	Out(&Q);
	printf("\nϡ�����b����:\n");
	CreatMat(&N,b);
	Out(&N);
	printf("\n\t����bѹ���洢:\n");
	Print(N);
	i=Multi(M,N,&Q);
	if(i==1)
	{ 
		printf("\n����a�����b��˽��:\n"); Out(&Q);
	}system("pause>nul");system("cls");
	menu();
	scanf("%d",&sel);
	while(sel!=0)
	{
		switch(sel)
		{
		case 1:
			CreatM(&M);
			printf("\n����Ԫ�������¾����ѹ���洢:\n");
			Out(&M);system("pause>nul");system("cls");
			break;
		case 2:
			CreatM(&M);		
			printf("\n����Ԫ�������¾����ѹ���洢:\n");
			Out(&M);
			printf("\n����ת�ý������:\n");
			FastTrans(M,&N);
			Out(&N);system("pause>nul");system("cls");
			break;
		case 3:
			printf("\n��������Ҫ��˵������������Ԫ��ѹ���洢��Ϣ:\n");
			CreatM(&M);
			CreatM(&N);
			printf("\nϡ�����a����:\n");
			Out(&M);
			printf("\nϡ�����b����:\n");
			Out(&N);
			i=Multi(M,N,&Q);
			if(i==1)
			{
				printf("\n����a�����b��˽��:\n");
				Out(&Q);
			}
			system("pause>nul");system("cls");
			break;
		default:printf("��������������ѡ��:");
		}
		menu();
		scanf("%d",&sel);
	}
	return 0;
}

void CreatM(TSMatrix *M)
{
	int i;
	printf("��������������������������Ԫ����:");
	scanf("%d%d%d",&M->r,&M->c,&M->v);
	printf("������þ������Ԫ���ʾ����(�÷���Ԫλ�ڵڼ��С��ڼ��С�ֵΪ����):\n");
	for(i=1;i<=M->v;i++)			//��Ԫ����Ǵ�1��ʼ���
		scanf("%d%d%d",&M->data[i].row,&M->data[i].col,&M->data[i].value);
}

void CreatMat(TSMatrix *M,int a[10][10])
{
	int i,j;
	M->r=10;M->c=10;
	M->v=0;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(a[i][j]!=0)
			{	
				M->v++;
				M->data[M->v].row=i+1;
				M->data[M->v].col=j+1;
				M->data[M->v].value=a[i][j];
			}
}


void Out(TSMatrix *M)		
{
	int i,j,k,s;  
	for(i=1;i<=M->r;i++)
	{
		for(j=1;j<=M->c;j++)
		{
			k=0;
			for(s=1;s<=M->v;s++)
			{				
				if(M->data[s].row==i&&M->data[s].col==j)
				{		
					printf("%6d",M->data[s].value);	
					k=1;	
				}
			}	
			if(k==0)
				printf("%6d",k);
		}	
		printf("\n");
	}
}

void Print(TSMatrix M)
{
	int i;
	printf("����Ԫ���:(��,��,ֵ)\n");
	for(i=1;i<=M.v;i++)
		printf("%5d%5d%5d\n",M.data[i].row,M.data[i].col,M.data[i].value);
}


void Trans(TSMatrix M,TSMatrix *N)
{
	int i,j,k;
	N->c=M.r;	N->r=M.c;	N->v=M.v;
	if(N->v!=0)
	{
		k=1;
		for(i=1;i<=M.c;i++)
		{
			for(j=1;j<=M.v;j++)
				if(M.data[j].col==i)
				{
					N->data[k].row=M.data[j].col;
					N->data[k].col=M.data[j].row;	
					N->data[k].value=M.data[j].value;	
					k++;
				}				
		}
	}
}


void FastTrans(TSMatrix M,TSMatrix *N)
{
	int i,k;
	int pot[MAX]={0};		//pot[]��1��ʼ��¼��ת�þ����ÿһ����ӵ�еķ���Ԫ��Ŀ
	N->c=M.r;	N->r=M.c;	N->v=M.v;
	if(N->v!=0)
	{
		CPot(M,pot);
		for(i=1;i<=M.v;i++)
		{
			k=M.data[i].col;
			N->data[pot[k]].row=M.data[i].col;
			N->data[pot[k]].col=M.data[i].row;
			N->data[pot[k]].value=M.data[i].value;
			pot[k]++;
		}
	}
}

int Multi(TSMatrix M,TSMatrix N,TSMatrix *Q)
{
	int i,j,k,m,flag;
	if(M.c!=N.r)
	{
		printf("�����������!\n");
		return 0;
	}
	else if(M.v*N.v!=0)
	{
		Q->r=M.r;	Q->c=N.c;	Q->v=0;			
		for(i=1;i<=MAX;i++)
			Q->data[i].value=0;
		for(i=1;i<=M.v;i++)
			for(j=1;j<=N.v;j++)
			{
				if(M.data[i].col==N.data[j].row)
				{
					flag=1;
					for(k=1;k<=Q->v;k++)
						if(M.data[i].row==Q->data[k].row&&N.data[j].col==Q->data[k].col)
							flag=0;   
					if(flag==1)				
					{
						Q->v++; 
						Q->data[Q->v].row=M.data[i].row; 
						Q->data[Q->v].col=N.data[j].col; 
						Q->data[Q->v].value=M.data[i].value*N.data[j].value;
					}
					if(flag==0)
					{
						for(k=1;k<=Q->v;k++)
							if(M.data[i].row==Q->data[k].row&&N.data[j].col==Q->data[k].col)
							{
								m=k;
								break;
							}
						Q->data[m].value+=M.data[i].value*N.data[j].value;
					}
				}
			}
			return 1;
	}
	else 
	{
		Q->r=M.r;	Q->c=N.c;	Q->v=0;
		return 1;
	}

}



void CPot(TSMatrix M,int pot[MAX])		//ȷ��ÿ�е�һ������Ԫ����Ԫ���е�λ��
{
	int i,j,k;
	for(i=1;i<=M.v;i++)
	{
		k=M.data[i].col;
		pot[k+1]++;
	}
	pot[1]=1;				//M���е�1�еĵ�1������Ԫ�ڱ�N�еĴ��λ��
	for(j=2;j<=M.c;j++)
		pot[j]+=pot[j-1];

}

void menu()
{
	printf("\n���Խ������²���:\n");
	printf("\n\t1--������Ԫ������\n");
	printf("\t2--����ת��\n");
	printf("\t3--���������\n");
	printf("\t0--�˳�\n");
	printf("\t����������ѡ��:");
}


/*
ʵ������
3 4 2
1 2 5
2 3 6
ʵ������
4 4 3
2 4 5
3 1 7
2 2 12
*/