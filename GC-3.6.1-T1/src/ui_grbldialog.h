/********************************************************************************
** Form generated from reading UI file 'grbldialog.ui'
**
** Created: Mon 2. Jun 09:04:53 2014
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRBLDIALOG_H
#define UI_GRBLDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_GrblDialog
{
public:
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QTableWidget *table;

    void setupUi(QDialog *GrblDialog)
    {
        if (GrblDialog->objectName().isEmpty())
            GrblDialog->setObjectName(QString::fromUtf8("GrblDialog"));
        GrblDialog->resize(440, 438);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GrblDialog->sizePolicy().hasHeightForWidth());
        GrblDialog->setSizePolicy(sizePolicy);
        btnOk = new QPushButton(GrblDialog);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(50, 390, 75, 31));
        btnCancel = new QPushButton(GrblDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(280, 390, 75, 31));
        table = new QTableWidget(GrblDialog);
        if (table->columnCount() < 2)
            table->setColumnCount(2);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(10, 20, 411, 351));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(10);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(table->sizePolicy().hasHeightForWidth());
        table->setSizePolicy(sizePolicy1);
        table->setInputMethodHints(Qt::ImhNone);
        table->setAutoScrollMargin(30);
        table->setCornerButtonEnabled(true);
        table->setColumnCount(2);
        table->horizontalHeader()->setCascadingSectionResizes(true);
        table->horizontalHeader()->setDefaultSectionSize(40);
        table->horizontalHeader()->setMinimumSectionSize(40);
        table->horizontalHeader()->setStretchLastSection(true);
        table->verticalHeader()->setDefaultSectionSize(30);

        retranslateUi(GrblDialog);

        QMetaObject::connectSlotsByName(GrblDialog);
    } // setupUi

    void retranslateUi(QDialog *GrblDialog)
    {
        GrblDialog->setWindowTitle(QApplication::translate("GrblDialog", "Grbl Settings", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("GrblDialog", "Apply", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("GrblDialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GrblDialog: public Ui_GrblDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRBLDIALOG_H
