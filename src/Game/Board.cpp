#include "Board.h"

namespace trc::game {
    Board::Board(int rows, int cols, int cellSizeX, int cellSizeY) :
        m_Rows(rows), m_Cols(cols), m_CellSizeX(cellSizeX * 2), m_CellSizeY(cellSizeY)
    {
		m_Width = cols * cellSizeX * 2 + 1;
        m_Height = rows * cellSizeY + 1;

        m_Scene = std::make_unique<Scene>(0, 0, m_Width, m_Height);
    }

    void Board::Update()
    {
        // Draw the Board
		for (int y = 0; y < m_Height; ++y)
        {
            for (int x = 0; x < m_Width; ++x)
            {
                if (y == 0 || y == m_Height - 1)
                    m_Scene->RenderAt('#', x, y);
            	else if (y % m_CellSizeY == 0)
                    m_Scene->RenderAt('#', x, y);
            	else if (x % m_CellSizeX == 0)
                    m_Scene->RenderAt('#', x, y);
                else if (x == 0 || x == m_Width - 1)
                    m_Scene->RenderAt('#', x, y);
            }
		}

		// Render the pawns
		std::for_each(m_Pawns.begin(), m_Pawns.end(),
                      [&](auto& ptr)
                      {
                          m_Scene->RenderAt(
                              ptr->GetSymbol(),
                              ptr->GetPosX() * m_CellSizeX + (m_CellSizeX / 2) + 1,
                              ptr->GetPosY() * m_CellSizeY + (m_CellSizeY / 2));
                          m_Scene->RenderAt(
                              ptr->GetColour(),
                              ptr->GetPosX() * m_CellSizeX + (m_CellSizeX / 2) - 1,
                              ptr->GetPosY() * m_CellSizeY + (m_CellSizeY / 2));
                      });

        // Update the window (scene)
        m_Scene->Update();
    }
} // namespace trc::game
