#include "showresult.h"
#include "ui_showresult.h"

showResult::showResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showResult)
{
    ui->setupUi(this);
}

showResult::~showResult()
{
    delete ui;
}

void showResult::setString(const string &res)
{
//    QFile file("default.txt");
//    file.open(QIODevice::ReadOnly);
//    TreeModel model(file.readAll());
//    file.close();
//    ui->treeView->setModel(&model);
//    ui->treeView->show();
    model = new QDirModel(this);
    // Enable modifying file system
    model->setReadOnly(false);
    // Tie TreeView with DirModel
    // QTreeView::setModel(QAbstractItemModel * model)
    // Reimplemented from QAbstractItemView::setModel().
    ui->treeView->setModel(model);
}
