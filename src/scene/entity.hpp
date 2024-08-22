#ifndef __ENTITY_HPP
#define __ENTITY_HPP

#include "scene.hpp"

namespace Yaml {

template <typename... Componenets> class EntityView;

class Entity {

  friend class Scene;
  template <typename... Componenets> friend class EntityView;

private:
  std::weak_ptr<Scene> m_scene{};
  entt::entity m_handle{entt::null};

  explicit Entity(std::shared_ptr<Scene> scene, entt::entity handle);

public:
  [[nodiscard]] std::shared_ptr<Scene> getParentScene() const noexcept;
  [[nodiscard]] entt::entity getHandle() const noexcept;

  //////////////////////////////////////////////////
  /////////////// Utility functions ////////////////
  //////////////////////////////////////////////////

  operator entt::entity() const noexcept;
  operator bool() const noexcept;
  bool operator==(const Entity &other) const noexcept;
  bool operator!=(const Entity &other) const noexcept;

  void destroy() noexcept;

  template <typename Component> bool hasComponent() noexcept {
    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is NULL");
    return scene->getRegistry().all_of<Component>(m_handle);
  }

  template <typename... Components> bool hasComponents() noexcept {
    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is NULL");
    return scene->getRegistry().all_of<Components...>(m_handle);
  }

  template <typename Component, typename... Args>
  auto addComponent(Args &&...args) noexcept -> decltype(auto) {
    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is NULL");
    if (hasComponent<Component>()) {
      YAML_WARN(std::format("Trying to add already existing component !!"));
    }

    return scene->getRegistry().emplace<Component>(m_handle,
                                                   std::forward<Args>(args)...);
  }

  template <typename Component, typename... Args>
  auto getOrAddComponent(Args &&...args) noexcept -> decltype(auto) {
    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is NULL");

    return scene->getRegistry().get_or_emplace<Component>(
        m_handle, std::forward<Args>()...);
  }

  template <typename Component> auto getComponent() noexcept -> decltype(auto) {
    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is null!!");
    return scene->getRegistry().get<Component>(m_handle);
  }

  template <typename Component>
  auto tryGetComponent() noexcept -> decltype(auto) {
    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is null!!");
    return scene->getRegistry().try_get<Component>(m_handle);
  }

  template <typename Component> void removeComponent() noexcept {
    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is null!!");
    if (!hasComponent<Component>()) {
      YAML_WARN("Removing component the entity does not contain!!");
    }
    scene->getRegistry().remove<Component>(m_handle);
  }
};

} // namespace Yaml

#endif // __ENTITY_HPP
