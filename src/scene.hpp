#ifndef __SCENE_H
#define __SCENE_H

#include "core/core.hpp"
#include <entt/entt.hpp>

namespace Yaml {

class Entity;
class EntityManager;

class Scene : public std::enable_shared_from_this<Scene> {
private:
  std::unique_ptr<EntityManager> m_entity_manager;

  Scene() = default;

  std::shared_ptr<Scene> _getSharedFromThis() noexcept;

public:
  static std::shared_ptr<Scene> createScene() noexcept;

  Entity createEntity() noexcept;

  entt::registry &getRegistry();
};

} // namespace Yaml

#endif // __SCENE_H