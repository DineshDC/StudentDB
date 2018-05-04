#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QTableWidget>
#include "db_tables.h"

class CustomTable : public QTableWidget
{
public:
    CustomTable(QWidget *parent = Q_NULLPTR);

    void updateTable(QStringList list, const QStringList& availableList = QStringList()<<"");
    QStringList getSelection();
};

#endif // CUSTOMTABLE_H
