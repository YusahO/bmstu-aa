set(SOURCES
    algorithms.cpp
    measure.cpp
)

add_library(lib STATIC ${SOURCES})

target_include_directories(lib PUBLIC "./")