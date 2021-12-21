#pragma once
#include "stdafx.h"

class IComponent
{
public:
	IComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform)
		: tool(tool), actor(actor), transform(transform) {};
	virtual ~IComponent() = default;

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	auto GetActor() const -> Actor* { return actor; }
	auto GetTransform() const -> TransformComponent* { return transform; }

	auto IsEnable() { return is_enabled; }
	void SetEnable(const bool& is_enabled) { this->is_enabled = is_enabled; }

protected:
	class Tool* tool = nullptr;
	class Actor* actor = nullptr;
	class TransformComponent* transform = nullptr;
	bool is_enabled = true;
};