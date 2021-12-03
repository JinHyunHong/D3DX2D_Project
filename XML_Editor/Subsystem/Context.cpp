#include "stdafx.h"
#include "Context.h"

Context::Context(Tool* const tool) :
	ISubsystem(tool)
{
}

bool Context::Initialize()
{
	return true;
}

void Context::AddElement(const std::string& element_name, const std::string& base_element_name)
{
	if (base_element_name.empty())
	{
		Xml::XMLElement* element = doc.NewElement(element_name.c_str());
		doc.LinkEndChild(element);
	}

	Xml::XMLElement* element = GetElement(base_element_name);
	Xml::XMLElement* element_child = doc.NewElement(element_name.c_str());
	element->LinkEndChild(element_child);
}

auto Context::GetElement(const std::string& element_name) -> Xml::XMLElement*
{
	Xml::XMLElement* element = doc.FirstChildElement();
	
	for (; element; element = element->NextSiblingElement())
		for (Xml::XMLElement* chlild_element = element->FirstChildElement();
			chlild_element; chlild_element = chlild_element->NextSiblingElement())
	{
		if (element->Name() == element_name)
		{
			return element;
		}
	}
	return nullptr;
}

bool Context::SaveToFile(const std::string& path)
{
	return Xml::XMLError::XML_SUCCESS != doc.SaveFile(path.c_str());
}

bool Context::LoadFromFile(const std::string& path)
{
	return  Xml::XMLError::XML_SUCCESS != doc.LoadFile(path.c_str());
}
