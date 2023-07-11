#pragma once
#include <raymath.h>
#include <box2d/b2_math.h>

namespace Maths {

	struct Vector2
	{
	public:
		float x;
		float y;

		Vector2() = default;
		Vector2(const Vector2& other) = default;
		Vector2(float _x, float _y)
			: x(_x), y(_y) {};
		Vector2(const RAYMATH_H::Vector2& other)
			: x(other.x), y(other.y) {};
		Vector2(const RAYMATH_H::Color& other)
			: x(other.r), y(other.g) {};
		Vector2(const Vector3& other)
			: x(other.x), y(other.y) {};
		Vector2(const b2Vec2& other)
			: x(other.x), y(other.y) {};

		operator RAYMATH_H::Vector2() const { return RAYMATH_H::Vector2{x, y}; };
		operator b2Vec2() const { return b2Vec2{x, y}; };
		operator RAYMATH_H::Color() const { RAYMATH_H::Color out; out.r = x, out.g = y; return out; }

		const Maths::Vector2& operator*(const Maths::Vector2& other) { return (RAYMATH_H::Vector2Multiply({ x, y }, other)); };
		const Maths::Vector2& operator+(const Maths::Vector2& other) { return Vector2{ x + other.x, y + other.y }; };
		const Maths::Vector2& operator*(float scalar) { return { this->x * scalar, this->y * scalar }; };
	};

	struct Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3() = default;
		Vector3(const Vector3& other) = default;
		Vector3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z) {};
		Vector3(const RAYMATH_H::Vector3& other)
			: x(other.x), y(other.y), z(other.z) {};
		Vector3(const RAYMATH_H::Color& other)
			: x(other.r), y(other.g), z(other.b) {};
		Vector3(const Vector2& other, float z)
			: x(other.x), y(other.y), z(z) {};
		Vector3(const Vector2& other)
			: x(other.x), y(other.y), z(1.0f) {};

		operator RAYMATH_H::Vector3() const { return RAYMATH_H::Vector3{x, y, z}; };
		operator RAYMATH_H::Color() const { RAYMATH_H::Color out; out.r = x, out.g = y; out.b = z; return out; }

		const Maths::Vector3& operator*(const Maths::Vector3& other) { return (RAYMATH_H::Vector3Multiply(Vector3(x, y, z), other)); };
		const Maths::Vector3& operator+(const Maths::Vector3& other) { return Vector3{ x + other.x, y + other.y, z + other.z }; };
		const Maths::Vector3& operator*(float scalar) { return { this->x * scalar, this->y * scalar, this->z * scalar }; };
	};
}