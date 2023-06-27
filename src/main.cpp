#include <iostream>
#include <vector>

#include <sdafx.h>

#include "Game/Game.h"

int main(int argc, const char *argv[])
{
	std::cout << "TChess\n";
	trc::game::Game g;
	g.Start();
}
