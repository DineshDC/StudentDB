#include "datatable.h"

DataTables::DataTables()
{
    resizeColumnsToContents();
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setFixedHeight(400);
}

void DataTables::addRow(QStringList list, QAbstractItemModel *model)
{
    int  i = 0;
    for(auto a : list)
        model->setHeaderData(i++, Qt::Horizontal, a);


   setModel(model);
}
