#include "transform.hpp"
#include <glm/gtx/matrix_decompose.hpp>

namespace Yaml {

namespace Component {

Transform::Transform(const glm::mat4 &matrix) {
    glm::vec3 skew{};
    glm::vec4 perspective{};
    glm::decompose(matrix, m_local_scale, m_local_orientation, m_local_position,
                   skew, perspective);

    m_world_matrix = matrix;
}

Transform::Transform(const glm::vec3 &position) { m_local_position = position; }

Transform::~Transform() {}

} // namespace Component

} // namespace Yaml
