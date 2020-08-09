#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
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
	unsigned FindMaxQuantity();
	bool ChangeParsingItem();
	RuleNum FindSuitableRule(const RuleNum rulenum = { 0, 0 });
	bool AxiomIsRecognized();
	void SetStartOfSearch();

	int CheckForRollback();

	//RuleNum FindRuleNum(const RuleNum& rulenum);
	//RuleNum GetNextRule();

	//void TransformAccordingRule(const ItemSymb& substr, const unsigned start, const unsigned num_of_cleaned);
	void TransformAccordingRule(const RuleNum& rule);
	RuleNum RollbackAndGetNextRule();

	void WriteToLog(const RuleNum cur_rule_num, 
		const TypeOfLtoRLine inp_status = TypeOfLtoRLine::REGULAR_LINE,
		const RuleNum& inp_offset = { 0, 0 });
	ItemString RestoreStringFromLog(const string& log_str);

};

