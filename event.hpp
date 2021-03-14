#pragma once
#include "DXUT.h"

enum class UI_CONTROL_ID : int {
    IDC_TOGGLEFULLSCREEN = 0,

    IDC_STATIC,
};

void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContexts);