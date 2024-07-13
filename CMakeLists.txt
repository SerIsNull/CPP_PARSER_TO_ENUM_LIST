# set required version for building
	cmake_minimum_required( VERSION 3.16.3 )

# set policy
	cmake_policy ( VERSION 3.16.3 )

# set name, descr , version
	project( parser_to_enum_list
		 DESCRIPTION "This parser for parsing to the enumeration list"
	 	 VERSION     0.0.0.1
		 LANGUAGES   CXX
	)

# find all the necessary components for successfull building
	message(===CHECK_START "Start the checking all the necessary components for the bulding ...")
	find_program( is_exist_protoc protoc )
	find_library( is_exist_gtest  gtest  )

	if( NOT( is_exist_protoc AND is_exist_gtest ) )
		message( ==CHECK_FAIL FATAL_ERROR " : The components such as ${is_exist_protoc} and ${is_exist_gtest} wasn't found!" )
	else()
		message( ==CHECK_PASS STATUS      " : The components such as ${is_exist_protoc} and ${is_exist_gtest} was found!"    )
	
	# try to pass the test 
		enable_testing()
		add_subdirectory( test )


	endif()



