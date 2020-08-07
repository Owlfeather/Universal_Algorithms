#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Basic_Algorithm.h"


class TtoD_LLk_MethodAlg : public ParseAlgorithm {

	ItemString target_str;

public:

	void SetRulesOfAlg() override;
	bool DoParse() override;
	void SetParsingStr(ItemString inp_str) override;

private:

	RuleNum FindRuleNum();
	bool FindCorrectTerm(const RuleNum& rulenum);
	void RemoveMatchingSymbs();

	void TransformAccordingRule(const RuleNum& rulenum);

	void WriteToLog(const RuleNum& cur_rule_num = { -1, 0 });


};
