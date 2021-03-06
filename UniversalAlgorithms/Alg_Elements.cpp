﻿#include "Alg_Elements.h"




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

//---------------------LtoR_u_Line---------------------

void LtoR_Line_u::SetLine(const string& inp_str, const RuleNum& inp_rnum,
						const unsigned inp_entry,
						const TypeOfLtoRLine inp_status, 
						const int inp_source_s,
						const RuleNum& inp_offset,
						const int inp_entry_p_off)
{
	cur_string = inp_str;
	rule_num = inp_rnum;
	entry_point = inp_entry;
	status = inp_status;
	source_step = inp_source_s;
	offset = inp_offset;
	entry_point_offset = inp_entry_p_off;
}

void LtoR_Line_u::PrintLine()
{
	string str_for_print;
	for (int i = 0; i < cur_string.size(); i++) {
		if (cur_string[i] != '\n') {
			str_for_print += cur_string[i];
		}
	}

	cout << "Строка: " << str_for_print;
	/*switch (status)
	{
	case REGULAR_LINE:
		cout << " Правило: " << char(rule_num.fir_num + 224) << rule_num.sec_num + 1 << " REGULAR_LINE" << endl;
		cout << "ENTRY_POINT: " << to_string(GetEntryPoint());
		cout << " ENTRY_POINT_OFFSET: " << to_string(GetOffsetEntryPoint());
		cout << " SOURCE_STEP: " << to_string(GetSourceStep());
		break;
	case REG_FURTHER_DEAD_END:
		cout << " Правило: " << char(rule_num.fir_num + 224) << rule_num.sec_num + 1 << " REG_FURTHER_DEAD_END" << endl;
		cout << "ENTRY_POINT: " << to_string(GetEntryPoint());
		cout << " ENTRY_POINT_OFFSET: " << to_string(GetOffsetEntryPoint());
		cout << " SOURCE_STEP: " << to_string(GetSourceStep());
		break;
	case DEAD_END_BRANCH:
		cout << " Правило: " << char(rule_num.fir_num + 224) << rule_num.sec_num + 1 << " \u00D8" << " DEAD_END_BRANCH" << endl;
		cout << "ENTRY_POINT: " << to_string(GetEntryPoint());
		cout << " ENTRY_POINT_OFFSET: " << to_string(GetOffsetEntryPoint());
		cout << " SOURCE_STEP: " << to_string(GetSourceStep());
		break;
	case DEAD_END_BRANCH_VIEWED:
		cout << " Правило: " << char(rule_num.fir_num + 224) << rule_num.sec_num + 1 << " \u00D8" << " DEAD_END_BRANCH_VIEWED" << endl;
		cout << "ENTRY_POINT: " << to_string(GetEntryPoint());
		cout << " ENTRY_POINT_OFFSET: " << to_string(GetOffsetEntryPoint());
		cout << " SOURCE_STEP: " << to_string(GetSourceStep());
		break;
	case DEAD_END:
		cout << " Тупик " << " DEAD_END" << endl;
		cout << "ENTRY_POINT: " << to_string(GetEntryPoint());
		cout << " ENTRY_POINT_OFFSET: " << to_string(GetOffsetEntryPoint());
		cout << " SOURCE_STEP: " << to_string(GetSourceStep());
		break;
	case PARSED_END:
		cout << " Конец " << " PARSED_END" << endl;
		break;
	case NOT_PARSED_END:
		cout << " Разбор невозможен " << " NOT_PARSED_END" << endl;
		break;
	default:
		break;
	}*/
	switch (status)
	{
	case REGULAR_LINE:
		cout << endl << " Правило: " << char(rule_num.fir_num + 224) << rule_num.sec_num + 1 ;
		break;
	case REG_FURTHER_DEAD_END:
		cout << endl << " Правило: " << char(rule_num.fir_num + 224) << rule_num.sec_num + 1 ;
		break;
	case DEAD_END_BRANCH:
		cout << endl << " Тупиковая ветвь!";
		break;
	case DEAD_END_BRANCH_VIEWED:
		cout << endl << " Известная тупиковая ветвь";
		break;
	case DEAD_END:
		cout << endl << " Тупик ";
		break;
	case PARSED_END:
		cout << endl << " Конец ";
		break;
	case NOT_PARSED_END:
		cout << endl << " Разбор невозможен ";
		break;
	default:
		break;
	}

	cout << endl << "-----------------------------------------------" << endl;
}

vector<string> LtoR_Line_u::GetLine()
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

	switch (status)
	{
	case REGULAR_LINE:
		line.push_back(char(rule_num.fir_num + 224) + to_string(rule_num.sec_num + 1));
		break;
	case REG_FURTHER_DEAD_END:
		line.push_back(char(rule_num.fir_num + 224) + to_string(rule_num.sec_num + 1));
		break;
	case DEAD_END_BRANCH:
		line.push_back(char(rule_num.fir_num + 224) + to_string(rule_num.sec_num + 1));
		break;
	case DEAD_END_BRANCH_VIEWED:
		line.push_back("Шаг ведет к тупику!");
		break;
	case DEAD_END:
		line.push_back("Тупик!");
		break;
	case PARSED_END:
		line.push_back("Конец разбора");
		break;
	case NOT_PARSED_END:
		line.push_back("Разбор дальше невозможен!");
		break;
	}

	return line;
}

TypeOfAlg LtoR_Line_u::GetType()
{
	return TypeOfAlg::LTOR;;
}


//---------------------ParseLog---------------------

void ParseLog::PrintLogLtoR() 
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		dynamic_cast<LtoR_Line *>(records[i])->PrintLine();
	}
}

void ParseLog::PrintLogLtoR_u()
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		cout << i << ")";
		dynamic_cast<LtoR_Line_u*>(records[i])->PrintLine();
	}
}

void ParseLog::PrintLogTtoD()
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		dynamic_cast<TtoD_Line *>(records[i])->PrintLine();
	}
}

void ParseLog::PrintLogTtoD_u()
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		cout << i << ")";
		dynamic_cast<TtoD_Line_u*>(records[i])->PrintLine();
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

//---------------------TtoD_u_Line---------------------

TypeOfAlg TtoD_Line_u::GetType()
{
	return TypeOfAlg::TTOD;
}

void TtoD_Line_u::SetLine(const string& inp_rec_str, const RuleNum& inp_rnum, const string& inp_pars_str, const string& inp_targ_str, TypeOfTtoDLine inp_status, const int inp_source_s)
{
	cur_string = inp_pars_str;
	rule_num = inp_rnum;
	recognized_string = inp_rec_str;
	target_string = inp_targ_str;
	status = inp_status;
	source_step = inp_source_s;
}

void TtoD_Line_u::PrintLine()
{
	cout << endl << "Распознано: " << MakePrintable(recognized_string);
	cout << " Строка: " << MakePrintable(cur_string);
	cout << " Цель: " << MakePrintable(target_string);
	cout << endl;

	switch (status)
	{
	case TypeOfTtoDLine::HYPOTHESIS:
		cout << rule_num.GetPrintable() << " HYPOTHESIS " << "SOURCE_STEP = " << source_step << endl;
		break;
	case TypeOfTtoDLine::WRONG_HYPO:
		cout << rule_num.GetPrintable() << " WRONG_HYPO " << "SOURCE_STEP = " << source_step << endl;
		break;
	case TypeOfTtoDLine::MISTAKE:
		cout << rule_num.GetPrintable() << " MISTAKE " << "SOURCE_STEP = " << source_step << endl;
		break;
	case TypeOfTtoDLine::RECOGNIZED:
		cout << rule_num.GetPrintable() << " RECOGNIZED " << "SOURCE_STEP = " << source_step << endl;
		break;
	case TypeOfTtoDLine::PARSED_END_TtoD:
		cout << rule_num.GetPrintable() << " PARSED_END " << "SOURCE_STEP = " << source_step << endl;
		break;
	case TypeOfTtoDLine::NOT_PARSED_END_TtoD:
		cout << rule_num.GetPrintable() << " NOT_PARSED_END " << "SOURCE_STEP = " << source_step << endl;
		break;
	}
}

vector<string> TtoD_Line_u::GetLine()
{
	vector<string> line;
	line.push_back(MakePrintable(recognized_string));
	line.push_back(MakePrintable(cur_string));
	line.push_back(MakePrintable(target_string));

	switch (status)
	{
	case TypeOfTtoDLine::HYPOTHESIS:
		line.push_back("?");
		break;
	case TypeOfTtoDLine::WRONG_HYPO:
		line.push_back("?");
		break;
	case TypeOfTtoDLine::MISTAKE:
		line.push_back(char(rule_num.fir_num + 224) + to_string(rule_num.sec_num + 1) + " - нет");
		break;
	case TypeOfTtoDLine::RECOGNIZED:
		line.push_back(char(rule_num.fir_num + 224) + to_string(rule_num.sec_num + 1) + " - да");
		break;
	case TypeOfTtoDLine::PARSED_END_TtoD:
		line.push_back("Разбор завершён");
		break;
	case TypeOfTtoDLine::NOT_PARSED_END_TtoD:
		line.push_back("Разбор дальше невозможен!");
		break;
	}

	return line;
}

string TtoD_Line_u::MakePrintable(string& str_with_seps)
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


