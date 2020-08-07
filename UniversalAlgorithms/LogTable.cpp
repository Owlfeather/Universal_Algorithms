#include "LogTable.h"
//#include <QColor>
//#include <QBrush>
//
//int LogTable::rowCount(const QModelIndex& parent) const
//{
//	return records.size();
//}
//
//int LogTable::columnCount(const QModelIndex& parent) const
//{
//	switch (alg_type)
//	{
//	case TypeOfAlg::LTOR:
//		return 2;
//	case TypeOfAlg::TTOD:
//		return 4;
//	case TypeOfAlg::LLK_TTOD:
//		return 3;
//	case TypeOfAlg::LRK_STACK:
//		return 6;
//	}
//}
//
//QVariant LogTable::data(const QModelIndex& index, int role) const
//{
//	if (role == Qt::DisplayRole) {
//		
//
//		QString unswer = QString::fromLocal8Bit(records[index.row()]->GetLine()[index.column()].c_str());
//		return QVariant(unswer);
//	}
//	///
//
//
//
//	if (role == Qt::BackgroundColorRole) {
//
//		switch (records[index.row()]->GetType())
//		{
//		case TypeOfAlg::LTOR:
//		{
//			if (records[index.row()]->GetRuleNum().fir_num == -2) {
//				return QVariant(QBrush(QColor(255, 217, 217)));
//			}
//			else if (records[index.row()]->GetRuleNum().fir_num == -3) {
//				return QVariant(QBrush(QColor(217, 255, 196)));
//			}
//			else if (records[index.row()]->GetRuleNum().fir_num == -4) {
//				return QVariant(QBrush(QColor(255, 215, 174)));
//			}
//			break;
//		}
//		case TypeOfAlg::TTOD:
//		{
//			switch (dynamic_cast<TtoD_Line*>(records[index.row()])->GetTypeOfLine())
//			{
//			case TypeOfTtoDLine::RULE_NOT_FIT:
//			{
//				return QVariant(QBrush(QColor(255, 217, 217)));
//				break;
//			}
//			case TypeOfTtoDLine::RULE_FIT:
//			{
//				return QVariant(QBrush(QColor(217, 255, 196)));
//				break;
//			}
//			case TypeOfTtoDLine::END_LINE:
//			{
//				return QVariant(QBrush(QColor(191, 255, 157)));
//				break;
//			}
//			case TypeOfTtoDLine::WRONG_SYMB:
//			{
//				return QVariant(QBrush(QColor(255, 215, 174)));
//				break;
//			}
//			}
//			break;
//		}
//		case TypeOfAlg::LLK_TTOD:
//		{
//			switch (records[index.row()]->GetRuleNum().fir_num)
//			{
//			case -3:
//			{
//				return QVariant(QBrush(QColor(217, 255, 196)));
//				break;
//			}
//			case -1:
//			case -2:
//			{
//				return QVariant(QBrush(QColor(255, 215, 174)));
//				break;
//			}
//			case -10:
//			{
//				return QVariant(QBrush(QColor(191, 255, 157)));
//				break;
//			}
//			default:
//			{
//				return QVariant(QBrush(QColor(255, 255, 255)));
//				break;
//			}
//			}
//		}
//		case TypeOfAlg::LRK_STACK:
//		{
//			string rel = records[index.row()]->GetLine()[2];
//			if (rel == "<") {
//				return QVariant(QBrush(QColor(255, 255, 255)));
//			}
//			else if (rel == ">") {
//				return QVariant(QBrush(QColor(217, 255, 196)));
//			}
//			else if (rel == "=") {
//				return QVariant(QBrush(QColor(217, 255, 196)));
//			}
//			else if (rel == "В") {
//				return QVariant(QBrush(QColor(191, 255, 157)));
//			}
//			else {
//				return QVariant(QBrush(QColor(255, 215, 174)));
//			}
//			
//		}
//		}
//
//	}
//
//	return QVariant();
//}
//
//QVariant LogTable::headerData(int section, Qt::Orientation orientation, int role) const
//{
//	if (role != Qt::DisplayRole) {
//		return QVariant();
//	}
//
//	if (orientation == Qt::Vertical) {
//		return section;
//	}
//	switch (alg_type)
//	{case TypeOfAlg::LTOR:
//		switch (section) {
//		case 0:
//			return QString::fromLocal8Bit("Строка");
//		case 1:
//			return QString::fromLocal8Bit("Правило");
//		}
//		break;
//	case TypeOfAlg::TTOD:
//		switch (section) {
//		case 0:
//			return QString::fromLocal8Bit("Распознано");
//		case 1:
//			return QString::fromLocal8Bit("Строка");
//		case 2:
//			return QString::fromLocal8Bit("Цель");
//		case 3:
//			return QString::fromLocal8Bit("Правило");
//		}
//		break;
//	case TypeOfAlg::LLK_TTOD:
//		switch (section) {
//		case 0:
//			return QString::fromLocal8Bit("Строка");
//		case 1:
//			return QString::fromLocal8Bit("Стек");
//		case 2:
//			return QString::fromLocal8Bit("Правило");
//		}
//		break;
//	case TypeOfAlg::LRK_STACK:
//		switch (section) {
//		case 0:
//			return QString::fromLocal8Bit("Стек");
//		case 1:
//			return QString::fromLocal8Bit("Рассм. символ");
//		case 2:
//			return QString::fromLocal8Bit("Отношение");
//		case 3:
//			return QString::fromLocal8Bit("Операция");
//		case 4:
//			return QString::fromLocal8Bit("Тройка");
//		case 5:
//			return QString::fromLocal8Bit("Результат");
//		}
//		break;
//	}
//
//	return QVariant();
//}
//
//void  LogTable::AppendLine(RecordLine* line)
//{
//	int row = records.size();
//
//	beginInsertRows(QModelIndex(), row, row);
//	records.push_back(line);
//	beginInsertRows(QModelIndex(), row, row);
//}