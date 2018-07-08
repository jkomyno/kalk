#include <QHeaderView>
#include <QAbstractTableModel>
#include "matrixtableview.h"

MatrixTableView::MatrixTableView(QAbstractTableModel* model, bool hideHeaders, QWidget* parent) :
    QTableView(parent)
{
    this->setModel(model);
    if (hideHeaders) {
        this->verticalHeader()->hide();
        this->horizontalHeader()->hide();
    }
    setup();
}

void MatrixTableView::setup()
{
    this->verticalHeader()->setDefaultSectionSize(40);
    this->horizontalHeader()->setDefaultSectionSize(40);
    this->setMinimumHeight(150);
    this->setSelectionMode(QAbstractItemView::NoSelection);
    // http://www.qtcentre.org/threads/35341-How-to-style-QTableView-headers-using-stylesheets
    this->setStyleSheet("QHeaderView::section {"
                            "background-color: #C4CFE7;"
                            "color: #222;"
                         "}");
}
