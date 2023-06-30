#include "Game.h"
#include "Pawn.h"
#include "../Utils/xstdf.h"

#define ASCII_ESCAPE 27
#define ASCII_BACKSPACE 8
#define ASCII_DELETE 127

#define printca(str, ...) clear(); mvprintw(m_MaxRows - 1, 0, str, __VA_ARGS__)
#define printc(str) clear(); mvprintw(m_MaxRows - 1, 0, str)

namespace trc::game {
    Game::Game()
    {
        m_Board = std::make_unique<Board>(8, 8, 4, 4,
                                          [&](Pawn& eatingPawn, Pawn& targetPawn)
                                          {
                                              switch (eatingPawn.GetColour())
                                              {
                                                  case 'B': m_PawnsEatenByB++; break;
                                                  case 'W': m_PawnsEatenByW++; break;
                                              }
                                          });
        m_Running = true;

        curs_set(0); // No Cursor for now.
        getmaxyx(stdscr, m_MaxRows, m_MaxCols);
    }

    Game::~Game()
    {
        endwin();
    }

    void Game::Start()
    {
        clear();
        refresh();

        // Pawns
        for (int y = 0; y <= 1; ++y)
        {
            for (int x = 0; x < 8; ++x)
            {
                m_Board->AddPawn<Pawn>(x, y * 5 + 1, (y == 0) ? 'B' : 'W');
            }
        }

        // Rooks
        for (int y = 0; y <= 1; ++y)
        {
            for (int x = 0; x <= 1; ++x)
            {
                m_Board->AddPawn<Rook>(x * 7, y * 7, (y == 0) ? 'B' : 'W');
            }
        }

        // Knights
        for (int y = 0; y <= 1; ++y)
        {
            for (int x = 0; x <= 1; ++x)
            {
                m_Board->AddPawn<Knight>(x * 5 + 1, y * 7, (y == 0) ? 'B' : 'W');
            }
        }

        // Bishops
        for (int y = 0; y <= 1; ++y)
        {
            for (int x = 0; x <= 1; ++x)
            {
                m_Board->AddPawn<Bishop>(x * 3 + 2, y * 7, (y == 0) ? 'B' : 'W');
            }
        }

        // Queens
        for (int y = 0; y <= 1; ++y)
        {
            m_Board->AddPawn<Queen>(3, y * 7, (y == 0) ? 'B' : 'W');
        }

        // Kings
        for (int y = 0; y <= 1; ++y)
        {
            m_Board->AddPawn<King>(4, y * 7, (y == 0) ? 'B' : 'W');
        }

        char c = 0;
        int x = 1, y = 1;
        float delta_time = -1.0f;
        while (m_Running)
        {
            if (!m_GameOver)
            {
                HandleUI();
                HandleInput();
                m_Board->Update();
                //CheckForCheckmate();
            }
            else
            {
                HandleUI();
                m_Board->Update();
                m_Running = false;

                char c = getchar();
                switch (c)
                {
                    case 'q':
                        endwin();
                        std::exit(EXIT_SUCCESS);
                    case 'r':
                        return;
                }
            }

            //std::printf("\033]0;TermChess FPS: %d Delta: %f Frames: %d\007", m_Fps, delta_time, m_FrameCount);
            m_Tp1 = std::chrono::system_clock::now();
            delta_time = std::chrono::duration<float>(m_Tp1 - m_Tp2).count();
            m_Tp2 = m_Tp1;
            m_Fps = (int)(1.0f / delta_time);
            if (m_FrameCap > 0) std::this_thread::sleep_for(
                std::chrono::milliseconds((uint32_t)(1.0f / m_FrameCap * 1000)));
            m_FrameCount++;
            move(m_CursorPos.first, m_CursorPos.second);
            m_Secs += delta_time;
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
                {
                    goto default_case;
                }
                break;
            }
            case 'q':
                endwin();
                std::exit(EXIT_SUCCESS);
            case 'm':
            {
                if (m_CommandMode && m_Command == CommandType::NullCmd)
                {
                    printc("[Move command]");
                    cmd_prefix = "Move >";
                    m_Command = CommandType::Move;
                }
                else
                {
                    goto default_case;
                }
                break;
            }
            case 'o': // FIXME: REMEMBER TO REMOVE!
                m_GameOver = true;
                break;
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
            case ASCII_ESCAPE:
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
            case ASCII_DELETE:
            case ASCII_BACKSPACE:
            {
                if (m_CommandMode)
                {
                    if (!cmd.empty()) cmd.pop_back();
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
                    m_CursorPos = { m_MaxRows - 1, cmd.size() };
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

    void Game::HandleUI()
    {
        if (!m_GameOver)
        {
            mvprintw(
                m_Board->GetDimensions().second + 3,
                3 * 2,
                "%s",
                (m_Turn == 'B') ? "Black's turn." : "White's turn."
            );
            mvprintw(
                m_Board->GetDimensions().second + 3 + 1,
                3 * 2,
                "Pawns eaten by White: %d\tPawns eaten by Black: %d\n",
                m_PawnsEatenByW,
                m_PawnsEatenByB
            );
        }
        else
        {
            clear();
            mvprintw(
                m_Board->GetDimensions().second + 3,
                3 * 2,
                "Game over. %s won.",
                (m_Turn == 'W') ? "White" : "Black"
            );
            mvprintw(
                m_Board->GetDimensions().second + 3 + 1,
                3 * 2,
                "Press 'r' to restart or 'q' to quit."
            );
            refresh();
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

                    auto [pos_x, pos_y] 	= std::pair<int, int> { tokens[0][0] - 'a', m_Board->GetRowsAndCols().first - std::stoi(tokens[0].substr(1)) };
                    auto [npos_x, npos_y] 	= std::pair<int, int> { tokens[1][0] - 'a', m_Board->GetRowsAndCols().first - std::stoi(tokens[1].substr(1)) };

                    printca("Moving pawn at (%d, %d) to (%d, %d)", pos_x, pos_y, npos_x, npos_y);
                    //return;
                    if (auto dim = m_Board->GetDimensions();
                        (pos_x > dim.first || pos_y > dim.second) ||
                        (pos_x < 0 || pos_y < 0) ||
                        (npos_x > dim.first || npos_y > dim.second) ||
                        (npos_x < 0 || npos_y < 0))
                    {
                        throw std::exception();
                    }

                    Pawn* pawn = m_Board->GetPawnAt({ pos_x, pos_y });
                    Pawn* target_pawn = m_Board->GetPawnAt({ npos_x, npos_y });
                    if (pawn && m_Turn == pawn->GetColour())
                    {
                        if (m_IsWUnderChess || m_IsBUnderChess &&
                            pawn->GetSymbol() != 'K')
                        {
                            printc("Your king is under threat, protect your king: Illegal movement attempt.");
                        }
                        else
                        {
                            if (m_Board->MovePawn(*pawn, { npos_x, npos_y }))
                            {
                                m_Turn = (m_Turn == 'W') ? 'B' : 'W';
                                CheckForCheckmate();
                            }
                            else
                            {
                                printc("Illegal movement attempt.");
                            }
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

    void Game::CheckForCheckmate()
    {
        std::vector<const Pawn*> pawns = m_Board->GetAllPawns();
        auto& current_king = *(King*)(*std::find_if(pawns.begin(), pawns.end(),
                                           [&](const auto* ptr)
                                           {
                                               return ptr->GetColour() == m_Turn &&
                                                   ptr->GetSymbol() == 'K';
                                           }));

        auto kings_range = current_king.GetMaxRangesFromCurrentPos();

        for (const auto* p : pawns)
        {
            if (p->GetColour() != m_Turn)
            {
                for (const auto& krange : kings_range)
                {
                    for (const auto& erange : p->GetMaxRangesFromCurrentPos())
                    {
                        if (erange.first == krange.first &&
                            erange.second == krange.second)
                        {
                            switch (m_Turn)
                            {
                                case 'W': m_IsWUnderChess = true; break;
                                case 'B': m_IsBUnderChess = true; break;
                            }
                        }
                    }
                }
            }
        }

        auto colliding_ranges_it = std::remove_if(kings_range.begin(), kings_range.end(),
                       [&](const auto& range)
                       {
                           for (const auto* ptr : pawns)
                           {
                               for (const auto& prange : ptr->GetMaxRangesFromCurrentPos())
                               {
                                   if (prange.first == range.first &&
                                       prange.second == range.second)
                                       return true;
                               }
                           }
                           return false;
                       });

        if (colliding_ranges_it != kings_range.end())
            kings_range.erase(colliding_ranges_it);

        if (kings_range.empty() && (m_IsWUnderChess || m_IsBUnderChess))
        {
            m_Turn = (m_Turn == 'W') ? 'B' : 'W';
            m_GameOver = true;
        }
    }
} // namespace trc::game
