#ifndef __COMPONENTS_HPP
#define __COMPONENTS_HPP

#include <glm/ext.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Yaml::Component {

struct Tag {
    std::string tag{};
};

struct Transform {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};

    glm::mat4 getMatrix() const noexcept {
        auto translation_mat{glm::translate({1.0f}, position)};
        auto rotation_mat{glm::mat4_cast(rotation)};
        auto scale_mat{glm::scale({1.0f}, scale)};
        return translation_mat * rotation_mat * scale_mat;
    }
};

} // namespace Yaml::Component

#endif // __COMPONENTS_HPP
