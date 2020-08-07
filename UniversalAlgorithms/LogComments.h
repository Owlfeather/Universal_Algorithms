#pragma once
//#include <QAbstractListModel>
#include <iostream>

using namespace std;

#include "Alg_Elements.h"
//
//class Comment
//{
//public:
//	Comment() {}
//	Comment(string inp_text, TypeOfComment inp_type, RuleNum inp_r_num)
//		: text(inp_text), type(inp_type), r_num(inp_r_num) {}
//
//	const TypeOfComment GetType() { return type; }
//	const string& GetText() { return text; }
//	const RuleNum GetRuleNum() { return r_num; }
//
//private:
//	string text;
//	TypeOfComment type;
//	RuleNum r_num;
//};
//
//class LogComments :
//	public QAbstractListModel
//{
//	Q_OBJECT
//public:
//	LogComments() {}
//	~LogComments() 
//	{
//		for (int i = 0; i < records.size(); i++) {
//			delete records[i];
//		}
//	}
//	Comment* GetRow(unsigned i) { return records[i]; }
//	void AddRecordLine(const string& inp_s, TypeOfComment inp_t, RuleNum inp_r = {-7, -7})
//	{ 
//		int row = records.size();
//		Comment* new_comment = new Comment(inp_s, inp_t, inp_r);
//
//		beginInsertRows(QModelIndex(), row, row);
//		records.push_back(new_comment);
//		beginInsertRows(QModelIndex(), row, row);
//
//	}
//
//	void ClearRecords() { records.clear(); }
//
//	const int Size() { return records.size(); }
//	void ResetRow() { next_row = 1; }
//	void IncRow()
//	{
//		if (next_row < records.size()) {
//			next_row++;
//		}
//	}
//	const unsigned GetNextRow() { return next_row; }
//	bool NotEnd() { return (next_row != records.size()); }
//
//
//private:
//
//	vector<Comment*> records;
//	unsigned next_row;
//
//	int rowCount(const QModelIndex& parent) const;
//	QVariant data(const QModelIndex& index, int role) const;
//};
//

