#include "Alg_Elements.h"




//---------------------ItemRule---------------------

void ItemRule::SetRule(const ItemSymb & inp_l, const vector <ItemString> & inp_r) 
{
	left = inp_l;
	right = inp_r;
}

void ItemRule::PrintRule() 
{
	cout << string(left) << " ::= ";
	for (unsigned i = 0; i < right.size(); i++) {
		right[i].PrintString();
		if (right.size() - i != 1) cout << "|";

	}
}

//---------------------LtoR_Line---------------------

void LtoR_Line::SetLine(const string & inp_str, const RuleNum & inp_rnum) 
{
	cur_string = inp_str;
	rule_num = inp_rnum;
}

void LtoR_Line::PrintLine()
{
	string str_for_print;
	for (int i = 0; i < cur_string.size(); i++) {
		if (cur_string[i] != '\n') {
			str_for_print += cur_string[i];
		}
	}

	cout << "Строка: " << str_for_print;
	if (rule_num.fir_num > -1) {
		cout << " Правило: " << rule_num.fir_num + 1 << char(rule_num.sec_num + 224) << endl;
	}
	else
		if (rule_num.sec_num == -3) {
			cout << "       конец!" << endl;
		}
		else if (rule_num.sec_num == -4) {
			cout << "       разбор дальше невозможен!" << endl;
		}
		else {
			cout << "       тупик!" << endl;
		}
}

vector<string> LtoR_Line::GetLine()
{
	vector<string> line;
	string cur_string = GetCurString();
	string str_for_print;

	for (int i = 0; i < cur_string.size(); i++) {
		if (cur_string[i] != '\n') {
			str_for_print += cur_string[i];
		}
	}
	line.push_back(str_for_print);

	RuleNum rule_num = GetRuleNum();

	if (rule_num.fir_num > -1) {
		line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224));
	}
	else
		if (rule_num.sec_num == -3) {
			line.push_back("Конец разбора");
		}
		else if (rule_num.sec_num == -4) {
			line.push_back("Разбор дальше невозможен!");
		}
		else {
			line.push_back("Тупик!");
		}
	return line;
}

TypeOfAlg LtoR_Line::GetType()
{
	return TypeOfAlg::LTOR;
}



//---------------------ParseLog---------------------

void ParseLog::PrintLogltoR() 
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		dynamic_cast<LtoR_Line *>(records[i])->PrintLine();
	}
}

void ParseLog::PrintLogTtoD()
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		dynamic_cast<TtoD_Line *>(records[i])->PrintLine();
	}
}

void ParseLog::PrintLogLLk()
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		dynamic_cast<LLk_TtoD_Line*>(records[i])->PrintLine();
	}
}



TypeOfAlg TtoD_Line::GetType()
{
	return TypeOfAlg::TTOD;
}

//---------------------TtoD_Line---------------------

void TtoD_Line::SetLine(const string& rec_str, const string& pars_str, const string& targ_str, unsigned type_of_l, TypeOfTtoDLine line_type, const RuleNum& inp_rnum)
{
	recognized = rec_str;
	cur_string = pars_str;
	target = targ_str;
	type = type_of_line;
	type = type_of_l;
	type_of_line = line_type;
	rule_num = inp_rnum;
}

void TtoD_Line::PrintLine()
{
	cout << endl << "Распознано: " << MakePrintable(recognized);
	cout << " Строка: " << MakePrintable(cur_string);
	cout << " Цель: " << MakePrintable(target);
	cout << "   ";
	switch (type)
	{
	case 1:
		cout << "?" << endl;
		break;
	case 2:
		cout << rule_num.fir_num+1 << char(rule_num.sec_num + 224) << " - ?" << endl;
		break;
	case 3:
		if (rule_num.sec_num == 0) {
			cout << rule_num.fir_num+1 << char(rule_num.sec_num + 224);
		}
		else {
			//cout << rule_num.fir_num+1 << "a..." << char(rule_num.sec_num + 224);
			if (rule_num.fir_num == 3) {
				cout << rule_num.fir_num + 1 << "a..." << char(rule_num.sec_num + 224 - 1);
			}
			else {
				cout << rule_num.fir_num + 1 << "a..." << char(rule_num.sec_num + 224);
			}
		}
		cout << " - нет" << endl;
		break;
	case 4:
		cout << rule_num.fir_num+1 << char(rule_num.sec_num + 224) << " - да" << endl;
		break;
	}
	
}

vector<string> TtoD_Line::GetLine()
{
	vector<string> line;
	line.push_back(MakePrintable(recognized));
	line.push_back(MakePrintable(cur_string));
	line.push_back(MakePrintable(target));
	


	switch (type_of_line)
	{
	case TypeOfTtoDLine::STATEMENT:
	{
		line.push_back("?");
		break;
	}
	case TypeOfTtoDLine::RULE_FIT:
	{
		line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224) + " - да");
		break;
	}
	case TypeOfTtoDLine::RULE_NOT_FIT:
	{
		if (rule_num.sec_num == 0) {
			line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224) + " - нет");
		}
		else {
			line.push_back(to_string(rule_num.fir_num + 1) + "а..." + char(rule_num.sec_num + 224) + " - нет");
		}
		break;
	}
	case TypeOfTtoDLine::END_LINE:
	{
		line.push_back("Разбор завершён");
		break;
	}
	case TypeOfTtoDLine::ROLLB_POSS:
	case TypeOfTtoDLine::ROLLB_IMPOSS:
	{
		line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224) + " - ?");
		break;
	}
	case TypeOfTtoDLine::WRONG_SYMB:
	{
		line.push_back("Разбор дальше невозможен!");
		break;
	}
	
	}


	return line;
}

string TtoD_Line::MakePrintable(string & str_with_seps)
{
	string str_for_print;
	for (int i = 0; i < str_with_seps.size(); i++) {
		if (str_with_seps[i] != '\n') {
			str_for_print += str_with_seps[i];
		}
	}
	return str_for_print;
}


//---------------------LLk_TtoD_Line---------------------


TypeOfAlg LLk_TtoD_Line::GetType()
{
	return TypeOfAlg::LLK_TTOD;
}

vector<string> LLk_TtoD_Line::GetLine()
{
	vector<string> line;
	line.push_back(cur_string);
	line.push_back(stack_str);

	if (rule_num.fir_num > 0) {
		if ((rule_num.fir_num == 1) || (rule_num.fir_num == 3)) {
			//cout << " Правило: " << rule_num.fir_num + 1;
			line.push_back(" Правило: " + to_string(rule_num.fir_num + 1));
		}
		else {
			//cout << " Правило: " << rule_num.fir_num + 1 << char(rule_num.sec_num + 224);
			line.push_back(" Правило: " + to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224));
		}
	}
	else {
		switch (rule_num.fir_num)
		{
		case -1:
			//cout << " Некорректный символ, разбор завершён";
			line.push_back("Некорректный символ, разбор завершён");
			break;
		case -2:
			//cout << " Некорректный символ, разбор завершён";
			line.push_back("Ошибка, разбор завершён");
			break;
		case -3:
			//cout << "";
			line.push_back("");
			break;
		case -10:
			//cout << " Разбор завершён";
			line.push_back("Разбор завершён");
			break;
		}
	}

	return line;
}

void LLk_TtoD_Line::SetLine(const string& pars_str, const string& st_str, const RuleNum& inp_rnum)
{
	cur_string = pars_str;
	stack_str = st_str;
	rule_num = inp_rnum;
}

void LLk_TtoD_Line::PrintLine()
{
	cout << endl << "Строка: " << cur_string;
	cout << " Стек: " << stack_str;


	if (rule_num.fir_num > 0) {
		if ((rule_num.fir_num == 1) || (rule_num.fir_num == 3)) {
			cout << " Правило: " << rule_num.fir_num + 1;
		}
		else {
			cout << " Правило: " << rule_num.fir_num + 1 << char(rule_num.sec_num + 224);
		}
	}
	else {
		switch (rule_num.fir_num)
		{
		case -1:
			cout << " Некорректный символ, разбор завершён";
			break;
		case -2:
			cout << " Ошибка, разбор завершён";
			break;
		case -3:
			cout << "";
			break;
		case -10:
			cout << " Разбор завершён";
			break;
		}
	}


}

//---------------------LRk_Stack_Line---------------------

TypeOfAlg LRk_Stack_Line::GetType()
{
	return TypeOfAlg::LRK_STACK;
}

vector<string> LRk_Stack_Line::GetLine()
{
	vector<string> line;
	line.push_back(stack_str);
	line.push_back(cur_string);

	switch (relation_str)
	{
	case TypeOfRelation::CARRY:
		//cout << " Отношение: < Операция: Перенос";
		line.push_back("<");
		line.push_back("Перенос");
		line.push_back("");
		line.push_back("");

		break;
	case TypeOfRelation::CONV:
		//cout << " Отношение: > Операция: Свёртка ";
		//cout << " Тройка: " << trio_str << " Результат: ";
		line.push_back(">");
		line.push_back("Свёртка");
		line.push_back(trio_str);

		if (result_str.fir_num == 0) {
			//cout << "Выражение";
			line.push_back("Выражение");
		}
		else if (result_str.fir_num == 1) {
			//cout << "Терм";
			line.push_back("Терм");
		}
		break;
	case TypeOfRelation::CONV_BR:
		line.push_back("=");
		line.push_back("Свёртка");
		//cout << " Отношение: = Операция: Свёртка ";
		//cout << " Тройка: " << trio_str << " Результат: Множ";
		line.push_back(trio_str);
		line.push_back("Множ");

		break;
	case TypeOfRelation::ERROR:
		//cout << " Отношение: ? Операция: Ошибка ";
		line.push_back("?");
		line.push_back("Ошибка");
		line.push_back("");
		line.push_back("");
		break;
	case TypeOfRelation::ID_ERROR:
		//cout << " Отношение: ! Операция: Отсутствие идентификатора ";
		line.push_back("!");
		line.push_back("Нет ид-ра");
		line.push_back("");
		line.push_back("");
		break;
	case TypeOfRelation::OP_ERROR:
		//cout << " Отношение: ! Операция: Отсутствие оператора ";
		line.push_back("!");
		line.push_back("Нет оп-ра");
		line.push_back("");
		line.push_back("");
		break;
	case TypeOfRelation::EXIT:
		//cout << " Отношение: В Операция: Выход ";
		line.push_back("В");
		line.push_back("Выход");
		line.push_back("");
		line.push_back("");
		break;
	}

	return line;
}

void LRk_Stack_Line::SetLine(const string& pars_str, const RuleNum rulenum, const string& st_str, const TypeOfRelation rel_str, const string& tr_str, const RuleNum res_str)
{
	cur_string = pars_str;
	rule_num = rulenum;
	stack_str = st_str;
	relation_str = rel_str;
	trio_str = tr_str;
	result_str = res_str;
}

void LRk_Stack_Line::PrintLine()
{
	cout << "Стек: " << stack_str << " Рассматриваемый элемент: " << cur_string;
	switch (relation_str)
	{
	case TypeOfRelation::CARRY:
		cout << " Отношение: < Операция: Перенос";
		break;
	case TypeOfRelation::CONV:
		cout << " Отношение: > Операция: Свёртка ";
		cout << " Тройка: " << trio_str << " Результат: ";
		if (result_str.fir_num == 0) {
			cout << "Выражение";
		}
		else if (result_str.fir_num == 1) {
			cout << "Терм";
		}
		break;
	case TypeOfRelation::CONV_BR:
		cout << " Отношение: = Операция: Свёртка ";
		cout << " Тройка: " << trio_str << " Результат: Множ";
		break;
	case TypeOfRelation::ERROR:
		cout << " Отношение: ? Операция: Ошибка ";
		break;
	case TypeOfRelation::ID_ERROR:
		cout << " Отношение: ! Операция: Отсутствие идентификатора ";
		break;
	case TypeOfRelation::OP_ERROR:
		cout << " Отношение: ! Операция: Отсутствие оператора ";
		break;
	case TypeOfRelation::EXIT:
		cout << " Отношение: В Операция: Выход ";
		break;
	}
	cout << endl;

}