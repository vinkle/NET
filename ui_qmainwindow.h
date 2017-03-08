/********************************************************************************
** Form generated from reading UI file 'qmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMAINWINDOW_H
#define UI_QMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qtopencvviewergl.h>

QT_BEGIN_NAMESPACE

class Ui_qMainWindow
{
public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionPause;
    QAction *actionFullscreen;
    QAction *actionStart_Activity;
    QAction *actionStop_2;
    QAction *actionFull_Screen;
    QAction *actionQuit;
    QAction *actionNext_Level;
    QAction *action_Vertical_Flip;
    QAction *action_Horizontal_Flip;
    QAction *actionSwitch_Camera;
    QAction *actionTemp;
    QAction *actionTemp2;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QtOpencvViewerGL *openCVviewer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCamera_Options;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qMainWindow)
    {
        if (qMainWindow->objectName().isEmpty())
            qMainWindow->setObjectName(QStringLiteral("qMainWindow"));
        qMainWindow->resize(920, 662);
        qMainWindow->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        actionStart = new QAction(qMainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon);
        actionStop = new QAction(qMainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionStop->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon1);
        actionPause = new QAction(qMainWindow);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        actionPause->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/images/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon2);
        actionFullscreen = new QAction(qMainWindow);
        actionFullscreen->setObjectName(QStringLiteral("actionFullscreen"));
        actionFullscreen->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/images/fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFullscreen->setIcon(icon3);
        actionStart_Activity = new QAction(qMainWindow);
        actionStart_Activity->setObjectName(QStringLiteral("actionStart_Activity"));
        actionStart_Activity->setEnabled(false);
        actionStop_2 = new QAction(qMainWindow);
        actionStop_2->setObjectName(QStringLiteral("actionStop_2"));
        actionStop_2->setEnabled(false);
        actionFull_Screen = new QAction(qMainWindow);
        actionFull_Screen->setObjectName(QStringLiteral("actionFull_Screen"));
        actionFull_Screen->setEnabled(false);
        actionQuit = new QAction(qMainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionQuit->setEnabled(true);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        actionQuit->setFont(font);
        actionNext_Level = new QAction(qMainWindow);
        actionNext_Level->setObjectName(QStringLiteral("actionNext_Level"));
        actionNext_Level->setEnabled(true);
        action_Vertical_Flip = new QAction(qMainWindow);
        action_Vertical_Flip->setObjectName(QStringLiteral("action_Vertical_Flip"));
        action_Vertical_Flip->setCheckable(true);
        action_Horizontal_Flip = new QAction(qMainWindow);
        action_Horizontal_Flip->setObjectName(QStringLiteral("action_Horizontal_Flip"));
        action_Horizontal_Flip->setCheckable(true);
        action_Horizontal_Flip->setChecked(false);
        actionSwitch_Camera = new QAction(qMainWindow);
        actionSwitch_Camera->setObjectName(QStringLiteral("actionSwitch_Camera"));
        actionSwitch_Camera->setCheckable(false);
        actionSwitch_Camera->setChecked(false);
        actionTemp = new QAction(qMainWindow);
        actionTemp->setObjectName(QStringLiteral("actionTemp"));
        actionTemp2 = new QAction(qMainWindow);
        actionTemp2->setObjectName(QStringLiteral("actionTemp2"));
        centralWidget = new QWidget(qMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        openCVviewer = new QtOpencvViewerGL(centralWidget);
        openCVviewer->setObjectName(QStringLiteral("openCVviewer"));
        openCVviewer->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(openCVviewer, 0, 0, 1, 1);

        qMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 920, 19));
        menuBar->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFile->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        menuCamera_Options = new QMenu(menuBar);
        menuCamera_Options->setObjectName(QStringLiteral("menuCamera_Options"));
        menuCamera_Options->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        qMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        qMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        qMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCamera_Options->menuAction());
        menuFile->addAction(actionStart);
        menuFile->addAction(actionStop);
        menuFile->addAction(actionPause);
        menuFile->addAction(actionFullscreen);
        menuCamera_Options->addAction(action_Vertical_Flip);
        menuCamera_Options->addAction(action_Horizontal_Flip);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionStart_Activity);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionStop_2);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionQuit);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSwitch_Camera);
        mainToolBar->addAction(actionTemp2);

        retranslateUi(qMainWindow);

        QMetaObject::connectSlotsByName(qMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *qMainWindow)
    {
        qMainWindow->setWindowTitle(QApplication::translate("qMainWindow", "qMainWindow", Q_NULLPTR));
        actionStart->setText(QApplication::translate("qMainWindow", "Start", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStart->setToolTip(QApplication::translate("qMainWindow", "Start", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionStart->setShortcut(QApplication::translate("qMainWindow", "Return", Q_NULLPTR));
        actionStop->setText(QApplication::translate("qMainWindow", "Stop", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStop->setToolTip(QApplication::translate("qMainWindow", "Stop", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionStop->setShortcut(QApplication::translate("qMainWindow", "Esc", Q_NULLPTR));
        actionPause->setText(QApplication::translate("qMainWindow", "Pause", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionPause->setToolTip(QApplication::translate("qMainWindow", "Pause", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionPause->setShortcut(QApplication::translate("qMainWindow", "P", Q_NULLPTR));
        actionFullscreen->setText(QApplication::translate("qMainWindow", "fullscreen", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionFullscreen->setToolTip(QApplication::translate("qMainWindow", "fullscreen", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFullscreen->setShortcut(QApplication::translate("qMainWindow", "Alt+Return", Q_NULLPTR));
        actionStart_Activity->setText(QApplication::translate("qMainWindow", "Start", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStart_Activity->setToolTip(QApplication::translate("qMainWindow", "Start the activity", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionStop_2->setText(QApplication::translate("qMainWindow", "Stop/ShowResults", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStop_2->setToolTip(QApplication::translate("qMainWindow", "Stop Activity", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFull_Screen->setText(QApplication::translate("qMainWindow", "Full Screen", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionFull_Screen->setToolTip(QApplication::translate("qMainWindow", "Full screen", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionQuit->setText(QApplication::translate("qMainWindow", "Exit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionQuit->setToolTip(QApplication::translate("qMainWindow", "exit the application", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionNext_Level->setText(QApplication::translate("qMainWindow", "Next Level", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNext_Level->setToolTip(QApplication::translate("qMainWindow", "Proceed to next Level", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Vertical_Flip->setText(QApplication::translate("qMainWindow", "&Vertical Flip", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Vertical_Flip->setToolTip(QApplication::translate("qMainWindow", "Vertical Mirror", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_Horizontal_Flip->setText(QApplication::translate("qMainWindow", "&Horizontal Flip", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_Horizontal_Flip->setToolTip(QApplication::translate("qMainWindow", "Horizontal Mirror", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSwitch_Camera->setText(QApplication::translate("qMainWindow", "Switch Camera", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSwitch_Camera->setToolTip(QApplication::translate("qMainWindow", "Switch to auxilarry camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSwitch_Camera->setShortcut(QApplication::translate("qMainWindow", "Ctrl+S", Q_NULLPTR));
        actionTemp->setText(QApplication::translate("qMainWindow", "temp", Q_NULLPTR));
        actionTemp2->setText(QApplication::translate("qMainWindow", "temp2", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        openCVviewer->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("qMainWindow", "File", Q_NULLPTR));
        menuCamera_Options->setTitle(QApplication::translate("qMainWindow", "Camera Options", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qMainWindow: public Ui_qMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMAINWINDOW_H
