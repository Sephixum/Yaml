#include "entity.hpp"

namespace Yaml {

Entity::Entity(std::shared_ptr<Scene> scene, entt::entity handle)
    : m_scene{scene},  //
      m_handle{handle} //
{}

std::shared_ptr<Scene> Entity::getParentScene() const noexcept {
  auto scene = m_scene.lock();
  YAML_ASSERTM(scene, "Scene is NULL !!");

  return scene;
}

entt::entity Entity::getHandle() const noexcept { return m_handle; }

Entity::operator entt::entity() const noexcept { return m_handle; }

Entity::operator bool() const noexcept {
  return m_handle != entt::null && !m_scene.expired();
}

bool Entity::operator==(const Entity &other) const noexcept {
  return (m_handle == other.m_handle) &&
         (m_scene.lock() == other.m_scene.lock());
}

bool Entity::operator!=(const Entity &other) const noexcept {
  return !(*this == other);
}

void Entity::destroy() noexcept {
  auto scene = m_scene.lock();
  YAML_ASSERTM(scene, "Scene is NULL !!");

  scene->getRegistry().destroy(m_handle);
  m_scene.reset();
}

} // namespace Yaml
