#include "customtable.h"

CustomTable::CustomTable(QWidget *parent ):QTableWidget(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void CustomTable::updateTable(QStringList list, const QStringList &availableList)
{

    setRowCount(list.count());

    int row = 0;
    int lessCnt = 0;
    for(QString l : list)
    {
        QStringList data = l.split(";");
        setColumnCount(data.count());
        for(int col = 0 ; col < data.count() ; col++)
        {

            if(col == 0)
            {
                QString cellVal = data.at(col);
                if(!availableList.isEmpty())
                {
                   if( availableList.contains(cellVal))
                   {
                       lessCnt++;
                       row--;
                       break;
                   }
                }
                QTableWidgetItem *item = new QTableWidgetItem(cellVal);
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
    if(lessCnt == list.count() )//this check is when all courses are enrolled by student so that course table should not show rows
    {
        setRowCount(1);
        setSpan(0,0,1,6);//this will change when column count is increased
        setItem(0,0,new QTableWidgetItem("No Course Available to enrolled"));
    }
    else {
        setRowCount(abs(row - lessCnt));
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
