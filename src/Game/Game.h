#ifndef TRC_GAME_H
#define TRC_GAME_H

#include <sdafx.h>

#include "Board.h"

namespace trc::game {
    enum class CommandType
    {
        NullCmd,
        Move,
        Exit
    };

    class Game
    {
    private:
        std::unique_ptr<Board> m_Board = nullptr;
        bool m_Running = false;
        int m_MaxRows = 0;
        int m_MaxCols = 0;
        std::chrono::system_clock::time_point m_Tp1, m_Tp2;
        int m_Fps = 0;
        uint32_t m_FrameCount = 0;
        uint32_t m_FrameCap = 240;
        bool m_CommandMode = false;
        CommandType m_Command = CommandType::NullCmd;
        std::pair<int, int> m_CursorPos = { 0, 0 };
        chtype m_Turn = 'W';
        float m_Secs = 0;
        int m_PawnsEatenByW = 0;
        int m_PawnsEatenByB = 0;
        bool m_IsWUnderChess = false;
        bool m_IsBUnderChess = false;
        bool m_IsWUnderCheckmate = false;
        bool m_IsBUnderCheckmate = false;
        bool m_GameOver = false;
        std::vector<std::pair<int, int>> m_AvailablePositionsForKing;

    public:
        Game();
        ~Game();

    public:
        void Start();
        void HandleInput();
        void HandleUI();
        void ExecuteCommand(std::string cmd);
        void CheckForCheckmate();
    };
} // namespace trc::game

#endif // TRC_GAME_H
