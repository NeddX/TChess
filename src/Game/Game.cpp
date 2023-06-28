#include "Game.h"
#include "Pawn.h"
#include "../Utils/xstdf.h"

#define KEY_ESCAPE 27

#define printca(str, ...) clear(); mvprintw(m_MaxRows - 1, 0, str, __VA_ARGS__)
#define printc(str) clear(); mvprintw(m_MaxRows - 1, 0, str)

namespace trc::game {
    Game::Game()
    {
        m_Board = std::make_unique<Board>(8, 8, 3, 3);
        m_Running = true;

        getmaxyx(stdscr, m_MaxRows, m_MaxCols);
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
        static std::string cmd_prefix;
        chtype c = getch();
        if (c == ERR) return;

        switch (c)
        {
            case ':':
            {
                if (!m_CommandMode)
                {
                    printc("[Command mode (:h for help.)]");
                    cmd_prefix = "Command >";
                    cmd.clear();
                    m_CommandMode = true;
                }
                else
                    goto default_case;
                break;
            }
            case 'm':
            {
                if (m_CommandMode && m_Command == CommandType::NullCmd)
                {
                    printc("[Move command]");
                    cmd_prefix = "Move >";
                    m_Command = CommandType::Move;
                }
                else
                    goto default_case;
                break;
            }
            case 'h':
            {
                if (m_CommandMode && m_Command == CommandType::NullCmd)
                {
                    clear();
                    printw("':' to enter command mode.\n\nList of commands\n:h\t- Display this message.\n"
                           ":m\t- Move command. Usage: [pawn pos] [new pos].\n"
                           ":q\t- Exit.\n\nPRESS Q TO CONTINUE");
                    refresh();
                    while (getchar() != 'q') ;
                    clear();
                    refresh();
                    m_CommandMode = false;
                }
                else
                {
                    goto default_case;
                }
                break;
            }
            case KEY_ESCAPE:
            {
                if (m_CommandMode)
                {
                    m_CommandMode = false;
                }
                else
                {
                    m_Running = false;
                }
                break;
            }
            case 127: // Backspace, on OSX at least.
            {
                if (m_CommandMode)
                {
                    cmd.pop_back();
					printca("%s %s", cmd_prefix.c_str(), cmd.c_str());
                }
                else
                {
                    goto default_case;
                }
                break;
            }
            case '\n':
            {
                ExecuteCommand(cmd);
                cmd.clear();
                m_CommandMode = false;
                m_Command = CommandType::NullCmd;
                break;
            }
            default:
            {
default_case:
                if (m_CommandMode)
                {
                    cmd.append(1, (char)c);
                    printca("%s %s", cmd_prefix.c_str(), cmd.c_str());
                }
                else
                {
                    printca("Unknown command key: %d", (int)c);
                }
                break;
            }
        }
    }

    void Game::ExecuteCommand(std::string cmd)
    {
        printc("Executing command...");
        switch (m_Command)
        {
            case CommandType::Move:
            {
                try
                {
                    if (cmd.empty()) throw std::exception();
                    utils::string::ToLower(cmd);
                    std::vector<std::string> tokens = utils::string::Split(cmd, ' ');
                    printca("Moving from: %s to %s\n", tokens[0].c_str(), tokens[1].c_str());

                    auto [pos_x, pos_y] 	= std::pair<int, int> { tokens[0][0] - 'a', std::stoi(tokens[0].substr(1)) };
                    auto [npos_x, npos_y] 	= std::pair<int, int> { tokens[1][0] - 'a', std::stoi(tokens[1].substr(1)) };

                    printca("Moving pawn at (%d, %d) to (%d, %d)", pos_x, pos_y, npos_x, npos_y);

                    if (auto dim = m_Board->GetDimensions();
                        (pos_x > dim.first || pos_y > dim.second) ||
                        (pos_x < 0 || pos_y < 0) ||
                        (npos_x > dim.first || npos_y > dim.second) ||
                        (npos_x < 0 || npos_y < 0))
                    {
                        throw std::exception();
                    }

                    Pawn* pawn = nullptr;
                    pawn = m_Board->GetPawnAt({ pos_x, pos_y });
                    if (pawn)
                    {
                        if (pawn->IsInRange({ npos_x, npos_y }))
                        {
                            m_Board->MovePawn(*pawn, { npos_x, npos_y });
                        }
                        else
                        {
                            printc("Illegal movement attempt.");
                        }
                    }
                    else
                    {
                        printc("No pawn at position provided.");
                    }
                }
                catch (std::exception &ex)
                {
                    printc("Bad arguments.");
                }
                break;
            }
            case CommandType::NullCmd:
            default:
            {
                printc("Invalid command.");
                break;
            }
        }
    }
} // namespace trc::game
