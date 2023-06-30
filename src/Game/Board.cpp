#include "Board.h"

namespace trc::game {
    Board::Board(int rows,
                 int cols,
                 int cellSizeX,
                 int cellSizeY,
                 std::function<void(Pawn&, Pawn&)> onPawnEat) :
        m_Rows(rows),
        m_Cols(cols),
        m_CellSizeX(cellSizeX * 2),
        m_CellSizeY(cellSizeY),
        Event_OnPawnEat(onPawnEat)
    {
        m_Width = cols * cellSizeX * 2 + 1;
        m_Height = rows * cellSizeY + 1;

        m_OffsetX = m_OffsetY = 3;

        m_Scene = std::make_unique<Scene>(
            0,
            0,
            m_Width + m_OffsetX * 2,
            m_Height + m_OffsetY
        );
        m_Map.resize(m_Rows * m_Cols);
        std::fill(m_Map.begin(), m_Map.end(), nullptr);
    }

    void Board::Update()
    {
        // Draw the Board
        const int offset_x = m_OffsetX * 2;
        const int offset_y = m_OffsetY;
        const int min_x = 0;
        const int min_y = 0;
        const int max_x = m_Width;
        const int max_y = m_Height;
        for (int y = min_y; y < max_y; ++y)
        {
            for (int x = min_x; x < max_x; ++x)
            {
                if (y % m_CellSizeY == 0 && x <= offset_x && x == offset_x / 2)
                    m_Scene->RenderAt('8' - y / m_CellSizeY, x, y + offset_y + m_CellSizeY / 2);
                else if (x % m_CellSizeX == 0 && y == offset_y / 2 && x / m_CellSizeX <= 7)
                    m_Scene->RenderAt('A' + x / m_CellSizeX, x + offset_x + m_CellSizeX / 2, y);

                 if ((y == min_y || y == max_y - 1) ||
                     (y % m_CellSizeY == 0) ||
                     (x % m_CellSizeX == 0) ||
                     (x == min_y || x == max_x - 1))
                         m_Scene->RenderAt('#', x + offset_x, y + offset_y);
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
