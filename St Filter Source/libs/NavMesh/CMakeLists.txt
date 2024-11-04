set(SOURCE_FILES src/RTNavMeshTerrain.cpp include/NavMesh/LocationInfo.cpp)

add_library(NavMesh STATIC ${SOURCE_FILES})
target_include_directories(NavMesh
        PUBLIC include/
        PRIVATE include/NavMesh)
