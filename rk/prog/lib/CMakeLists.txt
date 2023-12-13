set(SOURCES
    algorithms.cpp
)

add_library(lib STATIC ${SOURCES})

target_include_directories(lib PUBLIC "./")
