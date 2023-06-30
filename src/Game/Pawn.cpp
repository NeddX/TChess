#include "Pawn.h"
#include "Board.h"

namespace trc::game {
    Pawn::Pawn(int x, int y, chtype colour, const Board* owner) :
        m_PosX(x),
        m_PosY(y),
        m_Colour((colour == 'W' || colour == 'B') ? colour : 'W'),
        m_CurrentBoard(owner)
    {

    }

    Pawn::Pawn(int x, int y, chtype colour, chtype symbol, const Board* owner) :
        m_PosX(x),
        m_PosY(y),
        m_Colour((colour == 'W' || colour == 'B') ? colour : 'W'),
        m_Symbol(symbol),
        m_CurrentBoard(owner)
    {

    }

    bool Pawn::CanProceed(std::pair<int, int> pos, bool eatable) const
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
                    {
                        for (int i = 1; i <= 2; ++i)
                        {
                            if (m_CurrentBoard->GetPawnAt({ m_PosX, m_PosY - i }))
                                return false;
                        }
                        return true;
                    }
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
                    {
                        for (int i = 1; i <= 2; ++i)
                        {
                            if (m_CurrentBoard->GetPawnAt({ m_PosX, m_PosY + i }))
                                return false;
                        }
                        return true;
                    }
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

    std::vector<std::pair<int, int>> Pawn::GetMaxRangesFromCurrentPos() const
    {
        std::vector<std::pair<int, int>> ranges;
        if (m_Colour == 'B')
        {
            ranges.emplace_back(m_PosX + 1, m_PosY + 1);
            ranges.emplace_back(m_PosX - 1, m_PosY + 1);
        }
        else
        {
            ranges.emplace_back(m_PosX + 1, m_PosY - 1);
            ranges.emplace_back(m_PosX - 1, m_PosY - 1);
        }
        return ranges;
    }

    bool Knight::CanProceed(std::pair<int, int> pos, bool eatable) const
    {
        // Horizontal movement
        if (std::abs(pos.first - m_PosX) == 2 && std::abs(pos.second - m_PosY) == 1)
        {
            return true;
        }
        else if (std::abs(pos.second - m_PosY) == 2 && std::abs(pos.first - m_PosX) == 1)
        {
            return true;
        }
        return false;
    }

    std::vector<std::pair<int, int>> Knight::GetMaxRangesFromCurrentPos() const
    {
        return std::vector<std::pair<int, int>>
        {
            { m_PosX + 1, m_PosY + 2 },
            { m_PosX + 2, m_PosY + 1 },
            { m_PosX - 1, m_PosY + 2 },
            { m_PosX - 2, m_PosY + 1 },

            { m_PosX + 2, m_PosY - 1 },
            { m_PosX + 1, m_PosY - 2 },
            { m_PosX - 2, m_PosY - 1 },
            { m_PosX - 1, m_PosY - 2 }
        };
    }

    bool Bishop::CanProceed(std::pair<int, int> pos, bool eatable) const
    {
        if (std::abs(pos.first - m_PosX) == std::abs(pos.second - m_PosY))
        {
            if (pos.first - m_PosX > 0)
            {
                // Positive X
                if (pos.second - m_PosY > 0)
                {
                    // Positive Y
                    for (int i = 1; i < pos.second - m_PosY; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX + i, m_PosY + i }))
                            return false;
                    }
                }
                else
                {
                    // Negative Y
                    for (int i = 1; i < m_PosY - pos.second; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX + i, m_PosY - i }))
                            return false;
                    }
                }
            }
            else
            {
                // Negative X
                if (pos.second - m_PosY > 0)
                {
                    // Positive Y
                    for (int i = 1; i < pos.second - m_PosY; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX - i, m_PosY + i }))
                            return false;
                    }
                }
                else
                {
                    // Negative Y
                    for (int i = 1; i < m_PosY - pos.second; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX - i, m_PosY - i }))
                            return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    std::vector<std::pair<int, int>> Bishop::GetMaxRangesFromCurrentPos() const
    {
        std::vector<std::pair<int, int>> ranges;

        // THis is bad, really really bad but I gotta sleep.
        // There are also ranges that are out of bounds LOL.
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX + i, m_PosY + i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX - i, m_PosY + i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX + i, m_PosY - i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX - i, m_PosY - i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        return ranges;
    }

    bool Rook::CanProceed(std::pair<int, int> pos, bool eatable) const
    {
        if (pos.first == m_PosX || pos.second == m_PosY)
        {
            if (pos.first == m_PosX)
            {
                if (m_PosY - pos.second > 0)
                {
                    for (int i = 1; i < m_PosY - pos.second; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX, m_PosY - i }))
                            return false;
                    }
                }
                else
                {
                    for (int i = 1; i < pos.second - m_PosY; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX, m_PosY + i }))
                            return false;
                    }
                }
            }
            else if (pos.second == m_PosY)
            {
                if (m_PosX - pos.first > 0)
                {
                    for (int i = 1; i < m_PosX - pos.first; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX - i, m_PosY }))
                            return false;
                    }
                }
                else
                {
                    for (int i = 1; i < pos.first - m_PosX; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX + i, m_PosY }))
                            return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    std::vector<std::pair<int, int>> Rook::GetMaxRangesFromCurrentPos() const
    {
        std::vector<std::pair<int, int>> ranges;

        // This is awful too but you know the reasoning.
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX, m_PosY + i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX, m_PosY - i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX + i, m_PosY };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX - i, m_PosY };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        return ranges;
    }

    bool King::CanProceed(std::pair<int, int> pos, bool eatable) const
    {
        if (std::abs(pos.first - m_PosX) <= 1 && std::abs(pos.second - m_PosY) <= 1)
            return true;
        return false;
    }

    std::vector<std::pair<int, int>> King::GetMaxRangesFromCurrentPos() const
    {
        return std::vector<std::pair<int, int>>
        {
            { m_PosX + 1, m_PosY },
            { m_PosX - 1, m_PosY },

            { m_PosX, m_PosY + 1 },
            { m_PosX + 1, m_PosY + 1 },
            { m_PosX - 1, m_PosY + 1 },

            { m_PosX, m_PosY - 1 },
            { m_PosX + 1, m_PosY - 1 },
            { m_PosX - 1, m_PosY - 1 }
        };
    }

    bool Queen::CanProceed(std::pair<int, int> pos, bool eatable) const
    {
        if (pos.first == m_PosX || pos.second == m_PosY)
        {
            if (pos.first == m_PosX)
            {
                if (m_PosY - pos.second > 0)
                {
                    for (int i = 1; i < m_PosY - pos.second; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX, m_PosY - i }))
                            return false;
                    }
                }
                else
                {
                    for (int i = 1; i < pos.second - m_PosY; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX, m_PosY + i }))
                            return false;
                    }
                }
            }
            else if (pos.second == m_PosY)
            {
                if (m_PosX - pos.first > 0)
                {
                    for (int i = 1; i < m_PosX - pos.first; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX - i, m_PosY }))
                            return false;
                    }
                }
                else
                {
                    for (int i = 1; i < pos.first - m_PosX; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX + i, m_PosY }))
                            return false;
                    }
                }
            }
            return true;
        }
        else if (std::abs(pos.first - m_PosX) == std::abs(pos.second - m_PosY))
        {
            if (pos.first - m_PosX > 0)
            {
                // Positive X
                if (pos.second - m_PosY > 0)
                {
                    // Positive Y
                    for (int i = 1; i < pos.second - m_PosY; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX + i, m_PosY + i }))
                            return false;
                    }
                }
                else
                {
                    // Negative Y
                    for (int i = 1; i < m_PosY - pos.second; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX + i, m_PosY - i }))
                            return false;
                    }
                }
            }
            else
            {
                // Negative X
                if (pos.second - m_PosY > 0)
                {
                    // Positive Y
                    for (int i = 1; i < pos.second - m_PosY; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX - i, m_PosY + i }))
                            return false;
                    }
                }
                else
                {
                    // Negative Y
                    for (int i = 1; i < m_PosY - pos.second; ++i)
                    {
                        if (m_CurrentBoard->GetPawnAt({ m_PosX - i, m_PosY - i }))
                            return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    std::vector<std::pair<int, int>> Queen::GetMaxRangesFromCurrentPos() const
    {
        std::vector<std::pair<int, int>> ranges;

        // Same story.
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX + i, m_PosY + i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX - i, m_PosY + i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX + i, m_PosY - i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX - i, m_PosY - i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }

        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX, m_PosY + i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX, m_PosY - i };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX + i, m_PosY };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        for (int i = 0; i < 8; ++i)
        {
            std::pair<int, int> r = { m_PosX - i, m_PosY };
            if (m_CurrentBoard->GetPawnAt(r))
                break;
            ranges.emplace_back(r);
        }
        return ranges;
    }

} // namespace trc::game
