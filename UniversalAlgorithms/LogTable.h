#pragma once
//#include <QAbstractTableModel>
#include <iostream>

using namespace std;

#include "Alg_Elements.h"
//
//class LogTable :
//	public QAbstractTableModel
//{
//	Q_OBJECT
//public:
//	LogTable() {}
//	~LogTable()
//	{
//		for (int i = 0; i < records.size(); i++) {
//			delete records[i];
//		}
//	}
//	void SetType(TypeOfAlg type) { alg_type = type; };
//	void AppendLine(RecordLine * line);
//
//	void ClearRecords() { records.clear(); }
//
//	void ResetRow() { next_row = 0; }
//	void IncRow() 
//	{ 
//		if (next_row < records.size()) {
//			next_row++;
//		}
//	}
//	const unsigned GetNextRow() { return next_row; }
//
//	RecordLine* GetRow(unsigned i) { return records[i]; }
//
//
//private:
//
//	TypeOfAlg alg_type;
//	unsigned next_row;
//
//	///
//	vector<RecordLine*> records;
//	void AddRecordLine(RecordLine* inp_rec) { records.push_back(inp_rec); }
//	int Size() { return records.size(); }
//	///
//
//	int rowCount(const QModelIndex& parent) const;
//	int columnCount(const QModelIndex& parent) const;
//	QVariant data(const QModelIndex& index, int role) const;
//	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//};
//
