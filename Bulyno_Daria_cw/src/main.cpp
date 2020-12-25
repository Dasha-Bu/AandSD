#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

//������� ��� ���������� ��������
int iterations = 0;

//��������� ������
struct Node {
	int key;
	int size;
	Node* left;
	Node* right;
	Node(int k) {
		key = k;
		left = right = nullptr;
		size = 1;
	}
};

int getsize(Node* btree) {
	if (!btree) return 0;
	return btree->size;
}

int fixsize(Node* btree) {
	return btree->size = getsize(btree->left) + getsize(btree->right) + 1;
}

//������� ��� �������� ������������ ������ ������
int height(Node* btree){
	Node *temp = btree;
	int h1 = 0, h2 = 0;
	if (btree == NULL)return(0);
	if (btree->left) { h1 = height(btree->left); }
	if (btree->right) { h2 = height(btree->right); }
	return (max(h1, h2) + 1);
}

//������� ��� ���������� �������� ������
Node* find(Node* btree, int key){
	if (!btree) {
		iterations++;
		return 0;
	}
	if (key == btree->key) {
		iterations++;
		return btree;
	}
	if (key < btree->key) {
		iterations++;
		return find(btree->left, key);
	}
	else {
		iterations++;
		return find(btree->right, key);
	}
}

//������� ��� ������������ ������� �������� � ���
Node* usual_insert(Node* btree, int k){
	if (!btree) {
		iterations++;
		return new Node(k);
	}
	if (btree->key > k) {
		iterations++;
		btree->left = usual_insert(btree->left, k);
	}
	else {
		iterations++;
		btree->right = usual_insert(btree->right, k);
	}
	fixsize(btree);
	return btree;
}

//������� ��� �������� ������ ���������
Node* rotateright(Node* btree) {
	iterations++;
	//cout << "rotate R " << iterations << endl;
	Node* newbtree = btree->left;
	if (!newbtree) return btree;
	btree->left = newbtree->right;
	newbtree->right = btree;
	newbtree->size = btree->size;
	fixsize(btree);
	return newbtree;
}

//������� ��� �������� ����� ���������
Node* rotateleft(Node* btree) {
	iterations++;
	//cout << "rotate L " << iterations << endl;
	Node* newbtree = btree->right;
	if (!newbtree) return btree;
	btree->right = newbtree->left;
	newbtree->left = btree;
	newbtree->size = btree->size;
	fixsize(btree);
	return newbtree;
}

//������� ��� ������� � ������ �������� ������
Node* insertroot(Node* btree, int k) {
	if (!btree) {
		iterations++;
		//cout << "root new" << iterations << endl;
		return new Node(k);
	}
	if (k < btree->key) {
		iterations++;
		//cout << "root left " << iterations << endl;
		btree->left = insertroot(btree->left, k);
		return rotateright(btree);
	}
	else {
		iterations++;
		//cout << "root right " << iterations << endl;
		btree->right = insertroot(btree->right, k);
		return rotateleft(btree);
	}
}

//������� ��� ������ ������, ���������� �� 90 �������� ������ ������� �������
void Print(Node* btree, int level) {
	if (btree->right != nullptr) {
		Print(btree->right, level + 1);
	}
	for (int i = 0; i < level; i++) {
		cout << "    ";
	}
	cout << btree->key << "\n";
	if (btree->left != nullptr) {
		Print(btree->left, level + 1);
	}
}

//������� ������� �������� � ����������������� ������
Node* insert(Node* btree, int k) {
	if (!btree) {
		iterations++;
		//cout << "new " << iterations << endl;
		return new Node(k);
	}
	if (rand() % (btree->size + 1) == 0) {
		//cout << "������� � ������ �������� " << k << endl;
		btree = insertroot(btree, k);
		//Print(btree, 0);
		//cout << endl;
		return btree;
	}
	if (btree->key > k){
		iterations++;
		//cout << "left " << iterations << endl;
		btree->left = insert(btree->left, k);
	}		
	else{
		iterations++;
		//cout << "right " << iterations << endl;
		btree->right = insert(btree->right, k);
	}
	fixsize(btree);
	return btree;
}

//������� ��� ����������� ���� �����������
Node* join(Node* btree1, Node* btree2) {
	if (!btree1) {
		iterations++;
		//cout << "no left " << iterations << endl;
		return btree2;
	}
	if (!btree2) {
		iterations++;
		//cout << "no right " << iterations << endl;
		return btree1;
	}
	if (rand() % (btree1->size + btree2->size) < btree1->size) {
		iterations++;
		//cout << "right join " << iterations << endl;
		btree1->right = join(btree1->right, btree2);
		fixsize(btree1);
		return btree1;
	}
	else {
		iterations++;
		//cout << "left join " << iterations << endl;
		btree2->left = join(btree1, btree2->left);
		fixsize(btree2);
		return btree2;
	}
}

//������� ��� �������� �������� �� ������
Node* remove(Node* btree, int k) {
	if (!btree) {
		iterations++;
		//cout << "this " << iterations << endl;
		return btree;
	}
	if (btree->key == k) {
		Node* newbtree = join(btree->left, btree->right);
		delete btree;
		return newbtree;
	}
	else if (k < btree->key) {
		iterations++;
		//cout << "left " << iterations << endl;
		btree->left = remove(btree->left, k);
	}
	else {
		iterations++;
		//cout << "right " << iterations << endl;
		btree->right = remove(btree->right, k);
	}
	return btree;
}

//������� ��������� ��������� ��� �������� ������
vector<int> generate_average(int n) {
	vector<int> values;
	for (int i = 0; i < n; i++) {
		int value = rand () %10000;
		values.push_back(value);
	}
	if(n > 2){
		int count1 = 0;
		int count2 = 0;
		for (int i = 0; i < n; i++) {
			if (values[i] < values[i + 1] || values[i] == values[i + 1]) count1++;
			if (values[i] > values[i + 1] || values[i] == values[i + 1]) count2++;
		}
		if (count2 == n  || count1 == n) generate_average(n); //���������� �������� ������� ������
		else return values;
	}
	return values;
}

//������� ��������� ��������� ��� ������� ������
vector<int> generate_worst(int n) {
	vector<int> values;
	for (int i = 0; i < n; i++) {
		int value = rand() % 10000;
		values.push_back(value);
	}
	int chance = rand() % 2; //��������������� ����������� ��������� �� ����������� � ��������
	if (chance == 0) sort(values.begin(), values.end());
	if (chance == 1) sort(values.begin(), values.end(), greater<int>());
	return values;
}

//������� ��� ������ �� ���������������� ���������
void function_for_bst(string generation, Node* tree, Node* newtree) {
	srand(time(0));
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2, start3, end3; //������������ ��� �������� ������� ���������� ��������
	int value; //������������ ��� ����� ������ ��������
	string operation; //������������ ��� ������ ��������
	string menu_for_value;
	while (generation == "y" || generation == "yes") {
		iterations = 0;
		cout << "�������� ��������, ������� ������ �����������:\n0. �������� ������ ������.\n1. ����� ��������.\n2. ������� ��������.\n3. �������� ��������.\n";
		cout << "��������: ";
		cin >> operation;
		if (operation == "0") break;
		else if (operation == "1") { //����� �������� � ������
			cout << "�������� ��������, ������� ������ �����������:\n1. ������� ��������.\n2.������������� ��������.\n";
			cout << "��������: ";
			cin >> menu_for_value;
			if (menu_for_value == "1") {
				cout << "������� ��������, ������� ������ �����: ";
				cin >> value;
			}
			else value = rand() % 10000;
			start1 = chrono::system_clock::now(); //������ �������� �������
			newtree = find(tree, value);
			end1 = chrono::system_clock::now(); //����� �������� �������
			chrono::duration<double> duration1 = end1 - start1; //���������� ������� ������ �������
			if (!newtree) cout << "������� �������� ��� � ������.\n";
			else {
				if(fixsize(newtree) <= 20) Print(newtree, 0);
				cout << endl << "���������� �������� ��� ������ ������ ��������: " << iterations << endl;
				cout << "�����, ����������� �� ����� ������ ��������: " << duration1.count() << "s\n";
			}
		}
		else if (operation == "2") { //���������� �������� � ������
			cout << "�������� ��������, ������� ������ �����������:\n1. ������� ��������.\n2.������������� ��������.\n";
			cout << "��������: ";
			cin >> menu_for_value;
			if (menu_for_value == "1") {
				cout << "������� ��������, ������� ������ ��������: ";
				cin >> value;
			}
			else value = rand() % 10000;
			start2 = chrono::system_clock::now(); //������ �������� �������
			tree = insert(tree, value);
			end2 = chrono::system_clock::now(); //����� �������� �������
			chrono::duration<double> duration2 = end2 - start2; //���������� ������� ������ �������
			cout << "***************************************\n";
			if (1 + fixsize(tree) <= 20) {
				cout << "����� ��������� ��� � �������������:" << endl;
				Print(tree, 0);
			}
			cout << endl << "���������� �������� ��� ���������� ������ ��������: " << iterations << endl;
			cout << "�����, ����������� �� ���������� ������ ��������: " << duration2.count() << "s\n";
		}
		else if (operation == "3") { //�������� �������� � ������
			cout << "�������� ��������, ������� ������ �����������:\n1. ������� ��������.\n2.������������� ��������.\n";
			cout << "��������: ";
			cin >> menu_for_value;
			if (menu_for_value == "1") {
				cout << "������� ��������, ������� ������ �������: ";
				cin >> value;
			}
			else value = rand() % 10000;
			if (find(tree, value)) { //�������� �� ������� �������� � ������
				if (fixsize(tree) > 1) { //�������� �� ����������� ��������
					iterations = 0;
					start3 = chrono::system_clock::now(); //������ �������� �������
					tree = remove(tree, value);
					end3 = chrono::system_clock::now(); //����� �������� �������
					chrono::duration<double> elapsed_seconds3 = end3 - start3; //���������� ������� ������ �������
					cout << "***************************************\n";
					if (1 + fixsize(tree) <= 20) {
						cout << "����� ��������� ��� � �������������:" << endl;
						Print(tree, 0);
					}
					cout << endl << "���������� �������� ��� �������� ������ ��������: " << iterations << endl;
					cout << "�����, ����������� �� �������� ������ ��������: " << elapsed_seconds3.count() << "s\n";
				}
				else cout << endl << "������ ������� �� ������ ��������." << endl;
			}
			else cout << "������� �������� ��� � ������." << endl;
		}
		else {
			cout << "�������� ������� �������.";
		}
		cout << endl;
		cout << "������� 'yes/y', ���� ������ ���������� �������� � ������ ���: ";
		cin >> generation;
		if (generation == "y" || generation == "yes") continue;
		else {
			tree = nullptr;
			iterations = 0;
		}
	}
}

//������� �������� ������ ��� �������� ������
void func_for_researhing_average(int size, int new_iterations, string generation, Node* tree, Node* btree, Node* newtree, vector<int> average_case) {
	srand(time(0));
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2; //������������ ��� �������� ������� ��������� ��������
	cout << "������� ���������� ���������: ";
	cin >> size;
	while (size <= 0) {
		cout << "����������� ������� ���������� ���������.\n������� ���������� ���������: ";
		cin >> size;
	}
	tree = nullptr;
	average_case = generate_average(size); //����������� ������ �� ��������� ����� ��� �������� ������
	if (size <= 100) {
		for (int i = 0; i < size; i++) {
			cout << average_case[i] << " ";
		}
	}
	cout << endl;
	start1 = chrono::system_clock::now(); //������ �������� ������� ��� ��. ��� � �������������
	for (int i = 0; i < size; i++) {
		tree = insert(tree, average_case[i]);
	}
	end1 = chrono::system_clock::now(); //����� �������� ������� ��� ��. ��� � �������������
	chrono::duration<double> duration1 = end1 - start1; //���������� ������� ������ ������� ��� ��. ��� � �������������
	cout << "��������� ��� � ������������� � ������� ������:" << endl;
	if (size <= 20) Print(tree, 0);
	new_iterations = iterations;
	cout << endl << "������ ���������� ��� � �������������: " << height(tree) << endl;
	cout << "���������� �������� ��� ���������� ��� � �������������: " << iterations << endl;
	cout << "�����, ����������� �� ���������� ������ ��������: " << duration1.count() / size << "s";
	cout << endl;
	start2 = chrono::system_clock::now(); //������ �������� ������� ��� ��. ���
	for (int i = 0; i < size; i++) {
		btree = usual_insert(btree, average_case[i]);
	}
	end2 = chrono::system_clock::now(); //����� �������� ������� ��� ��. ���, ������� ���������� ��� ���������
	chrono::duration<double> duration2 = end2 - start2; //���������� ������� ������ ������� ��� ��. ���, ������� ���������� ��� ���������
	cout << "��������� ��� ��� ���������:" << endl;
	if (size <= 10) Print(btree, 0);
	cout << endl << "������ ���������� ���: " << height(btree) << endl;
	cout << "���������� �������� ��� ���������� ���: " << iterations - new_iterations << endl;
	cout << "�����, ����������� �� ���������� ������ ��������: " << duration2.count() / size << "s\n";
	generation = "y";
	function_for_bst(generation, tree, newtree);
}

//������� �������� ������ ��� ������� ������
void func_for_researching_worst(int size, int new_iterations, string generation, Node* tree, Node* btree, Node* newtree, vector<int> worst_case) {
	srand(time(0));
	chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2; //������������ ��� �������� ������� ��������� ��������
	cout << "������� ���������� ���������: ";
	cin >> size;
	while (size <= 0) {
		cout << "����������� ������� ���������� ���������.\n������� ���������� ���������: ";
		cin >> size;
	}
	tree = nullptr;
	worst_case = generate_worst(size); //����������� ������ �� ��������� ����� ��� ������� ������
	if (size <= 100) {
		for (int i = 0; i < size; i++) {
			cout << worst_case[i] << " ";
		}
	}
	cout << endl;
	start1 = chrono::system_clock::now(); //������ �������� ������� ��� ��. ��� � �������������
	for (int i = 0; i < size; i++) {
		tree = insert(tree, worst_case[i]); 
	}
	end1 = chrono::system_clock::now(); //����� �������� ������� ��� ��. ��� � �������������
	chrono::duration<double> duration1 = end1 - start1; //���������� ������� ������ ������� ��� ��. ��� � �������������
	cout << endl << "��������� ��� � ������������� � ������ ������:" << endl;
	if (size <= 20) Print(tree, 0);
	new_iterations = iterations;
	cout << endl << "������ ���������� ��� � �������������: " << height(tree) << endl;
	cout << "���������� �������� ��� ���������� ��� � �������������: " << iterations << endl;
	cout << "�����, ����������� �� ���������� ������ ��������: " << duration1.count() / size << "s";
	cout << endl;
	start2 = chrono::system_clock::now(); //������ �������� ������� ��� ��. ���, ������� ���������� ��� ���������
	for (int i = 0; i < size; i++) {
		btree = usual_insert(btree, worst_case[i]);
	}
	end2 = chrono::system_clock::now();  //����� �������� ������� ��� ��. ���, ������� ���������� ��� ���������
	chrono::duration<double> duration2 = end2 - start2; //���������� ������� ������ ������� ��� ��. ���, ������� ���������� ��� ���������
	cout << "��������� ��� ��� ���������:" << endl;
	if (size <= 10) Print(btree, 0);
	cout << endl << "������ ���������� ���: " << height(btree) << endl;
	cout << "���������� �������� ��� ���������� ���: " << iterations - new_iterations << endl;
	cout << "�����, ����������� �� ���������� ������ ��������: " << duration2.count() / size << "s\n";
	cout << endl;
	generation = "y";
	function_for_bst(generation, tree, newtree);
}

int main() {
	setlocale(LC_ALL, "Russian");
	int new_iterations = 0;
	string start_end; //������������ ��� ������ ��������� � �������� �����/������
	string menu_for_generation; //������������ � �������� ���� �� ��������� ��������
	string menu_for_creation; //������������ � �������� ���� �� ��������� ���������� ������
	string generation; //������������ ��� ������ �� ��������������� �������
	cout << "������� 'yes/y', ���� ������ ������ �������� � ���: ";
	cin >> start_end;
	while (start_end == "y" || start_end =="yes"){
		int size;
		cout << "�������� ��������, ������� ������ �����������:\n";
		cout << "0. ��������� ������.\n1. ������������� ��������� ��� � ������������� � �������� ��� ������.\n2. ��������� ��������� ��� � �������������.\n";
		string menu; //������������ � �������� ���� ���������
		cout << "��������: ";
		cin >> menu;
		vector<int> average_case;
		vector<int> worst_case;
		Node* tree = nullptr;
		Node* btree = nullptr;
		Node* newtree = nullptr;
		if(menu == "0") break;
		else if (menu == "1") { //��������� ���������� ��� � ������������� � ������
			menu_for_generation = "y";
			while (menu_for_generation == "y" || menu_for_generation == "yes") { //���� ������ ��������� ������
				cout << "�������� ��������, ������� ������ �����������:\n1. ��������� ��������� � ������� ������.\n2. ��������� ��������� � ������ ������.\n";
				cout << "��������: ";
				string type_generation; //������������ ��� ����������� ���� ���������
				cin >> type_generation;
				if (type_generation == "1") func_for_researhing_average(size, new_iterations, generation, tree, btree, newtree, average_case);
				else if (type_generation == "2") func_for_researching_worst(size, new_iterations, generation, tree, btree, newtree, average_case);
				else cout << "�������� ������� �������.";
				cout << endl;
				cout << "������� 'yes/y', ���� ������ ���������� �������� � ���������� ���: ";
				cin >> menu_for_generation;
				if (menu_for_generation == "y" || menu_for_generation == "yes") {
					btree = nullptr;
					iterations = 0;
				}
			}
		}
		else if (menu == "2") { //�������� ���������� ��� � �������������
			srand(time(0));
			cout << "������� ���������� ���������: ";
			cin >> size;
			while (size <= 0) {
				cout << "����������� ������� ���������� ���������.\n������� ���������� ���������: ";
				cin >> size;
			}
			cout << "������� ������ ���������: ";
			for (int i = 0; i < size; i++) {
				int in;
				cin >> in;
				tree = insert(tree, in);
			}
			cout << "***************************************\n";
			cout << "��������� ��� � �������������:" << endl;
			Print(tree, 0);
			cout << endl;
			menu_for_creation = "y";
			while (menu_for_creation == "y" || menu_for_creation == "yes") { //���� ������ ������ ������ � �������
				cout << "�������� ��������, ������� ������ �����������:\n0. �������� ������ ������.\n1. ����� ��������.\n2. ������� ��������.\n3. �������� ��������.\n";
				cout << "��������: ";
				string method;
				int value;
				cin >> method;
				if (method == "0") break;
				else if (method == "1") { //����� ��������
					srand(time(0));
					cout << "������� ��������, ������� ������ �����: ";
					cin >> value;
					cout << endl;
					newtree = find(tree, value);
					if (!newtree) cout << "������� �������� ��� � ������.\n";
					else Print(newtree, 0);
				}
				else if (method == "2") { //���������� ��������
					srand(time(0));
					cout << "������� ��������, ������� ������ ��������: ";
					cin >> value;
					cout << endl;
					tree = insert(tree, value);
					cout << "***************************************\n";
					cout << "����� ��������� ��� � �������������:" << endl;
					Print(tree, 0);
				}
				else if (method == "3") { //�������� ��������
					srand(time(0));
					cout << "������� ��������, ������� ������ �������: ";
					cin >> value;
					if (find(tree, value)) {
						if (fixsize(tree) >= 1) {
							tree = remove(tree, value);
							cout << "***************************************\n";
							cout << "����� ��������� ��� � �������������:" << endl;
							Print(tree, 0);
						}
					}
					else cout << "������� �������� ��� � ������.\n";
				}
				else{
					cout << "�������� ������� �������.";
				}
				cout << endl;
				cout << "������� 'yes/y', ���� ������ ���������� �������� � ������ ���: ";
				cin >> menu_for_creation;
				if (menu_for_creation == "y" || menu_for_creation == "yes") continue;
				else iterations = 0;
			}
		}
		else{
			cout << "�������� ������� �������.";
		}
		cout << endl;
		cout << "������� 'yes/y', ���� ������ ���������� �������� � ���: ";
		cin >> start_end;
		if (start_end == "y" || start_end == "yes") iterations = 0;
	}
	cout << "������ ���������.";
	return 0;
}