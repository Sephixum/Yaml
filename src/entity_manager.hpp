#ifndef __ENTITY_MANAGER_HPP
#define __ENTITY_MANAGER_HPP

#include "core/core.hpp"
#include "entity.hpp"

namespace Yaml {

class Scene;
class Entity;

template <typename... Component> struct EntityView {
  class iterator;
  using view_type = entt::view<entt::get_t<Component...>>;

public:
  EntityView(std::shared_ptr<Scene> scene_ptr);

  Entity operator[](size_t i) {}

  bool isEmpty() const {}
  size_t size() const {}
  Entity getFront() {}

  iterator begin();
  iterator end();

  class iterator {
  public:
    using iterator_category = std::output_iterator_tag;
    using value_type = Entity;
    using difference_type = std::ptrdiff_t;
    using pointer = Entity *;
    using reference = Entity &;

    explicit iterator(EntityView<Component...> &view, size_t index = 0)
        : view{view}, {}

    Entity operator*() noexcept const {
      return m_view[static_cast<int>(m_index)];
    }

    iterator &operator++() {
      ++m_index;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator!=(const iterator &rhs) const {
      return m_index != rhs.m_index;
    }

  private:
    size_t m_index{0};
    EntityView<Component...> &m_view;
  };

private:
  std::weak_ptr<Scene> m_owner_scene;
  view_type m_view;
};

template <typename... Component>
EntityView<Component...>::EntityView(std::shared_ptr<Scene> scene_ptr)
    : m_owner_scene(scene_ptr),
      view_type(m_owner_scene->getRegistry().view<Component...>()) {}

template <typename... Component>
typename EntityView<Component...>::iterator EntityView<Component...>::begin() {}

template <typename... Component>
typename EntityView<Component...>::iterator EntityView<Component...>::end() {
  return EntityView<Component...>::iterator(*this, size());
}

class EntityManager {
private:
  entt::registry m_registry{};
  std::weak_ptr<Scene> m_owner_scene;

public:
  EntityManager(std::shared_ptr<Scene> scene_ptr) : m_owner_scene(scene_ptr) {}

  Entity create();
  Entity create(std::string_view name);

  template <typename... Components>
  auto getEntitiesWithTypes() -> decltype(auto) {
    return m_registry.group<Components...>();
  }

  template <typename... Components>
  EntityView<Components...> getEntitiesWithType() {
    return EntityView<Components...>(m_owner_scene.lock());
  }

  entt::registry &getRegistry() { return m_registry; }

  void clear();

  bool EntityExists(Entity entity);
};

} // namespace Yaml

#endif // __ENTITY_MANAGER_HPP