#pragma once

#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Basic_Algorithm.h"


class Stack_LRk_MethodAlg : public ParseAlgorithm {


public:

	void SetRulesOfAlg() override;
	bool DoParse() override;
	void SetParsingStr(ItemString inp_str) override;
	vector<vector<TypeOfRelation>>* GetRelationTable() { return &relation_table; }

private:
	
	vector<vector<TypeOfRelation>> relation_table;
	ItemString stack_str;
	ItemString parsing_item;
	RuleNum rulenum;
	
	unsigned point_of_entry;

	bool SelectNextSymb();
	int FindLeftNum();
	int FindRightNum();
	void DoCarry();
	bool DoConvolution(bool full);


	void WriteToLog(const RuleNum& rel_rule_num, const string& stack_s, const string& parse_s,
		const string& trio_str = "", const RuleNum& res_rule_num = { -1, 0 });


};
