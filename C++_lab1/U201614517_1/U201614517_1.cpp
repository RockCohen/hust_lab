#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
struct stack {
	int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
	int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
void initstack(stack *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initstack(stack *const p, const stack&s); //��ջs��ʼ��pָ���ջ
int  size(const stack *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howmany(const stack *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem(const stack *const p, int x);	//ȡ�±�x����ջԪ��
stack *const push(stack *const p, int e); 	//��e��ջ��������p
stack *const pop(stack *const p, int &e); 	//��ջ��e��������p
stack *const assign(stack*const p, const stack&s); //��s��pָ��ջ,������p
void print(const stack*const p);			//��ӡpָ���ջ
void destroystack(stack*const p);		//����pָ���ջ
int main(int argc, char* argv[])
{
	int now_indexs;
	int last_indexs;//[now_indexs,last_indexs)֮������ݾ�Ϊ����Ĳ���
	char indexs = 1;//��ǰ������ַ����±�
	int error = 0;//������
	now_indexs = last_indexs = 1;
	stack * p = NULL;
	while (last_indexs < argc)
	{
		now_indexs = last_indexs++;
		indexs = argv[now_indexs++][1];//��ǰִ�е�����
		while (last_indexs < argc && !(argv[last_indexs][1] >= 'A' && argv[last_indexs][1] <= 'Z'))
		{
			last_indexs++;
		}//last_indexs��λ����һ������
		int num = -1;
		stack *pinews;

		//����ָ����в���
		switch (indexs)
		{
		case 'S':
			num = atoi(argv[now_indexs]);//��ȡ���� 
			if (num > 0)
			{
				p = new stack;
				initstack(p, num);//��ʼ��һ����ջ
				printf("S  %d", num);
			}
			else error = 1;//num���Ϸ�
			break;
		case 'I':
			if (last_indexs - now_indexs > p->max - p->pos)//��ջԪ�ظ���>=���Ԫ�ظ���-��ǰԪ�ظ���
				error = 1;
			else//����������ջ
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
			initstack(pinews, *p);//������ջ
			destroystack(p); delete p;//���پ�ջ
			p = pinews;
			printf("  C");
			print(p);
			break;
		case 'O':
			num = atoi(argv[now_indexs]);
			if (num > p->pos)//��ջԪ�ظ���>��ǰջ��Ԫ�ظ���
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
			assign(pinews, *p);//��ֵ��ջ
			destroystack(p);
			delete p;//���پ�ջ
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
void initstack(stack *const p, int m)	//��ʼ��pָ���ջ�����m��Ԫ��
{
	p->elems = (int*)malloc(m * sizeof(int));
	p->max = m;
	p->pos = 0;

}
void initstack(stack *const p, const stack&s)//��ջs��ʼ��pָ���ջ
{
	p->elems = (int *)malloc(sizeof(stack)*s.max);
	for (int i = 0; i < s.pos; i++)
		p->elems[i] = s.elems[i];
	p->max = s.max;
	p->pos = s.pos;
}
int  size(const stack *const p)		//����pָ���ջ�����Ԫ�ظ���max
{
	return p->max;
}
int  howmany(const stack *const p)	//����pָ���ջ��ʵ��Ԫ�ظ���pos
{
	return p->pos;
}
int  getelem(const stack *const p, int x)	//ȡ�±�x����ջԪ��
{
	if (x > p->pos)exit(-1);
	return p->elems[x];
}
stack *const push(stack *const p, int e)	//��e��ջ��������p
{
	if (p->pos == p->max)return NULL;
	p->elems[(p->pos)++] = e;
	return p;
}
stack *const pop(stack *const p, int &e) 	//��ջ��e��������p
{
	if (p->pos == 0)return NULL;
	e = p->elems[--(p->pos)];
	return p;
}
stack *const assign(stack*const p, const stack&s)
{
	p->max = s.max;
	p->pos = s.pos;
	p->elems = (int *)realloc(p->elems, s.max * sizeof(int));//���·����ڴ�
	if (!p->elems)//�ڴ����ʧ��
		exit(0);
	memcpy(p->elems, s.elems, s.pos * sizeof(int));//��������
	return p;
}

void print(const stack*const p)			//��ӡpָ���ջ
{
	for (int i = 0; i < p->pos; i++)
		printf(" %d ", p->elems[i]);
}
void destroystack(stack*const p)		//����pָ���ջ
{
	free(p->elems);
}

