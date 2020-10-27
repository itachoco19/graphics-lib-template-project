#pragma once
#include "ObjectFreeLookControl.hpp"
#include "ObjectLookAtControl.hpp"
#include "ObjectWASDControl.hpp"
#include "ObjectControllingMethod.hpp"





class CameraController
{
private:
	static constexpr float defaultMovementDelta = 0.1f;
	static constexpr float defaultAngleDelta    = cpp::Math::degreeToRadian(0.3f);
private:
	ObjectFreeLookControl m_freeLookControl;
	ObjectLookAtControl m_lookAtControl;
	ObjectWASDControl m_WASDControl;

	ObjectControllingMethod m_method = ObjectControllingMethod::freeLookWASD;

	bool m_isEnabled = true;
	bool m_isControllingMethodChanged = true;
public:
	float movementDelta = defaultMovementDelta;
	float angleDeltaRadian = defaultAngleDelta;
public:
	void control(cg::Camera& target);


	void changeControllingMethod(ObjectControllingMethod method);
	[[nodiscard]] ObjectControllingMethod getControllingMethod() const noexcept;

	[[nodiscard]] bool isEnabled() const noexcept;
	void enable();
	void disable();
};