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
        int m_OffsetX;
        int m_OffsetY;
        std::unique_ptr<Scene> m_Scene;
        std::vector<std::unique_ptr<Pawn>> m_Pawns;
        std::vector<Pawn*> m_Map;

    private:
        std::function<void(Pawn&, Pawn&)> Event_OnPawnEat;

    public:
        Board(
            int rows,
            int cols,
            int cellSizeX,
            int cellSizeY,
            std::function<void(Pawn& eatingPawn, Pawn& targetPawn)> onPawnEat);

    public:
        inline std::pair<int, int> GetDimensions() const { return { m_Width, m_Height }; }
        inline std::pair<int, int> GetRowsAndCols() const { return { m_Rows, m_Cols }; }
        inline std::pair<int, int> GetCellSize() const { return { m_CellSizeX, m_CellSizeY }; }
        inline Pawn* GetPawnAt(std::pair<int, int> pos) const { return m_Map[todim(pos.first, pos.second)]; }
        inline std::vector<const Pawn*> GetAllPawns() const
        {
            std::vector<const Pawn*> pawns;
            pawns.reserve(m_Pawns.size());
            for (const auto& ptr : m_Pawns)
                pawns.push_back(ptr.get());
            return pawns;
        }
        template<typename T, typename... TArgs, typename = typename std::enable_if<std::is_base_of<Pawn, T>::value>::type>
        inline T& AddPawn(TArgs&&... args)
        {
            auto ptr = std::make_unique<T>(std::forward<TArgs>(args)..., this);
            auto [x, y] = ptr->GetPos();
            m_Map[todim(x, y)] = ptr.get();
            m_Pawns.push_back(std::move(ptr));
            return *(T*)(m_Pawns.back().get());
        }
        template<typename T, typename = typename std::enable_if<std::is_base_of<Pawn, T>::value>::type>
        inline void RemovePawn(T& pawn)
        {
          auto it =
              std::find_if(m_Pawns.begin(), m_Pawns.end(),
                           [&pawn](auto &ptr) { return ptr.get() == &pawn; });

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

            Pawn* potential_target = m_Map[todim(newPos.first, newPos.second)];
            if (potential_target && potential_target->GetColour() != pawn.GetColour())
            {
                if (pawn.CanProceed(newPos, true))
                {
                    Event_OnPawnEat(pawn, *potential_target);
                    RemovePawn(*potential_target);

                    pawn.SetMoveCount(pawn.GetMoveCount() + 1); // Dodgy....
                    m_Map[todim(prev_x, prev_y)] = nullptr;
                    m_Map[todim(newPos.first, newPos.second)] = &pawn;

                    pawn.SetPos(newPos);
                    return true;
                }
            }
            else if (!potential_target)
            {
                if (pawn.CanProceed(newPos, false))
                {
                    pawn.SetMoveCount(pawn.GetMoveCount() + 1); // Dodgy....
                    m_Map[todim(prev_x, prev_y)] = nullptr;
                    m_Map[todim(newPos.first, newPos.second)] = &pawn;

                    pawn.SetPos(newPos);
                    return true;
                }
            }
            return false;
        }

    public:
        void Update();
    };
} // namespace trc::game

#undef todim

#endif // TRC_GAME_BOARD_H
