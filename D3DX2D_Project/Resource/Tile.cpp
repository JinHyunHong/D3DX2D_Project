#include "stdafx.h"
#include "Tile.h"

Tile::Tile(class Tool* const tool, const ResourceType type) :
	IResource(tool, type)
{
}

Tile::~Tile()
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

	Xml::XMLElement* first_element = root->FirstChildElement();
	
	for (int i = 0; i < index; ++i)
		first_element->NextSiblingElement();
	
	resource_name = first_element->Attribute("Name");
	potal_tile_name = first_element->Attribute("Potal_Tile_Name");
	is_move = first_element->BoolAttribute("Is_Move");

	return true;
}

void Tile::SetPotal(const std::string& potal_tile_name)
{
	this->potal_tile_name = potal_tile_name;
}
