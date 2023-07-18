#include "arcpch.h"
#include "src/Scene/Map.h"
#include "src/Scene/Entity.h"
#include "src/Scene/Components.h"

#include "src/Scene/Entity.h"

	Entity Map::CreateEntity(const std::string& name)
	{
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Map::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag._tag = name.empty() ? "Entity" : name;
		m_EntityList.push_back(entity);
		return entity;
	}

	void Map::DestroyEntity(entt::entity entity)
	{
		/*
		auto rigidComponent = (m_Registry.try_get<RigidBodyComponent>(entity));
		if (rigidComponent != nullptr)
			world->destroyRigidBody(rigidComponent->_rigidBody);
		auto collisionComponent = (m_Registry.try_get<CollisionBodyComponent>(entity));
		if (collisionComponent != nullptr)
			world->destroyCollisionBody(collisionComponent->_collisionBody);
		*/

		m_Registry.destroy(entity);
	}

	/*
	Entity Map::CreateMapField(rp3d::Transform* transform, int rows, int columns, float minHeight, float maxHeight, float heightValues[])
	{
		if (transform == nullptr)
			transform = &rp3d::Transform::identity();
		Entity entity = { m_Registry.create(), this };
		UUID id = UUID();
		entity.AddComponent<IDComponent>(id);
		auto& tag = entity.AddComponent<TagComponent>();
		tag._tag = "Map-";

		rp3d::CollisionBody* body = world->createCollisionBody(*transform);
		entity.AddComponent<CollisionBodyComponent>(body);
		rp3d::HeightFieldShape* heightFieldShape = AssetManagerInstance->GetPhysicsCommon()->createHeightFieldShape(
			columns, rows,
			minHeight, maxHeight,
			heightValues, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
		entity.GetComponent<CollisionBodyComponent>().AddCollider(heightFieldShape);
//		entity.GetComponent<CollisionBodyComponent>()._collisionBody->setIsActive(false);

		m_EntityList.push_back(entity);
		return entity;
	}
	*/

	Entity Map::CreateCamera(const Vector2& position)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(UUID());
		auto& tag = entity.AddComponent<TagComponent>();
		tag._tag = "MainCamera";

		entity.AddComponent<TransformComponent>();
		entity.AddComponent<CameraComponent>(position);
		auto _transf = entity.GetComponent<TransformComponent>();
		auto _cam = entity.GetComponent<CameraComponent>().cam;

		_transf.SetTranslation(position);
		_cam.target = position;
		_cam.offset = { 0, 0};
		_cam.zoom = 1.0f;

		m_EntityList.push_back(entity);
		playerCamera = entity;
		return entity;
	}

	Entity* Map::GetCamera()
	{
		if (playerCamera != entt::null)
			return &Entity(playerCamera, this);
		return nullptr;
	}

	/*
	Entity Map::CreateCollisionProjectile(UUID owner, float damage, rp3d::Transform* muzzleTransform, float muzzleVelocity)
	{
		if (muzzleTransform == nullptr)
			muzzleTransform = &rp3d::Transform::identity();

		Entity projectile = { m_Registry.create(), this };
		projectile.AddComponent<IDComponent>(UUID());
		projectile.AddComponent<TransformComponent>();
		projectile.AddComponent<ProjectileComponent>(owner, damage);
		rp3d::CollisionBody* body = world->createCollisionBody(*muzzleTransform);
		projectile.AddComponent<CollisionBodyComponent>(body);
		return projectile;
	}

	Entity Map::CreateRigidProjectile(UUID owner, float damage, rp3d::Transform* muzzleTransform, float muzzleVelocity)
	{
		if (muzzleTransform == nullptr)
			muzzleTransform = &rp3d::Transform::identity();

		Entity projectile = { m_Registry.create(), this };
		projectile.AddComponent<IDComponent>(UUID());
		projectile.AddComponent<TransformComponent>();
		projectile.AddComponent<ProjectileComponent>(owner, damage);
		rp3d::RigidBody* body = world->createRigidBody(*muzzleTransform);
		projectile.AddComponent<RigidBodyComponent>(body);
		projectile.GetComponent<RigidBodyComponent>()._rigidBody->setMass(0.1f);
//		projectile.GetComponent<RigidBodyComponent>()._rigidBody->enableGravity(false);
		projectile.GetComponent<RigidBodyComponent>()._rigidBody->applyLocalForceAtCenterOfMass({0,0,muzzleVelocity});
		return projectile;
	}
	*/

	void Map::OnUpdateEditor(Timestep ts, RAYLIB_H::Camera camera)
	{}

	void Map::OnUpdateRuntime(Timestep ts)
	{
		Maths::Vector2 _translation = { 0.0f, 0.0f };
		_translation = m_Registry.get<TransformComponent>(playerCamera).GetTranslation();
		if (IsKeyDown(KEY_A))
		{
			_translation.x -= ts;
			std::cout << "LEFT" << std::endl;
		}
		if (IsKeyDown(KEY_D))
		{
			_translation.x += ts;
			std::cout << "RIGHT" << std::endl;
		}
		if (IsKeyDown(KEY_S))
		{
			_translation.y -= ts;
			std::cout << "DOWN" << std::endl;
		}
		if (IsKeyDown(KEY_W))
		{
			_translation.y += ts;
			std::cout << "UP" << std::endl;
		}
		m_Registry.get<TransformComponent>(playerCamera).SetTranslation(_translation);

		// Network Poll?
		// Input Polling
		// Scripting
		PhysicsUpdate(ts); // Does physics update, provides new transforms
		DrawCall(); // Draws frame with updated transforms based on scripts and physics
		UIDrawCall(); // Draws UI items, done after DrawCall so this should draw over the frame
		LifetimeUpdate(ts); // Decreases the lifetime of all objects that have one

		// Need to do all processing before calculating if an object is to be destroyed
		auto view = m_Registry.view<LifetimeComponent>();
		for (entt::entity entity : view)
		{
			if (view.get<LifetimeComponent>(entity).life <= 0.0f)
				DestroyEntity(entity);
		}
	}

	void Map::DrawCall()
	{
		if (!m_IsDrawingEnabled)
			return;

		if (playerCamera == entt::null)
			CreateCamera();
		auto camera = m_Registry.try_get<CameraComponent>(playerCamera);
		auto transf = m_Registry.try_get<TransformComponent>(playerCamera);
		camera->cam.target = transf->GetTranslation();
		BeginMode2D(camera->cam);
//		std::cout << "Camera: (" << camera->cam.target.x << ", " << camera->cam.target.y << ")" << std::endl;
//		std::cout << "Offset: (" << camera->cam.offset.x << ", " << camera->cam.offset.y << ")" << std::endl;

		DrawText("HELLO WORLD", 0, 0, 12, RAYWHITE);

		if (m_IsDebugRendering)
		{
			world->DebugDraw();
		}

		auto viewTextureTransform = m_Registry.view<SpriteComponent, TransformComponent>();
//		auto group = m_Registry.group<TransformComponent>(entt::get<ModelComponent>);
		for (entt::entity entity : viewTextureTransform)
		{
			auto [_transform, _sprite] = viewTextureTransform.get<TransformComponent, SpriteComponent>(entity);
			DrawTexturePro(
				*_sprite.getSprite(),
				_sprite.source,
				_sprite.dest,
				Vector2(_transform.GetTranslation()),
				_transform.GetRotationRad(),
				RAYWHITE
			);
		}

		EndMode2D();
	}

	void Map::UIDrawCall()
	{
	}

	void Map::PhysicsUpdate(Timestep ts)
	{
		if (!m_IsPhysicsEnabled)
			return;
		world->Step(ts, 8, 3);
//		std::cout << "PHYSICS" << std::endl;

		auto groupBody = m_Registry.group<TransformComponent>(entt::get<Box2DBodyComponent>);
		for (entt::entity entity : groupBody)
		{
			auto [_transform, _body] = groupBody.get<TransformComponent, Box2DBodyComponent>(entity);
			_transform.SetTranslation(Maths::Vector3(_body.body->GetPosition().x, _body.body->GetPosition().y, 0.0f));
			_transform.SetRotationRad(_body.body->GetAngle());
		}
	}

	void Map::LifetimeUpdate(Timestep ts)
	{
		auto view = m_Registry.view<LifetimeComponent>();
		for (entt::entity entity : view)
		{
			view.get<LifetimeComponent>(entity).life -= ts;
		}
	}

	void Map::SerializeMap(char* _filepath)
	{
		MapSerializer mapSerializer(*this);
		mapSerializer.SerializeMap(_filepath);
	}

	void Map::DeserializeMap(char* _filepath)
	{
		MapSerializer mapSerializer(*this);
		mapSerializer.DeserializeMap(_filepath);
	}

	void Map::OnViewportResize(uint32_t width, uint32_t height)
	{}

	// TEMPLATES FOR ADD-COMPONENT BOOT FUNCTIONS
	template<typename T>
	void Map::OnComponentAdded(Entity entity, T& component)
	{}

	template<>
	void Map::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
	{}

	template<>
	void Map::OnComponentAdded<TagComponent>(Entity entity, TagComponent & component)
	{}

	template<>
	void Map::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent & component)
	{}

	template<>
	void Map::OnComponentAdded<Box2DBodyComponent>(Entity entity, Box2DBodyComponent& component)
	{}

	/*
	template<>
	void Map::OnComponentAdded<RigidBodyComponent>(Entity entity, RigidBodyComponent& component)
	{}

	template<>
	void Map::OnComponentAdded<CollisionBodyComponent>(Entity entity, CollisionBodyComponent& component)
	{}
	*/

	template<>
	void Map::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{}

	template<>
	void Map::OnComponentAdded<ModelComponent>(Entity entity, ModelComponent & component)
	{}

	template<>
	void Map::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component)
	{}

	template<>
	void Map::OnComponentAdded<ProjectileComponent>(Entity entity, ProjectileComponent& component)
	{}

	template<>
	void Map::OnComponentAdded<LifetimeComponent>(Entity entity, LifetimeComponent& component)
	{}

	template<>
	void Map::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{}