#include "bankspanel.h"

#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/icon.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textdlg.h>

#define DEF_RECT wxDefaultPosition, wxDefaultSize
#define POINT_AND_SIZE wxDefaultPosition, wxSize(31, 31)

CBanksPanel::CBanksPanel(wxWindow* parent)
    : wxPanel(parent)
{
    m_usd = new wxTextCtrl(this, NewControlId(), wxT("73.94"), DEF_RECT, wxBORDER_NONE);
    m_eur = new wxTextCtrl(this, NewControlId(), wxT("80.11"), DEF_RECT, wxBORDER_NONE);
    m_budget = new wxTextCtrl(this, NewControlId(), wxT("0.00"), DEF_RECT, wxTE_READONLY | wxTE_CENTRE | wxBORDER_NONE);
    m_budget->SetBackgroundColour(*wxWHITE);

    wxBitmapButton* addBank = new wxBitmapButton(this, NewControlId(), wxICON(add), POINT_AND_SIZE);
    wxBitmapButton* minusBank = new wxBitmapButton(this, NewControlId(), wxICON(minus), POINT_AND_SIZE);

    wxButton* calculate = new wxButton(this, NewControlId(), wxT("Рассчитать"));

    m_grid = new wxGrid(this, NewControlId());
    m_grid->CreateGrid(0, 3, wxGrid::wxGridSelectRows);

    m_grid->SetColLabelValue(0, wxT("Рубли"));
    m_grid->SetColLabelValue(1, wxT("Доллары"));
    m_grid->SetColLabelValue(2, wxT("Евро"));

    wxBoxSizer* hBox = nullptr;
    wxStaticBoxSizer* stBox = nullptr;
    wxBoxSizer* mainBox = new wxBoxSizer(wxVERTICAL);

    hBox = new wxBoxSizer(wxHORIZONTAL);
    hBox->Add(addBank, 0, wxALIGN_BOTTOM);
    hBox->Add(minusBank, 0, wxALIGN_BOTTOM);

    stBox = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Курс доллара"));
    stBox->Add(m_usd);
    hBox->Add(stBox);

    stBox = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Курс евро"));
    stBox->Add(m_eur);
    hBox->Add(stBox);

    hBox->Add(calculate, 0, wxALIGN_CENTER_VERTICAL);

    mainBox->Add(hBox);

    wxBoxSizer* v_box = new wxBoxSizer(wxVERTICAL);
    v_box->Add(
        new wxStaticText(this, NewControlId(), wxT("Бюджет")), 0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL);
    v_box->Add(m_budget);

    hBox = new wxBoxSizer(wxHORIZONTAL);
    hBox->Add(m_grid);
    hBox->Add(v_box);
    mainBox->Add(hBox);

    this->SetSizerAndFit(mainBox);

    Bind(wxEVT_BUTTON, &CBanksPanel::OnAdditionBank, this, addBank->GetId());
    Bind(wxEVT_BUTTON, &CBanksPanel::OnSubtractionBank, this, minusBank->GetId());
    Bind(wxEVT_BUTTON, &CBanksPanel::OnCalculate, this, calculate->GetId());
}

void CBanksPanel::OnCalculate(wxCommandEvent& event)
{
    double result = 0;
    double coefficient[3] = { 1 };

    m_usd->GetValue().ToDouble(&coefficient[1]);
    m_eur->GetValue().ToDouble(&coefficient[2]);

    int countRow = m_grid->GetNumberRows();
    int countCol = m_grid->GetNumberCols();

    for(int col = 0; col < countCol; col++) {
        for(int row = 0; row < countRow; row++) {
            double t_value = 0;
            m_grid->GetCellValue(row, col).ToDouble(&t_value);
            result += t_value * coefficient[col];
        }
    }

    m_budget->SetValue(wxString::Format(wxT("%.2f"), result));
}

void CBanksPanel::OnAdditionBank(wxCommandEvent& event)
{
    wxTextEntryDialog dlg(this, wxT("Ввод имени банка"), wxT("Имя нового банка"));
    if(dlg.ShowModal() == wxID_OK) {
        wxString t_str = dlg.GetValue();
        if(t_str.empty() == false) {
            m_grid->AppendRows();
            m_grid->SetRowLabelValue(m_grid->GetNumberRows() - 1, t_str);
            m_rowLabel.push_back(t_str); // wxWidgets-3.1.3
            this->Fit();
        }
    }
}

void CBanksPanel::OnSubtractionBank(wxCommandEvent& event)
{
    if(m_grid->GetNumberRows() != 0) {
        wxArrayInt arrayNumberRows = m_grid->GetSelectedRows();
        if(arrayNumberRows.empty() == false) {

            wxString message;
            wxString caption;
            int size = arrayNumberRows.size();

            if(size == 1) {
                wxString t_str = m_grid->GetRowLabelValue(arrayNumberRows.front());
                message = wxString::Format(wxT("Удалить %S?"), t_str);
                caption = wxT("Удаление элемента таблицы");
            } else {
                // BubbleSort(&arrayNumberRows[0], size - 1);
                message = wxT("Удалить элементы таблицы?");
                caption = wxT("Удаление элементов таблицы");
            }

            wxMessageDialog dlg(this, message, caption, wxOK | wxCANCEL);
            if(dlg.ShowModal() == wxID_OK) {
                for(auto& p : arrayNumberRows) {
                    m_rowLabel.erase(m_rowLabel.begin() + p); // wxWidgets-3.1.3
                    m_grid->DeleteRows(p);
                }

                int i = 0;                            // wxWidgets-3.1.3
                for(auto& l : m_rowLabel)             //
                    m_grid->SetRowLabelValue(i++, l); //

                this->Fit();
            }
        } else
            wxMessageBox(wxT("Нет выбранного элемента таблицы для удаления"));
    } else
        wxMessageBox(wxT("Нет элементов таблицы для удаления"));
}