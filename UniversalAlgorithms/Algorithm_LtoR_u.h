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

public:

	void SetRulesOfAlg() override;
	void SetParsingStr(ItemString inp_str) override;
	bool DoParse() override;

	void SetRulesOfAlg(unsigned code_of_rules);
	ResultOfStringReceiving SetParsingStr(string inp_str, bool contains_complex_nonterminals);

	//***for debugging
	void PrintParsingStr() { parsing_str.PrintElements(); }

private:

	ItemString parsing_item;
	unsigned entry_point;
	unsigned max_quantity;
	bool rollback_flag;
	int rollback_step;
	bool non_collapsible_axiom;
	std::list<ItemString> deadend_branch_steps;

	//-----------initialization-----------------
	bool DefineAxiomCollapsibility();
	unsigned FindMaxQuantity();

	//-----------deadend_branch_steps-----------
	bool CurrentStepIsDeadendBranch();
	void AddStepToDeadendStepsList();
	//***for debugging
	void PrintDeadEndBranches() {
		cout << endl << endl << "===DEAD_END_BRANCHES_LIST===" << endl << endl;
		for (ItemString step : deadend_branch_steps) {
			step.PrintString();
			cout << endl;
		}
	}

	//-----------rollback-----------------------
	bool StepHasDeadendStatus(unsigned step);
	bool RollbackIsPossible() { return (rollback_step != -1); }
	bool StepCanBeTried(unsigned num_of_step);
	void ClearRollbackFlag() { rollback_flag = false; }
	void SetRollbackFlag() { rollback_flag = true; }
	void AddOffsetToRollbackStep(const RuleNum& rule);
	int CheckForRollback();
	RuleNum RollbackAndGetNextRule();

	//-----------parsing-------------------------
	bool ChangeParsingItem();
	bool AxiomIsRecognized();
	bool ParsingIsOnRollbackBranch() { return rollback_flag; }
	bool AxiomIsNonCollapsible() { return non_collapsible_axiom; }
	bool GetAxiomInParsingString();
	RuleNum FindSuitableRule(const RuleNum rulenum = { 0, 0 });
	void SetStartOfSearch();
	void TransformAccordingRule(const RuleNum& rule);

	//-----------logging-------------------------
	void WriteToLog(const RuleNum cur_rule_num,
		const TypeOfLtoRLine inp_status = TypeOfLtoRLine::REGULAR_LINE,
		const int inp_source_s = -1,
		const RuleNum& inp_offset = { 0, 0 });
	ItemString RestoreStringFromLog(const string& log_str);
	void MarkLastStepInLogAs(TypeOfLtoRLine mark_status);
	void MarkDeadendBranch(unsigned step);
};

