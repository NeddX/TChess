#ifndef TRC_GAME_BOARD_H
#define TRC_GAME_BOARD_H

#include <sdafx.h>

#include "Scene.h"
#include "Pawn.h"

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
		std::vector<uint32_t> m_Map;
    	std::unique_ptr<Scene> m_Scene;
		std::vector<std::unique_ptr<Pawn>> m_Pawns;

    public:
        Board(int rows, int cols, int cellSizeX, int cellSizeY);

	public:
    	template<typename T, typename... TArgs, typename = typename std::enable_if<std::is_base_of<Pawn, T>::value>::type>
		inline T& AddPawn(TArgs&&... args)
        {
            auto ptr = std::make_unique<T>(std::forward<TArgs>(args)...);
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

    public:
        void Update();
    };
} // namespace trc::game

#endif // TRC_GAME_BOARD_H
