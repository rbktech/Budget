#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/textctrl.h>

class CBanksPanel : public wxPanel
{
private:
    // Надстройка для wxWidgets-3.1.3, названия строк в таблице не удаляются правильно
    std::vector<wxString> m_rowLabel;

    wxGrid* m_grid;
    wxTextCtrl* m_usd;
    wxTextCtrl* m_eur;
    wxTextCtrl* m_budget;

    void OnAdditionBank(wxCommandEvent& event);
    void OnSubtractionBank(wxCommandEvent& event);
    void OnCalculate(wxCommandEvent& event);

public:
    CBanksPanel(wxWindow* parent);
    ~CBanksPanel() = default;
};