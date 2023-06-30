#ifndef TRC_GAME_PAWN_H
#define TRC_GAME_PAWN_H

#include <cstdint>
#include <sdafx.h>

namespace trc::game {
    // Forward declerations
    class Board;

    class Pawn
    {
    protected:
        int m_PosX = 0;
        int m_PosY = 0;
        int m_MoveCount = 0;
        chtype m_Symbol = 'P';
        chtype m_Colour = 'W';
        const Board* const m_CurrentBoard;

    public:
        Pawn(int x, int y, chtype colour, const Board* owner);
        virtual ~Pawn() = default;

    protected:
        Pawn(int x, int y, chtype colour, chtype symbol, const Board* owner);

    public:
        inline std::pair<int, int> GetPos() const { return { m_PosX, m_PosY }; }
        inline int GetMoveCount() const { return m_MoveCount; }
        inline chtype GetColour() const { return m_Colour; }
        inline chtype GetSymbol() const { return m_Symbol; }
        inline void SetMoveCount(int newCount) { m_MoveCount = newCount; }
        inline void SetColour(char newColour) { m_Colour = (newColour == 'W' || newColour == 'B') ? newColour : m_Colour; }
        inline void SetPos(std::pair<int, int> newPos) { m_PosX = newPos.first; m_PosY = newPos.second; }

    public:
        virtual bool CanProceed(std::pair<int, int> pos, bool eatable = false) const;
        virtual std::vector<std::pair<int, int>> GetMaxRangesFromCurrentPos() const;
    };

    // Should've used a more data oriented approach here
    // instead of this inheritance fiesta we got here,
    // but unfortunately, I'm lazy.
    class Knight : public Pawn
    {
    public:
        Knight(int x, int y, chtype colour, const Board* owner) : Pawn(x, y, colour, 'N', owner) { };

    public:
        bool CanProceed(std::pair<int, int> pos, bool eatable = false) const override;
        std::vector<std::pair<int, int>> GetMaxRangesFromCurrentPos() const override;
    };

    class Bishop : public Pawn
    {
    public:
        Bishop(int x, int y, chtype colour, const Board* owner) : Pawn(x, y, colour, 'B', owner) { };

    public:
        bool CanProceed(std::pair<int, int> pos, bool eatable = false) const override;
        std::vector<std::pair<int, int>> GetMaxRangesFromCurrentPos() const override;
    };

    class Rook : public Pawn
    {
    public:
        Rook(int x, int y, chtype colour, const Board* owner) : Pawn(x, y, colour, 'R', owner) { };

    public:
        bool CanProceed(std::pair<int, int> pos, bool eatable = false) const override;
        std::vector<std::pair<int, int>> GetMaxRangesFromCurrentPos() const override;
    };

    class King : public Pawn
    {
    public:
        King(int x, int y, chtype colour, const Board* owner) : Pawn(x, y, colour, 'K', owner) { }

    public:
        bool CanProceed(std::pair<int, int> pos, bool eatable = false) const override;
        std::vector<std::pair<int, int>> GetMaxRangesFromCurrentPos() const override;
    };

    class Queen : public Pawn
    {
    public:
        Queen(int x, int y, chtype colour, const Board* owner) : Pawn(x, y, colour, 'Q', owner) { }

    public:
        bool CanProceed(std::pair<int, int> pos, bool eatable = false) const override;
        std::vector<std::pair<int, int>> GetMaxRangesFromCurrentPos() const override;
    };
} // namespace trc::game

#endif // TRC_GAME_PAWN_H
