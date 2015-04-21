#ifndef _ANIMATOR_HPP_
#define _ANIMATOR_HPP_
#include <SDL.h>
#include <memory>
#include <vector>
#include <algorithm>
#include "..\Definitions\Definitions.hpp"
#include "..\Definitions\Rect.hpp"
#include "Animation.hpp"

/*  
 *  Animation class handles procession of animation of Rects.
 */
class Animator
{
    public:
        template<typename T, typename... Ts>
        void add(Ts&&... vals) { m_animation.emplace_back(std::make_shared<T>(std::forward<Ts>(vals)...)); } // black magic
        void animate()
        {
            m_animation.erase(std::remove_if(begin(m_animation), end(m_animation), [](std::shared_ptr<Animation>& m){ return m->animate(); }), end(m_animation));
        }
        bool can_play() const { return m_animation.empty(); }
        void clear() { m_animation.clear(); }

    private:
        std::vector<std::shared_ptr<Animation>> m_animation;
};


#endif // _ANIMATOR_HPP_
