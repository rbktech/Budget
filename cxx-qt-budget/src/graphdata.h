#pragma once

#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QDateTime>
#include <QStackedBarSeries>

#include <sys/types.h>

using namespace QtCharts;

class CGraphData : public QChartView
{
private:
    QChart* mChart;
    QStackedBarSeries* mSeries;

    QDateTimeAxis* mAxisX;

    QWidget* mParent;

public:
    explicit CGraphData(QWidget* parent)
        : QChartView(parent)
    {
        mParent = parent;

        mChart = new QChart();

        mSeries = new QStackedBarSeries();

        QBarSet* set0 = new QBarSet("Jane");
        // QBarSet* set1 = new QBarSet("John");

        mSeries->setBarWidth(1);

        mChart->setTitle("Simple barchart example");
        mChart->setAnimationOptions(QChart::SeriesAnimations);

        /*mAxisX = new QDateTimeAxis;
        mAxisX->setTickCount(14);

        QDateTime startDateTime = QDateTime::currentDateTime();
        QDateTime endDateTime = startDateTime.addDays(7);

        mAxisX->setRange(startDateTime, endDateTime);

        // axisX->setRange(QDateTime(QDate(2025, 1 , 15), QTime(0, 0)), QDateTime(QDate(2025, 2, 15), QTime(0, 0)));
        // axisX->setFormat("MMM yyyy");
        mAxisX->setTitleText("Date");
        mChart->addAxis(mAxisX, Qt::AlignBottom);
        mSeries->attachAxis(mAxisX);*/

        QStringList categories;
        // categories << "1" << "2" << "3" << "4" << "5" << "6";

        {
            QVector<QStringList> tokens;

            ReadFile("../../res/data.csv", tokens);

            QDateTime dt = QDateTime::fromString(tokens[0][0], Qt::DateFormat::ISODate);
            QDate day = dt.date();
            int nDays = day.daysInMonth() + 1;
            QTime t = dt.time();
            int money = 0;

            for(int i = 1; i < nDays; i++) {

                /*QDate d = QDate(2025, i , 15);
                QDateTime dt = QDateTime(d, QTime(0,0));
                QString date = dt.toString("MMM\nyyyy");*/

                /*for(auto& p : tokens) {

                    QDate dd = QDateTime::fromString(tokens[0][0], Qt::DateFormat::ISODate).date();

                    int tt = dd.day();
                    if(tt == i) {
                        money += 1000;
                    }
                }*/

                set0->append(i);

                QString ss = QDateTime(QDate(day.year(), i, day.month()), t).toString("d dddd.M MMMM.yyyy");
                categories << QString::number(i);
            }
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        mChart->addAxis(axisX, Qt::AlignBottom);
        mSeries->attachAxis(axisX);

        QValueAxis* axisY = new QValueAxis();
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Sunspots count");
        mChart->addAxis(axisY, Qt::AlignLeft);
        mSeries->attachAxis(axisY);


        // *set0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11;
        // *set1 << 5 << 0 << 0 << 4 << 0 << 7;

        /*set0->insert(23423, 1);
        set0->insert(1, 2);
        set0->insert(2, 3);
        set0->insert(3, 4);
        set0->insert(15, 8);*/

        mSeries->append(set0);
        // mSeries->append(set1);
        // mSeries->append(set2);
        // mSeries->append(set3);
        // mSeries->append(set4);

        mChart->addSeries(mSeries);

        this->setChart(mChart);
    }

    ~CGraphData() override = default;

    void SetValue()
    {
        /*QBarSet *set0 = new QBarSet("Jane");
        QBarSet *set1 = new QBarSet("John");
        QBarSet *set2 = new QBarSet("Axel");
        QBarSet *set3 = new QBarSet("Mary");
        QBarSet *set4 = new QBarSet("Samantha");

        *set0 << 1 << 2 << 3 << 4 << 5 << 6;
        *set1 << 5 << 0 << 0 << 4 << 0 << 7;
        *set2 << 3 << 5 << 8 << 13 << 8 << 5;
        *set3 << 5 << 6 << 7 << 3 << 4 << 5;
        *set4 << 9 << 7 << 5 << 3 << 1 << 2;*/

        // mSeries->append(set0);
        // mSeries->append(set1);
        // mSeries->append(set2);
        // mSeries->append(set3);
        // mSeries->append(set4);

        // QDateTime startDateTime = QDateTime::currentDateTime();
        // QDateTime endDateTime = startDateTime.addDays(7 + 1);

        // mAxisX->setRange(startDateTime, endDateTime);
        // mAxisX->setTickCount(8);

        QBarSet* barSet = mSeries->barSets().at(0);

        // barSet->append(-2);
        // barSet->append(3);

        barSet->append(5);


        mChart->removeSeries(mSeries);

        mChart->addSeries(mSeries);

        int tg = mChart->series().count();

        // mChart->scroll(50, 0);


        barSet->replace(0, 12);

        int t = barSet->count();

        printf("");

        // mChart->scroll(10, 0);

        // mChart->zoom(0.5F);

        /*QRectF rect = mChart->plotArea();
        rect.setWidth(rect.width() - 10);
        mChart->setPlotArea(rect);*/

        // set0->append(1);

        /*QSizeF size = mChart->size();
        size.setWidth(size.width() - 10);
        mChart->resize(size);*/


        // mChart->setAutoFillBackground(true);
        // mChart->createDefaultAxes();

        // mChart->addSeries(mSeries);

        mChart->update();
        this->update();
        mParent->update();
    }

    void ReadFile(const QString& file, QVector<QStringList>& tokens);
};