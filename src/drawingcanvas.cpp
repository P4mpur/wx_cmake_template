#include "drawingcanvas.h"
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

DrawingCanvas::DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) : wxWindow(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
}

DrawingCanvas::~DrawingCanvas()
{
}

void DrawingCanvas::OnPaint(wxPaintEvent &evt)
{

    wxAutoBufferedPaintDC dc(this);

    dc.Clear();

    // inherited from wxGraphicsObject(wxObject)
    // more info on https://docs.wxwidgets.org/latest/classwx_graphics_context.html
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        // rectOrigin, where it begins, and rect Size what size is it from there
        wxPoint rectOrigin = this->FromDIP(wxPoint(189, 200));
        wxSize rectSize = this->FromDIP(wxSize(100, 80));

        gc->SetBrush(*wxRED_BRUSH);
        gc->DrawRectangle(rectOrigin.x, rectOrigin.y, rectSize.GetWidth(), rectSize.GetHeight());

        gc->SetFont(*wxNORMAL_FONT, *wxWHITE);
        wxString text = "Kompir";

        double textWidth, textHeight;
        gc->GetTextExtent(text, &textWidth, &textHeight);

        // calculation made so text is in the middle, **nothing to see here
        gc->DrawText(text, rectOrigin.x + rectSize.GetWidth() / 2.0 - textWidth / 2.0, rectOrigin.y + rectSize.GetHeight() / 2.0 - textHeight / 2.0);

        delete gc;
    }
}
