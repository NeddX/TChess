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
		std::unique_ptr<Board> m_Board;
		bool m_Running;
        int m_MaxRows;
        int m_MaxCols;
        std::chrono::system_clock::time_point m_Tp1, m_Tp2;
        int m_Fps = 0;
        uint32_t m_FrameCount = 0;
        uint32_t m_FrameCap = 240;
        bool m_CommandMode;
        CommandType m_Command;

    public:
        Game();
        ~Game();

    public:
        void Start();
        void HandleInput();
        void ExecuteCommand(std::string cmd);
    };
} // namespace trc::game

#endif // TRC_GAME_H
