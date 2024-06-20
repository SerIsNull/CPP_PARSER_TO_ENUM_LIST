# This CMakeLists.txt describes the building some tests for the parser

# set sources files for the tests
	set( SOURCES
	     parser_to_enum_list.cpp
	     main_gtest.cpp
		 fixture_gtest.cpp
	)

	set( HEADERS
	     parser_to_enum_list.h
	     fixture_gtest.h
	)

# set test target
	add_executable( test_parser ${CMAKE_SOURCE_DIR}/src/${SOURCES} )

# add some options for the linking
	target_link_options( test_parser PRIVATE
			     -pthread
	)

# link test with gtest library
	target_link_libraries( test_parser gtest )

# set include dir for the test target
	target_include_directories( test_parser PRIVATE
				    ${CMAKE_SOURCE_DIR}/src
				    ${CMAKE_CURRENT_SOURCE_DIR}
	)

# set output directory
	set_target_properties( test_parser
	               	       PROPERTIES
		       	       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)

# add test into the ctest
	add_test( test_parser 
		  COMMAND ${CMAKE_BINARY_DIR}/bin/test_parser
	)
	


