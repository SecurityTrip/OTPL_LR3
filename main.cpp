#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

enum AState{S, A, B, C, D, G, H, E, F, Y, X, Z};
enum ELexType{alpha, digit, separator, eq, co1, co2, ao, other, semicolon};

struct Lex
{
    ELexType type;
	char* str;
	int len;
};

char* word(char* text, int begin, int end)		//функция, которая возщвращает слово
{
	char* slovo = new char[end - begin + 1];
	int i = 0;
	while (begin < end)
	{
		slovo[i] = text[begin];
		++i;
		++begin;
	}
	slovo[i] = '\0';
	return slovo;
}

void LexAnalysis(char* text, int size, vector <Lex>& vec)		//функция лексического анализа
{
	int pos = 0; //текущая позиция в строке
	AState state = AState::S; //текущее состояние
	Lex lexema; //текущая лексема
	int firstPos; //позиция начала лексемы
	int character;
	AState matr[12][9];  //матрица состояний

	matr[AState::S][separator] = AState::S; //разделитель
	matr[AState::S][alpha] = AState::A; //буква
	matr[AState::S][digit] = AState::B; //цифра
	matr[AState::S][co1] = AState::C;	//знак меньше
	matr[AState::S][co2] = AState::D;	//знак больше
	matr[AState::S][eq] = AState::G;	// знак равенства
	matr[AState::S][ao] = AState::H;	//арифметическая операция
	matr[AState::S][other] = AState::E; //остальное
	matr[AState::S][semicolon] = AState::X; //точка с запятой

	matr[AState::A][separator] = AState::F; //разделитель
	matr[AState::A][alpha] = AState::A; //буква
	matr[AState::A][digit] = AState::A; //цифра
	matr[AState::A][co1] = AState::F;	//знак меньше
	matr[AState::A][co2] = AState::F;	//знак больше
	matr[AState::A][eq] = AState::F;	// знак равенства
	matr[AState::A][ao] = AState::F;	//арифметическая операция
	matr[AState::A][other] = AState::E; //остальное
	matr[AState::A][semicolon] = AState::F; //точка с запятой

	matr[AState::B][separator] = AState::F; //разделитель
	matr[AState::B][alpha] = AState::E; //буква
	matr[AState::B][digit] = AState::B; //цифра
	matr[AState::B][co1] = AState::F;	//знак меньше
	matr[AState::B][co2] = AState::F;	//знак больше
	matr[AState::B][eq] = AState::F;	// знак равенства
	matr[AState::B][ao] = AState::F;	//арифметическая операция
	matr[AState::B][other] = AState::E; //остальное
	matr[AState::B][semicolon] = AState::F; //точка с запятой

	matr[AState::C][separator] = AState::F; //разделитель
	matr[AState::C][alpha] = AState::F; //буква
	matr[AState::C][digit] = AState::F; //цифра
	matr[AState::C][co1] = AState::F;	//знак меньше
	matr[AState::C][co2] = AState::Z;	//знак больше
	matr[AState::C][eq] = AState::Y;	// знак равенства
	matr[AState::C][ao] = AState::F;	//арифметическая операция
	matr[AState::C][other] = AState::F; //остальное
	matr[AState::C][semicolon] = AState::F; //точка с запятой

	matr[AState::D][separator] = AState::F; //разделитель
	matr[AState::D][alpha] = AState::F; //буква
	matr[AState::D][digit] = AState::F; //цифра
	matr[AState::D][co1] = AState::F;	//знак меньше
	matr[AState::D][co2] = AState::F;	//знак больше
	matr[AState::D][eq] = AState::Y;	// знак равенства
	matr[AState::D][ao] = AState::F;	//арифметическая операция
	matr[AState::D][other] = AState::F; //остальное
	matr[AState::D][semicolon] = AState::F; //точка с запятой

	matr[AState::G][separator] = AState::F; //разделитель
	matr[AState::G][alpha] = AState::F; //буква
	matr[AState::G][digit] = AState::F; //цифра
	matr[AState::G][co1] = AState::F;	//знак меньше
	matr[AState::G][co2] = AState::F;	//знак больше
	matr[AState::G][eq] = AState::F;	// знак равенства
	matr[AState::G][ao] = AState::F;	//арифметическая операция
	matr[AState::G][other] = AState::F; //остальное
	matr[AState::G][semicolon] = AState::F; //точка с запятой

	matr[AState::H][separator] = AState::F; //разделитель
	matr[AState::H][alpha] = AState::F; //буква
	matr[AState::H][digit] = AState::F; //цифра
	matr[AState::H][co1] = AState::F;	//знак меньше
	matr[AState::H][co2] = AState::F;	//знак больше
	matr[AState::H][eq] = AState::F;	// знак равенства
	matr[AState::H][ao] = AState::F;	//арифметическая операция
	matr[AState::H][other] = AState::F; //остальное
	matr[AState::H][semicolon] = AState::F; //точка с запятой

	matr[AState::E][separator] = AState::F; //разделитель
	matr[AState::E][alpha] = AState::E; //буква
	matr[AState::E][digit] = AState::E; //цифра
	matr[AState::E][co1] = AState::F;	//знак меньше
	matr[AState::E][co2] = AState::F;	//знак больше
	matr[AState::E][eq] = AState::F;	// знак равенства
	matr[AState::E][ao] = AState::F;	//арифметическая операция
	matr[AState::E][other] = AState::E; //остальное
	matr[AState::E][semicolon] = AState::F; //точка с запятой

	matr[AState::Y][separator] = AState::F; //разделитель
	matr[AState::Y][alpha] = AState::F; //буква
	matr[AState::Y][digit] = AState::F; //цифра
	matr[AState::Y][co1] = AState::F;	//знак меньше
	matr[AState::Y][co2] = AState::F;	//знак больше
	matr[AState::Y][eq] = AState::F;	// знак равенства
	matr[AState::Y][ao] = AState::F;	//арифметическая операция
	matr[AState::Y][other] = AState::F; //остальное
	matr[AState::Y][semicolon] = AState::F; //точка с запятой

	matr[AState::X][separator] = AState::F; //разделитель
	matr[AState::X][alpha] = AState::F; //буква
	matr[AState::X][digit] = AState::F; //цифра
	matr[AState::X][co1] = AState::F;	//знак меньше
	matr[AState::X][co2] = AState::F;	//знак больше
	matr[AState::X][eq] = AState::F;	// знак равенства
	matr[AState::X][ao] = AState::F;	//арифметическая операция
	matr[AState::X][other] = AState::F; //остальное
	matr[AState::X][semicolon] = AState::F; //точка с запятой

	matr[AState::Z][separator] = AState::F; //разделитель
	matr[AState::Z][alpha] = AState::F; //буква
	matr[AState::Z][digit] = AState::F; //цифра
	matr[AState::Z][co1] = AState::F;	//знак меньше
	matr[AState::Z][co2] = AState::F;	//знак больше
	matr[AState::Z][eq] = AState::F;	// знак равенства
	matr[AState::Z][ao] = AState::F;	//арифметическая операция
	matr[AState::Z][other] = AState::F; //остальное
	matr[AState::Z][semicolon] = AState::F; //точка с запятой

	while (pos < size)
	{
		char curr = text[pos];
		//инициализация лексемы при обнаружении непробельного символа
		if (state == AState::S && !(curr == ' ' || curr == '\t' || curr == '\n')) firstPos = pos;

		if ((curr == '\n') || (curr == ' ') || (curr == '\t') || (curr == '\0')) character = separator;
		else if ((('A' <= curr) && (curr <= 'Z')) || (('a' <= curr) && (curr <= 'z'))) character = alpha;
		else if (('0' <= curr) && (curr <= '9')) character = digit;
		else if (curr == '<') character = co1;
		else if (curr == '>') character = co2;
		else if (curr == '=') character = eq;
		else if (curr == '+' || curr == '-' || curr == '/' || curr == '*') character = ao;
		else if (curr == ';') character = semicolon;
		else character = other;

		state = matr[state][character];

		if (state == AState::A) lexema.type = alpha;
		else if (state == AState::B) lexema.type = digit;
		else if (state == AState::C || state == AState::D) lexema.type = co1;
		else if (state == AState::E) lexema.type = other;
		else if (state == AState::G) lexema.type = eq;
		else if (state == AState::H) lexema.type = ao;
		else if (state == AState::X) lexema.type = semicolon;
		else if (state == AState::Z) lexema.type = co1;


		if (state == AState::F) //запись текущей лексемы в выходной список и инициализация новой лексемы
		{
			int length = pos - firstPos;
			lexema.str = new char[length + 1];
			lexema.str = word(text, firstPos, firstPos + length); //запись в лексему
			lexema.len = length;
			vec.push_back(lexema); //запись лексемы в список
			state = AState::S;
			--pos;
		}
		++pos;
	}
	return;
}


int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int size = 0;
	while (fin.get() != EOF) ++size;  //считаем кол-во символов в строке
	fin.clear(); //сбрасывание флагов ошибки
	fin.seekg(0); //переводит итератор на начало
	char* text = new char[++size];		//создаем массив, в котором будут храниться исходные данные
	fin.getline(text, size, '\0');
	fin.close();
	vector <Lex> vec;
	LexAnalysis(text, size, vec);
	delete[] text;
	//вывод результата
	//enum ELexType{alpha, digit, separator, eq, co1, co2, ao, other};
	for (int i = 0; i < (int)vec.size(); ++i)
	{
		cout << vec[i].str;
		if ((vec[i].type == digit) && (-32768  < atoi(vec[i].str) ) && (atoi(vec[i].str) < 32767)) cout << "[vl]" << ' ';
		else if (vec[i].type == eq) cout << "[eq]" << ' ';
		else if (vec[i].type == co1) cout << "[co]" << ' ';
		else if (vec[i].type == ao) cout << "[ao]" << ' ';
		else if (vec[i].type == other) cout << "[wl]" << ' ';
		else if (vec[i].type == semicolon) cout << "[sc]" << ' ';
		else if (vec[i].type == alpha)
		{
			if (!strcmp(vec[i].str, "for") || !strcmp(vec[i].str, "to") || !strcmp(vec[i].str, "next") || !strcmp(vec[i].str, "not") || !strcmp(vec[i].str, "and") || !strcmp(vec[i].str, "or")) cout << "[kw]" << ' ';
			else if (vec[i].len <= 5) cout << "[id]" << ' ';
			else cout << "[wl]" << ' ';
		}
		else cout << "[wl]" << ' ';
		fout << vec[i].str;
		if ((vec[i].type == digit) && (-32768 < atoi(vec[i].str)) && (atoi(vec[i].str) < 32767)) fout << "[vl]" << ' ';			//int isxdigit( int с );
		else if (vec[i].type == eq) fout << "[eq]" << ' ';
		else if (vec[i].type == co1) fout << "[co]" << ' ';
		else if (vec[i].type == ao) fout << "[ao]" << ' ';
		else if (vec[i].type == other) fout << "[wl]" << ' ';
		else if (vec[i].type == semicolon) fout << "[sc]" << ' ';
		else if (vec[i].type == alpha)
		{
			if (!strcmp(vec[i].str, "for") || !strcmp(vec[i].str, "to") || !strcmp(vec[i].str, "next") || !strcmp(vec[i].str, "not") || !strcmp(vec[i].str, "and") || !strcmp(vec[i].str, "or")) fout << "[kw]" << ' ';
			else if (vec[i].len <= 5) fout << "[id]" << ' ';
			else fout << "[wl]" << ' ';
		}
		else fout << "[wl]" << ' ';
	}
	cout << '\n';
	fout << '\n';
	for (int i = 0; i < (int)vec.size(); ++i)
	{
		if (vec[i].type == alpha)
		{
			if (!(!strcmp(vec[i].str, "for") || !strcmp(vec[i].str, "to") || !strcmp(vec[i].str, "next") || !strcmp(vec[i].str, "or") || !strcmp(vec[i].str, "and") || !strcmp(vec[i].str, "not")) && (vec[i].len <= 5))
			{
				cout << vec[i].str << ' ';
				fout << vec[i].str << ' ';
			}
		}
	}
	cout << '\n';
	fout << '\n';
	for (int i = 0; i < (int)vec.size(); ++i)
	{
		if ((vec[i].type == digit) && (-32768 < atoi(vec[i].str)) && (atoi(vec[i].str) < 32767))
		{
			cout << vec[i].str << ' ';
			fout << vec[i].str << ' ';
		}
	}
	fout.close();
	return 0;
}
