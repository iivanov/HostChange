/********************************************************************************
** Form generated from reading UI file 'asktabname.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASKTABNAME_H
#define UI_ASKTABNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AskTabName
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *AskTabName)
    {
        if (AskTabName->objectName().isEmpty())
            AskTabName->setObjectName(QStringLiteral("AskTabName"));
        AskTabName->resize(400, 114);
        buttonBox = new QDialogButtonBox(AskTabName);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 70, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(AskTabName);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 291, 16));
        lineEdit = new QLineEdit(AskTabName);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 40, 341, 22));

        retranslateUi(AskTabName);
        QObject::connect(buttonBox, SIGNAL(accepted()), AskTabName, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AskTabName, SLOT(reject()));

        QMetaObject::connectSlotsByName(AskTabName);
    } // setupUi

    void retranslateUi(QDialog *AskTabName)
    {
        AskTabName->setWindowTitle(QApplication::translate("AskTabName", "Dialog", 0));
        label->setText(QApplication::translate("AskTabName", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\274\321\217 \321\210\320\260\320\261\320\273\320\276\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class AskTabName: public Ui_AskTabName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASKTABNAME_H
