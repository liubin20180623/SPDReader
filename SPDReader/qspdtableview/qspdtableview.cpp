#include "qspdtableview.h"
#include <QCoreApplication>
#include <QHeaderView>
#include <qspdtableconfig.h>
#include <qspdtableitemdelegate.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <tuple>
#include <QFileInfo>

#define CELL_HEIGHT  12
#define CELL_WIDTH   20

QMap<QString,QColor> QSPDTableView::m_TxtColors = {
    {"NoData",QColor(107,107,107)},
    {"Normal",QColor(0,204,255)},
    {"Change",QColor(255,0,0)}
};

QSPDTableView::QSPDTableView(QWidget *parent)
   :QTableViewBasics(parent)
{
    initSPDTable();
    InitTable();
}

QSPDTableView::~QSPDTableView()
{

}

void QSPDTableView::InitTable(int rowHeight, bool Editable, bool isSorting, bool verticalHeadVisible, bool horizontalHeadVisible,bool isLastTensile, bool isShowGrid)
{
    /*设置默认行高*/
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setDefaultSectionSize(rowHeight);

    /*设置交替行颜色--允许交替行颜色*/
    this->setAlternatingRowColors(true);
    /*设置水平/垂直滚动模式--一次滚动一个项目*/
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    /*设置选择行为--每次选择只有一整行*/
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    /*设置拖放行为--不允许拖放*/
   // this->setDragDropMode(QAbstractItemView::NoDragDrop);
    /*设置选择模式--只能选择一个项目*/
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    /*设置Tab导航键--允许使用Tab键导航，shift+tab反向导航*/
    this->setTabKeyNavigation(true);
    /*设置是否自动换行--取消自动换行*/
    this->setWordWrap(false);
    /*设置文本省略模式--省略号不会出现在文本中*/
    this->setTextElideMode(Qt::ElideNone);
    /*设置左上角全选按钮--禁用*/
    this->setCornerButtonEnabled(false);
    /*设置是否支持表头排序--应该和表头是否可以单击保持一致*/
    this->setSortingEnabled(isSorting);
    /*设置是否显示网格线*/
    this->setShowGrid(isShowGrid);
    /*设置垂直表头是否可见*/
    this->verticalHeader()->setVisible(verticalHeadVisible);
    /*设置水平表头是否可见*/
    this->horizontalHeader()->setVisible(horizontalHeadVisible);
    /*设置选中一行表头是否加粗--不加粗*/
    this->horizontalHeader()->setHighlightSections(false);
    /*设置最后一行是否拉伸填充*/
    this->horizontalHeader()->setStretchLastSection(isLastTensile);
    /*设置行标题最小宽度尺寸*/
    this->horizontalHeader()->setMinimumSectionSize(0);
    /*设置行标题最小高度*/
    this->horizontalHeader()->setFixedHeight(rowHeight);
    /*设置表头是否可以单击--不可单击*/
    this->horizontalHeader()->setSectionsClickable(isSorting);
    /* 设置选中行的背景色,及文字颜色 */
    setStyleSheet("selection-background-color: #84AF9B;selection-color:#FFFFFF;");
    /* 开启捕获鼠标功能 */
    this->setMouseTracking(true);
}

void QSPDTableView::setFileID(int id)
{
    m_id = id;
    s_filePath =  QCoreApplication::applicationDirPath() + QString("/spd%1.txt").arg(id);
}

void QSPDTableView::removeFile()
{
   QFile::remove(s_filePath);
}

void QSPDTableView::initSPDTable()
{
   int row = 0;
   QStringList h_headers = QSPDTableConfig::getHorizontalHeader();
   QStringList v_headers = QSPDTableConfig::getVerticalHeader();
   setHorizontalHeaderLabels(h_headers);

   insertRow(0);
   setRowHeight(row,CELL_HEIGHT);

   for(int column = 0;  column< h_headers.size();column++)
   {
      setColumnWidth(column,CELL_WIDTH);
      setData(row,column,h_headers[column]);
   }

   for(int row = 1; row <= v_headers.size(); row++)
   {
      insertRow(row);
      setRowHeight(row,CELL_HEIGHT);
      setData(row,0,v_headers[row-1]);
   }

   delegate = new QSPDTableItemDelegate(this);
   setItemDelegate(delegate);
}

void QSPDTableView::clearSPDTable()
{
    QStringList h_headers = QSPDTableConfig::getHorizontalHeader();
    QStringList v_headers = QSPDTableConfig::getVerticalHeader();
    for(int row = 1;row <= v_headers.size(); row++)
    {
        for(int column = 1;column<= h_headers.size();column++ )
        {
           setData(row,column,"");
        }
    }
}

void QSPDTableView::updateSPDTable(MSpdData &mspdData)
{
   MSpdData preSpdData;
   readSPDTable(preSpdData);

   QStringList v_headers = QSPDTableConfig::getVerticalHeader();
   for(int row = 1; row <= v_headers.size(); row++)
   {
      QString key = v_headers[row-1];
      if(mspdData.contains(key))
      {
         QVector<std::tuple<QString,bool>> rowData  = mspdData[key];
         for(int column = 0; column< 16;column++)
         {
            QString cellTxt = std::get<0>(rowData[column]);
            setData(row,column+1,cellTxt);

            if(preSpdData.isEmpty())
            {
               setTextColor(row,column+1,(cellTxt == "00") ? m_TxtColors["NoData"] :m_TxtColors["Normal"]);
            }
            else
            {
               if(preSpdData.contains(key))
               {
                   QVector<std::tuple<QString,bool>> pre_rowData = preSpdData[key];
                   QString pre_cellTxt  = std::get<0>(pre_rowData[column]);
                   bool    isRevised    = std::get<1>(pre_rowData[column]);
                   if(isRevised)
                   {
                        setTextColor(row,column+1,m_TxtColors["Change"]);
                        std::get<1>(rowData[column]) = true;
                   }
                   else
                   {
                       if(cellTxt == pre_cellTxt)
                       {
                          setTextColor(row,column+1,(cellTxt == "00") ? m_TxtColors["NoData"] :m_TxtColors["Normal"]);
                       }
                       else
                       {
                          setTextColor(row,column+1,m_TxtColors["Change"]);
                          std::get<1>(rowData[column]) = true;
                       }
                   }
               }
               else
               {
                    setTextColor(row,column+1,m_TxtColors["Change"]);
                    std::get<1>(rowData[column]) = true;
               }
            }
         }
         mspdData[key] = rowData;
      }
   }

   saveSPDTable(mspdData);
}

void QSPDTableView::saveSPDTable(MSpdData &mspdData)
{
   QFile myFile(s_filePath);
   if(!myFile.open(QIODevice::WriteOnly)){
       return;
   }

   QTextStream textStream(&myFile);

   QStringList s_spdTable;
   QStringList v_headers = QSPDTableConfig::getVerticalHeader();
   for(int row = 1; row <= v_headers.size(); row++)
   {
      QString key = v_headers[row-1];
      if(mspdData.contains(key))
      {
         QStringList s_spdTable_row;
         s_spdTable_row <<key;

         QVector<std::tuple<QString,bool>> data = mspdData[key];
         for(int column = 0; column< 16;column++)
         {
            QString text     = std::get<0>(data[column]);
            int     iRevised = std::get<1>(data[column]) ? 1 :0;
            s_spdTable_row << QString("%1:%2").arg(text).arg(iRevised);
         }
         textStream<<s_spdTable_row.join(" ") + "\r\n";
      }
   }
   QString desPath = QCoreApplication::applicationDirPath() +
           QString("/log/spd%1_%2.txt").arg(m_id).arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));

   myFile.copy(desPath);
   myFile.close();
}

void QSPDTableView::readSPDTable(MSpdData &mspdData)
{
    QFile myFile(s_filePath);
    if(!myFile.open(QIODevice::ReadOnly)){
        return;
    }
    QTextStream textStream(&myFile);

    while(!textStream.atEnd())
    {
        QVector<std::tuple<QString,bool>> rowData;

        QString strLineData = textStream.readLine();
        QStringList ss = strLineData.split(" ");
        QString key = ss[0];

        for(int i =1; i < 17; i++)
        {
          QStringList cell = ss[i].split(":");
          rowData.push_back(std::make_tuple(cell[0],cell[1].toInt()));
        }
        mspdData[key] = rowData;
    }
    myFile.close();
}

