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

void TtoD_MethodAlg_u::SetStartTarget()
{
	for (ItemRule rule : rules) {
		if (rule.GetLeft().IsAxiom()) {
			target_str = { rule.GetLeft() };
			return;
		}
	}
}

bool TtoD_MethodAlg_u::NonTerminalLeftInTarget()
{
	if (target_str[0].IsTerm()) {
		return false;
	}
	else {
		return true;
	}
}

RuleNum TtoD_MethodAlg_u::FindSuitableRule(const RuleNum rulenum)
{
	if (rulenum == RuleNum{0, -1}) {
		ItemSymb nonterminal = target_str[0];
		for (int i = 0; i < rules.size(); i++) {
			if (nonterminal == rules[i].GetLeft()) {
				return RuleNum{ i, 0 };
			}
			else {
				return RuleNum{ -1, -1 };
			}
		}
	}
	else {
		if (rulenum.sec_num < rules[rulenum.fir_num].RightSize() - 1) {
			return RuleNum{ rulenum.fir_num, rulenum.sec_num + 1 };
		}
		else {
			return RuleNum{ -1, -1 };
		}
	}

}

void TtoD_MethodAlg_u::TransformAccordingRule(const RuleNum& rule)
{
	ItemString option_str = rules[rule.fir_num][rule.sec_num];
	target_str.DeleteSymb(0, 1);
	for (int i = option_str.Length() - 1; i > -1; i--) {
		target_str.AddSymb(option_str[i], 0);
	}
}

bool TtoD_MethodAlg_u::RuleIsLastPossible(const RuleNum& rule)
{
	if (rule.sec_num == rules[rule.fir_num].RightSize() - 1) {
		return true;
	}
	else {
		return false;
	}
}

void TtoD_MethodAlg_u::MarkSourceStepAsWrongHypo()
{
	dynamic_cast<TtoD_Line_u*>(parsing_log[rollback_step])->MarkAsWrongHypo();
}

bool TtoD_MethodAlg_u::TerminalsMatched()
{
	if (ParsingStrIsEmpty()) {
		return false;
	} 
	else {
		if (parsing_str[0] == target_str[0]) {
			return true;
		}
		else {
			return false;
		}
	}
}

void TtoD_MethodAlg_u::RecognizeAndClearTerminals()
{
	recognized_str.AddSymb(parsing_str[0]);
	parsing_str.DeleteSymb(0, 1);
	target_str.DeleteSymb(0, 1);
}

int TtoD_MethodAlg_u::CheckForRollback()
{
	int i = parsing_log.Size() - 1;
	while (i > -1) {
		if (dynamic_cast<TtoD_Line_u*>(parsing_log[i])->GetStatus() == TypeOfTtoDLine::HYPOTHESIS) {
			return i;
		}
		i--;
	}
	return -1;
}

RuleNum TtoD_MethodAlg_u::RollbackAndGetCurRule()
{
	TtoD_Line_u source_step = *dynamic_cast<TtoD_Line_u*>(parsing_log[rollback_step]);

	recognized_str = RestoreStringFromLog(source_step.GetRecString());
	parsing_str = RestoreStringFromLog(source_step.GetCurString());
	target_str = RestoreStringFromLog(source_step.GetTargString());

	return (source_step.GetRuleNum());
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

void TtoD_MethodAlg_u::MarkLastStepInLogAs(TypeOfTtoDLine mark_status)
{
	switch (mark_status)
	{
	case HYPOTHESIS:
		break;
	case WRONG_HYPO:
		break;
	case LAST_HYPO:
		break;
	case MISTAKE:
		break;
	case RECOGNIZED:
		break;
	case PARSED_END_TtoD:
		break;
	case NOT_PARSED_END_TtoD:
		dynamic_cast<TtoD_Line_u*>(parsing_log[parsing_log.Size() - 1])->MarkAsNotParsedEnd();
		break;
	}
}

bool TtoD_MethodAlg_u::DoParse()
{
	bool parsing_is_over = false;
	ClearRollbackFlag();
	SetStartTarget();
	RuleNum next_rule = { 0, -1 },
			rule;


	while (!parsing_is_over) {
		if (TargetStrIsEmpty()) {
			if ((ParsingStrIsEmpty()) && (TargetStrIsEmpty())) {
				WriteToLog(rule, TypeOfTtoDLine::PARSED_END_TtoD);
				parsing_is_over = true;
			}
			else {
				WriteToLog(rule, TypeOfTtoDLine::MISTAKE);
				rollback_step = CheckForRollback();
				if (RollbackIsPossible()) {
					SetRollbackFlag();
					next_rule = RollbackAndGetCurRule();
				}
				else {
					MarkLastStepInLogAs(TypeOfTtoDLine::NOT_PARSED_END_TtoD);
					parsing_is_over = true;
				}
			}
		}
		else {
			if (NonTerminalLeftInTarget()) {
				rule = FindSuitableRule(next_rule);
				if (rule.IsFound()) {
					if (ParsingIsOnRollbackBranch()) {
						WriteToLog(rule, HYPOTHESIS, rollback_step);
						if (RuleIsLastPossible(rule)) {
							WriteToLog(rule, TypeOfTtoDLine::LAST_HYPO, rollback_step);
						}
						else {
							WriteToLog(rule, HYPOTHESIS, rollback_step);
						}
						MarkSourceStepAsWrongHypo();
						ClearRollbackFlag();
					}
					else {
						WriteToLog(rule);
					}
					TransformAccordingRule(rule);
				}
			}
			else { // слева терминал
				if (TerminalsMatched()) {
					WriteToLog(rule, TypeOfTtoDLine::RECOGNIZED);
					RecognizeAndClearTerminals();
					ClearRollbackFlag();
				}
				else {
					WriteToLog(rule, TypeOfTtoDLine::MISTAKE);
					rollback_step = CheckForRollback();
					if (RollbackIsPossible()) {
						SetRollbackFlag();
						next_rule = RollbackAndGetCurRule();
					}
					else {
						MarkLastStepInLogAs(TypeOfTtoDLine::NOT_PARSED_END_TtoD);
						parsing_is_over = true;
					}
				}
			}
		}
		if (!ParsingIsOnRollbackBranch()) {
			next_rule = { 0, -1 };
		}
	}

	cout << endl << "***РАЗМЕР_ЛОГА=" << parsing_log.Size();

	parsing_log.PrintLogTtoD_u();

	return false;
}