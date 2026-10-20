# CMakeLists.txt for the hashtable project
cmake_minimum_required(VERSION 3.20)	

# Ensure we can use gdb
set(CMAKE_BUILD_TYPE Debug)	  	

project(project2-hashtable)		 

set(CMAKE_CXX_STANDARD 14)	 	   

include_directories(.)	   	

# Retrieve the googletest test framework
include(FetchContent)	 	 	
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)	   		
FetchContent_MakeAvailable(googletest)		  		

add_compile_options(-pedantic -Wall -Wextra -Werror=vla)		   		

add_executable(run-main hashtable.h main.cpp)	     
add_executable(run-tests hashtable.h tests/tests-setup.h tests/tests.cpp tests/tests-setup.cpp)					
add_executable(run-sneaky hashtable.h tests/sneaky.cpp)	    
add_custom_target(gradescope DEPENDS run-tests run-sneaky)	 	  	

if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")					  
target_link_libraries(run-tests GTest::gtest_main kvm procstat )					 	
else()		 	
target_link_libraries(run-tests GTest::gtest_main)		  	  
endif()	  		 
