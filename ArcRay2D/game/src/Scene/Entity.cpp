#include "arcpch.h"
#include "Entity.h"

	Entity::Entity(entt::entity handle, Map* map)
		: m_EntityHandle(handle), m_Map(map)
	{}
