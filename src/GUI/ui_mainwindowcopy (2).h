/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include "QVTKWidget.h"
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QActionGroup>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionReset;
    QAction *actionSuperior;
    QAction *actionAnterior;
    QAction *actionImageplane;
    QAction *actionBox;
    QAction *actionShow_On_off;
    QActionGroup *viewGroup;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
	QVTKWidget *qvtkwidget;
    QListWidget *listWidget_2;
    QListWidget *listWidget;
    QListView *listView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 786);
        MainWindow->setMinimumSize(QSize(1024, 768));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionSuperior = new QAction(MainWindow);
        actionSuperior->setObjectName(QStringLiteral("actionSuperior"));
        actionAnterior = new QAction(MainWindow);
        actionAnterior->setObjectName(QStringLiteral("actionAnterior"));
        actionImageplane = new QAction(MainWindow);
		actionImageplane->setObjectName(QStringLiteral("actionImageplane"));
		actionImageplane->setCheckable(true);
		actionBox = new QAction(MainWindow);
		actionBox->setObjectName(QStringLiteral("actionBox"));
		actionBox->setCheckable(true);
		viewGroup = new QActionGroup(MainWindow);
        viewGroup->addAction(actionImageplane);
        viewGroup->addAction(actionBox);
        actionImageplane->setChecked(true);
        actionShow_On_off = new QAction(MainWindow);
        actionShow_On_off->setObjectName(QStringLiteral("actionShow_On_off"));
        actionShow_On_off->setCheckable(true);
        actionShow_On_off->setChecked(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(1024, 748));
        centralwidget->setSizeIncrement(QSize(4, 3));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        qvtkwidget = new QVTKWidget(centralwidget);
                qvtkwidget->setObjectName(QStringLiteral("qvtkwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(qvtkwidget->sizePolicy().hasHeightForWidth());
		qvtkwidget->setSizePolicy(sizePolicy1);
		qvtkwidget->setMinimumSize(QSize(640, 480));

		gridLayout->addWidget(qvtkwidget, 0, 4, 2, 1);

        listWidget_2 = new QListWidget(centralwidget);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        sizePolicy.setHeightForWidth(listWidget_2->sizePolicy().hasHeightForWidth());
        listWidget_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(listWidget_2, 1, 0, 1, 3);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setSelectionRectVisible(false);

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));
        sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy);

        gridLayout->addWidget(listView, 0, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuWidget = new QMenu(menuView);
        menuWidget->setObjectName(QStringLiteral("menuWidget"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuView->addAction(actionReset);
        menuView->addAction(menuWidget->menuAction());
        menuWidget->addAction(actionShow_On_off);
        menuWidget->addSeparator();
        menuWidget->addAction(actionImageplane);
        menuWidget->addAction(actionBox);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open..", 0));
        actionReset->setText(QApplication::translate("MainWindow", "Reset", 0));
        actionSuperior->setText(QApplication::translate("MainWindow", "Superior", 0));
        actionAnterior->setText(QApplication::translate("MainWindow", "Anterior", 0));
        actionImageplane->setText(QApplication::translate("MainWindow", "Imageplane", 0));
        actionBox->setText(QApplication::translate("MainWindow", "Box", 0));
        actionShow_On_off->setText(QApplication::translate("MainWindow", "Show On", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        menuWidget->setTitle(QApplication::translate("MainWindow", "Widget", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
