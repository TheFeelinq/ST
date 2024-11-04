#include "SilkroadWeb.h"
#include "Rebot.h"
typedef long (CALLBACK* EmbedBrowserObjectPtr)(HWND);
typedef void (CALLBACK* ResizeBrowserPtr)(HWND, DWORD, DWORD);
typedef long (CALLBACK* DisplayHTMLPagePtr)(HWND, const char *);
extern HWND g_orig_wndproc_hwnd;

void SilkroadWeb::Start(int X, int Y, int Width, int Height,const std::string& url)
{
    m_Width = Width, m_Height = Height;

    HMODULE hModule = LoadLibrary("srwb.dll");
    EmbedBrowserObjectPtr create_obj;
    ResizeBrowserPtr resize_browser;
    DisplayHTMLPagePtr display_html;
    if (hModule)
    {
        create_obj = (EmbedBrowserObjectPtr)GetProcAddress(hModule, "EmbedBrowserObject");
        resize_browser = (ResizeBrowserPtr)GetProcAddress(hModule, "ResizeBrowser");
        display_html = (DisplayHTMLPagePtr)GetProcAddress(hModule, "DisplayHTMLPage");
        if (create_obj)
        {
            m_hMDIClient = CreateWindow(TEXT("STATIC"), TEXT("Ranking"), WS_CHILD,
                                        X, Y, Width, Height, Rebot::GameHWND, NULL, NULL, NULL);

            create_obj(m_hMDIClient);
            resize_browser(m_hMDIClient, Width, Height);
            display_html(m_hMDIClient, url.c_str());
            ShowWindow(m_hMDIClient, SW_SHOW);
            UpdateWindow(m_hMDIClient);

        }
        else
            FreeLibrary(hModule);
    }
}

void SilkroadWeb::Update(int X, int Y)
{
    SetWindowPos(m_hMDIClient, 0, X, Y, m_Width, m_Height, NULL);
    UpdateWindow(m_hMDIClient);
}

void SilkroadWeb::Close()
{
    SendMessage(m_hMDIClient, WM_CLOSE, NULL, NULL);
}
