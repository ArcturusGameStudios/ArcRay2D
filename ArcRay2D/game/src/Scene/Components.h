#pragma once
#include <string>
#include "raymath.h"
#include "Core/UUID.h"
#include "Map.h"
#include <cereal/archives/binary.hpp>

	struct IDComponent {
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;

		template <class PortableBinaryOutputArchive>
		void serialize(PortableBinaryOutputArchive& ar)
		{
			ar(ID);
		}
	};

	struct TagComponent {
		std::string _tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			:_tag(tag) {}
	};

	struct TransformComponent {
	private:
		Maths::Vector2 Translation = { 0.0f, 0.0f };
		float Depth = 0.0f;
		float Rotation = 0.0f;
		Maths::Vector2 Scale = { 1.0f, 1.0f };

	public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const RAYMATH_H::Matrix& transform) { SetMatrix(transform); }
		operator RAYMATH_H::Matrix() const { return GetMatrix(); }

		RAYMATH_H::Matrix GetMatrix() const
		{
			RAYMATH_H::Matrix translate = RAYMATH_H::MatrixTranslate(Translation.x, Translation.y, Depth);
			RAYMATH_H::Matrix rotate = RAYMATH_H::MatrixRotateZ(Rotation);
			RAYMATH_H::Matrix scale = RAYMATH_H::MatrixScale(Scale.x, Scale.y, 1.0f);

			return MatrixMultiply(MatrixMultiply(translate, rotate), scale);
		}

		Maths::Vector2 GetTranslation() const
		{
			GetMatrix();
			return Translation;
		}

		float GetDepth() const
		{
			GetMatrix();
			return Depth;
		}

		float GetRotationDeg() const
		{
			return GetRotationRad() * RAD2DEG;
		}

		float GetRotationRad() const
		{
			GetMatrix();
			return Rotation;
		}

		Maths::Vector2 GetScale() const
		{
			GetMatrix();
			return Scale;
		}

		Maths::Vector3 GetForwardVector() const
		{
			const RAYMATH_H::Matrix in = GetMatrix();
			return { in.m8, in.m9, in.m10 };
		}

		Maths::Vector3 GetRightVector() const
		{
			const RAYMATH_H::Matrix in = GetMatrix();
			return { in.m0, in.m1, in.m2 };
		}

		Maths::Vector3 GetUpVector() const
		{
			const RAYMATH_H::Matrix in = GetMatrix();
			return { in.m4, in.m5, in.m6 };
		}

		Maths::Vector3 GetForwardPosition() const
		{

			const RAYMATH_H::Matrix in = GetMatrix();
			return { in.m8 + in.m12, in.m9 + in.m13, in.m10 + in.m14 };
		}

		Maths::Vector3 GetRightPosition() const
		{
			const RAYMATH_H::Matrix in = GetMatrix();
			return { in.m0 + in.m12, in.m1 + in.m13, in.m2 + in.m14 };
		}

		Maths::Vector3 GetUpPosition() const
		{
			const RAYMATH_H::Matrix in = GetMatrix();
			return { in.m4 + in.m12, in.m5 + in.m13, in.m6 + in.m14 };
		}

		RAYMATH_H::Matrix SetMatrix(const RAYMATH_H::Matrix& transform)
		{
			Translation = RAYMATH_H::Vector2{ transform.m13, transform.m14 };
			Depth = transform.m15;
			Scale = RAYMATH_H::Vector2{ transform.m0, transform.m5 };
			Rotation = RAYMATH_H::QuaternionToEuler(RAYMATH_H::QuaternionFromMatrix(transform)).z;
			return GetMatrix();
		}

		void SetTranslation(Maths::Vector2 translation)
		{
			Translation = translation;
		}

		void SetTranslation(Maths::Vector2 translation, float depth)
		{
			Translation = translation;
			Depth = depth;
		}

		void SetTranslation(Maths::Vector3 translation)
		{
			Translation = { translation.x, translation.y };
			Depth = translation.z;
		}

		void SetDepth(float depth)
		{
			Depth = depth;
		}

		void SetRotationDeg(float rotation)
		{
			Rotation = rotation * DEG2RAD;
		}

		void SetRotationRad(float rotation)
		{
			Rotation = rotation;
		}

		void SetScale(Maths::Vector2 scale)
		{
			Scale = scale;
		}
	};

	/*
		struct RigidBodyComponent {
		rp3d::RigidBody* _rigidBody;
		std::list<rp3d::Collider*> _colliders;

		RigidBodyComponent() = default;
		RigidBodyComponent(const RigidBodyComponent&) = default;
		RigidBodyComponent(rp3d::RigidBody* body) { _rigidBody = body; };
		rp3d::Collider* AddCollider(rp3d::CollisionShape* collision, rp3d::Transform transform)
		{
			rp3d::Collider* out;
			out = _rigidBody->addCollider(collision, transform);
			_colliders.push_back(out);
			return out;
		};
		rp3d::Collider* AddCollider(rp3d::CollisionShape* collision)
		{
			rp3d::Collider* out;
			out = _rigidBody->addCollider(collision, rp3d::Transform::identity());
			_colliders.push_back(out);
			return out;
		};
	};

	struct CollisionBodyComponent {
		rp3d::CollisionBody* _collisionBody;
		std::list<rp3d::Collider*> _colliders;

		CollisionBodyComponent() = default;
		CollisionBodyComponent(const CollisionBodyComponent&) = default;
		CollisionBodyComponent(rp3d::CollisionBody* body) { _collisionBody = body; };
		rp3d::Collider* AddCollider(rp3d::CollisionShape* collision, rp3d::Transform transform)
		{
			rp3d::Collider* out;
			out = _collisionBody->addCollider(collision, transform);
			_colliders.push_back(out);
			return out;
		};
		rp3d::Collider* AddCollider(rp3d::CollisionShape* collision)
		{
			rp3d::Collider* out;
			out = _collisionBody->addCollider(collision, rp3d::Transform::identity());
			_colliders.push_back(out);
			return out;
		};
	};
	*/

	struct Box2DBodyComponent
	{
		b2Body* body;
		b2Shape* shape;

		Box2DBodyComponent(b2BodyDef* _definition) { body = AssetManagerInstance->GetPhysicsWorld()->CreateBody(_definition); };
		Box2DBodyComponent(b2Body* _body) : body(_body) {};

		void SetShape(b2Shape* _shape, float _density) { shape = _shape; body->CreateFixture(shape, _density); };
	};

	struct CameraComponent {
		Camera2D cam;

		CameraComponent(const Vector2& position) {
			cam = Camera2D();
			cam.target = position;
			cam.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
			cam.zoom = 1.0f;
		};
	};

	struct ModelComponent {
		UUID refID; // Looked up in asset manager
		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;
		ModelComponent(UUID id) { refID = id; } // Use Ref<Model> to lookup asset manager and find asset ID
		Ref<Model> getModel() { return AssetManager::Instance()->GetModel(refID); } // Returns the corresponding assetManager model with this ID
	};

	struct SpriteComponent {
		UUID refID; // Looked up in asset manager
		Rectangle source = Rectangle{ 0, 0, 0, 0 };
		Rectangle dest = Rectangle{ 0, 0, 0, 0 };
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(UUID id) { refID = id; } // Use Ref<Model> to lookup asset manager and find asset ID
		void SetSourceRect(Rectangle rect) { source = rect; };
		void SetSourceVec(Vector4 rect) { source = Rectangle{ rect.x, rect.y, rect.z, rect.w }; };
		void SetDestRec(Rectangle rect) { dest = rect; };
		void SetDestVec(Vector4 rect) { dest = Rectangle{ rect.x, rect.y, rect.z, rect.w }; };
		Ref<Image> getSprite() { return AssetManager::Instance()->GetTexture(refID); } // Returns the corresponding assetManager model with this ID
	};

	struct ProjectileComponent {
		UUID owner;
		float damage = 0.0f;

		ProjectileComponent() = default;
		ProjectileComponent(const ProjectileComponent&) = default;
		ProjectileComponent(UUID _owner, float _damage) : owner(_owner), damage(_damage) {};
	};

	struct LifetimeComponent {
		float life = 0.0f;

		LifetimeComponent() = default;
		LifetimeComponent(const LifetimeComponent&) = default;
		LifetimeComponent(float _life) : life(_life) {};
	};


	// Forward declaration to prevent circular dependencies
	// Entity includes Components, which includes NSC, which includes Entity
	class ScriptableEntity;
	struct NativeScriptComponent {
	};