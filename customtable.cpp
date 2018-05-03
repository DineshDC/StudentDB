#include "customtable.h"

CustomTable::CustomTable(QWidget *parent ):QTableWidget(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void CustomTable::updateTable(QStringList list)
{

    setRowCount(list.count());


    int row = 0;
    for(QString l : list)
    {
        QStringList data = l.split(";");
        setColumnCount(data.count());
        for(int col = 0 ; col < data.count() ; col++)
        {

            if(col == 0)
            {
                QTableWidgetItem *item = new QTableWidgetItem(data.at(col));
                item->setCheckState(Qt::Unchecked);
                setItem(row,col,item);
            }
            else
            {
                setItem(row,col,new QTableWidgetItem(data.at(col)));
            }

        }
        row++;

    }
}

QStringList CustomTable::getSelection()
{
    QStringList lst;
    int row = rowCount();
    for(int i = 0 ; i < row ; i++)
    {
        QTableWidgetItem *temp_item = item(i,0);
        if(temp_item->checkState() == Qt::Checked)
        {
            qDebug()<<temp_item->text();
            lst.push_back(temp_item->text());
        }
    }
    return lst;
}
