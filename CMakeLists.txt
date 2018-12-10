cmake_minimum_required(VERSION 3.12)
project(Janhavi)

set(CMAKE_CXX_STANDARD 11)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

find_package(OpenCV REQUIRED)
include_directories("/usr/local/include/libigl/include")
include_directories("/usr/local/include/eigen3/eigen3/cmake")
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCE_FILES
        MiniAssignment4.cpp
        Camera.cpp
        Camera.h
        Intersection.cpp
        Intersection.h
        Light.cpp
        Light.h
        Mesh.cpp
        Mesh.h
        Scene.cpp
        Scene.h
        SceneObject.cpp
        SceneObject.h
        Sphere.cpp
        Sphere.h
    )

add_executable(Janhavi ${SOURCE_FILES})
target_link_libraries (Janhavi Eigen3::Eigen)
target_link_libraries(Janhavi ${OpenCV_LIBS})
