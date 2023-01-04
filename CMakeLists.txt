cmake_minimum_required(VERSION 3.21)

# Set the project name and specify that it is written in C++
project(app LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Allow debug symbols to be generated
set(CMAKE_BUILD_TYPE Debug)

# Set the SFML libraries to link to
set(SFML_LIBS sfml-graphics sfml-audio)

# Enable the generation of compile_commands.json, which can be used by tools like clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the ImGui include directory
set(IMGUI_DIR include/imgui)

# Set the FontAwesome include directory
set(FA_DIR include/FontAwesome)

# Set the tinyxml2 include directory
set(TINYXML2_DIR include/tinyxml2)

# Add the ImGui and src directories to the include path
include_directories(src/ ${IMGUI_DIR} ${IMGUI_DIR}/backends ${FA_DIR} ${TINYXML2_DIR} ..)

# Add the OpenCV include directory to the include path
include_directories(${OpenCV_INCLUDE_DIRS})

# Set the list of ImGui source files
set(IMGUI_SRC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui-SFML.cpp
)

# Find the SFML, OpenGL, and OpenCV packages
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

# Set the list of libraries to link to
set(LIBRARIES "OpenGL::GL")

# Get a list of all the source files in the src directory
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

# Add a compile definition to silence deprecation warnings from OpenGL
add_compile_definitions(GL_SILENCE_DEPRECATION)

# Add the app executable target, linking to the SFML, OpenGL, and OpenCV libraries, as well as the ImGui source files
add_executable(app ${SRC_FILES} ${IMGUI_SRC} ${TINYXML2_DIR}/tinyxml2.cpp)
target_link_libraries(app PRIVATE ${SFML_LIBS} ${LIBRARIES} ${OpenCV_LIBS})

# Set the C++ standard for the app target to C++17
target_compile_features(app PRIVATE cxx_std_17)

# Install the app target
install(TARGETS app)

# Add a compile definition for the app target
target_compile_definitions(app PUBLIC -DImTextureID=ImU64 -D__CURRENT_DIR__="../" -D__DEFAULT_SPRITE__="../assets/images/spritesheets/vegito/ssj_blue.png")

# remove the narrowing conversion warning
target_compile_options(app PRIVATE -Wno-narrowing)