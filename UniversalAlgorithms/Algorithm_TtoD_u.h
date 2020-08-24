#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Basic_Algorithm.h"


class TtoD_MethodAlg_u : public ParseAlgorithm {

	ItemString target_str;
	ItemString recognized_str;

public:

	void SetRulesOfAlg() override;
	bool DoParse() override;
	void SetParsingStr(ItemString inp_str) override;

	ResultOfStringReceiving SetParsingStr(string inp_str, bool contains_complex_nonterminals);


private:


	//RuleNum FindRuleNum();
	//bool FindCorrectTerm(const RuleNum& rulenum);
	//void RemoveMatchingSymbs();


	//void TransformAccordingRule(const RuleNum& rulenum);
	//RuleNum Rollback();

	
	//-----------logging-------------------------
	void WriteToLog(const RuleNum cur_rule_num,
		const TypeOfTtoDLine inp_status = TypeOfTtoDLine::HYPOTHESIS,
		const int inp_source_s = -1);
	ItemString RestoreStringFromLog(const string& log_str);
	string MakeStrForLog(ItemString& orig_str);

};

