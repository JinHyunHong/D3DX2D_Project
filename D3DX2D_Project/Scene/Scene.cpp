#include "stdafx.h"
#include "Scene.h"
#include "Layer/Layer.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AIScriptComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"

Scene::Scene(Tool* const tool) :
	tool(tool)
{
	renderer = tool->GetManager<SubsystemManager>()->GetSubsystem<Renderer>();
	timer = tool->GetManager<SubsystemManager>()->GetSubsystem<Timer>();
	graphics = tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>();
	window_width = static_cast<float>(Core::GetInst().GetWidth());
	window_height = static_cast<float>(Core::GetInst().GetHeight());

	auto camera_layer = CreateLayer("MainCamera");

	camera = camera_layer->CreateActor();
	camera->SetName("MainCamera");
	camera->AddComponent<CameraComponent>();

	back_ground_layer = CreateLayer("BackGround");
	tile_layer = CreateLayer("Tile");
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
}

void Scene::Input()
{
}

void Scene::Update()
{
	if (!is_active)
		return;

	Input();

	for (const auto& layer : layers)
	{
		layer->Update(renderer);
	}
}

void Scene::Destroy()
{
	renderer->ClearRenderables();
}

auto Scene::CreateLayer(const std::string& name, bool is_active) -> std::shared_ptr<class Layer>
{
	auto new_layer = std::make_shared<Layer>(tool);

	if (!new_layer->Initialize())
	{
		assert(false);
		return nullptr;
	}

	new_layer->SetName(name);
	new_layer->SetActive(is_active);

	return layers.emplace_back(new_layer);
}

void Scene::CreateBackground(const std::vector<std::string>& animation_paths, 
	const std::string& current_animation, const D3DXVECTOR3& scale, const D3DXVECTOR3& position, Xml::XMLElement* sibling_element)
{
	if (back_ground)
	{
		back_ground->Destroy();
		back_ground_layer->EraseActors();
		back_ground.reset();
	}

	back_ground = back_ground_layer->CreateActor();
	back_ground->SetName("BackGround");
	auto transform = back_ground->GetComponent<TransformComponent>();
	transform->SetScale(scale);
	transform->SetPosition(position);
	back_ground->AddComponent<MeshRendererComponent>();
	auto animator = back_ground->AddComponent<AnimatorComponent>();


	Xml::XMLElement* element = sibling_element;

	for (const auto& path : animation_paths)
	{
		animator->AddAnimation_Continue(path, element);

		if (element && element->NextSiblingElement())
			element = element->NextSiblingElement();
	}


	animator->SetCurrentAnimation(current_animation);

	back_ground_layer->SetActive(true);
	back_ground_layer->SetUpdate(true);
}

void Scene::CreateTiles(const std::string& path,
	Xml::XMLElement* first_element, const float& width, const float& height)
{
	this->width = width;
	this->height = height;

	tile_number_y = static_cast<uint>(height / tile_size.y);
	tile_number_x = static_cast<uint>(width / tile_size.x);

	Xml::XMLElement* element = first_element;

	for (uint i = 0; i < tile_number_y; ++i)
	{
		for (uint j = 0; j < tile_number_x; ++j)
		{
			auto new_tile = tile_layer->CreateActor();
			new_tile->SetName("tile" + std::to_string(static_cast<uint>(i * tile_number_y + j)));
			auto transform = new_tile->GetComponent<TransformComponent>();
			transform->SetScale(D3DXVECTOR3(40.0f, 40.0f, 1.0f));
			transform->SetPosition(D3DXVECTOR3(j * tile_size.x, i * tile_size.y, 0.0f));
			auto tile = new_tile->AddComponent<TileRendererComponent>()->CreateTile(path, element);
			tile->SetName("tile" + std::to_string(static_cast<uint>(i * tile_number_y + j)));
			auto collider = new_tile->AddComponent<ColliderComponent>();
			collider->SetOffsetScale(D3DXVECTOR3(10.0f, 10.0f, 1.0f));

			if (!tile->IsMove())
				collider->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			else
				collider->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (element && element->NextSiblingElement())
				element = element->NextSiblingElement();
		}
	}

	tile_layer->SetActive(true);
	tile_layer->SetUpdate(true);
}


auto Scene::GetTileIndex(const D3DXVECTOR2& position) const -> const uint
{
	uint index_x = static_cast<uint>(position.x / tile_size.x);
	uint index_y = static_cast<uint>(position.y / tile_size.y);

	// 예외처리
	if (index_x < 0 || index_x >= tile_number_x)
		return -1;

	else if (index_y < 0 || index_y >= tile_number_y)
		return -1;

	return index_y * tile_number_x + index_x;

}

bool Scene::SaveToFile(const std::string& path)
{
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);

	if (back_ground)
	{
		auto transform = back_ground->GetComponent<TransformComponent>();
		auto first_element = doc.NewElement("background");
		doc.LinkEndChild(first_element);
		first_element->SetAttribute("ScaleX", transform->GetScale().x);
		first_element->SetAttribute("ScaleY", transform->GetScale().y);
		first_element->SetAttribute("PositionX", transform->GetPosition().x);
		first_element->SetAttribute("PositionY", transform->GetPosition().y);
		back_ground->GetComponent<AnimatorComponent>()->GetCurrentAnimation()->SaveToFile_Continue(doc, first_element);
	}


	auto second_element = doc.NewElement("Tiles");
	doc.LinkEndChild(second_element);
	second_element->SetAttribute("Width", width);
	second_element->SetAttribute("Height", height);
	second_element->SetAttribute("TileSizeX", tile_size.x);
	second_element->SetAttribute("TileSizeY", tile_size.y);

	auto actors = tile_layer->GetActors();

	for (const auto& actor : actors)
		actor->GetComponent<TileRendererComponent>()->GetTile()->SaveToFile_Continue(doc, second_element);

	return Xml::XMLError::XML_SUCCESS == doc.SaveFile(path.c_str());
}

bool Scene::LoadFromFile(const std::string& path, const std::string& current_animation, const bool& is_background)
{
	renderer->ClearRenderables();

	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return false;
	}


	Xml::XMLElement* first_element = nullptr;
	Xml::XMLElement* second_element = nullptr;
	D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 position = D3DXVECTOR2(0.0f, 0.0f);

	if (back_ground)
	{
		back_ground->Destroy();
		back_ground_layer->EraseActors();
		back_ground.reset();
	}

	if (is_background)
	{
		first_element = doc.FirstChildElement();
		second_element = first_element->NextSiblingElement();

		scale.x = first_element->FloatAttribute("ScaleX");
		scale.y = first_element->FloatAttribute("ScaleY");
		position.x = first_element->FloatAttribute("PositionX");
		position.y = first_element->FloatAttribute("PositionY");


		std::vector<std::string> paths{ path };
		CreateBackground(paths, current_animation, D3DXVECTOR3(scale.x, scale.y, 1.0f), 
			D3DXVECTOR3(position.x, position.y, 0.0f), first_element->FirstChildElement());
	}

	else
		second_element = doc.FirstChildElement();


	width = second_element->FloatAttribute("Width");
	height = second_element->FloatAttribute("Height");
	tile_size.x = second_element->FloatAttribute("TileSizeX");
	tile_size.y = second_element->FloatAttribute("TileSizeY");

	tile_layer->EraseActors();

	auto tile_element = second_element->FirstChildElement();

	CreateTiles(path, tile_element, width, height);

	camera->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return true;
}
