cmake_minimum_required(VERSION 3.8)
project(WhoseExcavatorTechnologyAdvanced)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ArrayList.h Test.cpp Test.h BasicString.h Stack.h LinkedList.h HashSet.h Utility.h CSVHandler.cpp CSVHandler.h StringConvert.cpp StringConvert.h Logger.cpp Logger.h HttpRequest.cpp HttpRequest.h HTMLParser.cpp HTMLParser.h DomNode.cpp DomNode.h QuerySelector.cpp QuerySelector.h)
add_executable(WhoseExcavatorTechnologyAdvanced ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(WhoseExcavatorTechnologyAdvanced ws2_32)
endif ()
