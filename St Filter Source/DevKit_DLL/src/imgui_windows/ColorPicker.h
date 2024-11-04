#pragma once

#include <imgui/imgui.h>
#include <IFSTCustomTitle.h>
#include <IFflorian0Guide.h>
class ColorSelect {
public:
    void Render();
private:
    float m_color[3];
    bool interface_draw_outline;
    bool interface_draw_marker;
};
