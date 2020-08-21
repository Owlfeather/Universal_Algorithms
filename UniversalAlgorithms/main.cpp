#include "Basic_Elements.h"
#include "Algorithm_LtoR.h"
#include "Algorithm_LtoR_u.h"
//#include "Algorithm_TtoD.h"
#include "Alg_Elements.h"
//#include "Algorithm_LLk_TtoD.h"
//#include "Algorithm_LRk_Stack.h"


//************************���������************************

int main() {
	setlocale(0, "russian");
	cout << "������!" << endl;

	//string input_str = "(<��>v<��>)^<��>";
	//string input_str = "while <�������> do begin while <�������> do <������������>; <������������> end";
	//string input_str = "(<��>v<��>)^(<��>v<��>)";

	string input_str = "--5";
	//string input_str = "d+c*(a+b)";
	//string input_str = "(Udh-(hdhdh*(((tuh)))))";

	LtoR_MethodAlg_u alg1;
	alg1.SetRulesOfAlg();
	
	switch (alg1.SetParsingStr(input_str, true))
	{
	case ResultOfStringReceiving::EMPTY_BRACKETS:
		cout << endl << "������ ������";
		break;
	case ResultOfStringReceiving::FAILURE:
		cout << endl << "������";
		break;
	case ResultOfStringReceiving::SUCCESS:
		cout << endl << "�����";
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


