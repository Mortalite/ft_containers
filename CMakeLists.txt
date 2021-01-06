cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(includes)
include_directories(includes/containers)
include_directories(includes/iterators)


add_executable(ft_containers srcs/main.cpp includes/containers/list.hpp includes/iterators/iteratorList.hpp includes/containers/vector.hpp includes/iterators/iteratorVector.hpp includes/containers/stack.hpp includes/containers/queue.hpp includes/containers/map.hpp includes/iterators/iteratorMap.hpp includes/containers/multimap.hpp includes/containers/set.hpp includes/iterators/iteratorSet.hpp includes/tests.hpp srcs/mainTesters.cpp includes/print.hpp includes/utils.hpp includes/mapTest.hpp includes/queueTest.hpp includes/defines.hpp includes/stackTest.hpp)