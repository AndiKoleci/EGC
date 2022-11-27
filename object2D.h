#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color);
    Mesh* CreateRect(const std::string& name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill = true);
}
