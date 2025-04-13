#include "mortgagepanel.h"

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/time.h>

#include "utils/utils.h"

CMortgagePanel::CMortgagePanel(wxWindow* parent)
    : wxPanel(parent)
{
    mGrid = new wxGrid(this, NewControlId());
    mGrid->CreateGrid(0, 0, wxGrid::wxGridSelectRows);
    mGrid->HideRowLabels();

    wxBoxSizer* mainBox = new wxBoxSizer(wxVERTICAL);
    mainBox->Add(mGrid, 1, wxEXPAND);
    this->SetSizerAndFit(mainBox);

    AddTimeCol();
    AddWageCol();
    AddIncWage();
    AddTaxCol();
    AddMortgageCol();
}

void CMortgagePanel::AddMortgageCol()
{
    double interest_rate = 5.00;
    double count_month = 360.0;
    double body = 8000000.0;

    int colBody = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(colBody, wxT("Body"));
    int colPercent = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(colPercent, wxT("Percent"));

    int colMonth = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(colMonth, wxT("Month"));

    int colBodyTotal = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(colBodyTotal, wxT("Body\nTotal"));

    int colPercentTotal = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(colPercentTotal, wxT("Percent\nTotal"));

    double bodyTotal = 0.0;
    double percentTotal = 0.0;
    // double repayment = 100000.0;
    double repayment = 0.0;

    for(int i = 0; i < 360; i++) {

        if(mGrid->GetNumberRows() == i)
            mGrid->AppendRows();

        double annuity = CUtils::annuity(body -= repayment, interest_rate, count_month);
        double bodyMonth = CUtils::body_month(annuity, interest_rate, count_month, i + 1);
        double percentMonth = CUtils::percent_month(annuity, interest_rate, count_month, i + 1);

        if(bodyMonth < 0 && percentMonth < 0)
            break;

        mGrid->SetCellValue(i, colBody, CUtils::formatMoney(bodyMonth));
        mGrid->SetCellAlignment(i, colBody, wxALIGN_CENTER, wxALIGN_CENTER);

        mGrid->SetCellValue(i, colPercent, CUtils::formatMoney(percentMonth));
        mGrid->SetCellAlignment(i, colPercent, wxALIGN_CENTER, wxALIGN_CENTER);

        mGrid->SetCellValue(i, colMonth, CUtils::formatMoney(bodyMonth + percentMonth));
        mGrid->SetCellAlignment(i, colMonth, wxALIGN_CENTER, wxALIGN_CENTER);

        mGrid->SetCellValue(i, colBodyTotal, CUtils::formatMoney(bodyTotal += bodyMonth + repayment));
        mGrid->SetCellAlignment(i, colBodyTotal, wxALIGN_CENTER, wxALIGN_CENTER);

        mGrid->SetCellValue(i, colPercentTotal, CUtils::formatMoney(percentTotal += percentMonth));
        mGrid->SetCellAlignment(i, colPercentTotal, wxALIGN_CENTER, wxALIGN_CENTER);
    }
}

void CMortgagePanel::AddWageCol()
{
    double wage = 100000;

    int cols = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(cols, wxT("Wage"));

    if(mGrid->GetNumberRows() == 0)
        mGrid->AppendRows();

    mGrid->SetCellValue(0, cols, wxString::Format(wxT("%.2f"), wage));
    mGrid->SetCellAlignment(0, cols, wxALIGN_CENTER, wxALIGN_CENTER);
}

void CMortgagePanel::AddTaxCol()
{
    wxString sWage;
    double dWage = 0.0;

    int iColWage = -1;
    int nCol = mGrid->GetNumberCols();
    int nRow = mGrid->GetNumberRows();

    for(int iCol = 0; iCol < nCol; iCol++) {
        if(mGrid->GetColLabelValue(iCol) == wxT("Wage"))
            iColWage = iCol;
    }

    if(iColWage == -1)
        return;

    int iColTax = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(iColTax, "Tax");

    for(int iRow = 0; iRow < nRow; iRow++) {

        sWage = mGrid->GetCellValue(iRow, iColWage);
        sWage.ToDouble(&dWage);

        if(dWage > 200000.0)
            dWage *= 0.85;
        else
            dWage *= 0.87;

        sWage = CUtils::formatMoney(dWage);

        mGrid->SetCellValue(iRow, iColTax, sWage);
        mGrid->SetCellAlignment(iRow, iColTax, wxALIGN_CENTER, wxALIGN_CENTER);
    }
}

void CMortgagePanel::AddIncWage()
{
    wxString sCurrDate;
    wxString sNextDate;

    int iColDate = -1;
    int iColWage = -1;
    int nCol = mGrid->GetNumberCols();
    int nRow = mGrid->GetNumberRows();

    for(int iCol = 0; iCol < nCol; iCol++) {
        if(mGrid->GetColLabelValue(iCol) == wxT("Wage"))
            iColWage = iCol;
        if(mGrid->GetColLabelValue(iCol) == wxT("Date"))
            iColDate = iCol;
    }

    if(iColDate == -1 || iColWage == -1)
        return;

    double dWage = 0.0;
    const double dIncWage = 0.0;
    wxString sWage = mGrid->GetCellValue(0, iColWage);
    sWage.ToDouble(&dWage);

    wxDateTime datetime = wxDateTime::Today();
    datetime.SetDay(1);
    datetime.SetMonth(wxDateTime::Jan);
    datetime += wxDateSpan::Year();
    sNextDate = datetime.Format("%d.%m.%Y");

    for(int iRow = 0; iRow < nRow; iRow++) {
        sCurrDate = mGrid->GetCellValue(iRow, iColDate);
        if(sCurrDate == sNextDate) {
            mGrid->SetCellValue(iRow, iColWage, wxString::Format(wxT("%.2f"), dWage += dIncWage));
            mGrid->SetCellAlignment(iRow, iColWage, wxALIGN_CENTER, wxALIGN_CENTER);
            datetime += wxDateSpan::Year();
            sNextDate = datetime.Format("%d.%m.%Y");
            for(int iCol = 0; iCol < nCol; iCol++)
                mGrid->SetCellBackgroundColour(iRow, iCol, *wxGREEN);

        } else {
            mGrid->SetCellValue(iRow, iColWage, wxString::Format(wxT("%.2f"), dWage));
            mGrid->SetCellAlignment(iRow, iColWage, wxALIGN_CENTER, wxALIGN_CENTER);
            if(iRow != 0)
                mGrid->SetCellTextColour(iRow, iColWage, *wxWHITE);
        }
    }
}

void CMortgagePanel::AddTimeCol()
{
    wxString sDate;
    wxDateTime datetime = wxDateTime::Today();

    datetime.SetDay(1);

    int cols = mGrid->GetNumberCols();
    mGrid->AppendCols();
    mGrid->SetColLabelValue(cols, "Date");

    for(int i = 0; i < 360; i++) {

        sDate = datetime.Format("%d.%m.%Y");

        if(mGrid->GetNumberRows() == i)
            mGrid->AppendRows();

        mGrid->SetCellValue(i, cols, sDate);
        mGrid->SetCellAlignment(i, cols, wxALIGN_CENTER, wxALIGN_CENTER);

        datetime += wxDateSpan::Month();
    }
}