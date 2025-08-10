#include <wx/app.h>

#include "ui/mainframe.h"

class wxMiniApp : public wxApp
{
public:
    bool OnInit() override
    {
        return (new CMainFrame())->Show();
    }
};

IMPLEMENT_APP(wxMiniApp)