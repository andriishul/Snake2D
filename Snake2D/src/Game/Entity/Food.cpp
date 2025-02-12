#include "Food.hpp"
#include <Board.hpp>
#include <random>

void Food::SetRandomPosition(Board& board)
{
    glm::ivec2 size = board.GetSize();

    static std::minstd_rand gen;
    static std::uniform_int_distribution<> distrX(0, size.x - 1);
    static std::uniform_int_distribution<> distrY(0, size.y - 1);

    do {
        m_Position = { distrX(gen), distrY(gen) };
    } while (board[m_Position]->GetColor() != board.GetColor());
}
