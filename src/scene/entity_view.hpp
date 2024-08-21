#ifndef __ENTITY_VIEW_HPP
#define __ENTITY_VIEW_HPP

#include "entity.hpp"
#include "scene.hpp"

namespace Yaml {

template <typename... Componenets> class EntityView {

  friend class Scene;
  using view_type = entt::view<entt::get_t<Componenets...>>;

private:
  std::weak_ptr<Scene> m_scene{};
  view_type m_view;

public:
  EntityView(std::shared_ptr<Scene> scene) : m_scene{scene} {
    auto locked_scene = m_scene.lock();
    YAML_ASSERTM(locked_scene, "Scene is NULL !!");

    m_view = locked_scene->getRegistry().view<Componenets...>();
  }

  EntityView(const EntityView &other) = delete;
  EntityView &operator=(const EntityView &rhs) = delete;
  EntityView(EntityView &&other) = default;
  EntityView &operator=(EntityView &&rhs) = default;
  ~EntityView() = default;

  class iterator;

  [[nodiscard]] [[deprecated]] Entity operator[](int32 idx) noexcept {
    YAML_ASSERTM(idx < size(), "Index out of range.");

    auto scene = m_scene.lock();
    YAML_ASSERTM(scene, "Scene is NULL !!");
    YAML_ASSERTM(static_cast<size_t>(idx) < m_view.size(),
                 "Index out of range in view.");

    return Entity(scene, *(m_view.begin() + idx));
  }

  bool isEmpty() const noexcept { return m_view.empty(); }

  int32 size() const noexcept {
    return static_cast<int32>(std::distance(m_view.begin(), m_view.end()));
  }

  Entity getFront() const noexcept { return Entity(m_view[0], m_scene.lock()); }

public:
  class iterator {
  private:
    int32 m_index{0};
    EntityView<Componenets...> &m_view;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Entity;
    using difference_type = std::ptrdiff_t;
    using pointer = Entity *;
    using reference = Entity &;

    explicit iterator(EntityView<Componenets...> &view, int32 index = 0)
        : m_index{index}, m_view{view} {}

    Entity operator*() const noexcept { return m_view[m_index]; }

    iterator &operator++() {
      ++m_index;
      return *this;
    }

    iterator operator++(int) {
      iterator temp{*this};
      ++(*this);
      return temp;
    }

    bool operator!=(const iterator &rhs) const {
      return m_index != rhs.m_index;
    }
  };

  iterator begin() noexcept { return iterator(*this, 0); }
  iterator end() noexcept { return iterator(*this, size()); }

  iterator cbegin() const noexcept { return iterator(*this, 0); }
  iterator cend() const noexcept { return iterator(*this, size()); }
};

} // namespace Yaml

#endif // __SCENE_HPP