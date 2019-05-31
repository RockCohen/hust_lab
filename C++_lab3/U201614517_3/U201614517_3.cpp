#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	int  const  max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m) :max(m), elems(new int[m]) {//初始化栈：最多存m个元素
		this->pos = 0;
	}
	STACK(const STACK&s):max(s.max), elems(new int [s.max]) {//用栈s拷贝初始化栈
		for (int i = 0; i < s.max; i++)
			this->elems[i] = s.elems[i];
		this->pos = s.pos;
	}
	virtual int  size() const			//返回栈的最大元素个数max
	{
		return this->max;
	}
	virtual  operator int () const			//返回栈的实际元素个数pos
	{
		return this->pos;
	}
	virtual int operator[ ] (int x) const	//取下标x处的栈元素，第1个元素x=0
	{
		return this->elems[x];
	}
	virtual STACK& operator<<(int e) 	//将e入栈,并返回栈
	{
		if (pos == max)exit(-1);
		this->elems[pos++] = e;
		return *this;
	}
	virtual STACK& operator>>(int &e)	//出栈到e,并返回栈
	{
		if (pos == 0)exit(-1);
		e = this->elems[--pos];
		return *this;
	}
	virtual STACK& operator=(const STACK&s) //赋s给栈,并返回被赋值的栈
	{
		delete[] this->elems;
		*((int **)&elems) = new int[s.max];
		*((int*)&max) = s.max;
		for (int i = 0; i < s.pos; i++)
			this->elems[i] = s.elems[i];
       this->pos=s.pos;
		return *this;
	}
	virtual void print() const//打印栈
	{
		for (int i = 0; i < this->pos; i++)
			cout << " " << this->elems[i] << " ";
	}	
	virtual ~STACK() {//销毁栈
		delete[] this->elems;
	}	
};
int main(int argc, char* argv[])
{
	char indexs = 1;//当前处理的字符串下标
	int now_indexs;
	int last_indexs;//[now_indexs,last_indexs)之间的数据均为命令的参数
	int error = 0;//错误标记
	now_indexs = last_indexs = 1;
	STACK * p = NULL;
	STACK s = STACK(10);
	while (last_indexs < argc)
	{
		now_indexs = last_indexs++;
		indexs = argv[now_indexs++][1];//当前执行的命令
		while (last_indexs<argc && !(argv[last_indexs][1] >= 'A' && argv[last_indexs][1] <= 'Z'))
		{
			last_indexs++;
		}//last_indexs定位到下一条命令
		int num = -1;
		STACK *pi;
		//根据指令进行操作
		switch (indexs)
		{
		case 'S':
			num = atoi(argv[now_indexs]);//获取参数 
			if (num > 0)
			{
				p =  new STACK(num);//初始化一个新栈
				printf("S  %d", num);

			}
			else error = 1;//num不合法
			break;
		case 'I':
			if( (last_indexs - now_indexs) >( p->size() - (*p)))//入栈元素个数>=最多元素个数-当前元素个数
				error = 1;
			else//参数依次入栈
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
			if (num > (*p))//出栈元素个数>当前栈中元素个数
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
			*pi=*p;//赋值新栈
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










