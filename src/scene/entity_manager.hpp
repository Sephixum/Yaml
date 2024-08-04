#ifndef __ENTITY_MANAGER_HPP
#define __ENTITY_MANAGER_HPP

#include "core/assert.hpp"
#include "entity.hpp"

namespace Yaml {

class Scene;
class Entity;

template <typename... Component> struct EntityView {

    class iterator;
    using view_type = entt::view<entt::get_t<Component...>>;

  private:
    std::weak_ptr<Scene> m_owner_scene;
    view_type m_view;

  public:
    EntityView(std::shared_ptr<Scene> scene_ptr);

    Entity operator[](size_t i) {
        YAML_ASSERTM(i < size(), "Index out of range on view");
        return {m_view[i], m_owner_scene.lock()};
    }

    bool isEmpty() const noexcept { return m_view.empty(); }

    size_t size() const noexcept { return m_view.size(); }

    Entity getFront() noexcept { return {m_view[0], m_owner_scene.lock()}; }

    iterator begin();
    iterator end();

    class iterator {
      private:
        size_t m_index{0};
        EntityView<Component...> &m_view;

      public:
        using iterator_category = std::output_iterator_tag;
        using value_type = Entity;
        using difference_type = std::ptrdiff_t;
        using pointer = Entity *;
        using reference = Entity &;

      public:
        explicit iterator(EntityView<Component...> &view, size_t index = 0)
            : m_view(view) {}

        Entity operator*() const noexcept {
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
    };
};

template <typename... Component>
EntityView<Component...>::EntityView(std::shared_ptr<Scene> scene_ptr)
    : m_owner_scene(scene_ptr),
      view_type(m_owner_scene.lock()->getRegistry().view<Component...>()) {}

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
    EntityManager(std::shared_ptr<Scene> scene_ptr)
        : m_owner_scene(scene_ptr) {}

    // TODO:
    Entity create();
    // TODO:
    Entity create(const std::string &name);

    template <typename... Components>
    auto getEntitiesWithTypes() -> decltype(auto) {
        return m_registry.group<Components...>();
    }

    template <typename... Components>
    EntityView<Components...> getEntitiesWithType() {
        return EntityView<Components...>(m_owner_scene.lock());
    }

    entt::registry &getRegistry() { return m_registry; }

    // TODO::
    void clear();

    // TODO::
    bool EntityExists(Entity entity);
};

} // namespace Yaml

#endif // __ENTITY_MANAGER_HPP
