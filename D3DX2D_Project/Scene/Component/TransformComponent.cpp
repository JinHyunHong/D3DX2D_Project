#include "stdafx.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(Tool* const tool, Actor* const actor, TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
	D3DXMatrixIdentity(&local);
	D3DXMatrixIdentity(&world);
	UpdateTransform();
}

bool TransformComponent::Initialize()
{
	return true;
}

void TransformComponent::Update()
{
}

void TransformComponent::Destroy()
{
}

void TransformComponent::SetLocalScale(const D3DXVECTOR3& scale)
{
	if (this->local_scale == scale)
		return;

	this->local_scale = scale;
	UpdateTransform();
}

void TransformComponent::SetLocalPosition(const D3DXVECTOR3& position)
{
	if (this->local_position == position)
		return;

	this->local_position = position;
	UpdateTransform();
}

void TransformComponent::SetLocalRotation(const D3DXVECTOR3& rotation)
{
	if (this->local_rotation == rotation)
		return;

	this->local_rotation = rotation;
	UpdateTransform();
}

auto TransformComponent::GetScale() -> const D3DXVECTOR3
{
	D3DXVECTOR3 world_scale;

	D3DXMatrixDecompose(&world_scale, &D3DXQUATERNION(), &D3DXVECTOR3(), &world);

	return world_scale;
}

void TransformComponent::SetScale(const D3DXVECTOR3& world_scale)
{
	if (GetScale() == world_scale)
		return;

	if (HasParent())
	{
		D3DXVECTOR3 scale;
		D3DXVECTOR3 parent_scale = parent->GetScale();
		scale.x = world_scale.x / parent_scale.x;
		scale.y = world_scale.y / parent_scale.y;
		scale.z = world_scale.z / parent_scale.z;

		SetLocalScale(scale);
	}

	else
		SetLocalScale(world_scale);
}

auto TransformComponent::GetPosition() -> const D3DXVECTOR3
{
	D3DXVECTOR3 world_postion;

	D3DXMatrixDecompose(&D3DXVECTOR3(), &D3DXQUATERNION(), &world_postion, &world);

	return world_postion;
}

void TransformComponent::SetPosition(const D3DXVECTOR3& world_position)
{
	if (GetPosition() == world_position)
		return;

	if (HasParent())
	{
		D3DXMATRIX inverse;
		D3DXMatrixInverse(&inverse, nullptr, &parent->GetWorldMatrix());
		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position, &world_position, &inverse);
		SetLocalScale(position);
	}

	else
		SetLocalScale(world_position);
}

auto TransformComponent::GetRotation() -> const D3DXVECTOR3
{
	D3DXQUATERNION world_rotation;
	D3DXMatrixDecompose(&D3DXVECTOR3(), &world_rotation, &D3DXVECTOR3(), &world);

	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, &world_rotation);

	return D3DXVECTOR3
	(
		atan2(rotation._31, rotation._33),
		static_cast<float>(atan2(-rotation._32, sqrt(pow(rotation._12, 2) + pow(rotation._22, 2)))),
		atan2(rotation._12, rotation._22)
	);
}

void TransformComponent::SetRotation(const D3DXVECTOR3& world_rotation)
{
	if (GetRotation() == world_rotation)
		return;

	if (HasParent())
	{
		D3DXMATRIX inverse;
		D3DXMatrixInverse(&inverse, nullptr, &GetWorldRotationMatrix());
		D3DXVECTOR3 rotation;
		D3DXVec3TransformNormal(&rotation, &world_rotation, &inverse);
		SetLocalScale(rotation);
	}

	else
		SetLocalScale(world_rotation);
}

auto TransformComponent::GetWorldRotationMatrix() const -> const D3DXMATRIX
{
	D3DXQUATERNION world_rotation;
	D3DXMatrixDecompose(&D3DXVECTOR3(), &world_rotation, &D3DXVECTOR3(), &world);

	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, &world_rotation);

	return rotation;
}

auto TransformComponent::GetRight() const -> const D3DXVECTOR3
{
	D3DXVECTOR3 right;
	D3DXVec3TransformNormal(&right, &D3DXVECTOR3(1, 0, 0), &world);
	return right;
}

auto TransformComponent::GetUp() const -> const D3DXVECTOR3
{
	D3DXVECTOR3 up;
	D3DXVec3TransformNormal(&up, &D3DXVECTOR3(0, 1, 0), &world);
	return up;
}

auto TransformComponent::GetForward() const -> const D3DXVECTOR3
{
	D3DXVECTOR3 forward;
	D3DXVec3TransformNormal(&forward, &D3DXVECTOR3(0, 0, 1), &world);
	return forward;
}

void TransformComponent::SetParent(TransformComponent* const new_parent)
{
	parent = new_parent;

	new_parent->AddChild(this);
}

auto TransformComponent::GetChildFromIndex(const uint& index) -> TransformComponent* const
{
	if (HasChilds())
		return nullptr;

	if (index >= GetChildCount())
		return nullptr;

	return childs[index];
}

void TransformComponent::AddChild(TransformComponent* const child)
{
	childs.emplace_back(child);
}

void TransformComponent::UpdateTransform()
{
	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, local_scale.x, local_scale.y, local_scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, local_rotation.y, local_rotation.x, local_rotation.z);
	D3DXMatrixTranslation(&T, local_position.x, local_position.y, local_position.z);

	local = S * R * T;

	if (HasParent())
		world = local * parent->GetWorldMatrix();
	else
		world = world;

	for (const auto& child : childs)
		child->UpdateTransform();
}
