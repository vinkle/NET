#ifndef SHOWRESULT_H
#define SHOWRESULT_H

#include <QDialog>
#include <QTreeView>
#include "treemodel.h"
#include <string>
#include <QFile>
#include <QDirModel>

using namespace std;

namespace Ui {
class showResult;
}

class showResult : public QDialog
{
    Q_OBJECT

public:
    explicit showResult(QWidget *parent = 0);
    ~showResult();
    void setString(const string &res);

private:
    Ui::showResult *ui;

    QDirModel *model;
};

#endif // SHOWRESULT_H
