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
��������� "�������"
����:
_numbers - ������������� ������ � 3 ����������;
_strings - ������, ���������� 2 ������;
������:
_element() - ����������� ��� ���������;
_element(int first, int second, int third, string str_f, string str_s) - ����������� � ����������;
~_element() - ���������� ��������
compare_element(_element *other_element, int field_number) - ����� ��������� �������� � ����������� ����������, ���� ����� �� true
largest_element(_element *other_element, int field_number)  - ����� ��������� �������� � ����������� ����������, ���� ������ ������ ������� �� true
*/
struct _element {
	int _numbers[3];
	string _strings[2];

	/*����������� ��� ���������*/
	_element() {
		//��������� ��� ��������� �����
		for (int i = 0; i < 3;)
			_numbers[i++] = rand() % 10;

		//��������� ���� �����
		string tmp[2];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < rand() % 3 + 1; j++) {
				tmp[i] += (char)(rand() % 26 + 65);
			}
			_strings[i] = tmp[i];
		}
	}

	/*����������� � ���������� (first-������ �����, second-������ �����, third-������ �����, str_f-������ ������, str_s-������ ������)*/
	_element(int first, int second, int third, string str_f, string str_s) {
		_numbers[0] = first;
		_numbers[1] = second;
		_numbers[2] = third;
		_strings[0] = str_f;
		_strings[1] = str_s;
	}

	/*����������*/
	~_element() {}

	/*��������� ���� ���������; ��������� true, ���� �������� �����, ����� false*/
	bool compare_element(_element *other_element, int field_number) {

		switch (field_number) {
		//��������� �������� �����
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
		//��������� ��������� �����
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

	/*��������� ���� ���������; ��������� true, ���� ������ ������� ������ �������, ����� false*/
	bool largest_element(_element *other_element, int field_number) {

		switch (field_number) {
		//��������� �������� �����
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
		//��������� ��������� �����
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
����� "������������� ����������"
����:
	_element - �������, ���������� 3 ����� ����, � 2 ���������;
������:
	reading_from_a_file(string name, vector<_element*> &elements) - ������ ��������� �� ����� � ������ �� � ������ ���������
	sifting(vector<_element*> &tmp_elements, int current, int size, int number_of_sort_field, int first_index) - ������������ ���������, ��� ���������� ��������
	sort(vector<_element*> &tmp_elements, int number_of_sort_field, int first_index) - ������������� ����������
*/
class data_array {
public:
	vector<_element*>_elements;

	/*������ ��������� �� �����*/
	void reading_from_a_file(string name) {

		ifstream fin; //������� �����
		fin.open(name); //������� �����

		//������ ��������
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

		fin.close(); //������� �����
	}

	/*������������, ������������ ��� ���������� ��������*/
	void sifting(vector<_element*> &tmp_elements, int current, int size, int number_of_sort_field, int first_index) {
		if (size == 1) return;

		int index_child= 0;

		//�������� �������� ������; ���� ������� ������ ���, �� ����� ������
		if ((current + 1) * 2 == size)			
			index_child = current * 2 + 1;
		else 
			//���� ������ ������� ������ �������, �� ������ �� �������, �� 
			if (tmp_elements[current * 2 + 1]->largest_element(tmp_elements[current * 2 + 2], number_of_sort_field)) 
				index_child = current * 2 + 1;
			else
				index_child = current * 2 + 2;

		//���� ������� ����� ������ ������, ������ ��
		if (tmp_elements[index_child]->largest_element(tmp_elements[current], number_of_sort_field)) {
			//������������ �� ��������������� �������
			_element *tmp = tmp_elements[current];
			tmp_elements[current] = tmp_elements[index_child];
			tmp_elements[index_child] = tmp;

			//������������ � �������� �������
			_element *tmpp = _elements[current + first_index];
			_elements[current + first_index] = _elements[index_child + first_index];
			_elements[index_child + first_index] = tmpp;
		}
		//���� ������ ������, ������ ��
		if (index_child * 2 + 2 <= size)
			sifting(tmp_elements, index_child, size, number_of_sort_field, first_index);
	}


	/*���������� ���������*/
	void sort(vector<_element*> &tmp_elements, int number_of_sort_field, int first_index) {

		//1 ����, �������������� � �������� ���� ������������
		for (int i = tmp_elements.size() / 2 - 1; i >= 0; i--) {
			sifting(tmp_elements, i, tmp_elements.size(), number_of_sort_field, first_index);
		}

		//2 ����, ���������� ��������
		for (int i = tmp_elements.size() - 1; i >= 1; i--) {

			//������ ������ � ��������� ������� �� ��������������� �������
			_element* tmp = tmp_elements[0];		
			tmp_elements[0] = tmp_elements[i];		
			tmp_elements[i] = tmp;					

			//������ � �������� �������
			_element *tmpp = _elements[0 + first_index];
			_elements[0 + first_index] = _elements[i + first_index];
			_elements[i + first_index] = tmpp;

			//����������
			sifting(tmp_elements, 0, i, number_of_sort_field, first_index);	
		}
	}
};


/*�������� �������*/
int main() {
	srand(time(0));
	setlocale(LC_ALL, "rus");
	data_array pyramid;
	

	//������� ����, ���� ��� �� ����������
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

	//������ ������ �� �����
	pyramid.reading_from_a_file("input.txt");

	//���� ����� ��� ����������
	int sort_fields[3];
	cout << "������� ������ ��� �������� ��� ���������� ����� ������: ";
	cin >> sort_fields[0] >> sort_fields[1] >> sort_fields[2];

	//������ ���������� �� ����� �������
	vector<_element*> tmp_elements;							// ��������������� ������ �� ���������� ���������
	for (int i = 0; i < pyramid._elements.size(); i++) 
		tmp_elements.push_back(pyramid._elements[i]);

	pyramid.sort(tmp_elements, sort_fields[0], 0);

	//������ ��������� � ����������� �� ������� ����������
	for (int i = 1; i < 3; i++) {

		tmp_elements.clear();						//������� ��������������� ������

		int index = sort_fields[i];					//������ ������������ �������
		int index_last = sort_fields[i - 1];		//������ �������� �������������� �������

		int index_sample = 0;								//������ ������� ��������, � �������� ���� ����������
		_element* sample = pyramid._elements[index_sample];	//����������� ������� ������ �������, ����� � ��� � ����� ����������
		
		int size_obj = pyramid._elements.size(); //������ ������� ���������

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

	//��������� ����� � ����
	ofstream ofs;
	ofs.open("output.txt");
	for (int i = 0; i <  pyramid._elements.size(); i++) 
		ofs << pyramid._elements[i]->_numbers[0] << " " << pyramid._elements[i]->_numbers[1] << " " << pyramid._elements[i]->_numbers[2] << " " << pyramid._elements[i]->_strings[0] << " " << pyramid._elements[i]->_strings[1] << endl;
	
	ofs.close();

	system("output.txt");
	
}
