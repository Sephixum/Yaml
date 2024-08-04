#ifndef __ENTITY_H
#define __ENTITY_H

#include "scene.hpp"

namespace Yaml {

class Entity {

  friend class EntityManager;

private:
  entt::entity m_handler{entt::null};
  std::weak_ptr<Scene> m_owner_scene;

  Entity() = default;
  Entity(entt::entity handler, std::shared_ptr<Scene> scene_ptr)
      : m_handler(handler), m_owner_scene(scene_ptr) {}

  template <typename C, typename... Args> void addComponent(Args &&...args) {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    if (hasComponent<C>()) {
      YAML_WARN(std::format(
                    "Trying to add component of type({}) that already exists!!",
                    typeid(C).name())
                    .c_str());
    }
    return m_owner_scene.lock()->getRegistry().emplace<C>(
        m_handler, std::forward<Args>(args)...);
  }

  template <typename C, typename... Args>
  auto getOrAddComponent(Args &&...args) -> decltype(auto) {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    return scene_ptr->getRegistry().get_or_emplace<C>(
        m_handler, std::forward<Args>(args)...);
  }

  template <typename C> auto getComponent() noexcept -> decltype(auto) {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    return scene_ptr->getRegistry().get<C>(m_handler);
  }

  template <typename C> auto tryGetComponent() -> decltype(auto) {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    return scene_ptr->getRegistry().try_get<C>(m_handler);
  }

  template <typename C> void RemoveComponent() noexcept {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    if (!hasComponent<C>()) {
      YAML_WARN(std::format("Removing component of type({}) that the "
                            "entity does not have!!",
                            typeid(C).name())
                    .c_str());
    }
    scene_ptr->getRegistry().remove<T>()
  }

  template <typename C> bool hasComponent() {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    return scene_ptr->getRegistry().all_of<C>(m_handler);
  }

  entt::entity getHandle() const noexcept { return m_handler; }

  void destroy() noexcept {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    scene_ptr->getRegistry().destroy(m_handler);
  }

  bool valid() const noexcept {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    return scene_ptr->getRegistry().valid(m_handler) &&
           !m_owner_scene.expired();
  }

  std::shared_ptr<Scene> getScene() const noexcept {
    auto scene_ptr = m_owner_scene.lock();
    YAML_ASSERTM(scene_ptr, "Scene is null!!");
    return scene_ptr;
  }

  operator entt::entity() const noexcept { return m_handler; }

  operator bool() const noexcept {
    return m_handler != entt::null && !m_owner_scene.expired();
  }

  bool operator==(const Entity &other) const noexcept {
    return (m_handler == other.m_handler) &&
           (m_owner_scene.lock() == other.m_owner_scene.lock());
  }

  bool operator!=(const Entity &other) const noexcept {
    return !(*this == other);
  }
};

} // namespace Yaml

#endif // __ENTITY_H