#ifndef TRC_GAME_PAWN_H
#define TRC_GAME_PAWN_H

#include <cstdint>
#include <sdafx.h>

namespace trc::game {
    enum class PawnType : uint16_t
    {
    	Pawn	= 0x0001,
        Knight	= 0x0002,
        Bishop	= 0x0004,
        Rook	= 0x0008,
        King	= 0x0010,
        Queen	= 0x0020
	};

    class Pawn
    {
    protected:
        int m_PosX = 0;
        int m_PosY = 0;
        chtype m_Symbol = 'P';
        chtype m_Colour = 'W';

    public:
		Pawn(int x, int y, chtype colour);

    public:
        inline int GetPosX() const { return m_PosX; }
        inline int GetPosY() const { return m_PosY; }
        inline chtype GetColour() const { return m_Colour; }
        inline chtype GetSymbol() const { return m_Symbol; }
        inline void SetColour(char newColour) { m_Colour = (newColour == 'W' || newColour == 'B') ? newColour : m_Colour; }
        inline void SetPosX(int newX) { m_PosX = newX; }
        inline void SetPosY(int newY) { m_PosY = newY; }

    public:
        virtual bool IsInRange(int x, int y);
    };

    class Knight : public Pawn
    {
    protected:
		chtype m_Symbol = 'K';

    public:
        bool IsInRange(int x, int y) override;
    };

    class Bishop : public Pawn
    {
    protected:
		chtype m_Symbol = 'B';

    public:
        bool IsInRange(int x, int y) override;
    };

    class Rook : public Pawn
    {
    protected:
		chtype m_Symbol = 'R';

    public:
        bool IsInRange(int x, int y) override;
    };

    class King : public Pawn
    {
    protected:
		chtype m_Symbol = 'K';

    public:
        bool IsInRange(int x, int y) override;
    };

    class Queen : public Pawn
    {
    protected:
        chtype m_Symbol = 'Q';

    public:
        bool IsInRange(int x, int y) override;
    };
} // namespace trc::game

#endif // TRC_GAME_PAWN_H
