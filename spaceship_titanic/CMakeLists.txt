# --------------------------------------------------
# CMAKE VERSION
# --------------------------------------------------
cmake_minimum_required(VERSION 3.12)

# --------------------------------------------------
# PROJECT NAME AND VERSION
# --------------------------------------------------
project(SpaceshipTitanic VERSION 1.0)

# --------------------------------------------------
# GENERATE COMPILATION DATABASE (FOR YCM)
# --------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------------------
# HOME DIRECTORY 
# --------------------------------------------------
set(HOME_DIR $ENV{HOME})

# --------------------------------------------------
# EXECUTABLE
# --------------------------------------------------
add_executable(SpaceshipTitanic
    "${CMAKE_CURRENT_SOURCE_DIR}/classifier.cpp")

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(SpaceshipTitanic PUBLIC OpenMP::OpenMP_CXX armadillo python3.12)
endif()



# --------------------------------------------------
# TARGET INCLUDE DIRECTORIES
# --------------------------------------------------
target_include_directories(SpaceshipTitanic PUBLIC
    "${HOME_DIR}/lib/mlpack/include")

# --------------------------------------------------
# SET OUTPUT DIRECTORIES
# --------------------------------------------------
set_target_properties(SpaceshipTitanic
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>")
     
# --------------------------------------------------
# COMPILER FLAGS
# --------------------------------------------------
target_compile_features(SpaceshipTitanic PUBLIC cxx_std_11)

# add compiler warning flags just when building this project
# via the BUILD_INTERFACE generator expression
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(gcc_flags "-Wall;-Wextra;-Wshadow;-Wshadow;-Wformat=2")

target_compile_options(SpaceshipTitanic PRIVATE
   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>")
