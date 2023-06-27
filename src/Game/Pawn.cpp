#include "Pawn.h"

namespace trc::game {
    Pawn::Pawn(int x, int y, chtype colour) :
		m_PosX(x), m_PosY(y), m_Colour((colour == 'W' || colour == 'B') ? colour : 'W')
    {

    }

    bool Pawn::IsInRange(int x, int y)
    {
		return true;
    }

    bool Knight::IsInRange(int x, int y)
    {
		return true;
    }

    bool Bishop::IsInRange(int x, int y)
    {
		return true;
    }

    bool Rook::IsInRange(int x, int y)
    {
        return true;
    }

    bool King::IsInRange(int x, int y)
    {
        return true;
    }

    bool Queen::IsInRange(int x, int y)
    {
        return true;
    }

} // namespace trc::game
