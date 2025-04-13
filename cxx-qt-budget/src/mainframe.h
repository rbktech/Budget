#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include "graphdata.h"

class CMainFrame : public QMainWindow
{
    // Q_OBJECT

private:
    int mCount;

    CGraphData* mGraphData;

private:
    QWidget* mCentralWidget;

    QLabel* mLabel;
    QPushButton* mButton;

    long long getTime();

private slots:
    void OnPushButton();

public:
    CMainFrame();
    ~CMainFrame() override;
};