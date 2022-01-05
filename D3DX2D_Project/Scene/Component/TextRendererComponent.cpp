#include "stdafx.h"
#include "TextRendererComponent.h"

TextRendererComponent::TextRendererComponent(Tool* const tool, Actor* const actor,
	TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
}

bool TextRendererComponent::Initialize()
{
	return true;
}

void TextRendererComponent::Update()
{
}

void TextRendererComponent::Destroy()
{
}

void TextRendererComponent::AddText(const std::string& name, const std::string& text, const D3DXCOLOR& color,
	const D3DXVECTOR2& scale, const D3DXVECTOR2& offset_position)
{
	if (text.empty() || GetText(name))
		return;

	texts[name] = std::make_shared<TextRenderInfo>(text, color, scale, offset_position);
}

auto TextRendererComponent::GetText(const std::string& name) -> const text_pointer
{
	if (texts.find(name) != texts.end())
		return texts[name];
	
	return nullptr;
}
