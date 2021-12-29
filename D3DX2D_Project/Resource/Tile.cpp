#include "stdafx.h"
#include "Tile.h"

Tile::Tile(class Tool* const tool, const ResourceType type) :
	IResource(tool, type)
{
}

Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Destroy()
{
}

bool Tile::LoadFromFile(const std::string& path)
{
	if (index == -1 || path.empty())
		return false;

	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return false;
	}
	Xml::XMLElement* root = doc.FirstChildElement();
	texture_size.x = root->FloatAttribute("Texture_Size_X");
	texture_size.y = root->FloatAttribute("Texture_Size_Y");

	Xml::XMLElement* first_element = root->FirstChildElement();
	
	for (int i = 0; i < index; ++i)
		first_element->NextSiblingElement();
	
	resource_name = first_element->Attribute("Name");
	texture_path = first_element->Attribute("Texture_Path");
	offset.x = first_element->FloatAttribute("Offset_X");
	offset.y = first_element->FloatAttribute("Offset_Y");
	size.x = first_element->FloatAttribute("Size_X");
	size.y = first_element->FloatAttribute("Size_Y");
	potal_tile_name = first_element->Attribute("Potal_Tile_Name");
	is_move = first_element->BoolAttribute("Is_Move");

	SetTileTexture(texture_path);
	return true;
}

void Tile::SetTileTexture(const std::string& path)
{
	this->resource_path = path;

	tile_texture = std::make_shared<D3D11_Texture>(tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>());
	tile_texture->Create(path);
}

void Tile::SetPotal(const std::string& potal_tile_name)
{
	this->potal_tile_name = potal_tile_name;
}
