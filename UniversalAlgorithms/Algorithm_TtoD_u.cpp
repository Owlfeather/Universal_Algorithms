#include "Algorithm_TtoD_u.h"

void TtoD_MethodAlg_u::SetRulesOfAlg()
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

	buf_symb = { c_number, c_unsigned_int };	// <цифра><цбз>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 1

	buf_symb.pop_back();						// <цифра>
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

	cout << endl << "Правила для разбора сверху вниз сформированы:" << endl << endl;
	for (unsigned i = 0; i < rules.size(); i++) {
		rules[i].PrintRule();
		cout << endl;
	}
}

void TtoD_MethodAlg_u::SetParsingStr(ItemString inp_str)
{
	parsing_str = inp_str;
}

ResultOfStringReceiving TtoD_MethodAlg_u::SetParsingStr(string inp_str, bool contains_complex_nonterminals)
{
	if (contains_complex_nonterminals) {
		unsigned table[5][4] = { {0, 1, 2, 5},
								 {5, 0, 0, 0},
								 {3, 4, 5, 6},
								 {3, 4, 5, 0},
								 {5, 3, 3, 3} };
		unsigned error = 5, empty = 6, i = 0;
		string working_str = inp_str;
		unsigned str_size = working_str.size();
		char current_state = 0;
		char control_char;
		unsigned char_signal, next_state;
		string complex_terminal;

		while (i < str_size) {
			control_char = working_str[i];
			if (control_char == '$') { char_signal = 1; }
			else if (control_char == '<') { char_signal = 2; }
			else if (control_char == '>') { char_signal = 3; }
			else { char_signal = 0; }

			next_state = table[current_state][char_signal];

			if (next_state == error) {
				return ResultOfStringReceiving::FAILURE;
			}
			if (next_state == empty) {
				return ResultOfStringReceiving::EMPTY_BRACKETS;
			}
			if (next_state == 2) {
				complex_terminal.clear();
			}
			if (((current_state == 0) && (next_state == 0))
				|| ((current_state == 1) && (next_state == 0))) {
				parsing_str.AddSymb(working_str[i]);
			}
			if (next_state == 3) {
				complex_terminal.push_back(working_str[i]);
			}
			if ((current_state == 3) && (next_state == 0)) {
				parsing_str.AddSymb("<" + complex_terminal + ">");
			}

			current_state = next_state;
			i++;
		}
		if ((current_state == 0) && (parsing_str.Length() != 0)) {
			return ResultOfStringReceiving::SUCCESS;
		}
		else {
			return ResultOfStringReceiving::FAILURE;
		}
	}
	else {
		parsing_str = inp_str;
	}
}

void TtoD_MethodAlg_u::WriteToLog(const RuleNum cur_rule_num, 
	const TypeOfTtoDLine inp_status, const int inp_source_s)
{
	TtoD_Line_u* buf_line;
	buf_line = new TtoD_Line_u();

	string rec_str = MakeStrForLog(recognized_str);
	string pars_str = MakeStrForLog(parsing_str);
	string targ_str = MakeStrForLog(target_str);

	buf_line->SetLine(rec_str, cur_rule_num, pars_str, targ_str, inp_status, inp_source_s);
	parsing_log.AddRecordLine(buf_line);
	///table_model->AppendLine(buf_line);
}

ItemString TtoD_MethodAlg_u::RestoreStringFromLog(const string& log_str)
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

string TtoD_MethodAlg_u::MakeStrForLog(ItemString& orig_str)
{
	string str_with_separators;
	for (int i = 0; i < orig_str.Length(); i++) {
		str_with_separators += string(orig_str[i]) + '\n';
	}
	return str_with_separators;
}

bool TtoD_MethodAlg_u::DoParse()
{
	return false;
}