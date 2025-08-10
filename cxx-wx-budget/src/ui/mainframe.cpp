#include "mainframe.h"
// #include <sorting.h>

#include <wx/textctrl.h>

#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include <vector>

#include "bankspanel.h"
#include "mortgagepanel.h"

#define WIDTH 300
#define HEIGHT 170

#define DEF_RECT wxDefaultPosition, wxDefaultSize

CMainFrame::CMainFrame()
    : wxFrame(nullptr, wxID_ANY, wxT("Расчет бюджета"))
{
    SetIcon(wxICON(coins));
    this->SetBackgroundColour(*wxWHITE);

    mNotebook = new wxNotebook(this, NewControlId(), wxDefaultPosition, wxSize(800, 400));
    mNotebook->AddPage(new CMortgagePanel(mNotebook), "Mortgage");
    mNotebook->AddPage(new CBanksPanel(mNotebook), "Banks");

    wxBoxSizer* mainBox = new wxBoxSizer(wxVERTICAL);
    mainBox->Add(mNotebook, 1, wxEXPAND);
    this->SetSizerAndFit(mainBox);
}