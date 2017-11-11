cmake_minimum_required(VERSION 3.8)
project(WhoseExcavatorTechnologyAdvanced)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ArrayList.h Test.cpp Test.h BasicString.h Stack.h LinkedList.h HashSet.h Utility.h CSVHandler.cpp CSVHandler.h StringConvert.cpp StringConvert.h Logger.cpp Logger.h HttpRequest.cpp HttpRequest.h HTMLParser.cpp HTMLParser.h DomNode.cpp DomNode.h cQuery.cpp cQuery.h Crawler.cpp Crawler.h WordDivider.cpp WordDivider.h)
add_executable(WhoseExcavatorTechnologyAdvanced ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(WhoseExcavatorTechnologyAdvanced ws2_32)
endif ()
