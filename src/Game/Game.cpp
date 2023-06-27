#include "Game.h"
#include "Pawn.h"
#include "../Utils/xstdf.h"

#define KEY_ESCAPE 27

#define printc(str, ...) mvprintw(0, m_MaxWidth - strlen(str), str, __VA_ARGS__)

namespace trc::game {
    Game::Game()
    {
        m_Board = std::make_unique<Board>(8, 8, 4, 4);
		m_Running = true;

        getmaxyx(stdscr, m_MaxWidth, m_MaxHeight);
    }

    Game::~Game()
    {
        endwin();
	}

    void Game::Start()
    {
		auto& pawn = m_Board->AddPawn<Pawn>(0, 0, 'B');

        char c = 0;
		int x = 1, y = 1;
		float delta_time = -1.0f;
        while (m_Running)
        {
            HandleInput();
        	m_Board->Update();

            std::printf("\033]0;TermChess FPS: %d Delta: %f Frames: %d\007", m_Fps, delta_time, m_FrameCount);
            m_Tp1 = std::chrono::system_clock::now();
            delta_time = std::chrono::duration<float>(m_Tp1 - m_Tp2).count();
            m_Tp2 = m_Tp1;
            m_Fps = (int)(1.0f / delta_time);
            if (m_FrameCap > 0) std::this_thread::sleep_for(
                std::chrono::milliseconds((uint32_t)(1.0f / m_FrameCap * 1000)));
			m_FrameCount++;
        }
	}

    void Game::HandleInput()
    {
        static std::string cmd;
    	chtype c = getch();
		if (c == ERR) return;

        switch (c)
    	{
            case ':':
            {
                if (!m_CommandMode)
                {
                    printc("Command mode!\n");
                    cmd.clear();
                	m_CommandMode = true;
                }
            }
            case 'm':
            {
                if (!m_CommandMode)
					m_Command = CommandType::Move;
            }
            case KEY_ESCAPE:
            {
                if (m_CommandMode)
                	m_CommandMode = false;
            }
            case KEY_ENTER:
            {
                ExecuteCommand(cmd);
                cmd.clear();
                m_CommandMode = false;
            }
            default:
            {
                cmd.append(1, (char)c);
                //std::printf("\033]0;%d\007", c);
            }
        }
    }

    void Game::ExecuteCommand(const std::string& cmd)
    {
        printc("Executing command...\n");
        switch (m_Command)
        {
			case CommandType::Move:
            {
				std::vector<std::string> tokens = utils::string::Split(cmd, ' ');
                printc("Moving from: %s to %s\n", tokens[0].c_str(), tokens[1].c_str());
            }
        }
    }
} // namespace trc::game
