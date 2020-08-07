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
	unsigned entry_point;

public:

	void SetRulesOfAlg() override;
	bool DoParse() override;
	void SetParsingStr(ItemString inp_str) override;

private:

	unsigned FindMaxQuantity();
	bool ChangeParsingItem();
	RuleNum FindSuitableRule(const RuleNum rulenum = { 0, 0 });

	//RuleNum FindRuleNum(const RuleNum& rulenum);
	//RuleNum GetNextRule();

	//void TransformAccordingRule(const ItemSymb& substr, const unsigned start, const unsigned num_of_cleaned);
	RuleNum RollbackAndGetNextRule();

	void WriteToLog(const RuleNum cur_rule_num);
	ItemString RestoreStringFromLog(const string& log_str);

};

