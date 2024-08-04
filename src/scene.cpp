#include "scene.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"

namespace Yaml {
std::shared_ptr<Scene> Scene::_getSharedFromThis() noexcept {
  return shared_from_this();
}

entt::registry &Scene::getRegistry() { return m_entity_manager->getRegistry(); }

} // namespace Yaml