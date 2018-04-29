#ifndef DATATABLE_H
#define DATATABLE_H

#include <QObject>
#include <QTableView>
#include <QAbstractItemModel>

class DataTables : public QTableView
{
public:
    DataTables();

    void addRow(QStringList list,QAbstractItemModel *model);

};

#endif // COURSETABLE_H
