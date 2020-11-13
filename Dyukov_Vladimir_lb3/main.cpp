#include "Header.h"
#include <windows.h>
#include <fstream>
#include <conio.h>

void sys_print() {

	system("cls");
	std::cout << "��������� �� ��������� �������� ��������\n���������: (a N (b ...)) , ��� N - ������ �����.\n\n";
}

int button_get(std::string* buttons, int height, int width, std::string title = "") {

	int _w = 0, _h = 0;

	std::cout << title;

	while (1) {

		for (int i = 0; i < height; i++) {
			std::cout << '\r';
			for (int j = 0; j < width; j++) {

				if (i == _h && j == _w) std::cout << "\t<" << buttons[i * width + j] << ">";
				else std::cout << "\t " << buttons[i * width + j] << " ";
			}
		}

		unsigned char ch = _getch();
		if (ch == 224) ch = _getch();
		switch (ch) {
		case 72:
			_h--;
			break;
		case 80:
			_h++;
			break;
		case 75:
			_w--;
			break;
		case 77:
			_w++;
			break;
		case 13:
			return _h * width + _w + 1;
		case 27:
			return 0;
		}

		_w = abs(_w) % width;
		_h = abs(_h) % height;
	}
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool looping = true;

	while (looping) {

		sys_print();
		std::string str1[] = { "�� �����", "�� �������" };
		int way = button_get(str1, 1, 2, "����� ������� �� ������ ������� ������?\n");
		if (way == 0) return 0;
		std::cout << "\n";

		std::ifstream file;
		TwoTree trees;
		
		if (way == 1) {
			
			
			while (!file.is_open()) {

				std::cout << "\n������� ��� �����:\n\n";
				std::string name;
				std::cin >> name;
				file.open(name);
				std::cout << "\n������ ����� ����� �����.\n\n";
				std::string str2[] = { "��", "���" };
				int check = button_get(str2, 1, 2, "����������� ������ ��� ��� ���?\n");
				if (check == 2) break;
				if (check == 0) return 0;
				sys_print();
			}
		}

		while (file.is_open() || way == 2) {
			
			Tree* f = nullptr, * s = nullptr;

			if (way == 1) {

				file >> &f >> &s;
				trees = TwoTree(f, s);
			}
			if (way == 2) {

				std::cout << "\n������� ������ �������� ������\n";
				std::cin >> &f;
				std::cout << "\n������� ������ �������� ������\n";
				std::cin >> &s;
				trees = TwoTree(f, s);
			}

			sys_print();
			std::cout << "�� �����:\n\n" << f << '\n' << s << '\n';
			std::cout << "\n����������:\n\n";

			bool nothing = true;
			if (trees.isEqual()) { std::cout << "+ ������� �����\n"; nothing = false; }
			if (trees.isMirrorEqual()) { std::cout << "+ ������� ��������� �����\n"; nothing = false; }
			if (trees.isSuch()) { std::cout << "+ ������� �������\n"; nothing = false; }
			if (trees.isMirrorSuch()) { std::cout << "+ ������� ��������� �������\n"; nothing = false; }
			if (nothing) std::cout << "� �������� ��� ����������.\n";

			if (f) delete f;
			if (s) delete s;

			if (way == 2) {

				std::cout << "\n";
				std::string str2[] = { "����������" };
				if (!button_get(str2, 1, 1)) return 0;
				else break;
			}
			if (way == 1) {

				std::cout << "\n";
				std::string str2[] = { "��", "���" };
				int fl = button_get(str2, 1, 2, "���������� ����� �� �����?\n");
				if (fl == 0) return 0;
				if (fl == 1) continue;
				if (fl == 2) break;
			}
		}
		if (file.is_open()) file.close();
	}

	return 0;
}