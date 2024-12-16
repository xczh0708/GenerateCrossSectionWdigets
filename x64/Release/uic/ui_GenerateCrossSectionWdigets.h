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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_GenerateCrossSectionWdigetsClass
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lidarLE;
    QPushButton *lidarOpenButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *sectionLE;
    QPushButton *sectionOpenButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *dxfSaveLE;
    QPushButton *dxfSaveButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *dwgSaveLE;
    QPushButton *dwgSaveButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *txtSaveLE;
    QPushButton *txtSaveButton;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *startButton;
    QPushButton *quitButton;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GenerateCrossSectionWdigetsClass)
    {
        if (GenerateCrossSectionWdigetsClass->objectName().isEmpty())
            GenerateCrossSectionWdigetsClass->setObjectName(QString::fromUtf8("GenerateCrossSectionWdigetsClass"));
        GenerateCrossSectionWdigetsClass->resize(573, 451);
        actionOpen = new QAction(GenerateCrossSectionWdigetsClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralWidget = new QWidget(GenerateCrossSectionWdigetsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 105, 296, 210));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lidarLE = new QLineEdit(layoutWidget);
        lidarLE->setObjectName(QString::fromUtf8("lidarLE"));

        horizontalLayout->addWidget(lidarLE);

        lidarOpenButton = new QPushButton(layoutWidget);
        lidarOpenButton->setObjectName(QString::fromUtf8("lidarOpenButton"));

        horizontalLayout->addWidget(lidarOpenButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        sectionLE = new QLineEdit(layoutWidget);
        sectionLE->setObjectName(QString::fromUtf8("sectionLE"));

        horizontalLayout_2->addWidget(sectionLE);

        sectionOpenButton = new QPushButton(layoutWidget);
        sectionOpenButton->setObjectName(QString::fromUtf8("sectionOpenButton"));

        horizontalLayout_2->addWidget(sectionOpenButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        dxfSaveLE = new QLineEdit(layoutWidget);
        dxfSaveLE->setObjectName(QString::fromUtf8("dxfSaveLE"));

        horizontalLayout_3->addWidget(dxfSaveLE);

        dxfSaveButton = new QPushButton(layoutWidget);
        dxfSaveButton->setObjectName(QString::fromUtf8("dxfSaveButton"));

        horizontalLayout_3->addWidget(dxfSaveButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        dwgSaveLE = new QLineEdit(layoutWidget);
        dwgSaveLE->setObjectName(QString::fromUtf8("dwgSaveLE"));

        horizontalLayout_4->addWidget(dwgSaveLE);

        dwgSaveButton = new QPushButton(layoutWidget);
        dwgSaveButton->setObjectName(QString::fromUtf8("dwgSaveButton"));

        horizontalLayout_4->addWidget(dwgSaveButton);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        txtSaveLE = new QLineEdit(layoutWidget);
        txtSaveLE->setObjectName(QString::fromUtf8("txtSaveLE"));

        horizontalLayout_5->addWidget(txtSaveLE);

        txtSaveButton = new QPushButton(layoutWidget);
        txtSaveButton->setObjectName(QString::fromUtf8("txtSaveButton"));

        horizontalLayout_5->addWidget(txtSaveButton);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_7->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        horizontalLayout_6->addWidget(startButton);

        quitButton = new QPushButton(layoutWidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        horizontalLayout_6->addWidget(quitButton);


        verticalLayout->addLayout(horizontalLayout_6);

        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(450, 210, 100, 100));
        GenerateCrossSectionWdigetsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GenerateCrossSectionWdigetsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 573, 22));
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
        label->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\346\277\200\345\205\211\351\233\267\350\276\276\346\225\260\346\215\256", nullptr));
        lidarOpenButton->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\351\200\211\346\213\251", nullptr));
        label_2->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\346\217\220\345\217\226\347\272\277\346\226\207\344\273\266", nullptr));
        sectionOpenButton->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\351\200\211\346\213\251", nullptr));
        label_3->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "dxf\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        dxfSaveButton->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\351\200\211\346\213\251", nullptr));
        label_4->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "dwg\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        dwgSaveButton->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\351\200\211\346\213\251", nullptr));
        label_5->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\346\226\207\346\234\254\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        txtSaveButton->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\351\200\211\346\213\251", nullptr));
        label_6->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\351\207\207\346\240\267\347\202\271\346\225\260", nullptr));
        startButton->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\346\217\220\345\217\226", nullptr));
        quitButton->setText(QApplication::translate("GenerateCrossSectionWdigetsClass", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QApplication::translate("GenerateCrossSectionWdigetsClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateCrossSectionWdigetsClass: public Ui_GenerateCrossSectionWdigetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATECROSSSECTIONWDIGETS_H
