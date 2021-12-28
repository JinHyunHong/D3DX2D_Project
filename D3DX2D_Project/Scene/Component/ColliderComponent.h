#pragma once
#include "IRendererComponent.h"

class ColliderComponent :
	public IRendererComponent
{
public:
	ColliderComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~ColliderComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

	bool IsCollision(class Actor* const dest);

	auto GetOffsetScale() -> const D3DXVECTOR3 { return offset_scale; }
	void SetOffsetScale(const D3DXVECTOR3& offset_scale) { this->offset_scale = offset_scale; }

	auto GetOffsetPosition() -> const D3DXVECTOR3 { return offset_position; }
	void SetOffsetPosition(const D3DXVECTOR3& offset_position) { this->offset_position = offset_position; }

	bool GetOverlapActor(const std::string& name);
	auto GetOverlapActor_back() -> class Actor* const;
	void ClearOverlapActors();

	void AddOverlapActor(class Actor* const dest);

private:
	std::vector<class Actor*> overlap_actors;
	D3DXVECTOR3 offset_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 offset_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};