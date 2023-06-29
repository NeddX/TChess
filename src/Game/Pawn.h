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
        int m_MoveCount = 0;
        chtype m_Symbol = 'P';
        chtype m_Colour = 'W';

    public:
        Pawn(int x, int y, chtype colour);

    protected:
        Pawn(int x, int y, chtype colour, chtype symbol);

    public:
        inline std::pair<int, int> GetPos() const { return { m_PosX, m_PosY }; }
        inline int GetMoveCount() const { return m_MoveCount; }
        inline chtype GetColour() const { return m_Colour; }
        inline chtype GetSymbol() const { return m_Symbol; }
        inline void SetMoveCount(int newCount) { m_MoveCount = newCount; }
        inline void SetColour(char newColour) { m_Colour = (newColour == 'W' || newColour == 'B') ? newColour : m_Colour; }
        inline void SetPos(std::pair<int, int> newPos) { m_PosX = newPos.first; m_PosY = newPos.second; }

    public:
        virtual bool IsInRange(std::pair<int, int> pos, bool eatable = false);
    };

    class Knight : public Pawn
    {
    protected:
        chtype m_Symbol = 'K';

    public:
        bool IsInRange(std::pair<int, int> pos, bool eatable = false) override;
    };

    class Bishop : public Pawn
    {
    public:
        Bishop(int x, int y, chtype colour) : Pawn(x, y, colour, 'B') { };

    public:
        bool IsInRange(std::pair<int, int> pos, bool eatable = false) override;
    };

    class Rook : public Pawn
    {
    public:
        Rook(int x, int y, chtype colour) : Pawn(x, y, colour, 'R') { };

    public:
        bool IsInRange(std::pair<int, int> pos, bool eatable = false) override;
    };

    class King : public Pawn
    {
    public:
        King(int x, int y, chtype colour) : Pawn(x, y, colour, 'K') { }

    public:
        bool IsInRange(std::pair<int, int> pos, bool eatable = false) override;
    };

    class Queen : public Pawn
    {
    public:
        Queen(int x, int y, chtype colour) : Pawn(x, y, colour, 'Q') { }

    public:
        bool IsInRange(std::pair<int, int> pos, bool eatable = false) override;
    };
} // namespace trc::game

#endif // TRC_GAME_PAWN_H
