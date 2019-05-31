#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
struct stack {
	int  *elems;	//申请内存用于存放栈的元素
	int   max;	//栈能存放的最大元素个数
	int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
void initstack(stack *const p, int m);	//初始化p指向的栈：最多m个元素
void initstack(stack *const p, const stack&s); //用栈s初始化p指向的栈
int  size(const stack *const p);		//返回p指向的栈的最大元素个数max
int  howmany(const stack *const p);	//返回p指向的栈的实际元素个数pos
int  getelem(const stack *const p, int x);	//取下标x处的栈元素
stack *const push(stack *const p, int e); 	//将e入栈，并返回p
stack *const pop(stack *const p, int &e); 	//出栈到e，并返回p
stack *const assign(stack*const p, const stack&s); //赋s给p指的栈,并返回p
void print(const stack*const p);			//打印p指向的栈
void destroystack(stack*const p);		//销毁p指向的栈
int main(int argc, char* argv[])
{
	int now_indexs;
	int last_indexs;//[now_indexs,last_indexs)之间的数据均为命令的参数
	char indexs = 1;//当前处理的字符串下标
	int error = 0;//错误标记
	now_indexs = last_indexs = 1;
	stack * p = NULL;
	while (last_indexs < argc)
	{
		now_indexs = last_indexs++;
		indexs = argv[now_indexs++][1];//当前执行的命令
		while (last_indexs < argc && !(argv[last_indexs][1] >= 'A' && argv[last_indexs][1] <= 'Z'))
		{
			last_indexs++;
		}//last_indexs定位到下一条命令
		int num = -1;
		stack *pinews;

		//根据指令进行操作
		switch (indexs)
		{
		case 'S':
			num = atoi(argv[now_indexs]);//获取参数 
			if (num > 0)
			{
				p = new stack;
				initstack(p, num);//初始化一个新栈
				printf("S  %d", num);
			}
			else error = 1;//num不合法
			break;
		case 'I':
			if (last_indexs - now_indexs > p->max - p->pos)//入栈元素个数>=最多元素个数-当前元素个数
				error = 1;
			else//参数依次入栈
			{
				while (now_indexs < last_indexs)
				{
					num = atoi(argv[now_indexs++]);
					push(p, num);

				}
				printf("  I");
				print(p);
			}
			break;
		case 'C':
			pinews = new stack;
			initstack(pinews, *p);//拷贝新栈
			destroystack(p); delete p;//销毁旧栈
			p = pinews;
			printf("  C");
			print(p);
			break;
		case 'O':
			num = atoi(argv[now_indexs]);
			if (num > p->pos)//出栈元素个数>当前栈中元素个数
				error = 1;
			else
			{
				while (num--)
				{
					int value;
					pop(p, value);

				}
				printf("  O");
				print(p);
			}
			break;
		case 'G':
			num = atoi(argv[now_indexs]);
			if (num >= p->pos) error = 1;
			else
				printf("  G  %d", p->elems[num]);
			break;
		case 'A':
			pinews = new stack;
			num = atoi(argv[now_indexs]);
			initstack(pinews, num);
			assign(pinews, *p);//赋值新栈
			destroystack(p);
			delete p;//销毁旧栈
			p = pinews;
			printf("  A");
			print(p);
			break;
		case 'N':
			printf("  N  %d", p->pos);
			break;
		default:
			break;
		}
		if (error == 1)
		{
			printf("  %c  E", indexs);
			break;
		}
	}
	delete p;
	return 0;
}
void initstack(stack *const p, int m)	//初始化p指向的栈：最多m个元素
{
	p->elems = (int*)malloc(m * sizeof(int));
	p->max = m;
	p->pos = 0;

}
void initstack(stack *const p, const stack&s)//用栈s初始化p指向的栈
{
	p->elems = (int *)malloc(sizeof(stack)*s.max);
	for (int i = 0; i < s.pos; i++)
		p->elems[i] = s.elems[i];
	p->max = s.max;
	p->pos = s.pos;
}
int  size(const stack *const p)		//返回p指向的栈的最大元素个数max
{
	return p->max;
}
int  howmany(const stack *const p)	//返回p指向的栈的实际元素个数pos
{
	return p->pos;
}
int  getelem(const stack *const p, int x)	//取下标x处的栈元素
{
	if (x > p->pos)exit(-1);
	return p->elems[x];
}
stack *const push(stack *const p, int e)	//将e入栈，并返回p
{
	if (p->pos == p->max)return NULL;
	p->elems[(p->pos)++] = e;
	return p;
}
stack *const pop(stack *const p, int &e) 	//出栈到e，并返回p
{
	if (p->pos == 0)return NULL;
	e = p->elems[--(p->pos)];
	return p;
}
stack *const assign(stack*const p, const stack&s)
{
	p->max = s.max;
	p->pos = s.pos;
	p->elems = (int *)realloc(p->elems, s.max * sizeof(int));//重新分配内存
	if (!p->elems)//内存分配失败
		exit(0);
	memcpy(p->elems, s.elems, s.pos * sizeof(int));//拷贝数据
	return p;
}

void print(const stack*const p)			//打印p指向的栈
{
	for (int i = 0; i < p->pos; i++)
		printf(" %d ", p->elems[i]);
}
void destroystack(stack*const p)		//销毁p指向的栈
{
	free(p->elems);
}

