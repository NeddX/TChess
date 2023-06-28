#include "Pawn.h"

namespace trc::game {
    Pawn::Pawn(int x, int y, chtype colour) :
		m_PosX(x), m_PosY(y), m_Colour((colour == 'W' || colour == 'B') ? colour : 'W')
    {

    }

    bool Pawn::IsInRange(std::pair<int, int> pos)
    {
		return true;
    }

    bool Knight::IsInRange(std::pair<int, int> pos)
    {
		return true;
    }

    bool Bishop::IsInRange(std::pair<int, int> pos)
    {
		return true;
    }

    bool Rook::IsInRange(std::pair<int, int> pos)
    {
        return true;
    }

    bool King::IsInRange(std::pair<int, int> pos)
    {
        return true;
    }

    bool Queen::IsInRange(std::pair<int, int> pos)
    {
        return true;
    }

} // namespace trc::game
