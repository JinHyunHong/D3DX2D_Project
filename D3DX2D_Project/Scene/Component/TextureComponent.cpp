#include "stdafx.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent(Tool* const tool, Actor* const actor, TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
}

bool TextureComponent::Initialize()
{
	return true;
}

void TextureComponent::Update()
{
}

void TextureComponent::Destroy()
{
	textures.clear();
}

auto TextureComponent::GetCurrentTexture() const -> const texture_pointer
{
	return current_texture.expired() ? nullptr : current_texture.lock();
}

void TextureComponent::SetCurrentTexture(const std::string& texture_name)
{
	assert(textures.find(texture_name) != textures.end());

	current_texture = textures[texture_name];
}

void TextureComponent::AddTexture(const std::string& texture_name, const texture_pointer& texture)
{
	assert(textures.find(texture_name) == textures.end());

	textures[texture_name] = texture;
}

void TextureComponent::AddTexture(const std::string& path)
{
	auto resource_manager = tool->GetManager<ResourceManager>();
	auto texture = resource_manager->Load<Texture>(path);

	if (!texture)
		assert(false);

	AddTexture(texture->GetResourceName(), texture);
}

void TextureComponent::AddTextures(const std::string& path)
{
	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return;
	}
	Xml::XMLElement* root = doc.FirstChildElement();


	Xml::XMLElement* first_element = root->FirstChildElement();

	for (; first_element; first_element = first_element->NextSiblingElement())
	{
		AddTexture_Continue(path, first_element);
	}

	return;
}

void TextureComponent::AddTexture_Continue(const std::string& path, Xml::XMLElement* sib_element)
{
	if (!sib_element)
	{
		AddTexture(path);
		return;
	}

	auto resource_manager = tool->GetManager<ResourceManager>();
	auto texture = resource_manager->Load_Continue<Texture>(path, sib_element);
	AddTexture(texture->GetResourceName(), texture);
}
