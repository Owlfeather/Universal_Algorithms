#include "Algorithm_LtoR_u.h"

void LtoR_MethodAlg_u::SetParsingStr(ItemString inp_str)
{
	parsing_str = inp_str;
}

void LtoR_MethodAlg_u::SetRulesOfAlg()
{

	//__________________________________________�������� ������������

	ItemSymb c_integer("<�����>", false, true);
	ItemSymb c_unsigned_int("<���>", false);
	ItemSymb c_number("<�����>", false);
	ItemSymb c_sign("<����>", false);

	vector<ItemSymb> buf_symb;					// ����������-������ ��� �������� ��������� �������
	vector<ItemString> buf_str;					// ����������-������ ��� �������� ���� ��������� ��������� ������� (������ ����� �������)

	buf_symb = { c_sign, c_unsigned_int };		// <����><���>
	buf_str.push_back(ItemString(buf_symb));	// �������� ������� 1

	buf_symb = { c_unsigned_int };				// <���>
	buf_str.push_back(ItemString(buf_symb));	// �������� ������� 2

	ItemRule rule(c_integer, buf_str);			// �������
	buf_str.clear();							// ������ ���������
	rules.push_back(rule);						// ���������� ������ �������
	//----------------------------------------------------

	buf_symb.push_back(c_number);				// <���><�����>
	buf_str.push_back(ItemString(buf_symb));	// �������� ������� 1

	buf_symb = { c_number };					// <�����>
	buf_str.push_back(ItemString(buf_symb));	// �������� ������� 2

	rule.SetRule(c_unsigned_int, buf_str);		// �������
	buf_str.clear();							// ������ ���������
	rules.push_back(rule);						// ���������� ������ �������

	//__________________________________________�������� ����������

	for (int i = 0; i < 10; i++) {
		buf_symb = { ItemSymb(to_string(i)) };
		buf_str.push_back(ItemString(buf_symb));   // ����� �������
	}

	rule.SetRule(c_number, buf_str);			// �������
	buf_str.clear();							// ������ ���������
	rules.push_back(rule);						// ���������� ������ �������
	//----------------------------------------------------

	buf_symb = { ItemSymb("+") };
	buf_str.push_back(ItemString(buf_symb));	// +

	buf_symb = { ItemSymb("-") };
	buf_str.push_back(ItemString(buf_symb));	// -

	rule.SetRule(c_sign, buf_str);				// �������
	rules.push_back(rule);						// ���������� ������ �������
	//----------------------------------------------------

	max_quantity = FindMaxQuantity();

	cout << endl << "������� ��� ������� ����� ������� ������������:" << endl << endl;
	for (unsigned i = 0; i < rules.size(); i++) {
		rules[i].PrintRule();
		cout << endl;
	}

	non_collapsible_axiom = DefineAxiomCollapsibility();
	if (non_collapsible_axiom) {
		cout << endl << "��������������� �������" << endl;
	}
	else {
		cout << endl << "������������� �������" << endl;
	}
}


bool LtoR_MethodAlg_u::CurrentStepIsDeadendBranch()
{
	auto it = std::find(std::begin(deadend_branch_steps),
		std::end(deadend_branch_steps), parsing_str);

	if (deadend_branch_steps.end() == it)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void LtoR_MethodAlg_u::AddStepToDeadendStepsList()
{
	deadend_branch_steps.push_back(parsing_str);
}

bool LtoR_MethodAlg_u::StepHasDeadendStatus(unsigned step)
{
	TypeOfLtoRLine status = dynamic_cast<LtoR_Line_u*>(parsing_log[step])->GetStatus();

	if ((status == TypeOfLtoRLine::DEAD_END_BRANCH)
		|| (status == TypeOfLtoRLine::DEAD_END)) {
		return true;
	}
	else {
		return false;
	}
}



bool LtoR_MethodAlg_u::DefineAxiomCollapsibility()
{
	unsigned repeats_of_axiom = 0;
	for (ItemRule rule : rules)
	{
		if (rule.GetLeft().IsAxiom()) {
			repeats_of_axiom++;
		}
		for (ItemString option : rule.GetRight())
		{
			for (ItemSymb symb : option.GetSymbs())
			{
				if (symb.IsAxiom()) {
					repeats_of_axiom++;
				}
			}
		}
	}
	if (repeats_of_axiom > 1) {
		return false;
	}
	else {
		return true;
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

	if (entry_point == last_entry_point) {
		return false;
	}
	else {
		if (((last_entry_point - entry_point) >= item_length) 
			and (item_length < max_quantity)) {
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

	cout << endl << "��������� �����������: ";
	parsing_item.PrintString();
	cout << endl << "   ��� �����: " << to_string(parsing_item.Length());

	for (auto i = rulenum.fir_num; i < rules_length; i++) {
		options_length = rules[i].RightSize();
		for (auto j = rulenum.sec_num; j < options_length; j++) {
			if (parsing_item == rules[i][j]) {
				//comment_line.clear();
				//comment_line = "   ������� " + (char(i + 224)) + to_string((j + 1)) + " �������!";
				//cout << comment_line;

				cout << endl << "������� " << char(i + 224) << to_string((j + 1)) << " �������!" << endl;
				return RuleNum{ i, j };
			}
			else {
				//comment_line.clear();
				//comment_line = "   ������� " + (char(i + 224)) + to_string((j + 1)) + " �� �������";
				///cout << comment_line;
			}
		}
	}
	cout << endl << "���������� ������ �� �������" << endl;
	return RuleNum{ -1, -1 }; // ���������� ������ �� �������
}




RuleNum LtoR_MethodAlg_u::RollbackAndGetNextRule()
{
	comment_line.clear();
	comment_line = "   ��������� ��������, ��������� ����� �����\n";
	comment_line += "   ������������ ����� � ������� " + to_string(rollback_step) + " �������";
	cout << comment_line;
	///comments_model->AddRecordLine(comment_line, TypeOfComment::DEAD_END);

	LtoR_Line_u current_line;
	//unsigned entry_point;
	RuleNum prev_rule;
	RuleNum last_rule = { rules.size() - 1, rules[rules.size() - 1].RightSize() - 1 };

	current_line = *(dynamic_cast<LtoR_Line_u*>(parsing_log[rollback_step]));
	parsing_str = RestoreStringFromLog(current_line.GetCurString());

	if (current_line.HasNoOffset()) {
		prev_rule = current_line.GetRuleNum();
		entry_point = current_line.GetEntryPoint();
	}
	else {
		prev_rule = (current_line.GetRuleNum() + current_line.GetOffset());
		entry_point = current_line.GetOffsetEntryPoint();
	}

	parsing_item = rules[prev_rule.fir_num][prev_rule.sec_num];
	
	//==============================================
	cout << endl << "   ����������� ������: ";
	parsing_str.PrintString();
	cout << endl;
	cout  << "   ��������� �������: ";
	parsing_item.PrintString();
	cout << "   ��� �����: " << to_string(parsing_item.Length());
	cout << endl;
	//==============================================


	if (prev_rule != last_rule) {

		if ((rules[prev_rule.fir_num].RightSize() - 1) > prev_rule.sec_num) {
			prev_rule.sec_num++;
		}
		else if ((rules.size() - 1) > prev_rule.fir_num) {
			prev_rule.fir_num++;
			prev_rule.sec_num = 0;
		}
		return prev_rule;
	}
	else {
		ChangeParsingItem(); // ������ true �����, ��������� ���� �������� � StepCanBeTried()
		return { 0, 0 };
	}

}

void LtoR_MethodAlg_u::WriteToLog(const RuleNum cur_rule_num, 
	const TypeOfLtoRLine inp_status, const int inp_source_s, const RuleNum& inp_offset)
{
	LtoR_Line_u* buf_line;
	buf_line = new LtoR_Line_u();

	string str_with_separators;
	for (int i = 0; i < parsing_str.Length(); i++) {
		str_with_separators += string(parsing_str[i]) + '\n';
	}

	buf_line->SetLine(str_with_separators, cur_rule_num, entry_point, inp_status, inp_source_s, inp_offset);
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

void LtoR_MethodAlg_u::MarkLastStepInLogAs(TypeOfLtoRLine mark_status)
{
	switch (mark_status)
	{
	case REGULAR_LINE:
		break;
	case DEAD_END_BRANCH:
		break;
	case DEAD_END:
		dynamic_cast<LtoR_Line_u*>(parsing_log[parsing_log.Size() - 1])->MarkAsDeadEnd();
		break;
	case PARSED_END:
		break;
	case NOT_PARSED_END:
		dynamic_cast<LtoR_Line_u*>(parsing_log[parsing_log.Size() - 1])->MarkAsNotParsedEnd();
		break;
	}
}

void LtoR_MethodAlg_u::MarkDeadendBranch(unsigned step)
{
		dynamic_cast<LtoR_Line_u*>(parsing_log[step])->MarkAsDeadEndBranch();

		cout << endl << "___�������� ��� ��������� �����: " << to_string(step) << endl;

		int step_source = step;
		while (dynamic_cast<LtoR_Line_u*>(parsing_log[step_source])->HasSource()) {
			step_source = dynamic_cast<LtoR_Line_u*>(parsing_log[step_source])->GetSourceStep();
			dynamic_cast<LtoR_Line_u*>(parsing_log[step_source])->MarkAsDeadEndBranch();
			cout << endl << "___�������� ��� ��������� �����: " << to_string(step_source) << endl;

		}
}

bool LtoR_MethodAlg_u::AxiomIsRecognized()
{
	if ((parsing_str.Length() == 1)
		and (parsing_str[0]).IsAxiom()) 
		return true;
	else
		return false;
}

bool LtoR_MethodAlg_u::GetAxiomInParsingString()
{
	bool get_axiom = false;
	for (ItemSymb symb : parsing_str.GetSymbs())
	{
		if (symb.IsAxiom()) {
			get_axiom = true;
		}
	}
	return get_axiom;
}

void LtoR_MethodAlg_u::SetStartOfSearch()
{
	entry_point = 0;
	parsing_item.SetString({ parsing_str[entry_point] });
}

void LtoR_MethodAlg_u::AddOffsetToRollbackStep(const RuleNum& rule)
{
	RuleNum offset = { 0, 0 }, new_rule = rule;
	RuleNum prev_rule = dynamic_cast<LtoR_Line_u*>(parsing_log[rollback_step])->GetRuleNum();
	offset = new_rule - prev_rule;

	dynamic_cast<LtoR_Line_u*>(parsing_log[rollback_step])->SetNewEntryPoint(entry_point);
	dynamic_cast<LtoR_Line_u*>(parsing_log[rollback_step])->SetOffset(offset);


	int step_source = rollback_step;
	while (dynamic_cast<LtoR_Line_u*>(parsing_log[step_source])->HasSource()) {
		step_source = dynamic_cast<LtoR_Line_u*>(parsing_log[step_source])->GetSourceStep();
		dynamic_cast<LtoR_Line_u*>(parsing_log[step_source])->SetNewEntryPoint(entry_point);
		dynamic_cast<LtoR_Line_u*>(parsing_log[step_source])->SetOffset(offset);
	}
	
}


void LtoR_MethodAlg_u::TransformAccordingRule(const RuleNum& rule)
{
	//==============================================
	cout << "   ������ ������ �������: ";
	parsing_str.PrintString();
	cout << endl;
	cout << "   ����������� ";
	parsing_item.PrintString();
	cout << " � " << string(rules[rule.fir_num].GetLeft()) << endl;
	//==============================================


	parsing_str[entry_point] = rules[rule.fir_num].GetLeft();

	unsigned num_of_cleaned = parsing_item.Length() - 1;
	if (num_of_cleaned > 0) {
		parsing_str.DeleteSymb(entry_point + 1, num_of_cleaned);
	}

	//==============================================
	cout << "   ����� ������ �������: ";
	parsing_str.PrintString();
	cout << endl;
	//==============================================
}

int LtoR_MethodAlg_u::CheckForRollback()
{
	int num_of_step = parsing_log.Size() - 2; // �������� � ���������� ������������ ����
	int step_source;

	while (num_of_step > -1) { // ���� �� ����������� ��� ����

		if (StepCanBeTried(num_of_step)) {
			// ����� ��������� �����
			SetRollbackFlag(); // ������� � ����� ������
			return num_of_step;
		}
		else {
			//auto already_deadend = StepHasDeadendStatus(num_of_step);
			//cout << endl << "===========================================" <<to_string(num_of_step) << " --- " << to_string(already_deadend) << endl;
			if (!StepHasDeadendStatus(num_of_step)) {

				MarkDeadendBranch(num_of_step);
				
			}
			num_of_step--;
		}
	}

	return -1; // ������� ������ �����������
}

bool LtoR_MethodAlg_u::StepCanBeTried(unsigned num_of_step)
{
	LtoR_Line_u current_line;
	ItemString current_string;
	unsigned entry_point;
	TypeOfLtoRLine status;

	current_line = *(dynamic_cast<LtoR_Line_u*>(parsing_log[num_of_step]));
	status = current_line.GetStatus();

	if ((status == TypeOfLtoRLine::DEAD_END)
		|| (status == TypeOfLtoRLine::DEAD_END_BRANCH)) {
		return false;
	}

	if (current_line.HasNoOffset()) {
		entry_point = current_line.GetEntryPoint();
	}
	else {
		entry_point = current_line.GetOffsetEntryPoint();
	}

	if (entry_point == current_string.Length() - 1) {
		return false; // �� ���� ���� ����������� ��� �������
	}
	else {
		return true; // ����� ����������� ��������� � ����� ����
	}
}

bool LtoR_MethodAlg_u::DoParse()
{
	bool parsing_is_over = false;
	ClearRollbackFlag();
	SetStartOfSearch();
	RuleNum next_rule = { 0, 0 }, 
			rule;


	while (!parsing_is_over) {

			rule = FindSuitableRule(next_rule);

			if (rule.IsFound()) {
				if (ParsingIsOnRollbackBranch()) {
					ClearRollbackFlag();
					AddOffsetToRollbackStep(rule);
					WriteToLog(rule, TypeOfLtoRLine::REGULAR_LINE, rollback_step);
				}
				else {
					WriteToLog(rule);
				}
				TransformAccordingRule(rule);
				SetStartOfSearch();

				if (AxiomIsRecognized()) {
					WriteToLog(rule, TypeOfLtoRLine::PARSED_END);
					parsing_is_over = true;
				}
				else if (AxiomIsNonCollapsible()) { /// ����� ��� ��������������� ������
					if (GetAxiomInParsingString()) {
						WriteToLog(rule, TypeOfLtoRLine::DEAD_END);
						rollback_step = CheckForRollback();
						if (RollbackIsPossible()) { // ���� ����������� ��������
							next_rule = RollbackAndGetNextRule();

							cout << endl << "ENTRY_POINT: " << to_string(entry_point) << endl;
						}
						else {
							MarkLastStepInLogAs(TypeOfLtoRLine::NOT_PARSED_END);
							parsing_is_over = true;
						}
					}
				}
				else if (CurrentStepIsDeadendBranch()) {
					//if (ParsingIsOnRollbackBranch()) {
						rollback_step = CheckForRollback();
						if (RollbackIsPossible()) { // ���� ����������� ��������
							next_rule = RollbackAndGetNextRule();
						}
						else {
							MarkLastStepInLogAs(TypeOfLtoRLine::NOT_PARSED_END);
							parsing_is_over = true;
						}
					//}
				}
			}
			else {
				if (!ChangeParsingItem()) { // ��������� ������
					if (AxiomIsNonCollapsible()) {
						if (ParsingIsOnRollbackBranch()) {
							cout << endl << "OH_SHIT" << endl;
							//WriteToLog(rule, TypeOfLtoRLine::DEAD_END_BRANCH, rollback_step);
							MarkDeadendBranch(rollback_step);
						}
						else {
							WriteToLog(rule, TypeOfLtoRLine::DEAD_END_BRANCH);
						}
						AddStepToDeadendStepsList();
					}
					else {
						WriteToLog(rule, TypeOfLtoRLine::DEAD_END);
					}
					rollback_step = CheckForRollback();
					if (RollbackIsPossible()) { // ���� ����������� ��������
						next_rule = RollbackAndGetNextRule();
					}
					else {
						MarkLastStepInLogAs(TypeOfLtoRLine::NOT_PARSED_END);
						parsing_is_over = true;
					}
				}
				else {
					next_rule = { 0, 0 };
				}
			}
			//parsing_log.PrintLogLtoR_u();
			//i++;
		//}
	}
	//////////////////
	cout << endl <<"***������_����=" << parsing_log.Size();

	parsing_log.PrintLogLtoR_u();
	return false;
}