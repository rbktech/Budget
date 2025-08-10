#include "mainframe.h"

#include <QVBoxLayout>

#include "graphdata.h"

CMainFrame::CMainFrame()
    : QMainWindow()
{
    this->setWindowTitle("Budget " + QString(VERSION));

    mCentralWidget = new QWidget(this);

    mCount = 0;

    mLabel = new QLabel("Лейбл", mCentralWidget);
    mButton = new QPushButton("Кнопка", mCentralWidget);

    mGraphData = new CGraphData(mCentralWidget);

    QVBoxLayout* mainBox = new QVBoxLayout(mCentralWidget);

    mainBox->addWidget(mLabel);
    mainBox->addWidget(mButton);
    mainBox->addWidget(mGraphData);

    this->setCentralWidget(mCentralWidget);

    this->setMinimumSize(1500, 900);

    connect(mButton,  &QAbstractButton::clicked, this, &CMainFrame::OnPushButton);
}

CMainFrame::~CMainFrame()
{

}

void CMainFrame::OnPushButton()
{
    // mLabel->setText(QString::number(mCount++));

    mGraphData->SetValue();
}

long long CMainFrame::getTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
}