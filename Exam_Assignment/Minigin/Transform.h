#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
		glm::vec3 mPosition;
		float mAngle = 0;
	public:
		const glm::vec3& GetPosition() const { return mPosition; }
		const float& GetAngle() const { return mAngle; }

		void SetPosition(float x, float y, float z);
	};
}
