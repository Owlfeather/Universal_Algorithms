#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

//----------------------------Классы-------------------------------

class ItemSymb {

	bool term;
	string content;
	bool axiom;

public:

	ItemSymb(): term(true), content(""), axiom(false) {}		// по умолчанию создаётся терминал (символы)
	ItemSymb(const string inp_cont, bool inp_term = true, bool inp_axiom = false) : content(inp_cont), term(inp_term), axiom(inp_axiom)  {}
	ItemSymb(const char inp_cont, bool inp_term = true, bool inp_axiom = false) : content({ inp_cont }), term(inp_term), axiom(inp_axiom) {}

	bool IsTerm() const { return term; }
	bool IsAxiom() const { return axiom; }

	void SetSymb(const string & inp_cont, bool inp_term = true, bool inp_axiom = false);
	void SetSymb(const char & inp_cont, bool inp_term = true, bool inp_axiom = false);
	void SetAsAxiom() { axiom = true; };

	operator string() const { return content; }
	bool operator == (const ItemSymb& c2) const { return content == c2.content; }
	bool operator != (const ItemSymb& c2) const { return content != c2.content; }
};

//-----------------------------------------------------------------

class ItemString {

	vector<ItemSymb> cur_string;

public:

	ItemString() {}
	ItemString(const vector<ItemSymb> & inp_str) : cur_string(inp_str) {}
	ItemString(const string & orig_str);	// первоначальная установка строки
	
	void SetString(const vector<ItemSymb> & inp_str) { cur_string = inp_str; }
	int Length() { return cur_string.size(); }
	void PrintString();

	void PrintElements() {
		cout << endl;
		for (int i = 0; i < cur_string.size(); i++) {
			cout << string(cur_string[i]) << "_";
		}
	}

	void AddSymb(const ItemSymb & inp_symb, const int pos = -1) 
	{ 
		if (pos == -1) {
			cur_string.push_back(inp_symb);
		}
		else {
			cur_string.insert(cur_string.begin() + pos, inp_symb);
		}

	}

	const vector<ItemSymb>& GetSymbs() { return cur_string; }

	void DeleteSymb(const int & first, const int & quantity);
	
	operator string() const; 
	ItemSymb &operator[] (int i) { return cur_string[i]; }
	bool operator==(const ItemString& another_str) const { return (cur_string == another_str.cur_string); }
	bool operator!=(const ItemString& another_str) const { return (cur_string != another_str.cur_string); }
};



enum class TypeOfAlg 
{
	LTOR,
	TTOD,
	LLK_TTOD,
	LRK_STACK
};

enum class ModeOfCWin 
{
	CWBEGIN,
	CWPARSE,
	CWPARSESTARTED,
	CWPARSEENDED,
	CWRESET,
	CWTEST
};

enum class Color
{
	RED,
	BLACK,
	GREEN
};

enum class TypeOfComment
{
	INFO,
	WRONG_RULE,
	CORRECT_RULE,
	DEAD_END,
	PARSE_CORRECT,
	PARSE_INCORRECT,
	HYPOTHESIS,
	ACTION
};

enum TypeOfLtoRLine
{
	REGULAR_LINE,
	REG_FURTHER_DEAD_END,
	DEAD_END_BRANCH,
	DEAD_END_BRANCH_VIEWED,
	DEAD_END,
	PARSED_END,
	NOT_PARSED_END
};

enum  TypeOfTtoDLine
{
	STATEMENT,
	ROLLB_POSS,
	ROLLB_IMPOSS,
	RULE_NOT_FIT,
	RULE_FIT,
	END_LINE,
	WRONG_SYMB,

	/// new:
	HYPOTHESIS,
	WRONG_HYPO,
	MISTAKE,
	RECOGNIZED,
	PARSED_END_TtoD,
	NOT_PARSED_END_TtoD
};

enum TypeOfRelation
{
	CARRY,		// перенос
	CONV,		// свёртка
	CONV_BR,	// свёртка скобок
	ID_ERROR,
	OP_ERROR,
	ERROR,
	EXIT
};

enum ResultOfStringReceiving
{
	SUCCESS,
	FAILURE,
	EMPTY_BRACKETS
};