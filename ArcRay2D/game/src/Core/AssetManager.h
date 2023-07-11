#pragma once
#include <unordered_map>
#include "raylib.h"
#include "box2d/b2_world.h"


class AssetManager
{
public:
	static AssetManager* Instance();
	void ReleaseMemory();

private:
	AssetManager() {};
	static AssetManager* m_Instance;

public:
	void TestIDs();
	b2World* GetPhysicsWorld() { return world; };

	std::shared_ptr<Model> GetModel(UUID id);
	bool AddModel(UUID id, std::shared_ptr<Model> model);

private:
	b2World* world = new b2World(b2Vec2(0.0f, 0.0f));
	std::unordered_map<UUID, std::shared_ptr<Model>> m_models;
};

extern AssetManager* AssetManagerInstance; // declaration