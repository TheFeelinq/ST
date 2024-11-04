#pragma once

#include "NIFWnd.h"

class CNIFStatic : public CNIFWnd { // 872 bytes
GFX_DECLARE_DYNAMIC_EXISTING(CNIFStatic, 0x115E090)
public:
	virtual void SetText(wchar_t* format, ...);
	char pad[32];
	
};
