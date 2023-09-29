#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

struct Condition
{
	char Simvol = ' ';
	char zamena = ' ';
	char sdvig_lenti = 'E';
	string sostoianie_1;// состояние принимающее
	string sostoianie_2;// состояние после

};

vector<char> dictionary;//алфавит (для начального ввода)
vector<string> states;//состояния

string lenta;
int lenta_i;//лента
string *Tape_with_additional_place;

char conditions;//условия (переменные для ввода новых условий)
char simvol;
string name_state;

int N;
Condition *replacement;


void Dctionary() {
	cout << "Ввёдем алфавит : ";
	do { //заполняем алфавит
		cin >> simvol;
		if (simvol != '.') dictionary.push_back(simvol);
		else break;
	} while (true);

	//@ - лямбда
	dictionary.push_back('@'); //символ для заполнения пустоты

	cout << "Алфавит -> ";
	for (char c : dictionary) cout << c << " ";
}

void States() {
	cout << "\nсостояние q0 занято под выход\nВвёдем состояния : ";
	do { //заполняем состояния
		cin >> name_state;
		if (name_state != ".") states.push_back(name_state);
		else break;
	} while (true);

	cout << "Состояния -> ";
	for (string s : states) cout << s << " ";
	cout << "q0";
}

void Сonditions() {
	//N = dictionary.size() * states.size(); //количество условий
	cout << "\nВсего комбинаций нужно ввести " << N<<"\n"; 
	int i = 0;

	for (char c : dictionary) { //символ
		for (string s : states) { //состояние
			cout << "РАБОТАЕМ С   (  " << c << s << "  )\n";
			//каждый символ записывает условие  для каждого из имеющихся состояний 
			cout << "На что заменить символ " << c <<" --> "; //замена символа
			cin >> simvol;
			cout << "Из состония " << s << " -->  в состояние --> "; //замена символа
			cin >> name_state;
			cout << "Сдвиг по ленте " << " -->  в R,L,E  --> "; //замена символа E- знак равно, R - право L - лево
			cin >> conditions;

			replacement[i].Simvol = c;//запоминаем какой символ был изначально 
			replacement[i].sdvig_lenti = conditions; //создаем переменную со всем условиями перехода
			replacement[i].sostoianie_1 = s; //запоминаем состояние , котрое у нас должно быть
			replacement[i].sostoianie_2 = name_state; //новое состояние
			replacement[i].zamena = simvol; // символ после замены   

			i++;//сдвигаемся по структуре
		}
	}
}

void ReadTape() {
	cout << "Введите строку";
	cin >> lenta; //ввод нашей строки
	int j = 0; //сравнения количества элементов переменной lenta

	Tape_with_additional_place = new string[(lenta.length()) * 3]; //строка с бльшим кол элементов

	lenta_i = lenta.length(); //откуда читать ленту

	for (int i = 0; i < lenta.length() * 3;) {
		if (i > lenta.length()- 1 && lenta.length() != j) { //создаем строку в 3 раза больше имеющейся
			for (char c : lenta) {

				Tape_with_additional_place[i] = c;
				i++;
				j++;
			}
		}
		else {
			Tape_with_additional_place[i] = "@"; //ERROR
			i++;
		}
	}

}

void Show_tape() {
	if(name_state != "q0")
	cout << "ЛЕНТА СЧИТЫВАЕТ " << Tape_with_additional_place[lenta_i]<<" \n Строка ->";

	for (int i = 0; i < lenta.length() * 3; i++) { //заполняем ленту (показывает изменения на ленте)
		cout << Tape_with_additional_place[i];
	}
	
	cout << "\n";
}

void Moving_tape() { //движение по ленте
	while (true) { //пока лента не кончится


		Show_tape();

		
		for (int i = 0; i < N; i++) { // выполняет операции на ленте
			string s;
			s.push_back(replacement[i].Simvol);
			if (Tape_with_additional_place[lenta_i] == s && name_state == replacement[i].sostoianie_1) { //если нашли символ, то проверяем состояние к которому оно может принадлежать
				if (replacement[i].sdvig_lenti == 'R') {

					Tape_with_additional_place[lenta_i] = replacement[i].zamena;
					name_state = replacement[i].sostoianie_2; // name_state - тут это наше новое состояние
					lenta_i++;
					if (name_state == "q0") {
						cout << "ВЫВОД: ";
						Show_tape();
						cout << "\nEND";
						return;
					}
					break;
				}
				else if (replacement[i].sdvig_lenti == 'L') {

					Tape_with_additional_place[lenta_i] = replacement[i].zamena;
					name_state = replacement[i].sostoianie_2; // name_state - тут это наше новое состояние
					lenta_i--;
					if (name_state == "q0") {
						cout << "ВЫВОД: ";
						Show_tape();
						cout << "\nEND";
						return;
					}
					break;
				}
				else if (replacement[i].sdvig_lenti == 'E') {

					Tape_with_additional_place[lenta_i] = replacement[i].zamena;
					name_state = replacement[i].sostoianie_2; // name_state - тут это наше новое состояние
					if (name_state == "q0") {
						cout << "ВЫВОД: ";
						Show_tape();
						cout << "\nEND";
						return;
					}
					break;
				}
			}	
		}
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	Dctionary();
	States();
	N = dictionary.size() * states.size(); //количество условий
	replacement = new Condition[N]; //для запоминания команд
	Сonditions();
	ReadTape();
	cout << "Вводим начальное состояние";
	cin >> name_state;
	Moving_tape();
	return 0;
}