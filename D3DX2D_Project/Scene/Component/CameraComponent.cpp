#include "stdafx.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

CameraComponent::CameraComponent(Tool* const tool, Actor* const actor, TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
}

bool CameraComponent::Initialize()
{
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&proj);

	UpdateViewMatrix();
	UpdateProjectionMatrix();

	return true;
}

void CameraComponent::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void CameraComponent::Destroy()
{
}

void CameraComponent::UpdateViewMatrix()
{
	auto position = transform->GetPosition();
	auto forward = transform->GetForward();
	auto up = transform->GetUp();

	D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
}

void CameraComponent::UpdateProjectionMatrix()
{
	D3DXMatrixOrthoLH(&proj, static_cast<float>(Core::GetInst().GetWidth()),
		static_cast<float>(Core::GetInst().GetHeight()), 0, 1);
}
