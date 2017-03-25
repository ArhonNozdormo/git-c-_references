/*
LValue - это выражения, допускающие присваивание
к примеру:
int x 
x + 2 
a[i + 2]
some_struct.some_field
*ptr
*(p + 2)
----------------------------------------------------
Любая ссылка на изменяемое значение является LValue.
Следовательно -> Любое LValue является ссылкой!
----------------------------------------------------
Операторы * и &.
Оператор * конвертирует операнд в & (в ссылку)
Оператор & конвертирует операнд в * (в указатель)
*	-	Разыменование адреса (возврат значения)
&	-	Взятие адреса
Пример:
int x = 5;
дан указатель int *ptr = &x;
адресс к примеру 0x2F3134;
int y = *ptr;
т.е. return *0x2F3134;	-> return 5;


string str = "some string";
string &ref = str;
string str2 = *&ref;	аналогично str2 = str; либо str2 = ref;

str2 = *&ref -> str2 = *0x313FD -> str2 = str -> str2 = "some string"
Следовательно можно упростить str2 = ref;

string *ptr = str;
string *ptr2 = &*ptr;	аналогично ptr2 = &str; либо ptr2 = ptr1;

ptr2 = &*0xF3212 -> ptr2 = &str -> ptr2 = 0xF3212 
Cледовательно можно упростить ptr2 = ptr;

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
	&x == x // ошибка компиляции, разные типы: int (*TYPE)[5] и int *TYPE
	(void *)&x == (void *)x // истина
	x == x + 0 // истина
	x == &(x[0]) // истина

	x[2] эквивалентно выражению "сдвинуть указатель на 2 int'a"
	1) x + 2
	2) x + 2 <-> (int *)((char *)x + 2 * sizeof(int)) 
		char =	1bit	->	char x = 8,
		int	 =	4bit	->	int	 x = 8/4 = 2;
	3) *(x + 2) - разыменовывая адрес, получаем объект 3 ячейки массива

	&x + 1 <-> (int (*)[5])((char *)&x + sizeof (int [5]))
	(int (*)[5])(&x + 5int'ов)
	(int (*x)[5])(&x[5])	*x[5] * &x[5]	*x * &x[1] = (&x)[1]
	(&x)[1] <-> (&x[4])[1] <-> x + 5	- выход за пределы массива
	*/
	/*	При передаче в качестве аргумента массив, мы получим указатель на 
		его нулевой элемент, а sizeof у него будет как у указателя.
		TYPE0 Foo (TYPE1 arr[] либо *arr)
		Следовательно в отличии от С в С++ можно косвенно узнать размер массива
		передав в функцию только массив. Реализуется это с помощью ссылки.
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