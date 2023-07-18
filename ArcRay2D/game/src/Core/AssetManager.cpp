#include "arcpch.h"
#include "AssetManager.h"

AssetManager* AssetManager::m_Instance = nullptr;
AssetManager* AssetManagerInstance = AssetManager::Instance();

AssetManager* AssetManager::Instance()
{
	if (m_Instance == nullptr)
		m_Instance = new AssetManager;
	return m_Instance;
}

void AssetManager::ReleaseMemory()
{
	world->~b2World();
}

void AssetManager::TestIDs()
{
}

std::shared_ptr<Model> AssetManager::GetModel(UUID id)
{
	for (const auto& _model : m_models)
	{
		if (_model.first == id)
		{
//			std::cout << "Model found with ID: " << (id) << std::endl;
			return _model.second;
		}
	}
//	std::cout << "Model not found!" << std::endl;
	return nullptr;
}

bool AssetManager::AddModel(UUID id, std::shared_ptr<Model> model)
{
	for (auto _model : m_models)
	{
		if (_model.first == id)
		{
//			std::cout << "Model found with ID: " << (id) << std::endl;
			return false;
		}
		if (_model.second = model)
		{
//			std::cout << "Model found with ID: " << (_model.first) << std::endl;
			return false;
		}
	}
//	std::cout << "Model not found, creating new asset with ID: " << (id) << std::endl;
	m_models.emplace(id, model);
	return true;
}

std::shared_ptr<Image> AssetManager::GetTexture(UUID id)
{
	for (const auto& _texture : m_Textures)
	{
		if (_texture.first == id)
		{
			//			std::cout << "Model found with ID: " << (id) << std::endl;
			return _texture.second;
		}
	}
	//	std::cout << "Model not found!" << std::endl;
	return nullptr;
}

bool AssetManager::AddTexture(UUID id, std::shared_ptr<Image> texture)
{
	for (auto _texture : m_Textures)
	{
		if (_texture.first == id)
		{
			//			std::cout << "Model found with ID: " << (id) << std::endl;
			return false;
		}
		if (_texture.second = texture)
		{
			//			std::cout << "Model found with ID: " << (_model.first) << std::endl;
			return false;
		}
	}
	//	std::cout << "Model not found, creating new asset with ID: " << (id) << std::endl;
	m_Textures.emplace(id, texture);
	return true;
}
