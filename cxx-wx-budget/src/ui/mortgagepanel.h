#include <wx/grid.h>
#include <wx/panel.h>

class CMortgagePanel : public wxPanel
{
private:
    wxGrid* mGrid;

    void AddTimeCol();
    void AddWageCol();
    void AddIncWage();
    void AddTaxCol();
    void AddMortgageCol();

public:
    CMortgagePanel(wxWindow* parent);
    ~CMortgagePanel() = default;
};