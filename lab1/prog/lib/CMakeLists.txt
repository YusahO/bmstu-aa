set(SOURCES
    matrix.cpp
    measure.cpp
    algorithms.cpp
)

add_library(lib STATIC ${SOURCES})

target_include_directories(lib PUBLIC "./")