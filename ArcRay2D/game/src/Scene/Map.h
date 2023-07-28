#pragma once

#include <raylib.h>
#include "include/entt.hpp"
#include "src/Core/Timestep.h"
#include <cameras/rlFPCamera/rlFPCamera.h>
#include <cameras/rlTPCamera/rlTPCamera.h>

	class Entity;

	class Map
	{
	public:
		Map() = default;
		Map(const Map& other) = default;
		~Map() = default;
		void SetViewport(Vector2& viewport) { m_ViewportWidth = viewport.x; m_ViewportHeight = viewport.y; };

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(entt::entity entity);

		// Special Entities
//		Entity CreateMapField(rp3d::Transform* transform, int rows, int columns, float minHeight, float maxHeight, float heightValues[]);
		Entity CreateCamera(const Vector2& position = {0, 0});
		Entity* GetCamera();
//		Entity CreateCollisionProjectile(UUID owner, float damage, rp3d::Transform* muzzleTransform, float muzzleVelocity);
//		Entity CreateRigidProjectile(UUID owner, float damage, rp3d::Transform* muzzleTransform, float muzzleVelocity);

//		void CreatePhysicsWorld() { world = AssetManagerInstance->GetPhysicsCommon()->createPhysicsWorld(); world->setIsDebugRenderingEnabled(false); };
//		rp3d::PhysicsWorld* GetWorld() { return world; };
		entt::registry* GetRegistry() { return &m_Registry; };
		std::list<Entity>* const  GetEntityList() { return &m_EntityList; };
		b2World* const GetPhysicsWorld() { return world; };

		void OnUpdateRuntime(float ts, float timeScale);
		void OnUpdateEditor(float ts, RAYLIB_H::Camera camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		void DrawCall(float ts);
		void UIDrawCall(float ts);
		void PhysicsUpdate(float ts);
		void LifetimeUpdate(float ts);

		void SerializeMap(char* _filepath);
		void DeserializeMap(char* _filepath);

	public:
		bool m_IsDrawingEnabled = false;
		bool m_IsPhysicsEnabled = false;
		bool m_IsDebugRendering = false;
		float m_Timescale = 1.0f;

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		std::list<Entity> m_EntityList;

		entt::entity playerCamera = entt::null;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
//		rp3d::PhysicsWorld* world;
		b2World* world = AssetManagerInstance->GetPhysicsWorld();

		friend class Entity;
	};