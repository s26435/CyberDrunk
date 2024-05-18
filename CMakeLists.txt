cmake_minimum_required(VERSION 3.21)
project(Cyberdrunk2137)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2\\include\\")
set(SDL2_LIB_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2\\lib\\x64\\")

set(SDL2_TTF_INCLUDE_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2_ttf\\include\\")
set(SDL2_TTF_LIB_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2_ttf\\lib\\x64\\")

set(SDL2_IMAGE_INCLUDE_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2_image\\include\\")
set(SDL2_IMAGE_LIB_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2_image\\lib\\x64\\")

set(SDL2_MIXER_INCLUDE_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2_mixer\\include\\")
set(SDL2_MIXER_LIB_DIR "C:\\Users\\user\\Documents\\SGD\\SGD\\SDL2_mixer\\lib\\x64\\")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp Camera.cpp Camera.h ResourceManager.cpp ResourceManager.h Window.cpp Window.h GameObject.cpp GameObject.h Game.h Game.cpp Environment.cpp Environment.h GameObject.h GameObject.cpp GUI.cpp GUI.h Mouse.cpp Mouse.h TestObject.cpp TestObject.h CollisionManager.cpp CollisionManager.h BoxCollider.cpp BoxCollider.h MobObject.cpp MobObject.h Inventory.h Inventory.cpp
        PauseMenu.h
        PauseMenu.cpp
        Button.cpp
        Button.cpp
        Button.h
        Platform.h
        Platform.h
        Platform.cpp
        Item.cpp
)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib ${SDL2_LIB_DIR}/SDL2main.lib ${SDL2_IMAGE_LIB_DIR}/SDL2_image.lib ${SDL2_MIXER_LIB_DIR}/SDL2_mixer.lib ${SDL2_TTF_LIB_DIR}/SDL2_ttf.lib)