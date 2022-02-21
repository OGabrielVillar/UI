#pragma once


namespace Hazel {

	enum class SpaceDimension : uint8_t {
		TwoDimentional,
		ThreeDimentional,
	};

	enum class TwoPointFiveD
	{
		XY, // Floor panel / Z-Oriented
		XZ, // Front panel / Y-Oriented
		YZ, // Side panel  / X-Oriented
	};

	class SpaceSettings {
		using enum SpaceDimension;
		using enum TwoPointFiveD;
		SpaceDimension m_Dimensions = TwoDimentional;
		TwoPointFiveD m_2DProjection = XY;
	};

	class Timestep {
	 public:
		Timestep() = default;

		float Tick() { m_Seconds = m_Timer.update().count(); }

	 private:
		Timer m_Timer;
		float m_Seconds = 0.f;
	};

	class TimeSettings {
		Timestep m_FT;
	};


}
