#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Basic_Elements.h"
//#include "LogTable.h"

using namespace std;

//-----------------------------------------------------------------

class ItemRule {

	ItemSymb left;
	vector<ItemString> right;

public:

	ItemRule() {}
	ItemRule(const ItemSymb & inp_l, const vector <ItemString> & inp_r) : left(inp_l), right(inp_r) {}

	void SetRule(const ItemSymb & inp_l, const vector <ItemString> & inp_r);
	int RightSize() { return right.size(); }
	ItemSymb GetLeft() { return left; }
	ItemString GetRightOption(unsigned i) { return right[i]; }
	vector<ItemString> GetRight() { return right; }
	void PrintRule();

	ItemString &operator[] (const int i) { return right[i]; }
};

//-----------------------------------------------------------------

struct RuleNum { 
	int fir_num; 
	int sec_num; 

	bool IsFound() { return ((fir_num > -1) and (sec_num > -1)); }
	bool operator == (const RuleNum& other_rule) const {
		return this->fir_num == other_rule.fir_num && this->sec_num == other_rule.sec_num;
	}
	bool operator != (const RuleNum& other_rule) const {
		return this->fir_num != other_rule.fir_num || this->sec_num != other_rule.sec_num;
	}
	const RuleNum operator+(const RuleNum& another) {
		return RuleNum({fir_num + another.fir_num, sec_num + another.sec_num});
	}
	const RuleNum operator-(const RuleNum& another) {
		return RuleNum({ fir_num - another.fir_num, sec_num - another.sec_num });
	}
};

//-----------------------------------------------------------------


class RecordLine {

protected:

	string cur_string;
	RuleNum rule_num;

public:

	virtual void PrintLine() = 0;
	virtual TypeOfAlg GetType() = 0;

	string GetCurString() { return cur_string; }
	RuleNum GetRuleNum() { return rule_num; }

	virtual vector<string>  GetLine() = 0;
};


//-----------------------------------------------------------------

class LtoR_Line : public RecordLine {

public:

	void SetLine(const string & inp_str, const RuleNum & inp_rnum);
	void PrintLine() override;
	vector<string>  GetLine() override;

	TypeOfAlg GetType() override;
};

//-----------------------------------------------------------------
class LtoR_Line_u : public RecordLine {

private:
	RuleNum offset;
	TypeOfLtoRLine status;
	unsigned entry_point;
	int entry_point_offset;
	int source_step;

public:

	void SetLine(const string& inp_str, const RuleNum& inp_rnum,
		const unsigned inp_entry,
		const TypeOfLtoRLine inp_status = TypeOfLtoRLine::REGULAR_LINE, 
		const int inp_source_s = -1,
		const RuleNum& inp_offset = {0, 0},
		const int inp_entry_p_off = -1);
	
	void PrintLine() override;
	vector<string>  GetLine() override;
	TypeOfAlg GetType() override;

	void MarkAsDeadEndBranch() { status = TypeOfLtoRLine::DEAD_END_BRANCH; }
	void MarkAsDeadEnd() { status = TypeOfLtoRLine::DEAD_END; }
	void MarkAsNotParsedEnd() { status = TypeOfLtoRLine::NOT_PARSED_END; }
	void SetNewEntryPoint(int inp_entry_point) { entry_point_offset = inp_entry_point;	}
	void SetOffset(const RuleNum& inp_rnum) { offset = inp_rnum; }

	const TypeOfLtoRLine GetStatus() { return status; }
	const RuleNum& GetOffset() { return offset; }
	const unsigned GetEntryPoint() { return entry_point; }
	const int GetOffsetEntryPoint() { return entry_point_offset; }
	const int GetSourceStep() { return source_step; }

	bool HasSource() { return (source_step != -1); }
	bool HasNoOffset() { return ((offset == RuleNum{0, 0}) and (entry_point_offset == -1)); }


	LtoR_Line_u& operator=(LtoR_Line_u& source)//перегрузка
	{
		cur_string = source.GetCurString();
		rule_num = source.GetRuleNum();
		status = source.GetStatus();
		offset = source.GetOffset();
		entry_point = source.GetEntryPoint();
		entry_point_offset = source.GetOffsetEntryPoint();
		source_step = source.GetSourceStep();
		return *this;//возвращаем ссылку на текущий объект
	}
};


class TtoD_Line : public RecordLine {

	string recognized;
	string target;
	unsigned type;
	TypeOfTtoDLine type_of_line;

public:

	TypeOfAlg GetType() override;

	//void SetLine(const string & rec_str, const string & pars_str, const string & targ_str, unsigned type_of_line, const RuleNum & inp_rnum);
	void SetLine(const string& rec_str, const string& pars_str,
		const string& targ_str, unsigned type_of_l,
		TypeOfTtoDLine line_type, const RuleNum& inp_rnum);
	void PrintLine() override;
	vector<string>  GetLine() override;

	void MarkLastLine() { type_of_line = END_LINE; }
	void MarkRollback() { rule_num.sec_num++; }
	void TypeMarkRollback() { type_of_line = TypeOfTtoDLine::ROLLB_IMPOSS; }
	string MakePrintable(string & str_with_seps);
	string GetRecString() { return recognized; }
	string GetTargString() { return target; }
	TypeOfTtoDLine& GetTypeOfLine() { return type_of_line; }
};

//-----------------------------------------------------------------

class LLk_TtoD_Line : public RecordLine {

	string stack_str;
	//unsigned type;
	//TypeOfTtoDLine type_of_line;

public:

	TypeOfAlg GetType() override;
	vector<string>  GetLine() override;

	void SetLine(const string& pars_str,
		const string& st_str, const RuleNum& inp_rnum);
	void PrintLine() override;

	string GetStackString() { return stack_str; }

	//void MarkRollback() { rule_num.sec_num++; }
	//void TypeMarkRollback() { type_of_line = TypeOfTtoDLine::ROLLB_IMPOSS; }
	//string MakePrintable(string& str_with_seps);
	//string GetRecString() { return recognized; }

	//TypeOfTtoDLine& GetTypeOfLine() { return type_of_line; }
};

//-----------------------------------------------------------------

class LRk_Stack_Line : public RecordLine {

	string stack_str;
	TypeOfRelation relation_str;
	string trio_str;
	RuleNum result_str;

public:
	TypeOfAlg GetType() override;
	vector<string>  GetLine() override;

	void SetLine(const string& pars_str, const RuleNum rulenum, const string& st_str,
		const TypeOfRelation rel_str, const string& tr_str,
		const RuleNum res_str);
	void PrintLine() override;

	string& GetStackString() { return stack_str; }
	TypeOfRelation GetRelation() { return relation_str; }
	string& GetTrioString() { return trio_str; }
	RuleNum GetResult() { return result_str; }

};

//-----------------------------------------------------------------


class ParseLog {
	vector<RecordLine *> records;
public:

	ParseLog() {}

	void AddRecordLine(RecordLine *inp_rec) { records.push_back(inp_rec); }
	int Size() { return records.size(); }
	void PrintLogLtoR();
	void PrintLogLtoR_u();
	void PrintLogTtoD();
	void PrintLogLLk();

	void ClearRecords() { records.clear(); }

	RecordLine * &operator[] (int i) { return records[i]; }
};

//-----------------------------------------------------------------

