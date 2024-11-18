#ifndef __ENTITY_VIEW_HPP
#define __ENTITY_VIEW_HPP

#include "entity.hpp"
#include "scene.hpp"
#include <functional>
#include <ranges>

namespace Yaml {

template <typename... Components> class View {

    friend class Scene;

  private:
    std::weak_ptr<Scene> m_scene{};
    entt::view<entt::get_t<Components...>> m_view;

  public:
    explicit View(std::shared_ptr<Scene> scene) : m_scene{scene} {
        auto locked_scene{m_scene.lock()};
        YAML_ASSERTM(locked_scene,
                     "View being constructed from a non existing scene!!");
        m_view = locked_scene->getRegistry().view<Components...>();
    }

    View(const View &other) = default;

    auto operator=(const View &rhs) -> View & = default;

    View(View &&other) noexcept
        : m_scene{std::move(other.m_scene)}, //
          m_view{std::move(other.m_view)}    //
    {
        other.m_scene.reset();
    }

    auto operator=(View &&rhs) noexcept -> View & {
        if (this != &rhs) {
            m_scene = std::move(rhs.m_scene);
            m_view = std::move(rhs.m_view);
            rhs.m_scene.reset();
        }
        return *this;
    }

    ~View() = default;

    class iterator;
    [[nodiscard]] auto begin() const noexcept { return iterator{*this, 0}; }
    [[nodiscard]] auto end() const noexcept { return iterator{*this, size()}; }

    [[nodiscard]] auto asRange() const noexcept {
        return std::ranges::subrange{begin(), end()};
    }

    [[nodiscard]] auto operator[](std::size_t idx) noexcept {
        YAML_ASSERTM(idx < size(), "Index out of range.");

        auto scene = m_scene.lock();
        YAML_ASSERTM(scene, "Scene is NULL !!");
        YAML_ASSERTM(idx < m_view.size(), "Index out of range in view.");

        return Entity{scene, *(m_view.begin() + idx)};
    }

    [[nodiscard]] bool isEmpty() const noexcept { return m_view.empty(); }

    [[nodiscard]] std::size_t size() const noexcept {
        return static_cast<std::size_t>(
            std::distance(m_view.begin(), m_view.end()));
    }

  public:
    class iterator {
      private:
        std::size_t m_index{0};
        std::reference_wrapper<View> m_view;

      public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Entity;
        using difference_type = std::ptrdiff_t;
        using pointer = Entity *;
        using reference = Entity &;

        constexpr explicit iterator(View &view, std::size_t index = 0)
            : m_index{index}, m_view{view} {}

        [[nodiscard]] Entity operator*() const noexcept {
            return m_view.get()[m_index];
        }

        iterator &operator++() {
            ++m_index;
            return *this;
        }

        iterator operator++(int32) {
            iterator temp{*this};
            ++(*this);
            return temp;
        }

        [[nodiscard]] constexpr bool
        operator==(const iterator &rhs) const noexcept {
            return m_index == rhs.m_index;
        }
        [[nodiscard]] constexpr bool
        operator!=(const iterator &rhs) const noexcept {
            return !(*this == rhs);
        }
        [[nodiscard]] constexpr bool
        operator<(const iterator &rhs) const noexcept {
            return m_index < rhs.m_index;
        }
        [[nodiscard]] constexpr bool
        operator<=(const iterator &rhs) const noexcept {
            return m_index <= rhs.m_index;
        }
        [[nodiscard]] constexpr bool
        operator>(const iterator &rhs) const noexcept {
            return m_index > rhs.m_index;
        }
        [[nodiscard]] constexpr bool
        operator>=(const iterator &rhs) const noexcept {
            return m_index >= rhs.m_index;
        }
    };
};

} // namespace Yaml

#endif // __SCENE_HPP
