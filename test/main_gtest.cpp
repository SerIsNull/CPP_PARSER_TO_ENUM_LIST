 # include <fixture_gtest.h>
 # include <atomic>

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
// Desc: this test for tesing methods such as add().
// good result: the number and the data in each Nodes of List are equal to the valid Nodes
// bad result : the data or the number in any Nodes of List are not equal to the valid Nodes
using ListTest = parser_test::ListTest;

    TEST_F( ListTest, methodAddAllNodesWasAddes) {

        Lib_parser::List list_nodes;

        // add some nodes into the List
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

// Name: test case #3. Test Number_enumerator
// Desc: this test for tesing methods such as inc_number() and add_number().
// good result: the number and the data of enumerate Node into the List are equal to number and data of valid Node.
// bad result: the number and the data of enumerate Node into the List are not equal to number and data of valid Node.
using NumberEnumeratorTest = parser_test::NumberEnumeratorTest;

    TEST_F( NumberEnumeratorTest, methodsIncNumberAndAddNumberResultIsEnumerateList) {

        Lib_parser::Number_enumerator enumerator;

        Lib_parser::Node* ptr_node = ls_nodes.get_head();

        enumerator.inc_number(ptr_node);

        // enumerate all nodes into the List
        while(ptr_node) {

            // move to the right and enumerate it
            while( ptr_node->m_ptr_right ) {

                ptr_node = ptr_node->m_ptr_right;
                enumerator.add_number(ptr_node);
            }

            // move to the down and enumerate it.
            while( ptr_node->m_ptr_down ) {

                ptr_node = ptr_node->m_ptr_down;
                enumerator.inc_number(ptr_node);
            }
        // this is end of List
        if( ptr_node->m_ptr_right == nullptr and ptr_node->m_ptr_down == nullptr ) break;
        }

        // check that our enumerating is valid!
        ptr_node = ls_nodes.get_head();
        std::size_t number_node{0};

        while( ptr_node ) {
            auto const& [valid_number, valid_data] = m_valid_enum_nodes[number_node];

            Lib_parser::number_t tested_number { ptr_node->m_number },
                                 tested_data   { ptr_node->m_data };

            ASSERT_TRUE( valid_number == tested_number and valid_data == tested_data );

            ptr_node = ptr_node->m_ptr_right ? ptr_node->m_ptr_right : ptr_node->m_ptr_down ? ptr_node->m_ptr_down : nullptr;

            number_node++;
        }
}

int main( int argc, char **argv ) {

// Name: test case #0. Test List destrutor
// Desc: this test for tesing destyructor in List type.
// good result: Valgrind says that Errors 0
// bad result : Valgrind find some leaks
    {
        Lib_parser::List ls;

            ls.add({"12", "12"});

            ls.add({"13", "13"});
    }

        ::testing::InitGoogleTest(&argc, argv );

return RUN_ALL_TESTS();
}
