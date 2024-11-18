/********************************************************************************
** Form generated from reading UI file 'GenerateCrossSectionWdigets.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATECROSSSECTIONWDIGETS_H
#define UI_GENERATECROSSSECTIONWDIGETS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateCrossSectionWdigetsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GenerateCrossSectionWdigetsClass)
    {
        if (GenerateCrossSectionWdigetsClass->objectName().isEmpty())
            GenerateCrossSectionWdigetsClass->setObjectName(QString::fromUtf8("GenerateCrossSectionWdigetsClass"));
        GenerateCrossSectionWdigetsClass->resize(600, 400);
        menuBar = new QMenuBar(GenerateCrossSectionWdigetsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        GenerateCrossSectionWdigetsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GenerateCrossSectionWdigetsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GenerateCrossSectionWdigetsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GenerateCrossSectionWdigetsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GenerateCrossSectionWdigetsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GenerateCrossSectionWdigetsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GenerateCrossSectionWdigetsClass->setStatusBar(statusBar);

        retranslateUi(GenerateCrossSectionWdigetsClass);

        QMetaObject::connectSlotsByName(GenerateCrossSectionWdigetsClass);
    } // setupUi

    void retranslateUi(QMainWindow *GenerateCrossSectionWdigetsClass)
    {
        GenerateCrossSectionWdigetsClass->setWindowTitle(QApplication::translate("GenerateCrossSectionWdigetsClass", "GenerateCrossSectionWdigets", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateCrossSectionWdigetsClass: public Ui_GenerateCrossSectionWdigetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATECROSSSECTIONWDIGETS_H
