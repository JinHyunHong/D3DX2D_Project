#pragma once
#include "IComponent.h"

struct TextRenderInfo final
{
	TextRenderInfo() = default;
	TextRenderInfo(const std::string& text, const D3DXCOLOR& color, const D3DXVECTOR2& offset) :
		text(text), color(color), offset(offset) {}

	std::string text{""};
	D3DXCOLOR color{0.0f, 0.0f, 0.0f, 0.0f};
	D3DXVECTOR2 offset{0.0f, 0.0f};
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

	void AddText(const std::string& text, const D3DXCOLOR& color, const D3DXVECTOR2& offset = D3DXVECTOR2(0.0f, 0.0f));
	auto GetText(const std::string& text) -> const std::shared_ptr<TextRenderInfo>;
	auto GetTexts() const -> const std::vector<std::shared_ptr<TextRenderInfo>>& { return texts; }

private:
	std::vector<std::shared_ptr<TextRenderInfo>> texts;
};