#include "Board.h"

namespace trc::game {
    Board::Board(int rows, int cols, int cellSizeX, int cellSizeY) :
        m_Rows(rows), m_Cols(cols), m_CellSizeX(cellSizeX * 2), m_CellSizeY(cellSizeY)
    {
        m_Width = cols * cellSizeX * 2 + 1;
        m_Height = rows * cellSizeY + 1;

        m_Scene = std::make_unique<Scene>(0, 0, m_Width, m_Height);
        m_Map.resize(m_Rows * m_Cols);
        std::fill(m_Map.begin(), m_Map.end(), nullptr);
    }

    void Board::Update()
    {
        // Draw the Board
        const int offset_x = 4;
        const int offset_y = 2;
        const int min_x = 0;
        const int min_y = 0;
        const int max_x = m_Width;
        const int max_y = m_Height;
        for (int y = min_y; y < max_y; ++y)
        {
            for (int x = min_x; x < max_x; ++x)
            {
                if (y == min_y || y == max_y - 1)
                    m_Scene->RenderAt('#', x + offset_x, y + offset_y);
            	else if (x == min_x || x == max_x - 1)
                    m_Scene->RenderAt('#', x + offset_x, y + offset_y);
                /*if (y == min_y || y == max_y - 1)
                    m_Scene->RenderAt('#', x + offset, y + offset);
                else if (y % m_CellSizeY == 0)
                    m_Scene->RenderAt('#', x + offset, y + offset);
                else if (x % m_CellSizeX == 0)
                    m_Scene->RenderAt('#', x + offset, y + offset);
                else if (x == min_y || x == max_x - 1)
                    m_Scene->RenderAt('#', x + offset, y + offset);*/
            }
        }

        // Render the pawns
        std::for_each(m_Pawns.begin(), m_Pawns.end(),
                      [&](auto& ptr)
                      {
                          auto pos = ptr->GetPos();
                          m_Scene->RenderAt(
                              ptr->GetSymbol(),
                              pos.first * m_CellSizeX + (m_CellSizeX / 2) + 1 + offset_x,
                              pos.second * m_CellSizeY + (m_CellSizeY / 2) + offset_y);
                          m_Scene->RenderAt(
                              ptr->GetColour(),
                              pos.first * m_CellSizeX + (m_CellSizeX / 2) - 1 + offset_x,
                              pos.second * m_CellSizeY + (m_CellSizeY / 2) + offset_y);
                      });

        // Update the window (scene)
        m_Scene->Update();
    }
} // namespace trc::game
