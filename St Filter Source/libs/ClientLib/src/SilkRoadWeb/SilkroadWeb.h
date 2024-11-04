#ifndef C_SIMPLE_WEB_PAGE
#define C_SIMPLE_WEB_PAGE
#include "Process.h"
#include <IFWnd.h>

class SilkroadWeb
{
public:
    void Start(int X, int Y, int Width, int Height, const std::string& url);
    void Update(int X, int Y);
    void Close();
private:
    HWND m_hMDIClient;
    int m_Width;
    int m_Height;
};
#endif