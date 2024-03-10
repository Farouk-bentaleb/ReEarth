#ifndef NUM_DELEGUATE_H
#define NUM_DELEGUATE_H

#include <QStyledItemDelegate>

class num_deleguate : public QStyledItemDelegate
{
Q_OBJECT
public:
explicit num_deleguate(QObject *parent = 0);
virtual QString displayText(const QVariant &value, const QLocale &locale) const;

signals:

public slots:

};

#endif // NUM_DELEGUATE_H
