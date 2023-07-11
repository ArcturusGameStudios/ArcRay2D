#pragma once
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>

#include "src/Scene/Map.h"
#include "src/Scene/Entity.h"
#include "src/Scene/Components.h"

struct EntityData
{
	uint64_t uuid = NULL;
	//	std::string tag = {};
	float translation[3] = {};
	float rotation[3] = {};
	float scale[3] = {};
	float camFovy = NULL;
	int camType = {};
	uint64_t modelUuid = NULL;
};

class MapSerializer
{
public:
	MapSerializer(Map& map) : m_Map(&map) {};
	~MapSerializer() = default;

	void SerializeMap(char* _filepath);
	void DeserializeMap(char* _filepath);
	EntityData SerializeEntity(Entity* entity);
	Entity* DeserializeEntity(EntityData data);

private:
	Map* m_Map;
};