#pragma once

#include "NIFFrame.h"
#include "NIFStatic.h"
#include "IFCloseButton.h"
#include "NIFDragableArea.h"

class CNIFMainFrame : public CNIFFrame {
GFX_DECLARE_DYNAMIC_EXISTING(CNIFMainFrame, 0x115DFA8)

GFX_DECLARE_MESSAGE_MAP(CNIFMainFrame)
    CNIFStatic *m_title;
public:
    /// \address 00816F20
    CNIFMainFrame();

    // Destructor is trivial
    // \address 00816F60
    // ~CIFMainFrame();

    /// \address 00479a50
    bool OnCreate(long ln) override;

    /// \address 00479dd0
    void SetGWndSize(int width, int height) override;

    /// \address 0046c2f0
    bool SetText(const wchar_t *src) override;

private:
    void OnClick_Exit();

public:
    //0x07B0
    CNIFDragableArea *m_handleBar; //0x07B4
    CIFCloseButton *m_close; //0x07B8

BEGIN_FIXTURE()
        ENSURE_SIZE(0x798)
        ENSURE_OFFSET(m_title, 0x78C)
        ENSURE_OFFSET(m_handleBar, 0x790)
        ENSURE_OFFSET(m_close, 0x794)
    END_FIXTURE()

    RUN_FIXTURE(CNIFMainFrame)
};
