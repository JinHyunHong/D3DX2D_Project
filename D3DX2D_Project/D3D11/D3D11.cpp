#include "stdafx.h"
#include "D3D11.h"

D3D11::D3D11(D3D11_Base* const base)
{
	device = base->GetDevice(); 
	device_context = base->GetDeviceContext();
}
