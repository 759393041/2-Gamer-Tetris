/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frm_main;
    QFrame *frm_next;
    QLabel *lbl_next;
    QPushButton *btn_new;
    QPushButton *btn_start;
    QLabel *lbl_score_text;
    QLabel *lbl_score;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 700);
        MainWindow->setMinimumSize(QSize(500, 700));
        MainWindow->setMaximumSize(QSize(500, 700));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(500, 700));
        centralWidget->setMaximumSize(QSize(500, 700));
        frm_main = new QFrame(centralWidget);
        frm_main->setObjectName(QString::fromUtf8("frm_main"));
        frm_main->setGeometry(QRect(10, 10, 320, 680));
        frm_main->setAutoFillBackground(false);
        frm_main->setFrameShape(QFrame::StyledPanel);
        frm_main->setFrameShadow(QFrame::Raised);
        frm_next = new QFrame(centralWidget);
        frm_next->setObjectName(QString::fromUtf8("frm_next"));
        frm_next->setGeometry(QRect(360, 30, 120, 140));
        frm_next->setAutoFillBackground(false);
        frm_next->setFrameShape(QFrame::StyledPanel);
        frm_next->setFrameShadow(QFrame::Raised);
        lbl_next = new QLabel(centralWidget);
        lbl_next->setObjectName(QString::fromUtf8("lbl_next"));
        lbl_next->setGeometry(QRect(360, 10, 31, 16));
        btn_new = new QPushButton(centralWidget);
        btn_new->setObjectName(QString::fromUtf8("btn_new"));
        btn_new->setGeometry(QRect(370, 640, 101, 41));
        btn_start = new QPushButton(centralWidget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(370, 590, 101, 41));
        lbl_score_text = new QLabel(centralWidget);
        lbl_score_text->setObjectName(QString::fromUtf8("lbl_score_text"));
        lbl_score_text->setGeometry(QRect(360, 190, 41, 16));
        lbl_score = new QLabel(centralWidget);
        lbl_score->setObjectName(QString::fromUtf8("lbl_score"));
        lbl_score->setGeometry(QRect(400, 190, 60, 16));
        lbl_score->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lbl_next->setText(QCoreApplication::translate("MainWindow", "Next:", nullptr));
        btn_new->setText(QCoreApplication::translate("MainWindow", "New game", nullptr));
        btn_start->setText(QCoreApplication::translate("MainWindow", "Start game", nullptr));
        lbl_score_text->setText(QCoreApplication::translate("MainWindow", "Score:", nullptr));
        lbl_score->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
