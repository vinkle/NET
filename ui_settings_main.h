/********************************************************************************
** Form generated from reading UI file 'settings_main.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_MAIN_H
#define UI_SETTINGS_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <auxcamgraphicsview.h>

QT_BEGIN_NAMESPACE

class Ui_settings_main
{
public:
    QLabel *label_status;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QListWidget *listWidgetAuxOnline;
    QLabel *label_7;
    QListWidget *listWidgetEndoOnline;
    QLabel *label_8;
    QLabel *label_11;
    QGraphicsView *view_endo;
    auxcamgraphicsview *view_aux;
    QPushButton *pbOnline;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioBoundingBox;
    QPushButton *btnBoundingBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioRingSegment;
    QPushButton *btnRingSegment;
    QSlider *sliderRingSegment;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioPegSegment;
    QPushButton *btnPegSegment;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioToolTipSegment;
    QPushButton *btnToolSegment;
    QSlider *sliderToolSegment;
    QComboBox *comboSelectLevel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_3;
    QLabel *label;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_14;
    QCheckBox *checkCalib;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkPauseVideo;
    QCheckBox *checkOverlay;
    QWidget *page_2;
    QCheckBox *checkBoxRecordEndo;
    QCheckBox *checkBoxRecordAux;
    QWidget *tab;
    QStackedWidget *stackedWidget_2;
    QWidget *page_3;
    QLabel *label_10;
    QListWidget *listWidgetAuxOffline;
    QListWidget *listWidgetEndoOffline;
    QLabel *label_9;
    QLabel *label_12;
    QGraphicsView *view_endo_2;
    QGraphicsView *view_aux_2;
    QPushButton *pbOffline;
    QWidget *page_4;
    QWidget *tab_2;
    QListWidget *listWidgetPractice;
    QPushButton *pbPractice;
    QLabel *label_5;
    QLabel *label_13;
    QGraphicsView *view_endo_3;
    QWidget *tab_3;
    QLabel *label_15;
    QComboBox *cmbName;
    QTableView *tableView;
    QPushButton *pbQuit;
    QPushButton *pbSettings;
    QPushButton *pbRefresh;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *boxName;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QComboBox *boxType;
    QLabel *label_6;
    QLineEdit *txtDetails;
    QLabel *label_3;
    QComboBox *selectLevel;

    void setupUi(QDialog *settings_main)
    {
        if (settings_main->objectName().isEmpty())
            settings_main->setObjectName(QStringLiteral("settings_main"));
        settings_main->resize(984, 644);
        settings_main->setToolTipDuration(1);
        settings_main->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_status = new QLabel(settings_main);
        label_status->setObjectName(QStringLiteral("label_status"));
        label_status->setGeometry(QRect(0, 601, 791, 20));
        QFont font;
        font.setFamily(QStringLiteral("Purisa"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_status->setFont(font);
        label_status->setToolTipDuration(1);
        label_status->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        tabWidget = new QTabWidget(settings_main);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 80, 971, 501));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        QBrush brush2(QColor(224, 214, 219, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush2);
        QBrush brush3(QColor(97, 87, 91, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush3);
        QBrush brush4(QColor(129, 116, 122, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush5(QColor(255, 255, 220, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush5);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush6(QColor(194, 174, 183, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        tabWidget->setPalette(palette);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        stackedWidget = new QStackedWidget(tab_5);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 40, 961, 431));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        stackedWidget->setFont(font1);
        stackedWidget->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(190, 116, 255);"));
        stackedWidget->setFrameShape(QFrame::Box);
        stackedWidget->setFrameShadow(QFrame::Raised);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        listWidgetAuxOnline = new QListWidget(page);
        listWidgetAuxOnline->setObjectName(QStringLiteral("listWidgetAuxOnline"));
        listWidgetAuxOnline->setGeometry(QRect(440, 30, 191, 51));
        listWidgetAuxOnline->setFont(font1);
        listWidgetAuxOnline->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        label_7 = new QLabel(page);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(470, 0, 141, 27));
        label_7->setFont(font1);
        label_7->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        listWidgetEndoOnline = new QListWidget(page);
        listWidgetEndoOnline->setObjectName(QStringLiteral("listWidgetEndoOnline"));
        listWidgetEndoOnline->setGeometry(QRect(90, 30, 191, 51));
        listWidgetEndoOnline->setFont(font1);
        listWidgetEndoOnline->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        label_8 = new QLabel(page);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(120, -4, 141, 21));
        label_8->setFont(font1);
        label_8->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        label_11 = new QLabel(page);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(260, 350, 341, 27));
        label_11->setFont(font1);
        label_11->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        view_endo = new QGraphicsView(page);
        view_endo->setObjectName(QStringLiteral("view_endo"));
        view_endo->setGeometry(QRect(10, 90, 320, 256));
        view_aux = new auxcamgraphicsview(page);
        view_aux->setObjectName(QStringLiteral("view_aux"));
        view_aux->setGeometry(QRect(360, 90, 320, 256));
        view_aux->setMouseTracking(true);
        pbOnline = new QPushButton(page);
        pbOnline->setObjectName(QStringLiteral("pbOnline"));
        pbOnline->setEnabled(false);
        pbOnline->setGeometry(QRect(470, 380, 171, 41));
        pbOnline->setFont(font1);
        pbOnline->setStyleSheet(QLatin1String("color: rgb(0, 0, 0);\n"
"background-color: rgb(49, 207, 255);"));
        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(690, 120, 241, 301));
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QLatin1String("color: rgb(30, 11, 11);\n"
"background-color: rgb(251, 250, 250);"));
        groupBox_2->setFlat(false);
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 10, 221, 281));
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioBoundingBox = new QRadioButton(layoutWidget);
        radioBoundingBox->setObjectName(QStringLiteral("radioBoundingBox"));
        radioBoundingBox->setEnabled(false);
        radioBoundingBox->setFont(font1);
        radioBoundingBox->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        radioBoundingBox->setChecked(true);

        horizontalLayout_2->addWidget(radioBoundingBox);

        btnBoundingBox = new QPushButton(layoutWidget);
        btnBoundingBox->setObjectName(QStringLiteral("btnBoundingBox"));
        btnBoundingBox->setEnabled(false);

        horizontalLayout_2->addWidget(btnBoundingBox);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        radioRingSegment = new QRadioButton(layoutWidget);
        radioRingSegment->setObjectName(QStringLiteral("radioRingSegment"));
        radioRingSegment->setEnabled(false);
        radioRingSegment->setFont(font1);
        radioRingSegment->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        radioRingSegment->setChecked(false);

        horizontalLayout_4->addWidget(radioRingSegment);

        btnRingSegment = new QPushButton(layoutWidget);
        btnRingSegment->setObjectName(QStringLiteral("btnRingSegment"));
        btnRingSegment->setEnabled(false);

        horizontalLayout_4->addWidget(btnRingSegment);


        verticalLayout->addLayout(horizontalLayout_4);

        sliderRingSegment = new QSlider(layoutWidget);
        sliderRingSegment->setObjectName(QStringLiteral("sliderRingSegment"));
        sliderRingSegment->setEnabled(false);
        sliderRingSegment->setStyleSheet(QStringLiteral(""));
        sliderRingSegment->setMaximum(30);
        sliderRingSegment->setValue(0);
        sliderRingSegment->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(sliderRingSegment);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        radioPegSegment = new QRadioButton(layoutWidget);
        radioPegSegment->setObjectName(QStringLiteral("radioPegSegment"));
        radioPegSegment->setEnabled(false);
        radioPegSegment->setFont(font1);
        radioPegSegment->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        verticalLayout_3->addWidget(radioPegSegment);

        btnPegSegment = new QPushButton(layoutWidget);
        btnPegSegment->setObjectName(QStringLiteral("btnPegSegment"));
        btnPegSegment->setEnabled(false);

        verticalLayout_3->addWidget(btnPegSegment);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioToolTipSegment = new QRadioButton(layoutWidget);
        radioToolTipSegment->setObjectName(QStringLiteral("radioToolTipSegment"));
        radioToolTipSegment->setEnabled(false);
        radioToolTipSegment->setFont(font1);
        radioToolTipSegment->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_3->addWidget(radioToolTipSegment);

        btnToolSegment = new QPushButton(layoutWidget);
        btnToolSegment->setObjectName(QStringLiteral("btnToolSegment"));
        btnToolSegment->setEnabled(false);

        horizontalLayout_3->addWidget(btnToolSegment);


        verticalLayout_2->addLayout(horizontalLayout_3);

        sliderToolSegment = new QSlider(layoutWidget);
        sliderToolSegment->setObjectName(QStringLiteral("sliderToolSegment"));
        sliderToolSegment->setEnabled(false);
        sliderToolSegment->setStyleSheet(QStringLiteral(""));
        sliderToolSegment->setMinimum(50);
        sliderToolSegment->setMaximum(75);
        sliderToolSegment->setValue(50);
        sliderToolSegment->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(sliderToolSegment);


        verticalLayout_4->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 0, 1, 1);

        comboSelectLevel = new QComboBox(layoutWidget);
        comboSelectLevel->setObjectName(QStringLiteral("comboSelectLevel"));
        comboSelectLevel->setEnabled(false);
        comboSelectLevel->setFont(font1);
        comboSelectLevel->setStyleSheet(QLatin1String("color: rgb(30, 11, 11);\n"
"background-color: rgb(251, 250, 250);"));

        gridLayout->addWidget(comboSelectLevel, 0, 0, 1, 1);


        verticalLayout_5->addLayout(gridLayout);

        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(180, 390, 294, 19));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        checkBox_3 = new QCheckBox(layoutWidget1);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        horizontalLayout_7->addWidget(checkBox_3);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        horizontalLayout_7->addWidget(label);

        layoutWidget2 = new QWidget(page);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(720, 70, 174, 19));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font1);

        horizontalLayout_5->addWidget(label_14);

        checkCalib = new QCheckBox(layoutWidget2);
        checkCalib->setObjectName(QStringLiteral("checkCalib"));
        checkCalib->setFont(font1);
        checkCalib->setStyleSheet(QStringLiteral("color: rgb(53, 255, 59);"));
        checkCalib->setChecked(false);

        horizontalLayout_5->addWidget(checkCalib);

        layoutWidget3 = new QWidget(page);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(701, 90, 241, 20));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        checkPauseVideo = new QCheckBox(layoutWidget3);
        checkPauseVideo->setObjectName(QStringLiteral("checkPauseVideo"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        checkPauseVideo->setFont(font2);

        horizontalLayout_8->addWidget(checkPauseVideo);

        checkOverlay = new QCheckBox(layoutWidget3);
        checkOverlay->setObjectName(QStringLiteral("checkOverlay"));

        horizontalLayout_8->addWidget(checkOverlay);

        stackedWidget->addWidget(page);
        layoutWidget->raise();
        groupBox_2->raise();
        layoutWidget->raise();
        listWidgetAuxOnline->raise();
        label_7->raise();
        listWidgetEndoOnline->raise();
        label_8->raise();
        label_11->raise();
        view_endo->raise();
        view_aux->raise();
        layoutWidget->raise();
        pbOnline->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);
        checkBoxRecordEndo = new QCheckBox(tab_5);
        checkBoxRecordEndo->setObjectName(QStringLiteral("checkBoxRecordEndo"));
        checkBoxRecordEndo->setGeometry(QRect(90, 0, 221, 22));
        checkBoxRecordEndo->setFont(font1);
        checkBoxRecordEndo->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        checkBoxRecordEndo->setChecked(true);
        checkBoxRecordAux = new QCheckBox(tab_5);
        checkBoxRecordAux->setObjectName(QStringLiteral("checkBoxRecordAux"));
        checkBoxRecordAux->setGeometry(QRect(450, 0, 204, 22));
        checkBoxRecordAux->setFont(font1);
        checkBoxRecordAux->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        checkBoxRecordAux->setChecked(true);
        tabWidget->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        stackedWidget_2 = new QStackedWidget(tab);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(10, 20, 871, 461));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        label_10 = new QLabel(page_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(160, 0, 141, 27));
        label_10->setFont(font1);
        label_10->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        listWidgetAuxOffline = new QListWidget(page_3);
        listWidgetAuxOffline->setObjectName(QStringLiteral("listWidgetAuxOffline"));
        listWidgetAuxOffline->setGeometry(QRect(500, 30, 211, 51));
        listWidgetAuxOffline->setFont(font1);
        listWidgetAuxOffline->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        listWidgetEndoOffline = new QListWidget(page_3);
        listWidgetEndoOffline->setObjectName(QStringLiteral("listWidgetEndoOffline"));
        listWidgetEndoOffline->setGeometry(QRect(130, 30, 211, 51));
        listWidgetEndoOffline->setFont(font1);
        listWidgetEndoOffline->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        label_9 = new QLabel(page_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(530, 0, 141, 27));
        label_9->setFont(font1);
        label_9->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        label_12 = new QLabel(page_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(250, 380, 341, 27));
        label_12->setFont(font1);
        label_12->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        view_endo_2 = new QGraphicsView(page_3);
        view_endo_2->setObjectName(QStringLiteral("view_endo_2"));
        view_endo_2->setGeometry(QRect(50, 90, 350, 280));
        view_aux_2 = new QGraphicsView(page_3);
        view_aux_2->setObjectName(QStringLiteral("view_aux_2"));
        view_aux_2->setGeometry(QRect(420, 90, 350, 280));
        pbOffline = new QPushButton(page_3);
        pbOffline->setObjectName(QStringLiteral("pbOffline"));
        pbOffline->setEnabled(false);
        pbOffline->setGeometry(QRect(340, 410, 131, 41));
        pbOffline->setFont(font1);
        pbOffline->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        stackedWidget_2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        stackedWidget_2->addWidget(page_4);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        listWidgetPractice = new QListWidget(tab_2);
        listWidgetPractice->setObjectName(QStringLiteral("listWidgetPractice"));
        listWidgetPractice->setGeometry(QRect(330, 30, 191, 51));
        listWidgetPractice->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        pbPractice = new QPushButton(tab_2);
        pbPractice->setObjectName(QStringLiteral("pbPractice"));
        pbPractice->setEnabled(false);
        pbPractice->setGeometry(QRect(360, 440, 131, 41));
        pbPractice->setStyleSheet(QLatin1String("background-color: rgb(251, 250, 250);\n"
"color: rgb(16, 0, 0);"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(350, 0, 141, 27));
        label_5->setFont(font1);
        label_5->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(260, 380, 341, 27));
        label_13->setFont(font1);
        label_13->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        view_endo_3 = new QGraphicsView(tab_2);
        view_endo_3->setObjectName(QStringLiteral("view_endo_3"));
        view_endo_3->setGeometry(QRect(250, 90, 350, 280));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(280, 20, 41, 20));
        cmbName = new QComboBox(tab_3);
        cmbName->setObjectName(QStringLiteral("cmbName"));
        cmbName->setGeometry(QRect(330, 20, 211, 23));
        tableView = new QTableView(tab_3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 60, 901, 391));
        tabWidget->addTab(tab_3, QString());
        pbQuit = new QPushButton(settings_main);
        pbQuit->setObjectName(QStringLiteral("pbQuit"));
        pbQuit->setGeometry(QRect(810, 590, 121, 51));
        pbQuit->setFont(font1);
        pbQuit->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        pbSettings = new QPushButton(settings_main);
        pbSettings->setObjectName(QStringLiteral("pbSettings"));
        pbSettings->setGeometry(QRect(0, 4, 99, 61));
        pbSettings->setStyleSheet(QLatin1String("color: rgb(255, 236, 236);\n"
"background-color: rgb(95, 151, 95);"));
        pbRefresh = new QPushButton(settings_main);
        pbRefresh->setObjectName(QStringLiteral("pbRefresh"));
        pbRefresh->setGeometry(QRect(830, 70, 99, 31));
        pbRefresh->setStyleSheet(QLatin1String("color: rgb(3, 3, 3);\n"
"background-color: rgb(225, 255, 196);"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Refresh.png"), QSize(), QIcon::Normal, QIcon::On);
        pbRefresh->setIcon(icon);
        layoutWidget4 = new QWidget(settings_main);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(380, 0, 251, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(label_2);

        boxName = new QComboBox(layoutWidget4);
        boxName->setObjectName(QStringLiteral("boxName"));
        boxName->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(boxName);

        layoutWidget5 = new QWidget(settings_main);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(100, 30, 831, 27));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget5);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);
        label_4->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_6->addWidget(label_4);

        boxType = new QComboBox(layoutWidget5);
        boxType->setObjectName(QStringLiteral("boxType"));
        boxType->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_6->addWidget(boxType);

        label_6 = new QLabel(layoutWidget5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);
        label_6->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_6->addWidget(label_6);

        txtDetails = new QLineEdit(layoutWidget5);
        txtDetails->setObjectName(QStringLiteral("txtDetails"));

        horizontalLayout_6->addWidget(txtDetails);

        label_3 = new QLabel(layoutWidget5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout_6->addWidget(label_3);

        selectLevel = new QComboBox(layoutWidget5);
        selectLevel->setObjectName(QStringLiteral("selectLevel"));
        selectLevel->setStyleSheet(QLatin1String("color: rgb(30, 11, 11);\n"
"background-color: rgb(251, 250, 250);"));

        horizontalLayout_6->addWidget(selectLevel);

        layoutWidget->raise();
        layoutWidget->raise();
        tabWidget->raise();
        label_status->raise();
        pbQuit->raise();
        pbSettings->raise();
        pbRefresh->raise();
        QWidget::setTabOrder(tabWidget, selectLevel);
        QWidget::setTabOrder(selectLevel, pbOffline);

        retranslateUi(settings_main);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);
        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(settings_main);
    } // setupUi

    void retranslateUi(QDialog *settings_main)
    {
        settings_main->setWindowTitle(QApplication::translate("settings_main", "Dialog", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_status->setToolTip(QApplication::translate("settings_main", "Status", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_status->setText(QString());
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QApplication::translate("settings_main", "Choose tab according to usage", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        listWidgetAuxOnline->setToolTip(QApplication::translate("settings_main", "Auxiliary cameras will be diplayed here", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("settings_main", "Auxiliary Cameras", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        listWidgetEndoOnline->setToolTip(QApplication::translate("settings_main", "Endoscpic cameras will be diplayed here", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("settings_main", "Endoscopy Cameras", Q_NULLPTR));
        label_11->setText(QApplication::translate("settings_main", "Adjust camera parameters to get the proper view", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbOnline->setToolTip(QApplication::translate("settings_main", "Run the application", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbOnline->setText(QApplication::translate("settings_main", "Run", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        radioBoundingBox->setText(QApplication::translate("settings_main", "Bounding Box", Q_NULLPTR));
        btnBoundingBox->setText(QApplication::translate("settings_main", "Confirm", Q_NULLPTR));
        radioRingSegment->setText(QApplication::translate("settings_main", "Ring Segment", Q_NULLPTR));
        btnRingSegment->setText(QApplication::translate("settings_main", "Confirm", Q_NULLPTR));
        radioPegSegment->setText(QApplication::translate("settings_main", "Peg Segment", Q_NULLPTR));
        btnPegSegment->setText(QApplication::translate("settings_main", "Place Ring at 1 and click", Q_NULLPTR));
        radioToolTipSegment->setText(QApplication::translate("settings_main", "Tool Segment", Q_NULLPTR));
        btnToolSegment->setText(QApplication::translate("settings_main", "Confirm", Q_NULLPTR));
        comboSelectLevel->clear();
        comboSelectLevel->insertItems(0, QStringList()
         << QApplication::translate("settings_main", "Straight Plate", Q_NULLPTR)
         << QApplication::translate("settings_main", "Left Tilt +15", Q_NULLPTR)
         << QApplication::translate("settings_main", "Right Tilt -15", Q_NULLPTR)
         << QApplication::translate("settings_main", "Left Tilt +20", Q_NULLPTR)
         << QApplication::translate("settings_main", "Right Tilt -20", Q_NULLPTR)
         << QApplication::translate("settings_main", "Left Tilt +30", Q_NULLPTR)
         << QApplication::translate("settings_main", "Right Tilt -30", Q_NULLPTR)
        );
        checkBox_3->setText(QString());
        label->setStyleSheet(QApplication::translate("settings_main", "color: rgb(0, 0, 0);", Q_NULLPTR));
        label->setText(QApplication::translate("settings_main", "I accept to give consent for the study", Q_NULLPTR));
        label_14->setText(QApplication::translate("settings_main", "Aux Cam Calibration", Q_NULLPTR));
        checkCalib->setText(QString());
        checkPauseVideo->setText(QApplication::translate("settings_main", "Pause Video", Q_NULLPTR));
        checkOverlay->setText(QApplication::translate("settings_main", "Show Overlay", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBoxRecordEndo->setToolTip(QApplication::translate("settings_main", "Record endoscopy video during evaluation process", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBoxRecordEndo->setText(QApplication::translate("settings_main", "Record endoscopic camera ?", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBoxRecordAux->setToolTip(QApplication::translate("settings_main", "Record auxiliary video during evaluation process", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBoxRecordAux->setText(QApplication::translate("settings_main", "Record Auxiliary camera ?", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("settings_main", "Online evaluation", Q_NULLPTR));
        label_10->setText(QApplication::translate("settings_main", "Endoscopy Cameras", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        listWidgetAuxOffline->setToolTip(QApplication::translate("settings_main", "Auxiliary cameras will be diplayed here", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        listWidgetEndoOffline->setToolTip(QApplication::translate("settings_main", "Endoscpic cameras will be diplayed here", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("settings_main", "Auxiliary Cameras", Q_NULLPTR));
        label_12->setText(QApplication::translate("settings_main", "Adjust camera parameters to get the proper view", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbOffline->setToolTip(QApplication::translate("settings_main", "Run the application", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbOffline->setText(QApplication::translate("settings_main", "Record", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("settings_main", "Record", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        listWidgetPractice->setToolTip(QApplication::translate("settings_main", "Endoscpic cameras will be diplayed here", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pbPractice->setToolTip(QApplication::translate("settings_main", "Run the application", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbPractice->setText(QApplication::translate("settings_main", "Run", Q_NULLPTR));
        label_5->setText(QApplication::translate("settings_main", "Endoscopy Cameras", Q_NULLPTR));
        label_13->setText(QApplication::translate("settings_main", "Adjust camera parameters to get the proper view", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("settings_main", "Practice", Q_NULLPTR));
        label_15->setText(QApplication::translate("settings_main", "Name", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("settings_main", "Search Database", Q_NULLPTR));
        pbQuit->setText(QApplication::translate("settings_main", "Quit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbSettings->setToolTip(QApplication::translate("settings_main", "call the setting GUI", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbSettings->setText(QApplication::translate("settings_main", "Settings", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbRefresh->setToolTip(QApplication::translate("settings_main", "Refresh to connect to camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbRefresh->setText(QApplication::translate("settings_main", "Refresh", Q_NULLPTR));
        label_2->setText(QApplication::translate("settings_main", "Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("settings_main", "Type", Q_NULLPTR));
        boxType->clear();
        boxType->insertItems(0, QStringList()
         << QApplication::translate("settings_main", "Regular", Q_NULLPTR)
         << QApplication::translate("settings_main", "Study", Q_NULLPTR)
         << QApplication::translate("settings_main", "Conference", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("settings_main", "Details", Q_NULLPTR));
        label_3->setText(QApplication::translate("settings_main", "Level", Q_NULLPTR));
        selectLevel->clear();
        selectLevel->insertItems(0, QStringList()
         << QApplication::translate("settings_main", "Level 1   - Straight          -> 0 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 2   - Left Tilt (+15)  -> 0 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 3   - Right Tilt (-15) ->0 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 4   - Left Tilt (+20)  ->0 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 5   - Right Tilt (-20) ->0 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 6   - Left Tilt(+30)   ->0 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 7   - Right Tilt(-30)   ->0 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 8   - Straight            ->30 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 9   - Left Tilt (+15)   ->30 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 10 - Right Tilt (-15)   ->30 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 11 - Left Tilt (+20)    ->30 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 12 - Right Tilt (-20)    ->30 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 13 - Left Tilt(+30)       ->30 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 14 - Right Tilt(-30)      ->30 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 15 - Straight               ->45 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 16 - Left Tilt (+15)     ->45 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 17 - Right Tilt (-15)    ->45 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 18 - Left Tilt (+20)    ->45 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 19 - Right Tilt (-20)    ->45 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 20 -  Left Tilt(+30)     ->45 degree scope", Q_NULLPTR)
         << QApplication::translate("settings_main", "Level 21 - Right Tilt(-30)     ->45 degree scope", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        selectLevel->setToolTip(QApplication::translate("settings_main", "Select levle of the difficulty", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class settings_main: public Ui_settings_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_MAIN_H
