#include "LogComments.h"
//#include <QColor>
//#include <QBrush>

//
//int LogComments::rowCount(const QModelIndex& parent) const
//{
//	return records.size();
//}
//
//QVariant LogComments::data(const QModelIndex& index, int role) const
//{
//	
//	if (role == Qt::DisplayRole) {
//		
//		QString unswer = QString::fromLocal8Bit(records[index.row()]->GetText().c_str());
//		
//		return QVariant(unswer);
//	}
//
//	if (role == Qt::BackgroundColorRole) {
//		QColor color;
//
//		switch (records[index.row()]->GetType())
//		{
//		case TypeOfComment::CORRECT_RULE:
//			color = QColor(217, 255, 196);
//			break;
//		case TypeOfComment::DEAD_END:
//			color = QColor(255, 155, 155);
//			break;
//		case TypeOfComment::INFO:
//			color = QColor(255, 243, 189);
//			break;
//		case TypeOfComment::PARSE_CORRECT:
//			color = QColor(217, 255, 196);
//			break;
//		case TypeOfComment::PARSE_INCORRECT:
//			color = QColor(255, 125, 125);
//			break;
//		case TypeOfComment::WRONG_RULE:
//			color = QColor(255, 255, 255);
//			break;
//		case TypeOfComment::HYPOTHESIS:
//			color = QColor(255, 255, 255);
//			break;
//		case TypeOfComment::ACTION:
//			color = QColor(255, 255, 255);
//			break;
//		}
//
//		return QVariant(QBrush(color));
//	}
//
//
//	return QVariant();
//}

