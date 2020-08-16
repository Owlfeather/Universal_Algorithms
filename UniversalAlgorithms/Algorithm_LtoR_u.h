#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include "Basic_Algorithm.h"


class LtoR_MethodAlg_u : public ParseAlgorithm {

	ItemString parsing_item;
	

public:

	void SetRulesOfAlg() override;
	bool DoParse() override;
	void SetParsingStr(ItemString inp_str) override;


private:

	unsigned entry_point;
	unsigned max_quantity;
	bool rollback_flag;
	int rollback_step;
	bool non_collapsible_axiom;
	std::list<ItemString> deadend_branch_steps;

	bool CurrentStepIsDeadendBranch();
	void AddStepToDeadendStepsList();

	bool RollbackIsPossible() { return (rollback_step != -1); }
	bool DefineAxiomCollapsibility();
	unsigned FindMaxQuantity();
	bool ChangeParsingItem();
	RuleNum FindSuitableRule(const RuleNum rulenum = { 0, 0 });
	bool AxiomIsRecognized();
	bool ParsingIsOnRollbackBranch() { return rollback_flag; }
	bool AxiomIsNonCollapsible() { return non_collapsible_axiom; }
	bool GetAxiomInParsingString();
	void ClearRollbackFlag() { rollback_flag = false; }
	void SetRollbackFlag() { rollback_flag = true; }
	void SetStartOfSearch();

	void AddOffsetToRollbackStep(const RuleNum& rule);

	int CheckForRollback();

	bool StepCanBeTried(unsigned num_of_step);

	void TransformAccordingRule(const RuleNum& rule);
	RuleNum RollbackAndGetNextRule();

	void WriteToLog(const RuleNum cur_rule_num, 
		const TypeOfLtoRLine inp_status = TypeOfLtoRLine::REGULAR_LINE,
		const int inp_source_s = -1,
		const RuleNum& inp_offset = { 0, 0 });
	ItemString RestoreStringFromLog(const string& log_str);

	void MarkLastStepInLogAs(TypeOfLtoRLine mark_status);
	void MarkDeadendBranch();


};

