#include "stdafx.h"
#include "ID3D11.h"

ID3D11::ID3D11(D3D11_Base* const base)
{
	id = GUID_Creator::CreateID(); 
	device = base->GetDevice(); 
	device_context = base->GetDeviceContext();
}
