/********************************************************************************
** Form generated from reading UI file 'openchart_demo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENCHART_DEMO_H
#define UI_OPENCHART_DEMO_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenChart_demoClass
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTreeWidget *configTreeWigdet;
    QWebEngineView *myWebView;
    QPushButton *lineButton;
    QPushButton *barButton;
    QPushButton *pieButton;
    QPushButton *scatterButton;
    QPushButton *d3BarButton;
    QPushButton *heatmapButton;
    QPushButton *reloadButton;
    QPushButton *exitButton;

    void setupUi(QWidget *OpenChart_demoClass)
    {
        if (OpenChart_demoClass->objectName().isEmpty())
            OpenChart_demoClass->setObjectName(QString::fromUtf8("OpenChart_demoClass"));
        OpenChart_demoClass->resize(1001, 681);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OpenChart_demoClass->sizePolicy().hasHeightForWidth());
        OpenChart_demoClass->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(OpenChart_demoClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(OpenChart_demoClass);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        configTreeWigdet = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        configTreeWigdet->setHeaderItem(__qtreewidgetitem);
        configTreeWigdet->setObjectName(QString::fromUtf8("configTreeWigdet"));
        splitter->addWidget(configTreeWigdet);
        myWebView = new QWebEngineView(splitter);
        myWebView->setObjectName(QString::fromUtf8("myWebView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(myWebView->sizePolicy().hasHeightForWidth());
        myWebView->setSizePolicy(sizePolicy1);
        myWebView->setMinimumSize(QSize(700, 500));
        myWebView->setUrl(QUrl(QString::fromUtf8("about:blank")));
        splitter->addWidget(myWebView);

        gridLayout->addWidget(splitter, 0, 0, 1, 4);

        lineButton = new QPushButton(OpenChart_demoClass);
        lineButton->setObjectName(QString::fromUtf8("lineButton"));

        gridLayout->addWidget(lineButton, 1, 0, 1, 1);

        barButton = new QPushButton(OpenChart_demoClass);
        barButton->setObjectName(QString::fromUtf8("barButton"));

        gridLayout->addWidget(barButton, 1, 1, 1, 1);

        pieButton = new QPushButton(OpenChart_demoClass);
        pieButton->setObjectName(QString::fromUtf8("pieButton"));

        gridLayout->addWidget(pieButton, 1, 2, 1, 1);

        scatterButton = new QPushButton(OpenChart_demoClass);
        scatterButton->setObjectName(QString::fromUtf8("scatterButton"));

        gridLayout->addWidget(scatterButton, 1, 3, 1, 1);

        d3BarButton = new QPushButton(OpenChart_demoClass);
        d3BarButton->setObjectName(QString::fromUtf8("d3BarButton"));

        gridLayout->addWidget(d3BarButton, 2, 0, 1, 1);

        heatmapButton = new QPushButton(OpenChart_demoClass);
        heatmapButton->setObjectName(QString::fromUtf8("heatmapButton"));

        gridLayout->addWidget(heatmapButton, 2, 1, 1, 1);

        reloadButton = new QPushButton(OpenChart_demoClass);
        reloadButton->setObjectName(QString::fromUtf8("reloadButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(reloadButton->sizePolicy().hasHeightForWidth());
        reloadButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(reloadButton, 2, 2, 1, 1);

        exitButton = new QPushButton(OpenChart_demoClass);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        sizePolicy2.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(exitButton, 2, 3, 1, 1);

        QWidget::setTabOrder(lineButton, barButton);
        QWidget::setTabOrder(barButton, pieButton);
        QWidget::setTabOrder(pieButton, scatterButton);
        QWidget::setTabOrder(scatterButton, d3BarButton);
        QWidget::setTabOrder(d3BarButton, heatmapButton);
        QWidget::setTabOrder(heatmapButton, reloadButton);
        QWidget::setTabOrder(reloadButton, exitButton);

        retranslateUi(OpenChart_demoClass);
        QObject::connect(exitButton, SIGNAL(clicked()), OpenChart_demoClass, SLOT(close()));

        QMetaObject::connectSlotsByName(OpenChart_demoClass);
    } // setupUi

    void retranslateUi(QWidget *OpenChart_demoClass)
    {
        OpenChart_demoClass->setWindowTitle(QCoreApplication::translate("OpenChart_demoClass", "OpenChart_demo", nullptr));
        lineButton->setText(QCoreApplication::translate("OpenChart_demoClass", "\346\212\230\347\272\277\345\233\276", nullptr));
        barButton->setText(QCoreApplication::translate("OpenChart_demoClass", "\346\237\261\347\212\266\345\233\276", nullptr));
        pieButton->setText(QCoreApplication::translate("OpenChart_demoClass", "\351\245\274\345\233\276", nullptr));
        scatterButton->setText(QCoreApplication::translate("OpenChart_demoClass", "\346\225\243\347\202\271\345\233\276", nullptr));
        d3BarButton->setText(QCoreApplication::translate("OpenChart_demoClass", "3D\346\237\261\347\212\266\345\233\276", nullptr));
        heatmapButton->setText(QCoreApplication::translate("OpenChart_demoClass", "\347\203\255\345\212\233\345\233\276", nullptr));
        reloadButton->setText(QCoreApplication::translate("OpenChart_demoClass", "\345\210\267\346\226\260", nullptr));
        exitButton->setText(QCoreApplication::translate("OpenChart_demoClass", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenChart_demoClass: public Ui_OpenChart_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENCHART_DEMO_H
