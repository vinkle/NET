/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings
{
public:
    QDialogButtonBox *buttonBox;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_8;
    QLineEdit *cap_path;
    QLabel *label_22;
    QLineEdit *cap_auxCam;
    QLabel *label_9;
    QLineEdit *cap_queueSize;
    QLabel *label_10;
    QLineEdit *cap_binSize;
    QLabel *label_13;
    QLineEdit *cap_rowAux;
    QLabel *label_12;
    QLineEdit *cap_fpsAux;
    QLineEdit *cap_colsAux;
    QLabel *label_11;
    QLineEdit *cap_camID_IDS;
    QLabel *label_15;
    QLineEdit *cap_rows_endo;
    QLabel *label_18;
    QLineEdit *cap_cols_endo;
    QLabel *label_14;
    QLabel *label_20;
    QLineEdit *cap_fps_endo;
    QPushButton *pushButton;
    QWidget *page_2;
    QLabel *label_23;
    QStackedWidget *stackedWidget_2;
    QWidget *page_3;
    QGridLayout *gridLayout_2;
    QLabel *label_24;
    QLineEdit *tr_nameTracker;
    QWidget *page_4;
    QLabel *label_39;
    QGroupBox *groupBox;
    QGroupBox *serialPortBox;
    QComboBox *serialPortInfoListBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnCalib;
    QLabel *lblImg;
    QGroupBox *parametersBox;
    QGridLayout *gridLayout_3;
    QLabel *baudRateLabel;
    QComboBox *baudRateBox;
    QLabel *dataBitsLabel;
    QComboBox *dataBitsBox;
    QComboBox *stopBitsBox;
    QComboBox *parityBox;
    QLabel *stopBitsLabel;
    QComboBox *flowControlBox;
    QLabel *flowControlLabel;
    QLabel *parityLabel;
    QGroupBox *groupBox_2;
    QPushButton *btnAddtoDatabase;
    QLabel *label_4;
    QComboBox *cmbExperience;
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *cmbSalutation;
    QLineEdit *txtName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *txtEmail;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QTextEdit *textDetails;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QStringLiteral("settings"));
        settings->resize(973, 530);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        settings->setFont(font);
        settings->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        buttonBox = new QDialogButtonBox(settings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(420, 500, 161, 32));
        buttonBox->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(70, 67, 166);"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        stackedWidget = new QStackedWidget(settings);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 20, 321, 431));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label_8 = new QLabel(page);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(9, 17, 79, 16));
        label_8->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_path = new QLineEdit(page);
        cap_path->setObjectName(QStringLiteral("cap_path"));
        cap_path->setGeometry(QRect(167, 17, 111, 23));
        cap_path->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_22 = new QLabel(page);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(9, 54, 152, 16));
        label_22->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_auxCam = new QLineEdit(page);
        cap_auxCam->setObjectName(QStringLiteral("cap_auxCam"));
        cap_auxCam->setGeometry(QRect(167, 54, 125, 23));
        cap_auxCam->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(9, 91, 68, 16));
        label_9->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_queueSize = new QLineEdit(page);
        cap_queueSize->setObjectName(QStringLiteral("cap_queueSize"));
        cap_queueSize->setGeometry(QRect(167, 91, 125, 23));
        cap_queueSize->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_10 = new QLabel(page);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(9, 128, 48, 16));
        label_10->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_binSize = new QLineEdit(page);
        cap_binSize->setObjectName(QStringLiteral("cap_binSize"));
        cap_binSize->setGeometry(QRect(167, 128, 125, 23));
        cap_binSize->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_13 = new QLabel(page);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(9, 165, 61, 16));
        label_13->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_rowAux = new QLineEdit(page);
        cap_rowAux->setObjectName(QStringLiteral("cap_rowAux"));
        cap_rowAux->setGeometry(QRect(167, 165, 125, 23));
        cap_rowAux->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_12 = new QLabel(page);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(9, 202, 55, 16));
        label_12->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_fpsAux = new QLineEdit(page);
        cap_fpsAux->setObjectName(QStringLiteral("cap_fpsAux"));
        cap_fpsAux->setGeometry(QRect(167, 239, 125, 23));
        cap_fpsAux->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_colsAux = new QLineEdit(page);
        cap_colsAux->setObjectName(QStringLiteral("cap_colsAux"));
        cap_colsAux->setGeometry(QRect(167, 202, 125, 23));
        cap_colsAux->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_11 = new QLabel(page);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(9, 239, 95, 16));
        label_11->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_camID_IDS = new QLineEdit(page);
        cap_camID_IDS->setObjectName(QStringLiteral("cap_camID_IDS"));
        cap_camID_IDS->setGeometry(QRect(167, 276, 125, 23));
        cap_camID_IDS->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_15 = new QLabel(page);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(9, 276, 67, 16));
        label_15->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_rows_endo = new QLineEdit(page);
        cap_rows_endo->setObjectName(QStringLiteral("cap_rows_endo"));
        cap_rows_endo->setGeometry(QRect(167, 313, 125, 23));
        cap_rows_endo->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_18 = new QLabel(page);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(9, 313, 68, 16));
        label_18->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_cols_endo = new QLineEdit(page);
        cap_cols_endo->setObjectName(QStringLiteral("cap_cols_endo"));
        cap_cols_endo->setGeometry(QRect(167, 350, 125, 23));
        cap_cols_endo->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_14 = new QLabel(page);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(9, 350, 62, 16));
        label_14->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        label_20 = new QLabel(page);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(9, 387, 104, 16));
        label_20->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        cap_fps_endo = new QLineEdit(page);
        cap_fps_endo->setObjectName(QStringLiteral("cap_fps_endo"));
        cap_fps_endo->setGeometry(QRect(167, 387, 125, 23));
        cap_fps_endo->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(280, 17, 21, 23));
        stackedWidget->addWidget(page);
        label_8->raise();
        cap_path->raise();
        label_9->raise();
        cap_queueSize->raise();
        label_10->raise();
        cap_binSize->raise();
        cap_fpsAux->raise();
        label_11->raise();
        cap_colsAux->raise();
        label_12->raise();
        cap_rowAux->raise();
        label_13->raise();
        cap_cols_endo->raise();
        cap_camID_IDS->raise();
        label_18->raise();
        cap_rows_endo->raise();
        label_15->raise();
        label_20->raise();
        cap_fps_endo->raise();
        label_14->raise();
        label_22->raise();
        cap_auxCam->raise();
        pushButton->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);
        label_23 = new QLabel(settings);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(100, 10, 169, 27));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_23->setFont(font1);
        label_23->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        stackedWidget_2 = new QStackedWidget(settings);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(10, 460, 339, 51));
        stackedWidget_2->setStyleSheet(QStringLiteral(""));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        gridLayout_2 = new QGridLayout(page_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_24 = new QLabel(page_3);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(label_24, 0, 0, 1, 1);

        tr_nameTracker = new QLineEdit(page_3);
        tr_nameTracker->setObjectName(QStringLiteral("tr_nameTracker"));
        tr_nameTracker->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        gridLayout_2->addWidget(tr_nameTracker, 0, 1, 1, 1);

        stackedWidget_2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        stackedWidget_2->addWidget(page_4);
        label_39 = new QLabel(settings);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(90, 440, 169, 16));
        label_39->setFont(font1);
        label_39->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        groupBox = new QGroupBox(settings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(660, 10, 301, 411));
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        serialPortBox = new QGroupBox(groupBox);
        serialPortBox->setObjectName(QStringLiteral("serialPortBox"));
        serialPortBox->setGeometry(QRect(60, 350, 191, 61));
        serialPortBox->setFont(font1);
        serialPortBox->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        serialPortInfoListBox = new QComboBox(serialPortBox);
        serialPortInfoListBox->setObjectName(QStringLiteral("serialPortInfoListBox"));
        serialPortInfoListBox->setGeometry(QRect(10, 30, 151, 27));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 291, 321));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnCalib = new QPushButton(layoutWidget);
        btnCalib->setObjectName(QStringLiteral("btnCalib"));
        btnCalib->setEnabled(false);
        btnCalib->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(btnCalib);

        lblImg = new QLabel(layoutWidget);
        lblImg->setObjectName(QStringLiteral("lblImg"));
        lblImg->setStyleSheet(QStringLiteral("image: url(:/icons/endo-calib_0.png);"));

        verticalLayout->addWidget(lblImg);

        parametersBox = new QGroupBox(layoutWidget);
        parametersBox->setObjectName(QStringLiteral("parametersBox"));
        gridLayout_3 = new QGridLayout(parametersBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        baudRateLabel = new QLabel(parametersBox);
        baudRateLabel->setObjectName(QStringLiteral("baudRateLabel"));

        gridLayout_3->addWidget(baudRateLabel, 0, 0, 1, 1);

        baudRateBox = new QComboBox(parametersBox);
        baudRateBox->setObjectName(QStringLiteral("baudRateBox"));

        gridLayout_3->addWidget(baudRateBox, 0, 1, 1, 1);

        dataBitsLabel = new QLabel(parametersBox);
        dataBitsLabel->setObjectName(QStringLiteral("dataBitsLabel"));

        gridLayout_3->addWidget(dataBitsLabel, 1, 0, 1, 1);

        dataBitsBox = new QComboBox(parametersBox);
        dataBitsBox->setObjectName(QStringLiteral("dataBitsBox"));

        gridLayout_3->addWidget(dataBitsBox, 1, 1, 1, 1);

        stopBitsBox = new QComboBox(parametersBox);
        stopBitsBox->setObjectName(QStringLiteral("stopBitsBox"));

        gridLayout_3->addWidget(stopBitsBox, 3, 1, 1, 1);

        parityBox = new QComboBox(parametersBox);
        parityBox->setObjectName(QStringLiteral("parityBox"));

        gridLayout_3->addWidget(parityBox, 2, 1, 1, 1);

        stopBitsLabel = new QLabel(parametersBox);
        stopBitsLabel->setObjectName(QStringLiteral("stopBitsLabel"));

        gridLayout_3->addWidget(stopBitsLabel, 3, 0, 1, 1);

        flowControlBox = new QComboBox(parametersBox);
        flowControlBox->setObjectName(QStringLiteral("flowControlBox"));

        gridLayout_3->addWidget(flowControlBox, 4, 1, 1, 1);

        flowControlLabel = new QLabel(parametersBox);
        flowControlLabel->setObjectName(QStringLiteral("flowControlLabel"));

        gridLayout_3->addWidget(flowControlLabel, 4, 0, 1, 1);

        parityLabel = new QLabel(parametersBox);
        parityLabel->setObjectName(QStringLiteral("parityLabel"));

        gridLayout_3->addWidget(parityLabel, 2, 0, 1, 1);


        verticalLayout->addWidget(parametersBox);

        layoutWidget->raise();
        serialPortBox->raise();
        groupBox_2 = new QGroupBox(settings);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 20, 301, 291));
        groupBox_2->setFont(font1);
        btnAddtoDatabase = new QPushButton(groupBox_2);
        btnAddtoDatabase->setObjectName(QStringLiteral("btnAddtoDatabase"));
        btnAddtoDatabase->setGeometry(QRect(70, 250, 151, 31));
        btnAddtoDatabase->setFont(font1);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 30, 81, 20));
        label_4->setFont(font1);
        cmbExperience = new QComboBox(groupBox_2);
        cmbExperience->setObjectName(QStringLiteral("cmbExperience"));
        cmbExperience->setGeometry(QRect(150, 30, 79, 22));
        cmbExperience->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 60, 281, 181));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        cmbSalutation = new QComboBox(widget);
        cmbSalutation->setObjectName(QStringLiteral("cmbSalutation"));
        cmbSalutation->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(cmbSalutation);

        txtName = new QLineEdit(widget);
        txtName->setObjectName(QStringLiteral("txtName"));

        horizontalLayout->addWidget(txtName);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        horizontalLayout_2->addWidget(label_5);

        txtEmail = new QLineEdit(widget);
        txtEmail->setObjectName(QStringLiteral("txtEmail"));

        horizontalLayout_2->addWidget(txtEmail);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        textDetails = new QTextEdit(widget);
        textDetails->setObjectName(QStringLiteral("textDetails"));

        horizontalLayout_3->addWidget(textDetails);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QApplication::translate("settings", "Dialog", Q_NULLPTR));
        label_8->setText(QApplication::translate("settings", "Capture path", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_path->setToolTip(QApplication::translate("settings", "Set the full capture path. Separate by comma for multiple paths", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_path->setText(QApplication::translate("settings", "/home/terminalx/Desktop", Q_NULLPTR));
        label_22->setText(QApplication::translate("settings", "Choose Auxiliary Camera", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_auxCam->setToolTip(QApplication::translate("settings", "choose the auxiliry camera \"basler\" vs \"ids\"", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_auxCam->setText(QApplication::translate("settings", "basler", Q_NULLPTR));
        label_9->setText(QApplication::translate("settings", "Queue Size", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_queueSize->setToolTip(QApplication::translate("settings", "Size of the queue of fifo buffer", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_queueSize->setText(QApplication::translate("settings", "10", Q_NULLPTR));
        label_10->setText(QApplication::translate("settings", "Bin Size", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_binSize->setToolTip(QApplication::translate("settings", "No of images to dumped at one throgh", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_binSize->setText(QApplication::translate("settings", "1", Q_NULLPTR));
        label_13->setText(QApplication::translate("settings", "Rows_Aux", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_rowAux->setToolTip(QApplication::translate("settings", "No of Rows for the auxiliary camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_rowAux->setText(QApplication::translate("settings", "1024", Q_NULLPTR));
        label_12->setText(QApplication::translate("settings", "Cols_Aux", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_fpsAux->setToolTip(QApplication::translate("settings", "Frame rate for the auxiliary camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_fpsAux->setText(QApplication::translate("settings", "25", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_colsAux->setToolTip(QApplication::translate("settings", "No of Cloumns for the auxiliary camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_colsAux->setText(QApplication::translate("settings", "1280", Q_NULLPTR));
        label_11->setText(QApplication::translate("settings", "FrameRate_Aux", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_camID_IDS->setToolTip(QApplication::translate("settings", "Camera ID for the IDS camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_camID_IDS->setText(QApplication::translate("settings", "2", Q_NULLPTR));
        label_15->setText(QApplication::translate("settings", "CamID_IDS", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_rows_endo->setToolTip(QApplication::translate("settings", "No of Rows for the Endoscopic camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_rows_endo->setText(QApplication::translate("settings", "720", Q_NULLPTR));
        label_18->setText(QApplication::translate("settings", "Rows_Endo", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_cols_endo->setToolTip(QApplication::translate("settings", "No of cols for the Endoscopic camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_cols_endo->setText(QApplication::translate("settings", "1280", Q_NULLPTR));
        label_14->setText(QApplication::translate("settings", "Cols_Endo", Q_NULLPTR));
        label_20->setText(QApplication::translate("settings", "Frame Rate Endo", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        cap_fps_endo->setToolTip(QApplication::translate("settings", "Frame rate for the Endoscopic camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cap_fps_endo->setText(QApplication::translate("settings", "25", Q_NULLPTR));
        pushButton->setText(QApplication::translate("settings", "...", Q_NULLPTR));
        label_23->setText(QApplication::translate("settings", "Capture Settings", Q_NULLPTR));
        label_24->setText(QApplication::translate("settings", "Tracker to be used", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tr_nameTracker->setToolTip(QApplication::translate("settings", "choose tracker tld or markerBased", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        tr_nameTracker->setText(QApplication::translate("settings", "tld", Q_NULLPTR));
        label_39->setText(QApplication::translate("settings", "Tracker Settings", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("settings", "                Calibrate Neuro-Endo-Trainer", Q_NULLPTR));
        serialPortBox->setTitle(QApplication::translate("settings", "Select Serial Port", Q_NULLPTR));
        serialPortInfoListBox->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        btnCalib->setText(QApplication::translate("settings", "Start Calibration", Q_NULLPTR));
        lblImg->setText(QString());
        parametersBox->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        parametersBox->setTitle(QApplication::translate("settings", "Select Parameters", Q_NULLPTR));
        baudRateLabel->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        baudRateLabel->setText(QApplication::translate("settings", "Baud Rate:", Q_NULLPTR));
        baudRateBox->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        dataBitsLabel->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        dataBitsLabel->setText(QApplication::translate("settings", "Data bits:", Q_NULLPTR));
        dataBitsBox->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        stopBitsBox->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        parityBox->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        stopBitsLabel->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        stopBitsLabel->setText(QApplication::translate("settings", "Stop bits:", Q_NULLPTR));
        flowControlBox->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        flowControlLabel->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        flowControlLabel->setText(QApplication::translate("settings", "Flow control:", Q_NULLPTR));
        parityLabel->setStyleSheet(QApplication::translate("settings", "background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);", Q_NULLPTR));
        parityLabel->setText(QApplication::translate("settings", "Parity:", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("settings", "Add user to the Database", Q_NULLPTR));
        btnAddtoDatabase->setText(QApplication::translate("settings", "ADD", Q_NULLPTR));
        label_4->setText(QApplication::translate("settings", "Experience", Q_NULLPTR));
        cmbExperience->clear();
        cmbExperience->insertItems(0, QStringList()
         << QApplication::translate("settings", "Novice (Prelimenary stage)", Q_NULLPTR)
         << QApplication::translate("settings", "Intermediate (Assisted and manipulated endoscopes)", Q_NULLPTR)
         << QApplication::translate("settings", "Experienced (Performing endoscopic surgeries)", Q_NULLPTR)
         << QApplication::translate("settings", "Expert (performed more than 200 endoscopic surgeries)", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("settings", "Name", Q_NULLPTR));
        cmbSalutation->clear();
        cmbSalutation->insertItems(0, QStringList()
         << QApplication::translate("settings", "Prof.", Q_NULLPTR)
         << QApplication::translate("settings", "Dr.", Q_NULLPTR)
         << QApplication::translate("settings", "Trainee", Q_NULLPTR)
         << QApplication::translate("settings", "Other", Q_NULLPTR)
        );
        txtName->setText(QString());
        label_5->setText(QApplication::translate("settings", "Email-ID", Q_NULLPTR));
        txtEmail->setText(QString());
        label_3->setText(QApplication::translate("settings", "Contact", Q_NULLPTR));
        textDetails->setHtml(QApplication::translate("settings", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Phone No:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Hospital: </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Address:</p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
