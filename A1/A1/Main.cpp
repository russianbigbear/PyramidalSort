#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <locale>
#include <tchar.h>
#include <string>
using namespace std;

#define count_elements 1000

/*
Структура "Элемент"
поля:
_numbers - целочисленный массив с 3 элементами;
_strings - массив, содержащий 2 строки;
методы:
_element() - конструктор без параметра;
_element(int first, int second, int third, string str_f, string str_s) - конструктор с параметром;
~_element() - деструктор элемента
compare_element(_element *other_element, int field_number) - метод сравнения текущего и переданного аргументов, если равны то true
largest_element(_element *other_element, int field_number)  - метод сравнения текущего и переданного аргументов, если первый больше второго то true
*/
struct _element {
	int _numbers[3];
	string _strings[2];

	/*конструктор без параметра*/
	_element() {
		//генерация трёх численных полей
		for (int i = 0; i < 3;)
			_numbers[i++] = rand() % 10;

		//генерация двух строк
		string tmp[2];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < rand() % 3 + 1; j++) {
				tmp[i] += (char)(rand() % 26 + 65);
			}
			_strings[i] = tmp[i];
		}
	}

	/*конструктор с параметром (first-первое число, second-второе число, third-третье число, str_f-первая строка, str_s-вторая строка)*/
	_element(int first, int second, int third, string str_f, string str_s) {
		_numbers[0] = first;
		_numbers[1] = second;
		_numbers[2] = third;
		_strings[0] = str_f;
		_strings[1] = str_s;
	}

	/*деструктор*/
	~_element() {}

	/*сравнение двух элементов; возращает true, если элементы равны, иначе false*/
	bool compare_element(_element *other_element, int field_number) {

		switch (field_number) {
		//сравнение числовых полей
		case 1: {
			if (this->_numbers[0] == other_element->_numbers[0])
				return true;
			else
				return false;
			break;
		}
		case 2: {
			if (this->_numbers[1] == other_element->_numbers[1])
				return true;
			else
				return false;
			break;
		}
		case 3: {
			if (this->_numbers[2] == other_element->_numbers[2])
				return true;
			else
				return false;
			break;
		}
		//сравнение строковых полей
		case 4: {
			if (this->_strings[0] == other_element->_strings[0])
				return true;
			else
				return false;
			break;
		}
		case 5: {
			if (this->_strings[1] == other_element->_strings[1]) 
				return true;
			else
				return false;
			break;
		}

		default: {
			return true;
			break;
		}
		}
	}

	/*сравнение двух элементов; возращает true, если первый элемент больше второго, иначе false*/
	bool largest_element(_element *other_element, int field_number) {

		switch (field_number) {
		//сравнение числовых полей
		case 1: {
			if (this->_numbers[0] > other_element->_numbers[0])
				return true;
			else
				return false;
			break;
		}
		case 2: {
			if (this->_numbers[1] > other_element->_numbers[1])
				return true;
			else
				return false;
			break;
		}
		case 3: {
			if (this->_numbers[2] > other_element->_numbers[2])
				return true;
			else
				return false;
			break;
		}
		//сравнение строковых полей
		case 4: {
			if (this->_strings[0] > other_element->_strings[0])
				return true;
			else
				return false;
			break;
		}
		case 5: {
			if (this->_strings[1] > other_element->_strings[1])
				return true;
			else
				return false;
			break;
		}

		default: {
			return true;
			break;
		}
		}
	}

};


/*
Класс "Пирамидальная сортировка"
поля:
	_element - елемент, содержащий 3 целых поля, и 2 строковых;
методы:
	reading_from_a_file(string name, vector<_element*> &elements) - чтение элементов из файла и запись их в вектор элементов
	sifting(vector<_element*> &tmp_elements, int current, int size, int number_of_sort_field, int first_index) - проссеивание элементов, для построения пирамиды
	sort(vector<_element*> &tmp_elements, int number_of_sort_field, int first_index) - пирамидальная сортировка
*/
class data_array {
public:
	vector<_element*>_elements;

	/*чтение элементов из файла*/
	void reading_from_a_file(string name) {

		ifstream fin; //входной поток
		fin.open(name); //открыли поток

		//читаем элементы
		while (!fin.eof()) {
			int first; fin >> first;
			int second; fin >> second;
			int third; fin >> third;
			string str_f; fin >> str_f;
			string str_s; fin >> str_s;
			_element *tmp = new _element(first, second, third, str_f, str_s);

			if (!fin.eof())
				_elements.push_back(tmp);
		}

		fin.close(); //закрыли поток
	}

	/*проссеивание, используется для построения пирамиды*/
	void sifting(vector<_element*> &tmp_elements, int current, int size, int number_of_sort_field, int first_index) {
		if (size == 1) return;

		int index_child= 0;

		//выбираем большего предка; если правого предка нет, то берем левого
		if ((current + 1) * 2 == size)			
			index_child = current * 2 + 1;
		else 
			//если первый элемент больше второго, по какому то столбцу, то 
			if (tmp_elements[current * 2 + 1]->largest_element(tmp_elements[current * 2 + 2], number_of_sort_field)) 
				index_child = current * 2 + 1;
			else
				index_child = current * 2 + 2;

		//если текущее число меньше предка, меняем их
		if (tmp_elements[index_child]->largest_element(tmp_elements[current], number_of_sort_field)) {
			//переставляем во вспомогательном векторе
			_element *tmp = tmp_elements[current];
			tmp_elements[current] = tmp_elements[index_child];
			tmp_elements[index_child] = tmp;

			//переставляем в основном векторе
			_element *tmpp = _elements[current + first_index];
			_elements[current + first_index] = _elements[index_child + first_index];
			_elements[index_child + first_index] = tmpp;
		}
		//если предок больше, меняем их
		if (index_child * 2 + 2 <= size)
			sifting(tmp_elements, index_child, size, number_of_sort_field, first_index);
	}


	/*сортировка пирамидой*/
	void sort(vector<_element*> &tmp_elements, int number_of_sort_field, int first_index) {

		//1 этап, преобразование в пирамиду путём проссеивания
		for (int i = tmp_elements.size() / 2 - 1; i >= 0; i--) {
			sifting(tmp_elements, i, tmp_elements.size(), number_of_sort_field, first_index);
		}

		//2 этап, сортировка пирамиды
		for (int i = tmp_elements.size() - 1; i >= 1; i--) {

			//меняем первый и последний элемент во вспомогательном векторе
			_element* tmp = tmp_elements[0];		
			tmp_elements[0] = tmp_elements[i];		
			tmp_elements[i] = tmp;					

			//меняем в основном векторе
			_element *tmpp = _elements[0 + first_index];
			_elements[0 + first_index] = _elements[i + first_index];
			_elements[i + first_index] = tmpp;

			//просеиваем
			sifting(tmp_elements, 0, i, number_of_sort_field, first_index);	
		}
	}
};


/*основная функция*/
int main() {
	srand(time(0));
	setlocale(LC_ALL, "rus");
	data_array pyramid;
	

	//создаем файл, если его не существует
	ifstream ifs;
	ifs.open("input.txt");
	ifs.close();

	if (!ifs) {
		ofstream ofs;
		ofs.open("input.txt");

		for (int i = 0; i < count_elements; i++) {
			_element *tmp = new _element();
			ofs << tmp->_numbers[0] << " " << tmp->_numbers[1] << " " << tmp->_numbers[2] << " " << tmp->_strings[0] << " " << tmp->_strings[1] << " " << endl;
		}
		ofs.close();
	}

	//читаем строки из файла
	pyramid.reading_from_a_file("input.txt");

	//ввод полей для сортировки
	int sort_fields[3];
	cout << "Введите номера трёх столбцов для сортировки через пробел: ";
	cin >> sort_fields[0] >> sort_fields[1] >> sort_fields[2];

	//первая сортировка по всему столбцу
	vector<_element*> tmp_elements;							// вспомогательный вектор из одинаковых элементов
	for (int i = 0; i < pyramid._elements.size(); i++) 
		tmp_elements.push_back(pyramid._elements[i]);

	pyramid.sort(tmp_elements, sort_fields[0], 0);

	//теперь сортируем в зависимости от прошлой сортировки
	for (int i = 1; i < 3; i++) {

		tmp_elements.clear();						//очищаем вспомогательный вектор

		int index = sort_fields[i];					//индекс сортируемого столбца
		int index_last = sort_fields[i - 1];		//индекс прошлого сортированного столбца

		int index_sample = 0;								//индекс первого элемента, с которого идут одинаковые
		_element* sample = pyramid._elements[index_sample];	//присваиваем образцу первый элемент, далее с ним и будем сравнивать
		
		int size_obj = pyramid._elements.size(); //размер вектора элементов

		for (int j = 0; j < size_obj; j++) {

			if ( sample->compare_element(pyramid._elements[j], index_last) )
				tmp_elements.push_back(pyramid._elements[j]);
			else {
				pyramid.sort(tmp_elements, index, index_sample);
				tmp_elements.clear();
				sample =  pyramid._elements[j];
				index_sample = j;
				tmp_elements.push_back(pyramid._elements[j]);
			}

			if (j == pyramid._elements.size() - 1) {
				pyramid.sort(tmp_elements, index, index_sample);
			}
		}
	}

	//результат пишем в файл
	ofstream ofs;
	ofs.open("output.txt");
	for (int i = 0; i <  pyramid._elements.size(); i++) 
		ofs << pyramid._elements[i]->_numbers[0] << " " << pyramid._elements[i]->_numbers[1] << " " << pyramid._elements[i]->_numbers[2] << " " << pyramid._elements[i]->_strings[0] << " " << pyramid._elements[i]->_strings[1] << endl;
	
	ofs.close();

	system("output.txt");
	
}
