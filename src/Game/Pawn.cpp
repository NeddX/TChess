#include "Pawn.h"

namespace trc::game {
    Pawn::Pawn(int x, int y, chtype colour) :
        m_PosX(x), m_PosY(y), m_Colour((colour == 'W' || colour == 'B') ? colour : 'W')
    {

    }

    Pawn::Pawn(int x, int y, chtype colour, chtype symbol) :
        m_PosX(x), m_PosY(y), m_Colour((colour == 'W' || colour == 'B') ? colour : 'W'), m_Symbol(symbol)
    {

    }

    bool Pawn::IsInRange(std::pair<int, int> pos, bool eatable)
    {
        if (m_Colour == 'W')
        {
            if (eatable)
            {
                if (std::abs(m_PosX - pos.first) == 1 && m_PosY - pos.second == 1)
                    return true;
            }
            else
            {
                if (m_MoveCount == 0)
                {
                    if (pos.first == m_PosX && m_PosY - pos.second > 0 && m_PosY - pos.second <= 2)
                        return true;
                }
                else
                {
                    if (pos.first == m_PosX && m_PosY - pos.second == 1)
                        return true;
                }
            }
        }
        else
        {
            if (eatable)
            {
                if (std::abs(pos.first - m_PosX) == 1 && pos.second - m_PosY == 1)
                    return true;
            }
            else
            {
                if (m_MoveCount == 0)
                {
                    if (pos.first == m_PosX && pos.second - m_PosY > 0 && pos.second - m_PosY <= 2)
                        return true;
                }
                else
                {
                    if (pos.first == m_PosX && pos.second - m_PosY == 1)
                        return true;
                }
            }
        }
        return false;
    }

    bool Knight::IsInRange(std::pair<int, int> pos, bool eatable)
    {
        return true;
    }

    bool Bishop::IsInRange(std::pair<int, int> pos, bool eatable)
    {
        if (std::abs(pos.first - m_PosX) == std::abs(pos.second - m_PosY))
            return true;
        return false;
    }

    bool Rook::IsInRange(std::pair<int, int> pos, bool eatable)
    {
        if (pos.first == m_PosX || pos.second == m_PosY)
            return true;
        return false;
    }

    bool King::IsInRange(std::pair<int, int> pos, bool eatable)
    {
        return true;
    }

    bool Queen::IsInRange(std::pair<int, int> pos, bool eatable)
    {
        if (pos.first == m_PosX || pos.second == m_PosY)
            return true;
        else if (std::abs(pos.first - m_PosX) == std::abs(pos.second - m_PosY))
            return true;
        return false;
    }

} // namespace trc::game
