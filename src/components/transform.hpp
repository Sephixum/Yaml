#ifndef __TRANSFORM_HPP
#define __TRANSFORM_HPP

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Yaml {

namespace Component {

class Transform {
  protected:
    glm::mat4 m_world_matrix{glm::mat4(1.0f)};

    glm::vec3 m_local_position{glm::vec3(0.0f, 0.0f, 0.0f)};
    glm::vec3 m_local_scale{glm::vec3(1.0f, 1.0f, 1.0f)};
    glm::quat m_local_orientation{glm::quat(glm::vec3(0.0f, 0.0f, 0.0f))};

  public:
    Transform() = default;
    Transform(const glm::mat4 &matrix);
    Transform(const glm::vec3 &position);
};

} // namespace Component

} // namespace Yaml

#endif // __TRANSFORM_HPP
