# This CMakeLists.txt describes the building some tests for the parser

    project( tester
             VERSION 0.0.0.2
             DESCRIPTION "This is tests for testing Lib_parser"
             LANGUAGES CXX
    )

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
                           CXX_STANDARD 20
                           CXX_STANDARD_REQUIRED ON
	)

# add test into the ctest
    add_test( NAME tests_lib_parser
              COMMAND ${CMAKE_BINARY_DIR}/bin/test_parser
	)
# add autorun test
    add_custom_command( TARGET test_parser POST_BUILD
                        COMMAND ${CMAKE_CTEST_COMMAND} -V --output-on-failure
                        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                        VERBATIM
    )

