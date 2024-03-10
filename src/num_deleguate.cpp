#include "num_deleguate.h"

num_deleguate::num_deleguate(QObject *parent) :
QStyledItemDelegate(parent)
{
}

QString num_deleguate::displayText(const QVariant &value, const QLocale &locale) const
{
QString formattedNum = locale.toString(value.toDouble(), 'f', 0); //double to string
return formattedNum;
}
