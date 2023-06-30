#include "Scene.h"
#include <curses.h>

namespace trc::game {
    Scene::Scene(int x, int y, int width, int height) :
        m_Width(width), m_Height(height)
    {
        initscr();
        noecho();
        nodelay(stdscr, 1);
        //curs_set(1);

        m_Buffer.resize(m_Width * m_Height);
        std::memset(m_Buffer.data(), ' ', m_Buffer.size() * sizeof(chtype));

        m_Window = newwin(m_Height, m_Width, x, y);
        //box(m_Window, 0, 0);
        wrefresh(m_Window);
    }

    Scene::~Scene()
    {
        curs_set(1);
        endwin();
    }

    void Scene::Update()
    {
        //wclear(m_Window);

        for (int y = 0; y < m_Height; ++y)
        {
            for (int x = 0; x < m_Width; ++x)
            {
                chtype c = m_Buffer[y * m_Width + x];
                mvwaddch(m_Window, y, x, c);
            }
        }

        std::memset(m_Buffer.data(), ' ', m_Buffer.size() * sizeof(chtype));
        //box(m_Window, 0, 0);
        wrefresh(m_Window);
    }

    void Scene::RenderAt(chtype c, int x, int y)
    {
        m_Buffer[y * m_Width + x] = c;
    }
} // namespace trc::game
