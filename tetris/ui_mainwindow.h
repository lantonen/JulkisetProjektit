/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *leftPushButton;
    QPushButton *rightPushButton;
    QPushButton *downPushButton;
    QPushButton *startPushButton;
    QPushButton *resetPushButton;
    QPushButton *exitPushButton;
    QPushButton *rotatePushButton;
    QLCDNumber *scoreLcdNumber;
    QLabel *label;
    QTextBrowser *textBrowser;
    QRadioButton *hardRadioButton;
    QRadioButton *mediumRadioButton;
    QRadioButton *easyRadioButton;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QFrame *line_9;
    QFrame *line_10;
    QFrame *line_11;
    QFrame *line_12;
    QFrame *line_13;
    QFrame *line_14;
    QFrame *line_15;
    QFrame *line_16;
    QFrame *line_17;
    QFrame *line_18;
    QFrame *line_19;
    QFrame *line_20;
    QFrame *line_21;
    QFrame *line_22;
    QFrame *line_23;
    QFrame *line_24;
    QFrame *line_25;
    QFrame *line_26;
    QFrame *line_27;
    QFrame *line_28;
    QFrame *line_29;
    QFrame *line_30;
    QFrame *line_31;
    QFrame *line_32;
    QFrame *line_33;
    QFrame *line_34;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(701, 691);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(130, 411, 171, 71));
        leftPushButton = new QPushButton(centralWidget);
        leftPushButton->setObjectName(QStringLiteral("leftPushButton"));
        leftPushButton->setGeometry(QRect(410, 390, 84, 28));
        rightPushButton = new QPushButton(centralWidget);
        rightPushButton->setObjectName(QStringLiteral("rightPushButton"));
        rightPushButton->setGeometry(QRect(500, 390, 84, 28));
        downPushButton = new QPushButton(centralWidget);
        downPushButton->setObjectName(QStringLiteral("downPushButton"));
        downPushButton->setGeometry(QRect(470, 420, 51, 71));
        startPushButton = new QPushButton(centralWidget);
        startPushButton->setObjectName(QStringLiteral("startPushButton"));
        startPushButton->setGeometry(QRect(510, 10, 84, 28));
        resetPushButton = new QPushButton(centralWidget);
        resetPushButton->setObjectName(QStringLiteral("resetPushButton"));
        resetPushButton->setGeometry(QRect(510, 50, 84, 28));
        exitPushButton = new QPushButton(centralWidget);
        exitPushButton->setObjectName(QStringLiteral("exitPushButton"));
        exitPushButton->setGeometry(QRect(510, 90, 84, 28));
        rotatePushButton = new QPushButton(centralWidget);
        rotatePushButton->setObjectName(QStringLiteral("rotatePushButton"));
        rotatePushButton->setGeometry(QRect(450, 310, 91, 61));
        scoreLcdNumber = new QLCDNumber(centralWidget);
        scoreLcdNumber->setObjectName(QStringLiteral("scoreLcdNumber"));
        scoreLcdNumber->setGeometry(QRect(510, 130, 64, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(460, 130, 63, 20));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(110, 0, 221, 131));
        hardRadioButton = new QRadioButton(centralWidget);
        hardRadioButton->setObjectName(QStringLiteral("hardRadioButton"));
        hardRadioButton->setGeometry(QRect(370, 10, 106, 26));
        mediumRadioButton = new QRadioButton(centralWidget);
        mediumRadioButton->setObjectName(QStringLiteral("mediumRadioButton"));
        mediumRadioButton->setGeometry(QRect(370, 50, 106, 26));
        easyRadioButton = new QRadioButton(centralWidget);
        easyRadioButton->setObjectName(QStringLiteral("easyRadioButton"));
        easyRadioButton->setGeometry(QRect(370, 90, 106, 26));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(110, 150, 20, 481));
        line->setMinimumSize(QSize(20, 0));
        line->setMaximumSize(QSize(20, 16777215));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(100, 160, 241, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(130, 150, 20, 481));
        line_3->setMinimumSize(QSize(20, 0));
        line_3->setMaximumSize(QSize(20, 16777215));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(150, 150, 20, 481));
        line_4->setMinimumSize(QSize(20, 0));
        line_4->setMaximumSize(QSize(20, 16777215));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(170, 150, 20, 481));
        line_5->setMinimumSize(QSize(20, 0));
        line_5->setMaximumSize(QSize(20, 16777215));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(190, 150, 20, 481));
        line_6->setMinimumSize(QSize(20, 0));
        line_6->setMaximumSize(QSize(20, 16777215));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(210, 150, 20, 481));
        line_7->setMinimumSize(QSize(20, 0));
        line_7->setMaximumSize(QSize(20, 16777215));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(centralWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(230, 150, 20, 481));
        line_8->setMinimumSize(QSize(20, 0));
        line_8->setMaximumSize(QSize(20, 16777215));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);
        line_9 = new QFrame(centralWidget);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setGeometry(QRect(250, 150, 20, 481));
        line_9->setMinimumSize(QSize(20, 0));
        line_9->setMaximumSize(QSize(20, 16777215));
        line_9->setFrameShape(QFrame::VLine);
        line_9->setFrameShadow(QFrame::Sunken);
        line_10 = new QFrame(centralWidget);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setGeometry(QRect(270, 150, 20, 481));
        line_10->setMinimumSize(QSize(20, 0));
        line_10->setMaximumSize(QSize(20, 16777215));
        line_10->setFrameShape(QFrame::VLine);
        line_10->setFrameShadow(QFrame::Sunken);
        line_11 = new QFrame(centralWidget);
        line_11->setObjectName(QStringLiteral("line_11"));
        line_11->setGeometry(QRect(290, 150, 20, 481));
        line_11->setMinimumSize(QSize(20, 0));
        line_11->setMaximumSize(QSize(20, 16777215));
        line_11->setFrameShape(QFrame::VLine);
        line_11->setFrameShadow(QFrame::Sunken);
        line_12 = new QFrame(centralWidget);
        line_12->setObjectName(QStringLiteral("line_12"));
        line_12->setGeometry(QRect(310, 150, 20, 481));
        line_12->setMinimumSize(QSize(20, 0));
        line_12->setMaximumSize(QSize(20, 16777215));
        line_12->setFrameShape(QFrame::VLine);
        line_12->setFrameShadow(QFrame::Sunken);
        line_13 = new QFrame(centralWidget);
        line_13->setObjectName(QStringLiteral("line_13"));
        line_13->setGeometry(QRect(100, 180, 241, 20));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);
        line_14 = new QFrame(centralWidget);
        line_14->setObjectName(QStringLiteral("line_14"));
        line_14->setGeometry(QRect(100, 200, 241, 20));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);
        line_15 = new QFrame(centralWidget);
        line_15->setObjectName(QStringLiteral("line_15"));
        line_15->setGeometry(QRect(100, 220, 241, 20));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);
        line_16 = new QFrame(centralWidget);
        line_16->setObjectName(QStringLiteral("line_16"));
        line_16->setGeometry(QRect(100, 240, 241, 20));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);
        line_17 = new QFrame(centralWidget);
        line_17->setObjectName(QStringLiteral("line_17"));
        line_17->setGeometry(QRect(100, 260, 241, 20));
        line_17->setFrameShape(QFrame::HLine);
        line_17->setFrameShadow(QFrame::Sunken);
        line_18 = new QFrame(centralWidget);
        line_18->setObjectName(QStringLiteral("line_18"));
        line_18->setGeometry(QRect(100, 280, 241, 20));
        line_18->setFrameShape(QFrame::HLine);
        line_18->setFrameShadow(QFrame::Sunken);
        line_19 = new QFrame(centralWidget);
        line_19->setObjectName(QStringLiteral("line_19"));
        line_19->setGeometry(QRect(100, 300, 241, 20));
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);
        line_20 = new QFrame(centralWidget);
        line_20->setObjectName(QStringLiteral("line_20"));
        line_20->setGeometry(QRect(100, 320, 241, 20));
        line_20->setFrameShape(QFrame::HLine);
        line_20->setFrameShadow(QFrame::Sunken);
        line_21 = new QFrame(centralWidget);
        line_21->setObjectName(QStringLiteral("line_21"));
        line_21->setGeometry(QRect(100, 340, 241, 20));
        line_21->setFrameShape(QFrame::HLine);
        line_21->setFrameShadow(QFrame::Sunken);
        line_22 = new QFrame(centralWidget);
        line_22->setObjectName(QStringLiteral("line_22"));
        line_22->setGeometry(QRect(100, 360, 241, 20));
        line_22->setFrameShape(QFrame::HLine);
        line_22->setFrameShadow(QFrame::Sunken);
        line_23 = new QFrame(centralWidget);
        line_23->setObjectName(QStringLiteral("line_23"));
        line_23->setGeometry(QRect(100, 380, 241, 20));
        line_23->setFrameShape(QFrame::HLine);
        line_23->setFrameShadow(QFrame::Sunken);
        line_24 = new QFrame(centralWidget);
        line_24->setObjectName(QStringLiteral("line_24"));
        line_24->setGeometry(QRect(100, 400, 241, 20));
        line_24->setFrameShape(QFrame::HLine);
        line_24->setFrameShadow(QFrame::Sunken);
        line_25 = new QFrame(centralWidget);
        line_25->setObjectName(QStringLiteral("line_25"));
        line_25->setGeometry(QRect(100, 420, 241, 20));
        line_25->setFrameShape(QFrame::HLine);
        line_25->setFrameShadow(QFrame::Sunken);
        line_26 = new QFrame(centralWidget);
        line_26->setObjectName(QStringLiteral("line_26"));
        line_26->setGeometry(QRect(100, 440, 241, 20));
        line_26->setFrameShape(QFrame::HLine);
        line_26->setFrameShadow(QFrame::Sunken);
        line_27 = new QFrame(centralWidget);
        line_27->setObjectName(QStringLiteral("line_27"));
        line_27->setGeometry(QRect(100, 460, 241, 20));
        line_27->setFrameShape(QFrame::HLine);
        line_27->setFrameShadow(QFrame::Sunken);
        line_28 = new QFrame(centralWidget);
        line_28->setObjectName(QStringLiteral("line_28"));
        line_28->setGeometry(QRect(100, 480, 241, 20));
        line_28->setFrameShape(QFrame::HLine);
        line_28->setFrameShadow(QFrame::Sunken);
        line_29 = new QFrame(centralWidget);
        line_29->setObjectName(QStringLiteral("line_29"));
        line_29->setGeometry(QRect(100, 500, 241, 20));
        line_29->setFrameShape(QFrame::HLine);
        line_29->setFrameShadow(QFrame::Sunken);
        line_30 = new QFrame(centralWidget);
        line_30->setObjectName(QStringLiteral("line_30"));
        line_30->setGeometry(QRect(100, 520, 241, 20));
        line_30->setFrameShape(QFrame::HLine);
        line_30->setFrameShadow(QFrame::Sunken);
        line_31 = new QFrame(centralWidget);
        line_31->setObjectName(QStringLiteral("line_31"));
        line_31->setGeometry(QRect(100, 540, 241, 20));
        line_31->setFrameShape(QFrame::HLine);
        line_31->setFrameShadow(QFrame::Sunken);
        line_32 = new QFrame(centralWidget);
        line_32->setObjectName(QStringLiteral("line_32"));
        line_32->setGeometry(QRect(100, 560, 241, 20));
        line_32->setFrameShape(QFrame::HLine);
        line_32->setFrameShadow(QFrame::Sunken);
        line_33 = new QFrame(centralWidget);
        line_33->setObjectName(QStringLiteral("line_33"));
        line_33->setGeometry(QRect(100, 580, 241, 20));
        line_33->setFrameShape(QFrame::HLine);
        line_33->setFrameShadow(QFrame::Sunken);
        line_34 = new QFrame(centralWidget);
        line_34->setObjectName(QStringLiteral("line_34"));
        line_34->setGeometry(QRect(100, 600, 241, 20));
        line_34->setFrameShape(QFrame::HLine);
        line_34->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 701, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(exitPushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        leftPushButton->setText(QApplication::translate("MainWindow", "LEFT", Q_NULLPTR));
        rightPushButton->setText(QApplication::translate("MainWindow", "RIGHT", Q_NULLPTR));
        downPushButton->setText(QApplication::translate("MainWindow", "DOWN", Q_NULLPTR));
        startPushButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        resetPushButton->setText(QApplication::translate("MainWindow", "Reset", Q_NULLPTR));
        exitPushButton->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        rotatePushButton->setText(QApplication::translate("MainWindow", "Rotate", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Score:", Q_NULLPTR));
        hardRadioButton->setText(QApplication::translate("MainWindow", "Hard", Q_NULLPTR));
        mediumRadioButton->setText(QApplication::translate("MainWindow", "Medium", Q_NULLPTR));
        easyRadioButton->setText(QApplication::translate("MainWindow", "Easy", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
