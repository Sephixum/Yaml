#ifndef __SCENE_HPP
#define __SCENE_HPP

#include "core/core.hpp"
#include <entt/entt.hpp>

namespace Yaml {

class Entity;
template <typename... Componenets> class View;

class Scene : public std::enable_shared_from_this<Scene> {
  protected:
    entt::registry m_registry{};
    std::string m_name{};

    Scene() = default;

  public:
    Scene(const Scene &other) = delete;
    Scene &operator=(const Scene &rhs) = delete;
    Scene(Scene &&other) = default;
    Scene &operator=(Scene &&rhs) = default;
    virtual ~Scene() = default;

    [[nodiscard]] static std::shared_ptr<Scene> New() noexcept;
    [[nodiscard]] Entity createEntity() noexcept;
    [[nodiscard]] Entity createEntity(const std::string &name) noexcept;

    [[nodiscard]] entt::registry &getRegistry() noexcept;
    [[nodiscard]] std::string_view getName() const noexcept;

    //////////////////////////////////////////////////
    /////////////// Utility functions ////////////////
    //////////////////////////////////////////////////

    template <typename... Components>
    [[nodiscard]] decltype(auto) getEntitiesWith() noexcept {
        return View<Components...>(shared_from_this());
    }

    [[nodiscard]] bool isEntityValid(const Entity &entity) const noexcept;
    void clearEntities() noexcept;

    template <typename... Components> void clearEntities() noexcept {
        m_registry.clear<Components...>();
    }
};

} // namespace Yaml

#endif // __SCENE_HPP
