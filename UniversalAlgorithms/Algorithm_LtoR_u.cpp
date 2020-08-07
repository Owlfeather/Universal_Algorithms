#include "Algorithm_LtoR_u.h"

void LtoR_MethodAlg_u::SetParsingStr(ItemString inp_str)
{
	parsing_str = inp_str;
}

void LtoR_MethodAlg_u::SetRulesOfAlg()
{

	//__________________________________________Создание нетерминалов

	ItemSymb c_integer("<Целое>", false);
	ItemSymb c_unsigned_int("<ЦБЗ>", false);
	ItemSymb c_number("<Цифра>", false);
	ItemSymb c_sign("<Знак>", false);

	vector<ItemSymb> buf_symb;					// переменная-шаблон для варианта раскрытия правила
	vector<ItemString> buf_str;					// переменная-шаблон для хранения всех вариантов раскрытия правила (правая часть правила)

	buf_symb = { c_sign, c_unsigned_int };		// <знак><цбз>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 1

	buf_symb = { c_unsigned_int };				// <цбз>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 2

	ItemRule rule(c_integer, buf_str);			// ПРАВИЛО
	buf_str.clear();							// чистка вариантов
	rules.push_back(rule);						// добавление нового правила
	//----------------------------------------------------

	buf_symb.push_back(c_number);				// <цбз><цифра>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 1

	buf_symb = { c_number };					// <цифра>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 2

	rule.SetRule(c_unsigned_int, buf_str);		// ПРАВИЛО
	buf_str.clear();							// чистка вариантов
	rules.push_back(rule);						// добавление нового правила

	//__________________________________________Создание терминалов

	for (int i = 0; i < 10; i++) {
		buf_symb = { ItemSymb(to_string(i)) };
		buf_str.push_back(ItemString(buf_symb));   // новый вариант
	}

	rule.SetRule(c_number, buf_str);			// ПРАВИЛО
	buf_str.clear();							// чистка вариантов
	rules.push_back(rule);						// добавление нового правила
	//----------------------------------------------------

	buf_symb = { ItemSymb("+") };
	buf_str.push_back(ItemString(buf_symb));	// +

	buf_symb = { ItemSymb("-") };
	buf_str.push_back(ItemString(buf_symb));	// -

	rule.SetRule(c_sign, buf_str);				// ПРАВИЛО
	rules.push_back(rule);						// добавление нового правила
	//----------------------------------------------------

	cout << endl << "Правила для разбора слева направо сформированы:" << endl << endl;
	for (unsigned i = 0; i < rules.size(); i++) {
		rules[i].PrintRule();
		cout << endl;
	}
}


unsigned LtoR_MethodAlg_u::FindMaxQuantity()
{
	unsigned max_quantity = 0;
	unsigned cur_length = 0;
	for (ItemRule rule : rules)
	{
		for (ItemString option : rule.GetRight())
		{
			cur_length = option.Length();
			if (cur_length > max_quantity) {
				max_quantity = cur_length;
			}
		}
	}
	return max_quantity;
}

bool LtoR_MethodAlg_u::ChangeParsingItem()
{
	unsigned item_length = parsing_item.Length();
	unsigned last_entry_point = parsing_str.Length()-1;
	unsigned max_quantity = FindMaxQuantity();

	if (entry_point == last_entry_point) {
		return false;
	}
	else {
		if ((last_entry_point - entry_point) >= item_length) {
			parsing_item.AddSymb(parsing_str[entry_point + item_length]);
		}
		else {
			parsing_item.DeleteSymb(0, item_length);
			entry_point++;
			parsing_item.AddSymb(parsing_str[entry_point]);
		}
		return true;
	}
}

RuleNum LtoR_MethodAlg_u::FindSuitableRule(const RuleNum rulenum)
{
	unsigned rules_length = rules.size();
	unsigned options_length;

	for (auto i = rulenum.fir_num; i < rules_length; i++) {
		options_length = rules[i].RightSize();
		for (auto j = rulenum.sec_num; j < options_length; j++) {
			if (parsing_item == rules[i][j]) {
				comment_line.clear();
				comment_line = "   Правило " + (char(i + 224)) + to_string((j + 1)) + " подошло!";
				cout << comment_line;
				return RuleNum{ i, j };
			}
			else {
				comment_line.clear();
				comment_line = "   Правило " + (char(i + 224)) + to_string((j + 1)) + " не подошло";
				cout << comment_line;
			}
		}
	}

	return RuleNum{ -1, -1 }; // подходящих правил не найдено
}

RuleNum LtoR_MethodAlg_u::RollbackAndGetNextRule()
{
	comment_line.clear();
	comment_line = "   Тупиковая ситуация, необходим откат назад\n";
	comment_line += "   Производится откат к позиции " + to_string(parsing_log.Size() - 2) + " разбора";
	cout << comment_line;
	///comments_model->AddRecordLine(comment_line, TypeOfComment::DEAD_END);

	parsing_str = RestoreStringFromLog((*(parsing_log[parsing_log.Size() - 2])).GetCurString());
	RuleNum prev_rule = (*(parsing_log[parsing_log.Size() - 2])).GetRuleNum();

	parsing_item = rules[prev_rule.fir_num][prev_rule.sec_num];

	if (prev_rule.sec_num == rules[prev_rule.fir_num].RightSize() - 1) prev_rule.fir_num++;
	else prev_rule.sec_num++;
	return prev_rule;

}

void LtoR_MethodAlg_u::WriteToLog(const RuleNum cur_rule_num)
{
	LtoR_Line* buf_line;
	buf_line = new LtoR_Line();

	string str_with_separators;
	for (int i = 0; i < parsing_str.Length(); i++) {
		str_with_separators += string(parsing_str[i]) + '\n';
	}

	buf_line->SetLine(str_with_separators, cur_rule_num);
	parsing_log.AddRecordLine(buf_line);
	///table_model->AppendLine(buf_line);
}

ItemString LtoR_MethodAlg_u::RestoreStringFromLog(const string& log_str)
{
	ItemString restored_str;
	char* arr_of_char = new char[log_str.size() + 1];
	copy(log_str.begin(), log_str.end(), arr_of_char);
	arr_of_char[log_str.size()] = '\0';
	char* context;
	bool added = false;

	char* item;
	item = strtok_s(arr_of_char, "\n", &context);
	while (item != NULL)
	{
		for (int i = 0; i < rules.size(); i++) {
			if (string(item) == string(rules[i].GetLeft())) {
				added = true;
				restored_str.AddSymb(rules[i].GetLeft());
			}
		}
		if (!added) {
			restored_str.AddSymb(ItemSymb(item));
		}
		item = strtok_s(NULL, "\n", &context);
		added = false;
	}

	return restored_str;
}

bool LtoR_MethodAlg_u::DoParse()
{
	return false;
}