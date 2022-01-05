#include "stdafx.h"
#include "IResource.h"

IResource::IResource(class Tool* const tool, const ResourceType type)
	: tool(tool), resource_type(type) 
{
}

template<typename T>
constexpr ResourceType IResource::DeduceResourceType()
{
	return ResourceType::Unknown;
}

#define REGISTER_RESOURCE_TYPE(T, enum_type) template<> ResourceType IResource::DeduceResourceType<T>() { return enum_type; }
REGISTER_RESOURCE_TYPE(Animation, ResourceType::Animation)
REGISTER_RESOURCE_TYPE(Texture, ResourceType::Texture2D)
REGISTER_RESOURCE_TYPE(Tile, ResourceType::Tile)