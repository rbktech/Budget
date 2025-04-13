#pragma once

#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/notebook.h>

#include <vector>

class CMainFrame : public wxFrame
{
private:
    wxNotebook* mNotebook;

public:
    CMainFrame();
    ~CMainFrame() override = default;
};