set(SOURCES
    utils.cpp
    measure.cpp
    pipeline.cpp
    algorithms.cpp

    midifile/src/Binasc.cpp
    midifile/src/MidiFile.cpp
    midifile/src/MidiEvent.cpp
    midifile/src/MidiMessage.cpp
    midifile/src/MidiEventList.cpp
)

add_library(lib STATIC ${SOURCES})

target_include_directories(lib PUBLIC "./")
target_include_directories(lib PUBLIC "midifile/include")
