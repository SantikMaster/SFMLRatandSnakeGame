cmake_minimum_required(VERSION 3.9)

project(SNAKE_RAT VERSION 1.0.0 DESCRIPTION "Game for fun")
add_definitions(-std=c++14)

add_executable(
	SNAKE_RAT main.cpp
	AStar.h
	AStar.cpp
	BannerManager.h
	BannerManager.cpp
	Character.h
	Character.cpp
	Engine.h
	Engine.cpp
	Map.h
	Map.cpp
	Menu.h
	Menu.cpp
	Node.h
	Node.cpp
	WorldManager.h
	WorldManager.cpp 	
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/repos/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(SNAKE_RAT sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
