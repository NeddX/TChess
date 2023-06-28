#ifndef TRC_GAME_BOARD_H
#define TRC_GAME_BOARD_H

#include <sdafx.h>

#include "Scene.h"
#include "Pawn.h"

#define todim(x, y) y * m_Cols + x

namespace trc::game {
	class Board
    {
    private:
        int m_Rows;
        int m_Cols;
        int m_Width;
        int m_Height;
        int m_CellSizeX;
        int m_CellSizeY;
        std::unique_ptr<Scene> m_Scene;
        std::vector<std::unique_ptr<Pawn>> m_Pawns;
        std::vector<Pawn*> m_Map;

    public:
        Board(int rows, int cols, int cellSizeX, int cellSizeY);

    public:
        inline std::pair<int, int> GetDimensions() const { return std::make_pair(m_Rows, m_Cols); }
        inline Pawn* GetPawnAt(std::pair<int, int> pos) const { return m_Map[todim(pos.first, pos.second)]; }
        template<typename T, typename... TArgs, typename = typename std::enable_if<std::is_base_of<Pawn, T>::value>::type>
        inline T& AddPawn(TArgs&&... args)
        {
            auto ptr = std::make_unique<T>(std::forward<TArgs>(args)...);
            auto [x, y] = ptr->GetPos();
            m_Map[todim(x, y)] = ptr.get();
            m_Pawns.push_back(std::move(ptr));
            return *m_Pawns.back();
        }
        template<typename T, typename = typename std::enable_if<std::is_base_of<Pawn, T>::value>::type>
        inline void RemovePawn(T& pawn)
        {
            auto it = std::find_if(m_Pawns.begin(), m_Pawns.end(),
                                    [&pawn](auto& ptr)
                                    {
                                        return ptr.get() == &pawn;
                                    });

            if (it != m_Pawns.end())
                m_Pawns.erase(it);
        }
        inline bool IsInBoard(const Pawn& pawn)
        {
            auto it = std::find_if(m_Pawns.begin(), m_Pawns.end(),
                                   [&pawn](auto& ptr)
                                   {
                                       return ptr.get() == &pawn;
                                   });
            return it != m_Pawns.end();
        }
        inline bool MovePawn(Pawn& pawn, std::pair<int, int> newPos)
        {
            if (!IsInBoard(pawn)) return false;

            auto [prev_x, prev_y] = pawn.GetPos();

            if (pawn.IsInRange(newPos))
            {
                m_Map[todim(prev_x, prev_y)] = nullptr;
                m_Map[todim(newPos.first, newPos.second)] = &pawn;

                pawn.SetPos(newPos);
                return true;
            }
            return false;
        }

    public:
        void Update();
    };
} // namespace trc::game

#undef todim

#endif // TRC_GAME_BOARD_H
