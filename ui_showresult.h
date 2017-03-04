/********************************************************************************
** Form generated from reading UI file 'showresult.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWRESULT_H
#define UI_SHOWRESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_showResult
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeView;

    void setupUi(QDialog *showResult)
    {
        if (showResult->objectName().isEmpty())
            showResult->setObjectName(QStringLiteral("showResult"));
        showResult->resize(400, 300);
        showResult->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(showResult);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeView = new QTreeView(showResult);
        treeView->setObjectName(QStringLiteral("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 1);


        retranslateUi(showResult);

        QMetaObject::connectSlotsByName(showResult);
    } // setupUi

    void retranslateUi(QDialog *showResult)
    {
        showResult->setWindowTitle(QApplication::translate("showResult", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class showResult: public Ui_showResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWRESULT_H
