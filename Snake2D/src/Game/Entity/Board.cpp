#include <Board.hpp>
#include <Graphics/2D/Renderer2D.hpp>
Board::Board(int width, int height, int tileSize, const glm::vec3 color) : m_Color(color)
{
    SetDimension(width, height, tileSize);
}

Sprite* Board::operator[](const glm::ivec2 vecIndex)
{
    glm::ivec2 size = GetSize();
    if (vecIndex.x >= size.x || vecIndex.y >= size.y || vecIndex.x < 0 || vecIndex.y < 0)
        return nullptr;

    return &m_Tiles[vecIndex.y * size.x + vecIndex.x];
}

bool Board::IsOn(const glm::ivec2& snakePosition) const
{
    return snakePosition.x >= 0 && snakePosition.x < m_Size.x && snakePosition.y >= 0 && snakePosition.y < m_Size.y;
}


void Board::OnRender(const Snake& snake, const Food& food)
{
    for (Sprite& tile : m_Tiles)
        tile.SetColor(m_Color);

    Sprite* headTile = (*this)[snake.GetHeadPosition()];
    if (headTile)
        headTile->SetColor(snake.GetColor());
    

    for (auto& segment : snake.GetSegments())
    {
        Sprite* segmentTile = (*this)[segment.Position];
        if (segmentTile)
            segmentTile->SetColor(snake.GetColor());
    }

    Sprite* foodTile = (*this)[food.GetPosition()];
    if (foodTile)
        foodTile->SetColor(food.GetColor());

    for (Sprite& tile : m_Tiles)
        Renderer2D::DrawSprite(tile);
}

void Board::SetDimension(int width, int height, int tileSize)
{
    m_Size = { width, height };
    float centerX = (width - 1) * 0.5f;
    float centerY = (height - 1) * 0.5f;
    m_Center = { centerX, centerY };

    m_Tiles.resize(width * height);
  
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            glm::vec2 position;

            position.x = (x - centerX) * tileSize;
            position.y = (y - centerY) * tileSize;

            m_Tiles[y * width + x] = Sprite(position, { tileSize, tileSize }, m_Color, 0);
        }
    }
}
