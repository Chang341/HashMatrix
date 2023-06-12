#include<stdio.h>
#include <stdlib.h>

#define MAX 10000
typedef struct 
{
	int row;			//非零元所在行数
	int col;			//非零元所在列
	int value;			//非零元的值
}TNode;					//三元组类型

typedef struct 
{
	int r;				//行数
	int c;				//列数
	int v;				//非零元个数
	TNode data[MAX+1];		//三元组表，data下标从1开始
}TSMatrix;					//三元组表类型

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
	printf("\n稀疏矩阵a如下:\n");
	CreatMat(&M,a);
	Out(&M);
	printf("\n\t矩阵a压缩存储:\n");
	Print(M);
	printf("\na的转置矩阵为:\n");
	FastTrans(M,&Q);
	Out(&Q);
	printf("\n稀疏矩阵b如下:\n");
	CreatMat(&N,b);
	Out(&N);
	printf("\n\t矩阵b压缩存储:\n");
	Print(N);
	i=Multi(M,N,&Q);
	if(i==1)
	{ 
		printf("\n矩阵a与矩阵b相乘结果:\n"); Out(&Q);
	}system("pause>nul");system("cls");
	menu();
	scanf("%d",&sel);
	while(sel!=0)
	{
		switch(sel)
		{
		case 1:
			CreatM(&M);
			printf("\n该三元组是如下矩阵的压缩存储:\n");
			Out(&M);system("pause>nul");system("cls");
			break;
		case 2:
			CreatM(&M);		
			printf("\n该三元组是如下矩阵的压缩存储:\n");
			Out(&M);
			printf("\n快速转置结果如下:\n");
			FastTrans(M,&N);
			Out(&N);system("pause>nul");system("cls");
			break;
		case 3:
			printf("\n请输入需要相乘的两个矩阵的三元组压缩存储信息:\n");
			CreatM(&M);
			CreatM(&N);
			printf("\n稀疏矩阵a如下:\n");
			Out(&M);
			printf("\n稀疏矩阵b如下:\n");
			Out(&N);
			i=Multi(M,N,&Q);
			if(i==1)
			{
				printf("\n矩阵a与矩阵b相乘结果:\n");
				Out(&Q);
			}
			system("pause>nul");system("cls");
			break;
		default:printf("输入有误，请重新选择:");
		}
		menu();
		scanf("%d",&sel);
	}
	return 0;
}

void CreatM(TSMatrix *M)
{
	int i;
	printf("请输入矩阵的行数、列数、非零元个数:");
	scanf("%d%d%d",&M->r,&M->c,&M->v);
	printf("请输入该矩阵的三元组表示内容(该非零元位于第几行、第几列、值为多少):\n");
	for(i=1;i<=M->v;i++)			//三元组表是从1开始存的
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
	printf("其三元组表:(行,列,值)\n");
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
	int pot[MAX]={0};		//pot[]从1开始记录待转置矩阵的每一列所拥有的非零元数目
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
		printf("两矩阵不能相乘!\n");
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



void CPot(TSMatrix M,int pot[MAX])		//确定每列第一个非零元在三元组中的位置
{
	int i,j,k;
	for(i=1;i<=M.v;i++)
	{
		k=M.data[i].col;
		pot[k+1]++;
	}
	pot[1]=1;				//M表中第1列的第1个非零元在表N中的存放位置
	for(j=2;j<=M.c;j++)
		pot[j]+=pot[j-1];

}

void menu()
{
	printf("\n可以进行如下测试:\n");
	printf("\n\t1--输入三元组内容\n");
	printf("\t2--快速转置\n");
	printf("\t3--两矩阵相乘\n");
	printf("\t0--退出\n");
	printf("\t请输入您的选择:");
}


/*
实验数据
3 4 2
1 2 5
2 3 6
实验数据
4 4 3
2 4 5
3 1 7
2 2 12
*/