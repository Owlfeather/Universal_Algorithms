#pragma once
#include "LogTable.h"
#include"LogComments.h"

class ParseAlgorithm {

protected:

	vector<ItemRule> rules;
	ItemString parsing_str;
	ParseLog parsing_log;


	//LogTable* table_model;
	//LogComments* comments_model;
	string comment_line;
	

public:

	ParseAlgorithm() 
	{ 
		/*table_model = new LogTable; 
		table_model->ResetRow();
		comments_model = new LogComments;
		comments_model->ResetRow();*/
	}
	ParseAlgorithm(ItemString& inp_str) {
		parsing_str = inp_str;
		/*table_model = new LogTable;
		table_model->ResetRow();
		comments_model = new LogComments;
		comments_model->ResetRow();*/
	}

	void ResetLogs()
	{
		/*table_model->ResetRow();
		comments_model->ResetRow();

		table_model->ClearRecords();
		comments_model->ClearRecords();*/
		parsing_log.ClearRecords();
	}

	ItemRule& GetRule(unsigned i) { return rules[i]; }
	unsigned RulesSize() { return rules.size(); }
	void SetLogTableType(TypeOfAlg type_alg);
	/*LogTable* GetTable() { return table_model; }
	LogComments* GetComments() { return comments_model; }*/
	vector<ItemRule>& GetRules() { return rules; }
	string GetParsingString() {return string(parsing_str);}


	virtual void SetParsingStr(ItemString inp_str) = 0;
	virtual void SetRulesOfAlg() = 0;
	virtual bool DoParse() = 0;
};


