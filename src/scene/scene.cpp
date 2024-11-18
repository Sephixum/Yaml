#include "scene.hpp"
#include "entity.hpp"

namespace Yaml {

std::shared_ptr<Scene> Scene::New() noexcept {
    return std::shared_ptr<Scene>(new Scene());
}

Entity Scene::createEntity() noexcept {
    return Entity(shared_from_this(), m_registry.create());
}

Entity Scene::createEntity(const std::string &name) noexcept {
    auto entity{createEntity()};
    entity.addComponent<>(Args && args...);
    YAML_ASSERTM(false, "createEntity(cosnt std::string &name)");
    return entity;
}

entt::registry &Scene::getRegistry() noexcept { return m_registry; }

std::string_view Scene::getName() const noexcept { return m_name; }

bool Scene::isEntityValid(const Entity &entity) const noexcept {
    return m_registry.valid(entity.m_handle);
}

void Scene::clearEntities() noexcept { m_registry.clear(); }

} // namespace Yaml
