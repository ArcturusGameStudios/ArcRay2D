#pragma once

	class Timestep
	{
	public:
		Timestep()
			: m_Time(GetFrameTime()) {}

//		float operator*(const float& other) const { return m_Time * other; };
		operator float() const { return m_Time; }
		float operator *(const float& b) { return m_Time * b; };

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
		float GetFramerate() const { return round(1 / m_Time); }

	private:
		float m_Time;
	};