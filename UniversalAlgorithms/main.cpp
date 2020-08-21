#include "Basic_Elements.h"
#include "Algorithm_LtoR.h"
#include "Algorithm_LtoR_u.h"
//#include "Algorithm_TtoD.h"
#include "Alg_Elements.h"
//#include "Algorithm_LLk_TtoD.h"
//#include "Algorithm_LRk_Stack.h"


//************************Программа************************

int main() {
	setlocale(0, "russian");
	cout << "Запуск!" << endl;

	//string input_str = "(<Ид>v<Ид>)^<Ид>";
	//string input_str = "while <Условие> do begin while <Условие> do <Присваивание>; <Присваивание> end";
	//string input_str = "(<Ид>v<Ид>)^(<Ид>v<Ид>)";

	string input_str = "--5";
	//string input_str = "d+c*(a+b)";
	//string input_str = "(Udh-(hdhdh*(((tuh)))))";

	LtoR_MethodAlg_u alg1;
	alg1.SetRulesOfAlg();
	
	switch (alg1.SetParsingStr(input_str, true))
	{
	case ResultOfStringReceiving::EMPTY_BRACKETS:
		cout << endl << "Пустые скобки";
		break;
	case ResultOfStringReceiving::FAILURE:
		cout << endl << "Ошибка";
		break;
	case ResultOfStringReceiving::SUCCESS:
		cout << endl << "Успех";
		alg1.PrintParsingStr();
		break;
	}

	alg1.DoParse();

	//alg1.PrintLogLtoR();


	/*
	LtoR_MethodAlg alg1;
	alg1.SetRulesOfAlg();
	alg1.SetParsingStr(input_str);
	alg1.DoParse();
	input_str = "11";
	alg1.SetParsingStr(input_str);
	alg1.DoParse();
	//*/
	/*
	TtoD_MethodAlg alg2;
	alg2.SetRulesOfAlg();
	alg2.SetParsingStr(input_str);
	alg2.DoParse();
	*/

	/*
	TtoD_LLk_MethodAlg alg3;
	alg3.SetRulesOfAlg();
	alg3.SetParsingStr(input_str);
	alg3.DoParse();
	//*/

	/*Stack_LRk_MethodAlg alg4;
	alg4.SetRulesOfAlg();
	alg4.SetParsingStr(input_str);
	alg4.DoParse();*/

	system("pause");
	return 0;
}


