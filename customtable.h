#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QTableWidget>
#include "db_tables.h"

class CustomTable : public QTableWidget
{
public:
    CustomTable(QWidget *parent = Q_NULLPTR);

    void updateTable(QStringList list);
    QStringList getSelection();
};

#endif // CUSTOMTABLE_H
