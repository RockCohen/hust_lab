#include<iostream>
#include<limits>
#include<string>
using namespace std;
class STACK {
private:
	int *const elems;
	const int max;
	int pos;

public:
	STACK(int m);
	STACK(const STACK &s);
	virtual int size() const;
	virtual operator int() const;
	virtual int operator [](int x) const;
	virtual STACK &operator <<(int e);
	virtual STACK &operator >>(int &e);
	virtual STACK &operator =(const STACK &s);
	virtual void print() const;
	virtual ~STACK();
};
class QUEUE : public STACK {
private:
	STACK s2;

public:
	QUEUE(int m);
	QUEUE(const QUEUE &s);
	virtual operator int() const;
	virtual int full() const;
	virtual int operator[](int x)const;
	virtual QUEUE &operator<<(int e);
	virtual QUEUE &operator>>(int &e);
	virtual QUEUE &operator=(const QUEUE &s);
	virtual void print() const;
	virtual ~QUEUE();
};

int main(int argc, char *argv[]) {
	QUEUE *queue = nullptr;
	char indexs = 1;//当前处理的字符串下标
	int now_indexs;
	int number;
	int last_indexs;//[now_indexs,last_indexs)之间的数据均为命令的参数
	int error = 0;//错误标记
	now_indexs = last_indexs = 1;

	while(last_indexs<argc){
		now_indexs = last_indexs++;
		indexs = argv[now_indexs++][1];//当前执行的命令
		while (last_indexs < argc && !(argv[last_indexs][1] >= 'A' && argv[last_indexs][1] <= 'Z'))
		{
			last_indexs++;
		}//last_indexs定位到下一条命令
		int num = -1;
		switch (indexs) {
		case 'S':
			num = atoi(argv[now_indexs]);//获取参数 
			number = num;
			if (num > 0)
			{
				queue = new QUEUE(num);//初始化一个新栈
				printf("S  %d", num);

			}
			else error = 1;//num不合法
			break;
		case 'I':
			if ((last_indexs - now_indexs) > (number  -(int)(*queue)))//入栈元素个数>=最多元素个数-当前元素个数
				error = 1;
			else//参数依次入栈
			{
				while (now_indexs < last_indexs)
				{
					num = atoi(argv[now_indexs++]);
					(*queue) << num;
				}
				printf("  I  ");
				queue->print();
			}
			break;
		case 'O':
			num = atoi(argv[now_indexs]);
			if (num > int(*queue))//出栈元素个数>当前栈中元素个数
				error = 1;
			else
			{
				while (num--)
				{
					int value;
					(*queue) >> value;
				}
				printf("  O  ");
				(*queue).print();
			}
			break;
		case 'C': {
			QUEUE *newQueue = new QUEUE(*queue);
			queue = newQueue;
			printf("  C  ");
			(*queue).print();
			break; }
		case 'A': {
			num = atoi(argv[now_indexs]);
			QUEUE *newQueue = new QUEUE(number);
			*newQueue = *queue;
			queue = newQueue;
			printf("  A  ");
			(*queue).print();
			break; }
		case 'G':
			num = atoi(argv[now_indexs]);
			if (num >= (*queue)) error = 1;
			else cout << "  G  " << (*queue)[num] << " ";
			break;
		case 'N':
			printf("  N  %d  ", (int)(*queue));
			break;
		default:
			break;
			
		}
		if (error == 1)
		{
			printf(" %c ", indexs);
			printf("  E  ");
			break;
		}
		
	}
	return 0;
}
//栈函数定义
STACK::STACK(int m) : elems(new int[m]), max(m) {
	this->pos = 0;
}

STACK::STACK(const STACK &s) : elems(new int[s.max]), max(s.max) {
	this->pos = s.pos;
	for (int i = 0; i < pos; ++i)
		elems[i] = s.elems[i];
}

int STACK::size() const {
	return this->max;
}

STACK::operator int() const {
	return this->pos;
}

int STACK::operator [](int x) const {
	if (x >= pos)
		throw std::logic_error(" out of range");
	return this->elems[x];
}

STACK &STACK::operator <<(int e) {
	if (pos == max)
		throw std::logic_error(" full");
	elems[pos++] = e;
	return *this;
}

STACK &STACK::operator >>(int &e) {
	if (pos == 0)
		throw std::logic_error("empty stack");
	e = elems[--pos];
	return *this;
}

STACK &STACK::operator =(const STACK &s) {
	int *ref = const_cast<int *>(elems);
	delete ref;
	ref = new int[s.max];
	int *num = const_cast<int *>(&max);
	*num = s.max;
	pos = s.pos;
	for (int i = 0; i < pos; ++i)
		elems[i] = s.elems[i];
	return *this;
}

void STACK::print() const {
	for (int i = 0; i < pos; ++i) {
		cout << elems[i] << "  ";
	}
	cout << flush;
}

STACK::~STACK() {
	delete[]elems;
}

//队列函数定义
QUEUE::QUEUE(int m) : STACK(m), s2(m) {}

QUEUE::QUEUE(const QUEUE &s) : STACK(static_cast<STACK>(s)), s2(s.s2) {}

QUEUE::operator int() const {
	return STACK::operator int() + s2.operator int();
}

int QUEUE::full() const {
	return STACK::operator int() == STACK::size() && !s2.operator int();
}

QUEUE &QUEUE::operator <<(int e) {
	// 判断是否满
	if (STACK::operator int() == STACK::size()) {
		int temp;
		int origSize = STACK::operator int();
		for (int i = 0; i < origSize; ++i) {
			STACK::operator >>(temp);
			s2 << temp;
		}
	}
	STACK::operator <<(e);
	return *this;
}

QUEUE &QUEUE::operator =(const QUEUE &s) {
	STACK::operator=(static_cast<STACK>(s));
	s2 = s.s2;
	return *this;
}
int QUEUE::operator [](int x) const {
	if (x >= STACK::operator int() + s2.operator int())
		throw std::logic_error("trying to get elem outside of queue");
	// 判断元素的位置
	if (x >= int(s2))
		return STACK::operator [](x - int(s2));
	else
		return s2[int(s2) - x - 1];
}
void QUEUE::print() const {
	using namespace std;
	for (int i = 0; i < int(s2); ++i) {
		if (i)
			cout << "  ";
		cout << s2[int(s2) - i - 1];
	}
	if (int(s2) && STACK::operator int())
		cout << "  ";
	for (int i = 0; i < STACK::operator int(); ++i) {
		if (i)
			cout << "  ";
		cout << STACK::operator [](i);
	}
	cout << flush;
}
QUEUE &QUEUE::operator >>(int &e) {
	if (int(s2)) {
		s2 >> e;
	}
	else {
		int templates;
		int origize = STACK::operator int();
		for (int i = 0; i < origize - 1; ++i) {
			STACK::operator >>(templates);
			s2 << templates;
		}
		STACK::operator >>(e);
	}
	return *this;
}
QUEUE::~QUEUE() {}


