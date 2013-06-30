cmake_minimum_required(VERSION 2.6)
project(rsys C)
enable_testing()

if(NOT CMAKE_COMPILER_IS_GNUCC)
  message(FATAL_ERROR "Unsupported compiler")
endif(NOT CMAKE_COMPILER_IS_GNUCC)

set(CMAKE_DEBUG_POSTFIX "-dbg")

set(CMAKE_C_FLAGS "-pedantic -std=c99 -Wall -Wextra -Wcast-align -Wmissing-declarations -Wmissing-prototypes -fvisibility=hidden -fstrict-aliasing -Wl,-z,defs -Wconversion")
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

#add_definitions(-D_POSIX_C_SOURCE=200809L)

################################################################################
# Define targets
################################################################################
set(RSYS_FILES_SRC 
#clock_time.c 
#image.c 
    mem_allocator.c)

set(RSYS_FILES_INC
   atomic.h
#  clock_time.h
#  image.h
  list.h
#  math.h
  mem_allocator.h
#  ref_count.h
#  signal.h
  rsys.h)

add_library(rsys SHARED ${RSYS_FILES_SRC} ${RSYS_FILES_INC})
set_target_properties(rsys PROPERTIES DEFINE_SYMBOL RSYS_SHARED_BUILD)

################################################################################
# Add tests
################################################################################
add_executable(test_list test_list.c)
target_link_libraries(test_list rsys)
add_test(test_list test_list)

add_executable(test_mem_allocator test_mem_allocator.c)
target_link_libraries(test_mem_allocator rsys)
add_test(test_mem_allocator test_mem_allocator)

#add_executable(test_signal test_signal.c)
#target_link_libraries(test_signal snlsys)
#add_test(test_signal test_signal)

################################################################################
# Define output & install directories
################################################################################
#install(TARGETS rsys LIBRARY DESTINATION lib)
install(FILES ${RSYS_FILES_INC} DESTINATION include/rsys)
