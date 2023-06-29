#ifndef TRC_GAME_SCENE_H
#define TRC_GAME_SCENE_H

#include <sdafx.h>

namespace trc::game {
    class Scene
    {
    private:
        int m_Width;
        int m_Height;
        WINDOW* m_Window;
        std::vector<chtype> m_Buffer;

    public:
        Scene(int x, int y, int width, int height);
        ~Scene();

    public:
        inline int GetKey() const { return getch(); }
        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

    public:
        void Update();
        void RenderAt(chtype c, int x, int y);
    };
} // namespace trc::game

#endif // TRC_GAME_SCENE_H
