/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created: Mon 2. Jun 09:04:53 2014
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *iconLabel;
    QLabel *warrantyLabel;
    QLabel *labelProductAndVersion;
    QLabel *label_2;
    QLabel *label_iconZ;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(414, 214);
        buttonBox = new QDialogButtonBox(About);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 170, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        iconLabel = new QLabel(About);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));
        iconLabel->setGeometry(QRect(10, 30, 151, 61));
        iconLabel->setTextFormat(Qt::PlainText);
        iconLabel->setPixmap(QPixmap(QString::fromUtf8(":/img/logotiny.PNG")));
        warrantyLabel = new QLabel(About);
        warrantyLabel->setObjectName(QString::fromUtf8("warrantyLabel"));
        warrantyLabel->setGeometry(QRect(180, 70, 201, 91));
        warrantyLabel->setWordWrap(true);
        labelProductAndVersion = new QLabel(About);
        labelProductAndVersion->setObjectName(QString::fromUtf8("labelProductAndVersion"));
        labelProductAndVersion->setGeometry(QRect(180, 10, 211, 51));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelProductAndVersion->setFont(font);
        label_2 = new QLabel(About);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 10, 71, 16));
        label_iconZ = new QLabel(About);
        label_iconZ->setObjectName(QString::fromUtf8("label_iconZ"));
        label_iconZ->setGeometry(QRect(20, 120, 130, 33));
        label_iconZ->setPixmap(QPixmap(QString::fromUtf8(":/img/zapmaker-logo-130.png")));

        retranslateUi(About);
        QObject::connect(buttonBox, SIGNAL(accepted()), About, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), About, SLOT(reject()));

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About...", 0, QApplication::UnicodeUTF8));
        iconLabel->setText(QString());
        warrantyLabel->setText(QApplication::translate("About", "The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.", 0, QApplication::UnicodeUTF8));
        labelProductAndVersion->setText(QApplication::translate("About", "Grbl Controller", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        label_iconZ->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
