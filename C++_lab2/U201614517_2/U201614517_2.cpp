#include<iostream>
#include<string>
using namespace std;
class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	int  size() const;		//返回栈的最大元素个数max
	int  howMany() const;	//返回栈的实际元素个数pos
	int  getelem(int x) const;	//取下标x处的栈元素
	STACK& push(int e); 	//将e入栈,并返回栈
	STACK& pop(int &e); 	//出栈到e,并返回栈
	STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
	void print() const;		//打印栈
	~STACK();				//销毁栈
};
STACK::STACK(int m):max(m),elems(new int[m]){//列表初始化
	pos = 0;
}
STACK::STACK(const STACK&s) : max(s.max), elems(new int[s.max]) {//将s完全拷贝给p
	for (int i = 0; i < s.pos; i++)
		this->elems[i] = s.elems[i];
	this->pos = s.pos;
}
int STACK::size()const {//返回栈的容量
	return this->max;
}
int STACK::howMany()const {//返回当前元素个数
	return this->pos;
}
int STACK::getelem(int x)const  {//获取下标为x的元素
	if (x > pos)exit(-1);//越界时结束
	return this->elems[x];
}
STACK &STACK::push(int e) {
	if (pos == max)exit(-1);//栈满时入栈失败
     	this->elems[pos++] = e;
	return *this;
}
STACK &STACK::pop(int &e) {
	if (pos == 0)exit(-1);//当前元素个数为0时出栈失败
	e = this->elems[--pos];
	return *this;
}
STACK &STACK::assign(const STACK &s) {
	    delete[] this->elems;//释放原始栈的内存
		*((int*)&max) = s.max;
		*((int **)&elems) = new int[s.max];//分配新的空间，其大小与s保持一致
			for (int i = 0; i < s.pos; i++)//元素进行拷贝
			this->elems[i] = s.elems[i];
			pos = s.pos;
	    return *this;
}
void STACK::print()const {//打印元素
	for (int i = 0; i < pos; i++)
		cout << " " << elems[i]<<" ";
}
STACK::~STACK() {//析构函数
	delete[] elems;
}
int main(int argc, char* argv[])
{
	
	//STACK s = STACK(10);
	char indexs = 1;//当前处理的字符串下标
	int now_indexs;
	int last_indexs;//[now_indexs,last_indexs)之间的数据均为命令的参数
	int error = 0;//错误标记
	now_indexs = last_indexs = 1;
	STACK * p = NULL;
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
			if( (last_indexs - now_indexs) >( p->size() - p->howMany()))//入栈元素个数>=最多元素个数-当前元素个数
				error = 1;
			else//参数依次入栈
			{
				while (now_indexs < last_indexs)
				{
					num = atoi(argv[now_indexs++]);
					p->push(num);
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
			if (num > p->howMany())//出栈元素个数>当前栈中元素个数
				error = 1;
			else
			{
				while (num--)
				{
					int value;
					(*p).pop(value);
				}
				printf("  O");
				(*p).print();
			}
			break;
		case 'G':
			num = atoi(argv[now_indexs]);
			if (num >= p->howMany()) error = 1;
			else 
				cout << "  G  " << (*p).getelem(num) << " ";
			break;
		case 'A':
		
			num = atoi(argv[now_indexs]);
			 pi = new  STACK(num);
			(*pi).assign(*p);//赋值新栈
			delete p;
			p = pi;
			printf("  A");
			(*p).print();
			break;
		
	    case 'N':
			printf("  N  %d", p->howMany());
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
	//system("pause");
	return 0;
}