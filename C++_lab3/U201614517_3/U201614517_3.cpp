#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	int  const  max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m) :max(m), elems(new int[m]) {//��ʼ��ջ������m��Ԫ��
		this->pos = 0;
	}
	STACK(const STACK&s):max(s.max), elems(new int [s.max]) {//��ջs������ʼ��ջ
		for (int i = 0; i < s.max; i++)
			this->elems[i] = s.elems[i];
		this->pos = s.pos;
	}
	virtual int  size() const			//����ջ�����Ԫ�ظ���max
	{
		return this->max;
	}
	virtual  operator int () const			//����ջ��ʵ��Ԫ�ظ���pos
	{
		return this->pos;
	}
	virtual int operator[ ] (int x) const	//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
	{
		return this->elems[x];
	}
	virtual STACK& operator<<(int e) 	//��e��ջ,������ջ
	{
		if (pos == max)exit(-1);
		this->elems[pos++] = e;
		return *this;
	}
	virtual STACK& operator>>(int &e)	//��ջ��e,������ջ
	{
		if (pos == 0)exit(-1);
		e = this->elems[--pos];
		return *this;
	}
	virtual STACK& operator=(const STACK&s) //��s��ջ,�����ر���ֵ��ջ
	{
		delete[] this->elems;
		*((int **)&elems) = new int[s.max];
		*((int*)&max) = s.max;
		for (int i = 0; i < s.pos; i++)
			this->elems[i] = s.elems[i];
       this->pos=s.pos;
		return *this;
	}
	virtual void print() const//��ӡջ
	{
		for (int i = 0; i < this->pos; i++)
			cout << " " << this->elems[i] << " ";
	}	
	virtual ~STACK() {//����ջ
		delete[] this->elems;
	}	
};
int main(int argc, char* argv[])
{
	char indexs = 1;//��ǰ������ַ����±�
	int now_indexs;
	int last_indexs;//[now_indexs,last_indexs)֮������ݾ�Ϊ����Ĳ���
	int error = 0;//������
	now_indexs = last_indexs = 1;
	STACK * p = NULL;
	STACK s = STACK(10);
	while (last_indexs < argc)
	{
		now_indexs = last_indexs++;
		indexs = argv[now_indexs++][1];//��ǰִ�е�����
		while (last_indexs<argc && !(argv[last_indexs][1] >= 'A' && argv[last_indexs][1] <= 'Z'))
		{
			last_indexs++;
		}//last_indexs��λ����һ������
		int num = -1;
		STACK *pi;
		//����ָ����в���
		switch (indexs)
		{
		case 'S':
			num = atoi(argv[now_indexs]);//��ȡ���� 
			if (num > 0)
			{
				p =  new STACK(num);//��ʼ��һ����ջ
				printf("S  %d", num);

			}
			else error = 1;//num���Ϸ�
			break;
		case 'I':
			if( (last_indexs - now_indexs) >( p->size() - (*p)))//��ջԪ�ظ���>=���Ԫ�ظ���-��ǰԪ�ظ���
				error = 1;
			else//����������ջ
			{
				while (now_indexs < last_indexs)
				{
					num = atoi(argv[now_indexs++]);
					(*p) << num;
				}
				printf("  I");
				(*p).print();
			}
			break;
		case 'C':
		{
			pi = new STACK(*p);
			delete p;
			p = pi;
			printf("  C");
			(*p).print();
			break;
		}
		case 'O':
			num = atoi(argv[now_indexs]);
			if (num > (*p))//��ջԪ�ظ���>��ǰջ��Ԫ�ظ���
				error = 1;
			else
			{
				while (num--)
				{
					int value;
					(*p)>>value;
				}
				printf("  O");
				(*p).print();
			}
			break;
		case 'G':
			num = atoi(argv[now_indexs]);
			if (num >= (*p)) error = 1;
			else cout << "  G  " << (*p)[num] << " ";
			break;
		case 'A':
		{
			num = atoi(argv[now_indexs]);
			 pi = new  STACK(num);
			*pi=*p;//��ֵ��ջ
			delete p;
			p = pi;
			printf("  A");
			(*p).print();
			break;
		}
		case 'N':
			printf("  N  %d", (int)(*p));
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










