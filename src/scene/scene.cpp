#include "scene.hpp"
#include "entity.hpp"

namespace Yaml {

std::shared_ptr<Scene> Scene::create() noexcept {
  return std::shared_ptr<Scene>(new Scene());
}

Entity Scene::createEntity() noexcept {
  return Entity(shared_from_this(), m_registry.create());
}

Entity Scene::createEntity(const std::string &name) noexcept {
  YAML_ASSERTM(false, "createEntity(cosnt std::string &name)");

  auto entity{createEntity()};
  return entity;
}

entt::registry &Scene::getRegistry() noexcept { return m_registry; }

const std::string &Scene::getName() const noexcept { return m_name; }

bool Scene::isEntityValid(const Entity &entity) {
  return m_registry.valid(entity.m_handle);
}

void Scene::clearEntities() noexcept { m_registry.clear(); }

} // namespace Yaml