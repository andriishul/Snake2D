#pragma once
#include <glm/glm.hpp>

namespace Constants {

    namespace Colors
    {
        static const glm::vec3 Red = { 1.0f, 0.0f, 0.0f }; 
        static const glm::vec3 Green = { 0.0f, 1.0f, 0.0f };
        static const glm::vec3 Blue = { 0.0f, 0.0f, 1.0f };

        static const glm::vec3 Yellow = { 1.0f, 1.0f, 0.0f };
        static const glm::vec3 Cyan = { 0.0f, 1.0f, 1.0f };
        static const glm::vec3 Magenta = { 1.0f, 0.0f, 1.0f };

        static const glm::vec3 Black = { 0.0f, 0.0f, 0.0f };
        static const glm::vec3 White = { 1.0f, 1.0f, 1.0f };
        static const glm::vec3 Gray = { 0.5f, 0.5f, 0.5f };

        static const glm::vec3 LightGray = { 0.75f, 0.75f, 0.75f };
        static const glm::vec3 DarkGray = { 0.25f, 0.25f, 0.25f };
    }

    // Constants for commonly used 2D directions
    namespace Directions2D
    {
        static const glm::vec2 Right = { 1.0f, 0.0f };
        static const glm::vec2 Left = { -1.0f, 0.0f };
        static const glm::vec2 Up = { 0.0f, 1.0f };
        static const glm::vec2 Down = { 0.0f, -1.0f };
    }
}
