 # include <fixture_gtest.h>

// Name: test case #1. Test Tokens_stream
// Desc: this test for tesing methods such as bool() and get()
// good result: false if eof for bool()  and valid token for get()
// bad result : true if eof for bool()   and invalid token for get()
using TokensStreamTest = parser_test::TokensStreamTest;

	TEST_F( TokensStreamTest, methodCheckEofReturnTrue ) {

		Lib_parser::Tokens_stream tokens_stream;

		tokens_stream.set_buffer(m_source_data);

		decltype(m_valid_tokens)::size_type cnt_tokens {0};
		while( tokens_stream ) {
			tokens_stream.get();
			cnt_tokens++;
		}

		ASSERT_EQ( cnt_tokens, m_valid_tokens.size() );
	}

	TEST_F( TokensStreamTest, methodGetReturnValidToken ) {

		Lib_parser::Tokens_stream tokens_stream;

		tokens_stream.set_buffer(m_source_data);

		for( auto const& valid_token : m_valid_tokens )
			ASSERT_EQ( tokens_stream.get(), valid_token );
	}

// Name: test case #2. Test List
// Desc: this test for tesing methods such as add() TODO
// good result: the number and the data in each Nodes of List are equal to the valid Nodes
// bad result : the data or the number in any Nodes of List are not equal to the valid Nodes

using ListTest = parser_test::ListTest;

    TEST_F( ListTest, methodAddAllNodesWasAddes) {

        Lib_parser::List list_nodes;

        // add some nodes into the tree
        while( m_tokens_stream )

            list_nodes.add( m_tokens_stream.get() );

    // are the results nodes are equal to valid nodes ?
        Lib_parser::Node* ptr_result { get_next_node( list_nodes) };
        std::size_t index {0};

    while( ptr_result ) {
        ASSERT_TRUE(ptr_result->m_data == m_valid_tokens[index].second and ptr_result->m_number == m_valid_tokens[index].first);
        index++;
        ptr_result = get_next_node( list_nodes );
    }
}

int main( int argc, char **argv ) {

        ::testing::InitGoogleTest(&argc, argv );

return RUN_ALL_TESTS();
}
