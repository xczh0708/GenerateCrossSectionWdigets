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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateCrossSectionWdigetsClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GenerateCrossSectionWdigetsClass)
    {
        if (GenerateCrossSectionWdigetsClass->objectName().isEmpty())
            GenerateCrossSectionWdigetsClass->setObjectName(QString::fromUtf8("GenerateCrossSectionWdigetsClass"));
        GenerateCrossSectionWdigetsClass->resize(484, 406);
        actionOpen = new QAction(GenerateCrossSectionWdigetsClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralWidget = new QWidget(GenerateCrossSectionWdigetsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GenerateCrossSectionWdigetsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GenerateCrossSectionWdigetsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 484, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        GenerateCrossSectionWdigetsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GenerateCrossSectionWdigetsClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GenerateCrossSectionWdigetsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GenerateCrossSectionWdigetsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GenerateCrossSectionWdigetsClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionOpen);

        retranslateUi(GenerateCrossSectionWdigetsClass);

        QMetaObject::connectSlotsByName(GenerateCrossSectionWdigetsClass);
    } // setupUi

    void retranslateUi(QMainWindow *GenerateCrossSectionWdigetsClass)
    {
        GenerateCrossSectionWdigetsClass->setWindowTitle(QApplication::translate("GenerateCrossSectionWdigetsClass", "GenerateCrossSectionWdigets", nullptr));
        actionOpen->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\346\211\223\345\274\200", nullptr));
        menu->setTitle(QApplication::translate("GenerateCrossSectionWdigetsClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateCrossSectionWdigetsClass: public Ui_GenerateCrossSectionWdigetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATECROSSSECTIONWDIGETS_H
