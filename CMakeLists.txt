cmake_minimum_required (3.18)

#Build project Ajastra
#For each project command, CMake will create a top level IDE project file. Project will contain all targets
#that are in the CMakeLists.txt file, and any of its subdirectories as specified by the add_subdirectory
#command.
project (Ajastra)

set (AJASTRA_SRCS Ajastra.cpp Init.cpp)



#If you want to do operations specific to platform
#if (WIN32)
	#do operation here
#else()
	#do operation here
#endif()

add_executable (Ajastra ${AJASTRA_SRCS})

#Look for the BOOST library
#find_library (BOOST_LIBRARY
#	NAMES boost boost1 boost2
#	PATHS /usr/lib /usr/local/lib


#if (BOOST_LIBRARY)
#	target_link_library (Ajastra ${BOOST_LIBRARY})
#endif()


