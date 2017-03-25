/*
LValue - ��� ���������, ����������� ������������
� �������:
int x 
x + 2 
a[i + 2]
some_struct.some_field
*ptr
*(p + 2)
----------------------------------------------------
����� ������ �� ���������� �������� �������� LValue.
������������� -> ����� LValue �������� �������!
----------------------------------------------------
��������� * � &.
�������� * ������������ ������� � & (� ������)
�������� & ������������ ������� � * (� ���������)
*	-	������������� ������ (������� ��������)
&	-	������ ������
������:
int x = 5;
��� ��������� int *ptr = &x;
������ � ������� 0x2F3134;
int y = *ptr;
�.�. return *0x2F3134;	-> return 5;


string str = "some string";
string &ref = str;
string str2 = *&ref;	���������� str2 = str; ���� str2 = ref;

str2 = *&ref -> str2 = *0x313FD -> str2 = str -> str2 = "some string"
������������� ����� ��������� str2 = ref;

string *ptr = str;
string *ptr2 = &*ptr;	���������� ptr2 = &str; ���� ptr2 = ptr1;

ptr2 = &*0xF3212 -> ptr2 = &str -> ptr2 = 0xF3212 
C������������ ����� ��������� ptr2 = ptr;

*/

#include <iostream>
#include <memory>
#include <vector>

#define cout std::cout

template <typename T, size_t N>
class Arr {
	T *arr;
	size_t size;
public:
	Arr() {
		arr = new T[N];
		this->size = N;
	}
	~Arr() {
		delete[] arr;
	}
	T &operator[] (size_t itr) {
		if (itr < this->size)
			return arr[itr];
	}
	size_t len() {
		return this->size;
	}
};



const int N = 5;

void showArr(int(&arr)[N]);

template <typename T, size_t n>
size_t len(T(&arr)[n]) {
	return n;
}

std::string f() {
	return "testing";
}

int main() {	

	Arr<int, 5> ar;
	for (size_t i = 0; i < ar.len(); ++i) {
		ar[i] = (int)i;
		cout << ar[i] << " ";
	}
	//cout << ar[5];
	cout << "\nEnd\n";
	int x[N];			// x[5] <-> (&x)[5]
	int *ptr = (x + 0);	// x+0 <-> &(x[0])
	x[0] = 5;
	cout << *ptr;
	(x + 2)[2] = 4;		//	x[4]
	cout << "x[4]=" << x[4] << std::endl;
	/*
	&x == x // ������ ����������, ������ ����: int (*TYPE)[5] � int *TYPE
	(void *)&x == (void *)x // ������
	x == x + 0 // ������
	x == &(x[0]) // ������

	x[2] ������������ ��������� "�������� ��������� �� 2 int'a"
	1) x + 2
	2) x + 2 <-> (int *)((char *)x + 2 * sizeof(int)) 
		char =	1bit	->	char x = 8,
		int	 =	4bit	->	int	 x = 8/4 = 2;
	3) *(x + 2) - ������������� �����, �������� ������ 3 ������ �������

	&x + 1 <-> (int (*)[5])((char *)&x + sizeof (int [5]))
	(int (*)[5])(&x + 5int'��)
	(int (*x)[5])(&x[5])	*x[5] * &x[5]	*x * &x[1] = (&x)[1]
	(&x)[1] <-> (&x[4])[1] <-> x + 5	- ����� �� ������� �������
	*/
	/*	��� �������� � �������� ��������� ������, �� ������� ��������� �� 
		��� ������� �������, � sizeof � ���� ����� ��� � ���������.
		TYPE0 Foo (TYPE1 arr[] ���� *arr)
		������������� � ������� �� � � �++ ����� �������� ������ ������ �������
		������� � ������� ������ ������. ����������� ��� � ������� ������.
		TYPE0 Foo (TYPE1 (&x)[SIZE]);
	*/ 
	int x2[12];
	cout << "\nSize Of X: " << len(x2) << std::endl;

	std::shared_ptr<int> arr(new int[N]);
	try {
		for (int i = 0; i < N; ++i) {
			arr.get()[i] = i;
			cout << arr.get()[i] << '\t';
			*(x + i) = i;
		}
		showArr(x);
	}
	catch (std::exception e) {
		cout << e.what() << std::endl;
	}

	std::cin.get();
	return EXIT_SUCCESS;
}

void showArr(int(&arr)[N]) {
	cout << std::endl << "Show Array x:\n";
	for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
		cout << arr[i] << '\t';
}