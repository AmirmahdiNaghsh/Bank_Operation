/********************************************************************************
** Form generated from reading UI file 'transferdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFERDIALOG_H
#define UI_TRANSFERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TransferDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *transferGroup;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *sourceCardCombo;
    QLabel *label_2;
    QLineEdit *destCardEdit;
    QLabel *label_3;
    QLineEdit *amountEdit;
    QLabel *label_4;
    QLineEdit *passwordEdit;
    QLabel *feeLabel;
    QLabel *totalLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TransferDialog)
    {
        if (TransferDialog->objectName().isEmpty())
            TransferDialog->setObjectName("TransferDialog");
        TransferDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(TransferDialog);
        verticalLayout->setObjectName("verticalLayout");
        transferGroup = new QGroupBox(TransferDialog);
        transferGroup->setObjectName("transferGroup");
        gridLayout = new QGridLayout(transferGroup);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(transferGroup);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sourceCardCombo = new QComboBox(transferGroup);
        sourceCardCombo->setObjectName("sourceCardCombo");

        gridLayout->addWidget(sourceCardCombo, 0, 1, 1, 1);

        label_2 = new QLabel(transferGroup);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        destCardEdit = new QLineEdit(transferGroup);
        destCardEdit->setObjectName("destCardEdit");
        destCardEdit->setMaxLength(16);

        gridLayout->addWidget(destCardEdit, 1, 1, 1, 1);

        label_3 = new QLabel(transferGroup);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        amountEdit = new QLineEdit(transferGroup);
        amountEdit->setObjectName("amountEdit");

        gridLayout->addWidget(amountEdit, 2, 1, 1, 1);

        label_4 = new QLabel(transferGroup);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        passwordEdit = new QLineEdit(transferGroup);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordEdit, 3, 1, 1, 1);


        verticalLayout->addWidget(transferGroup);

        feeLabel = new QLabel(TransferDialog);
        feeLabel->setObjectName("feeLabel");
        feeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(feeLabel);

        totalLabel = new QLabel(TransferDialog);
        totalLabel->setObjectName("totalLabel");
        totalLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(totalLabel);

        buttonBox = new QDialogButtonBox(TransferDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(TransferDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, TransferDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TransferDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TransferDialog);
    } // setupUi

    void retranslateUi(QDialog *TransferDialog)
    {
        TransferDialog->setWindowTitle(QCoreApplication::translate("TransferDialog", "Card to Card Transfer", nullptr));
        transferGroup->setTitle(QCoreApplication::translate("TransferDialog", "Transfer Details", nullptr));
        label->setText(QCoreApplication::translate("TransferDialog", "Source Card:", nullptr));
        label_2->setText(QCoreApplication::translate("TransferDialog", "Destination Card:", nullptr));
        destCardEdit->setPlaceholderText(QCoreApplication::translate("TransferDialog", "Enter 16-digit card number", nullptr));
        label_3->setText(QCoreApplication::translate("TransferDialog", "Amount:", nullptr));
        amountEdit->setPlaceholderText(QCoreApplication::translate("TransferDialog", "Enter amount in Toman", nullptr));
        label_4->setText(QCoreApplication::translate("TransferDialog", "Second Password:", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("TransferDialog", "Enter second password", nullptr));
        feeLabel->setText(QCoreApplication::translate("TransferDialog", "Transfer fee: 0 Toman", nullptr));
        totalLabel->setText(QCoreApplication::translate("TransferDialog", "Total amount: 0 Toman", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TransferDialog: public Ui_TransferDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFERDIALOG_H
