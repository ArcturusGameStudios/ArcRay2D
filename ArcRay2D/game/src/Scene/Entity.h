#pragma once

#include "Map.h"
#include "Components.h"
#include <entt.hpp>
#include "src/Core/UUID.h"
#include "src/Core/Serialization.h"

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Map* map);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
				return GetComponent<T>();
			T& component = m_Map->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Map->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			if (HasComponent<T>())
				return m_Map->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		T* TryGetComponent()
		{
			if (HasComponent<T>())
				return &m_Map->m_Registry.get<T>(m_EntityHandle);
			return nullptr;
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Map->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			if (HasComponent<T>())
				m_Map->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Map == other.m_Map;
		}
		bool operator != (const Entity& other) const
		{
			return !(*this == other);
		}

		Map* GetMap() { return m_Map; };

	private:
		entt::entity m_EntityHandle = entt::null;
		Map* m_Map = nullptr;
	};