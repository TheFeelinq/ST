#include "DrawingHelpers.h"

#include "GFXVideo3d.h"


// I feel guilty for this function, sorry. I couldn't figure out how to do this with DirectX :(
void rotatey(D3DXVECTOR3& vec, float radiant)
{
	float x = cos(radiant) * vec.x + sin(radiant) * vec.z;
	float y = vec.y;
	float z = -sin(radiant) * vec.x + cos(radiant) * vec.z;

	vec.x = x;
	vec.y = y;
	vec.z = z;
}
void Line3D(const D3DVECTOR& p1, const D3DVECTOR& p2, D3DCOLOR color, float width)
{
    D3DVECTOR p12d, p22d;

    CGFXVideo3d* gfx = CGFXVideo3d::get();
    bool vis1 = gfx->Project(p1, p12d) > 0;
    bool vis2 = gfx->Project(p2, p22d) > 0;

    if (vis1 && vis2)
    {
        DXDrawLine(p12d.x, p12d.y, p22d.x, p22d.y, color, width);
    }
}