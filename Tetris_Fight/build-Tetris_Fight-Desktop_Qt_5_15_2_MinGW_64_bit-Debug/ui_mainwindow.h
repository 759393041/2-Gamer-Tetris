/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frm_main;
    QFrame *frm_next;
    QPushButton *btn_start;
    QPushButton *btn_new;
    QLabel *lbl_next;
    QLabel *lbl_score_text;
    QLabel *lbl_score;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(596, 654);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frm_main = new QFrame(centralwidget);
        frm_main->setObjectName(QString::fromUtf8("frm_main"));
        frm_main->setGeometry(QRect(20, 0, 381, 601));
        frm_main->setFrameShape(QFrame::StyledPanel);
        frm_main->setFrameShadow(QFrame::Raised);
        frm_next = new QFrame(centralwidget);
        frm_next->setObjectName(QString::fromUtf8("frm_next"));
        frm_next->setGeometry(QRect(420, 40, 120, 151));
        frm_next->setFrameShape(QFrame::StyledPanel);
        frm_next->setFrameShadow(QFrame::Raised);
        btn_start = new QPushButton(centralwidget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(460, 460, 93, 29));
        btn_new = new QPushButton(centralwidget);
        btn_new->setObjectName(QString::fromUtf8("btn_new"));
        btn_new->setGeometry(QRect(460, 540, 93, 29));
        lbl_next = new QLabel(centralwidget);
        lbl_next->setObjectName(QString::fromUtf8("lbl_next"));
        lbl_next->setGeometry(QRect(420, 10, 69, 20));
        lbl_score_text = new QLabel(centralwidget);
        lbl_score_text->setObjectName(QString::fromUtf8("lbl_score_text"));
        lbl_score_text->setGeometry(QRect(450, 260, 69, 20));
        lbl_score = new QLabel(centralwidget);
        lbl_score->setObjectName(QString::fromUtf8("lbl_score"));
        lbl_score->setGeometry(QRect(460, 300, 69, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 596, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_start->setText(QCoreApplication::translate("MainWindow", "Start game", nullptr));
        btn_new->setText(QCoreApplication::translate("MainWindow", "New game", nullptr));
        lbl_next->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        lbl_score_text->setText(QCoreApplication::translate("MainWindow", "\345\276\227\345\210\206:", nullptr));
        lbl_score->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
