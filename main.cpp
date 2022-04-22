#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

enum AnalysisStates{S, A, B, C, D, G, H, E, F, Y, X, Z};
enum ELexType{alpha, digit, separator, eq, co1, co2, ao, other, semicolon};

struct Lex
{
    ELexType type;
	char* str;
	int len;
};

char* word(char* str, int begin, int end)
{
	char* word = new char[end - begin + 1];
	int i = 0;
	while (begin < end)
	{
        word[i] = str[begin];
		++i;
		++begin;
	}
    word[i] = '\0';
	return word;
}

void correctPosition(int &position){
    --position;
}

void LexAnalysis(char* text, int size, vector <Lex>& vec)
{
	int pos = 0;
	AnalysisStates state = AnalysisStates::S;
	Lex lexem;
	int firstPos;
	int character;
	AnalysisStates matrix[12][9];

	matrix[AnalysisStates::S][separator] = AnalysisStates::S;   //разделитель
	matrix[AnalysisStates::S][alpha] = AnalysisStates::A;       //буква
	matrix[AnalysisStates::S][digit] = AnalysisStates::B;       //цифра
	matrix[AnalysisStates::S][co1] = AnalysisStates::C;	        //знак меньше
	matrix[AnalysisStates::S][co2] = AnalysisStates::D;	        //знак больше
	matrix[AnalysisStates::S][eq] = AnalysisStates::G;	        //знак равенства
	matrix[AnalysisStates::S][ao] = AnalysisStates::H;	        //арифметическая операция
	matrix[AnalysisStates::S][other] = AnalysisStates::E;       //остальное
	matrix[AnalysisStates::S][semicolon] = AnalysisStates::X;   //точка с запятой

	matrix[AnalysisStates::A][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::A][alpha] = AnalysisStates::A;       //буква
	matrix[AnalysisStates::A][digit] = AnalysisStates::A;       //цифра
	matrix[AnalysisStates::A][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::A][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::A][eq] = AnalysisStates::F;	        //знак равенства
	matrix[AnalysisStates::A][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::A][other] = AnalysisStates::E;       //остальное
	matrix[AnalysisStates::A][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::B][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::B][alpha] = AnalysisStates::E;       //буква
	matrix[AnalysisStates::B][digit] = AnalysisStates::B;       //цифра
	matrix[AnalysisStates::B][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::B][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::B][eq] = AnalysisStates::F;	        //знак равенства
	matrix[AnalysisStates::B][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::B][other] = AnalysisStates::E;       //остальное
	matrix[AnalysisStates::B][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::C][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::C][alpha] = AnalysisStates::F;       //буква
	matrix[AnalysisStates::C][digit] = AnalysisStates::F;       //цифра
	matrix[AnalysisStates::C][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::C][co2] = AnalysisStates::Z;	        //знак больше
	matrix[AnalysisStates::C][eq] = AnalysisStates::F;	        //знак равенства
	matrix[AnalysisStates::C][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::C][other] = AnalysisStates::F;       //остальное
	matrix[AnalysisStates::C][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::D][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::D][alpha] = AnalysisStates::F;       //буква
	matrix[AnalysisStates::D][digit] = AnalysisStates::F;       //цифра
	matrix[AnalysisStates::D][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::D][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::D][eq] = AnalysisStates::Y;	        //знак равенства
	matrix[AnalysisStates::D][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::D][other] = AnalysisStates::F;       //остальное
	matrix[AnalysisStates::D][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::G][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::G][alpha] = AnalysisStates::F;       //буква
	matrix[AnalysisStates::G][digit] = AnalysisStates::F;       //цифра
	matrix[AnalysisStates::G][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::G][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::G][eq] = AnalysisStates::F;	        //знак равенства
	matrix[AnalysisStates::G][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::G][other] = AnalysisStates::F;       //остальное
	matrix[AnalysisStates::G][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::H][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::H][alpha] = AnalysisStates::F;       //буква
	matrix[AnalysisStates::H][digit] = AnalysisStates::F;       //цифра
	matrix[AnalysisStates::H][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::H][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::H][eq] = AnalysisStates::F;	        // знак равенства
	matrix[AnalysisStates::H][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::H][other] = AnalysisStates::F;       //остальное
	matrix[AnalysisStates::H][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::E][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::E][alpha] = AnalysisStates::E;       //буква
	matrix[AnalysisStates::E][digit] = AnalysisStates::E;       //цифра
	matrix[AnalysisStates::E][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::E][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::E][eq] = AnalysisStates::F;	        //знак равенства
	matrix[AnalysisStates::E][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::E][other] = AnalysisStates::E;       //остальное
	matrix[AnalysisStates::E][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::X][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::X][alpha] = AnalysisStates::F;       //буква
	matrix[AnalysisStates::X][digit] = AnalysisStates::F;       //цифра
	matrix[AnalysisStates::X][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::X][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::X][eq] = AnalysisStates::F;	        //знак равенства
	matrix[AnalysisStates::X][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::X][other] = AnalysisStates::F;       //остальное
	matrix[AnalysisStates::X][semicolon] = AnalysisStates::F;   //точка с запятой

	matrix[AnalysisStates::Z][separator] = AnalysisStates::F;   //разделитель
	matrix[AnalysisStates::Z][alpha] = AnalysisStates::F;       //буква
	matrix[AnalysisStates::Z][digit] = AnalysisStates::F;       //цифра
	matrix[AnalysisStates::Z][co1] = AnalysisStates::F;	        //знак меньше
	matrix[AnalysisStates::Z][co2] = AnalysisStates::F;	        //знак больше
	matrix[AnalysisStates::Z][eq] = AnalysisStates::F;	        //знак равенства
	matrix[AnalysisStates::Z][ao] = AnalysisStates::F;	        //арифметическая операция
	matrix[AnalysisStates::Z][other] = AnalysisStates::F;       //остальное
	matrix[AnalysisStates::Z][semicolon] = AnalysisStates::F;   //точка с запятой

	while (pos < size)
	{
		char curr = text[pos];

		if (state == AnalysisStates::S && !(curr == ' ' || curr == '\t' || curr == '\n')) firstPos = pos;

		if ((curr == '\n') || (curr == ' ') || (curr == '\t') || (curr == '\0')) character = separator;
		else if ((('A' <= curr) && (curr <= 'Z')) || (('a' <= curr) && (curr <= 'z'))) character = alpha;
		else if (('0' <= curr) && (curr <= '9')) character = digit;
		else if (curr == '<') character = co1;
		else if (curr == '>') character = co2;
		else if (curr == '=') character = eq;
		else if (curr == '+' || curr == '-' || curr == '/' || curr == '*') character = ao;
		else if (curr == ';') character = semicolon;
		else character = other;

		state = matrix[state][character];

		if (state == AnalysisStates::A) lexem.type = alpha;
		else if (state == AnalysisStates::B) lexem.type = digit;
		else if (state == AnalysisStates::C || state == AnalysisStates::D) lexem.type = co1;
		else if (state == AnalysisStates::E) lexem.type = other;
		else if (state == AnalysisStates::G) lexem.type = eq;
		else if (state == AnalysisStates::H) lexem.type = ao;
		else if (state == AnalysisStates::X) lexem.type = semicolon;
		else if (state == AnalysisStates::Z) lexem.type = co1;


		if (state == AnalysisStates::F)
		{
			int length = pos - firstPos;
            lexem.str = new char[length + 1];
            lexem.str = word(text, firstPos, firstPos + length);
            lexem.len = length;
			vec.push_back(lexem);
			state = AnalysisStates::S;
            correctPosition(pos);
		}
		++pos;
	}
	}

void read(ifstream &fin, int &out_size, char *&out_text){
    int size = 0;
    fin.seekg(0, ios::end);
    size = fin.tellg();
    fin.seekg(0, ios::beg);
    char* text = new char[++size];
    fin.getline(text, size, '\0');
    out_size = size;
    out_text = text;
}

void write(vector <Lex> &array, ofstream &fout){

    for (size_t i = 0; i < (size_t)array.size(); ++i)
    {
        cout << array[i].str;
        if ((array[i].type == digit) && (-32768  < atoi(array[i].str) ) && (atoi(array[i].str) < 32767)) cout << "[vl]" << ' ';
        else if (array[i].type == eq) cout << "[eq]" << ' ';
        else if (array[i].type == co1) cout << "[co]" << ' ';
        else if (array[i].type == ao) cout << "[ao]" << ' ';
        else if (array[i].type == other) cout << "[wl]" << ' ';
        else if (array[i].type == semicolon) cout << "[sc]" << ' ';
        else if (array[i].type == alpha)
        {
            if (!strcmp(array[i].str, "do") || !strcmp(array[i].str, "while") || !strcmp(array[i].str, "loop") || !strcmp(array[i].str, "not") || !strcmp(array[i].str, "and") || !strcmp(array[i].str, "or")) cout << "[kw]" << ' ';
            else if (array[i].len <= 5) cout << "[id]" << ' ';
            else cout << "[wl]" << ' ';
        }
        else cout << "[wl]" << ' ';
        fout << array[i].str;
        if ((array[i].type == digit) && (-32768 < atoi(array[i].str)) && (atoi(array[i].str) < 32767)) fout << "[vl]" << ' ';
        else if (array[i].type == eq) fout << "[eq]" << ' ';
        else if (array[i].type == co1) fout << "[co]" << ' ';
        else if (array[i].type == ao) fout << "[ao]" << ' ';
        else if (array[i].type == other) fout << "[wl]" << ' ';
        else if (array[i].type == semicolon) fout << "[sc]" << ' ';
        else if (array[i].type == alpha)
        {
            if (!strcmp(array[i].str, "do") || !strcmp(array[i].str, "while") || !strcmp(array[i].str, "loop") || !strcmp(array[i].str, "not") || !strcmp(array[i].str, "and") || !strcmp(array[i].str, "or")) fout << "[kw]" << ' ';
            else if (array[i].len <= 5) fout << "[id]" << ' ';
            else fout << "[wl]" << ' ';
        }
        else fout << "[wl]" << ' ';
    }

    cout << '\n';
    fout << '\n';

    for (int i = 0; i < (int)array.size(); ++i)
    {
        if (array[i].type == alpha)
        {
            if (!(!strcmp(array[i].str, "do") || !strcmp(array[i].str, "while") || !strcmp(array[i].str, "loop") || !strcmp(array[i].str, "or") || !strcmp(array[i].str, "and") || !strcmp(array[i].str, "not")) && (array[i].len <= 5))
            {
                cout << array[i].str << ' ';
                fout << array[i].str << ' ';
            }
        }
    }

    cout << '\n';
    fout << '\n';

    for (int i = 0; i < (int)array.size(); ++i)
    {
        if ((array[i].type == digit) && (-32768 < atoi(array[i].str)) && (atoi(array[i].str) < 32767))
        {
            cout << array[i].str << ' ';
            fout << array[i].str << ' ';
        }
    }
}

int main()
{
    int size;
    char* text;

    ifstream fin("input.txt");
    read(fin,size,text);
    fin.close();

	vector <Lex> array;
	LexAnalysis(text, size, array);
	delete[] text;

    ofstream fout("output.txt");
    write(array, fout);
	fout.close();

	return 0;
}
