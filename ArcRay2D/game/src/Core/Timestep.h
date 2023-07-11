#pragma once

	class Timestep
	{
	public:
		Timestep()
			: m_Time(GetFrameTime()) {}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
		float GetFramerate() const { return round(1 / m_Time); }

	private:
		float m_Time;
	};