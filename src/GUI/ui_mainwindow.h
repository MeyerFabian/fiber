/********************************************************************************
** Form generated from reading UI file 'Mainwindow.ui'
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include "QVTKWidget.h"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
	QGridLayout *gridLayout;
	QVTKWidget *qvtkwidget;
    QListWidget *listWidget_2;
    QListWidget *listWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuWidget;
	QStatusBar *statusbar;
	QActionGroup *viewGroup;

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
        actionShow_On_off = new QAction(MainWindow);
        actionShow_On_off->setObjectName(QStringLiteral("actionShow_On_off"));
        actionShow_On_off->setCheckable(true);
		actionShow_On_off->setChecked(true);
		actionImageplane->setChecked(true);
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
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
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

		gridLayout->addWidget(qvtkwidget, 0, 3, 2, 1);

        listWidget_2 = new QListWidget(centralwidget);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget_2->sizePolicy().hasHeightForWidth());
        listWidget_2->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(listWidget_2, 0, 1, 1, 1);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(listWidget, 1, 1, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tabWidget->setMinimumSize(QSize(200, 0));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalSlider = new QSlider(tab);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_3->addWidget(pushButton);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 2, 2, 1);


        verticalLayout_2->addLayout(gridLayout);

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

        tabWidget->setCurrentIndex(1);


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
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
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
