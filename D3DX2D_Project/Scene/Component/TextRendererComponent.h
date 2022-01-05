#pragma once
#include "IComponent.h"

struct TextRenderInfo final
{
	TextRenderInfo() = default;
	TextRenderInfo(const std::string& text, const D3DXCOLOR& color,
		const D3DXVECTOR2& scale , const D3DXVECTOR2& offset_position) :
		text(text), color(color), scale(scale), offset_position(offset_position) {}

	std::string text{""};
	D3DXCOLOR color{0.0f, 0.0f, 0.0f, 0.0f};
	D3DXVECTOR2 scale{ 1.0f, 1.0f };
	D3DXVECTOR2 offset_position{0.0f, 0.0f};
};

class TextRendererComponent :
	public IComponent
{
public:
	TextRendererComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~TextRendererComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

private:
	using text_pointer = std::shared_ptr<TextRenderInfo>;

public:
	void AddText(const std::string& name, const std::string& text, const D3DXCOLOR& color,
		const D3DXVECTOR2& scale = D3DXVECTOR2(1.0f, 1.0f), 
		const D3DXVECTOR2& offset_position = D3DXVECTOR2(0.0f, 0.0f));
	auto GetText(const std::string& text) -> const text_pointer;
	auto GetTexts() const -> const std::unordered_map<std::string, text_pointer>& { return texts; }

private:
	std::unordered_map<std::string, text_pointer> texts;
};