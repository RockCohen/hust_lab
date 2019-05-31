#include<iostream>
#include<string>
using namespace std;
class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ�����m��Ԫ��
	STACK(const STACK&s); //��ջs������ʼ��ջ
	int  size() const;		//����ջ�����Ԫ�ظ���max
	int  howMany() const;	//����ջ��ʵ��Ԫ�ظ���pos
	int  getelem(int x) const;	//ȡ�±�x����ջԪ��
	STACK& push(int e); 	//��e��ջ,������ջ
	STACK& pop(int &e); 	//��ջ��e,������ջ
	STACK& assign(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	void print() const;		//��ӡջ
	~STACK();				//����ջ
};
STACK::STACK(int m):max(m),elems(new int[m]){//�б��ʼ��
	pos = 0;
}
STACK::STACK(const STACK&s) : max(s.max), elems(new int[s.max]) {//��s��ȫ������p
	for (int i = 0; i < s.pos; i++)
		this->elems[i] = s.elems[i];
	this->pos = s.pos;
}
int STACK::size()const {//����ջ������
	return this->max;
}
int STACK::howMany()const {//���ص�ǰԪ�ظ���
	return this->pos;
}
int STACK::getelem(int x)const  {//��ȡ�±�Ϊx��Ԫ��
	if (x > pos)exit(-1);//Խ��ʱ����
	return this->elems[x];
}
STACK &STACK::push(int e) {
	if (pos == max)exit(-1);//ջ��ʱ��ջʧ��
     	this->elems[pos++] = e;
	return *this;
}
STACK &STACK::pop(int &e) {
	if (pos == 0)exit(-1);//��ǰԪ�ظ���Ϊ0ʱ��ջʧ��
	e = this->elems[--pos];
	return *this;
}
STACK &STACK::assign(const STACK &s) {
	    delete[] this->elems;//�ͷ�ԭʼջ���ڴ�
		*((int*)&max) = s.max;
		*((int **)&elems) = new int[s.max];//�����µĿռ䣬���С��s����һ��
			for (int i = 0; i < s.pos; i++)//Ԫ�ؽ��п���
			this->elems[i] = s.elems[i];
			pos = s.pos;
	    return *this;
}
void STACK::print()const {//��ӡԪ��
	for (int i = 0; i < pos; i++)
		cout << " " << elems[i]<<" ";
}
STACK::~STACK() {//��������
	delete[] elems;
}
int main(int argc, char* argv[])
{
	
	//STACK s = STACK(10);
	char indexs = 1;//��ǰ������ַ����±�
	int now_indexs;
	int last_indexs;//[now_indexs,last_indexs)֮������ݾ�Ϊ����Ĳ���
	int error = 0;//������
	now_indexs = last_indexs = 1;
	STACK * p = NULL;
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
			if( (last_indexs - now_indexs) >( p->size() - p->howMany()))//��ջԪ�ظ���>=���Ԫ�ظ���-��ǰԪ�ظ���
				error = 1;
			else//����������ջ
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
			if (num > p->howMany())//��ջԪ�ظ���>��ǰջ��Ԫ�ظ���
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
			(*pi).assign(*p);//��ֵ��ջ
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