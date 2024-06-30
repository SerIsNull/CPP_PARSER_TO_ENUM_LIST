# include <fixture_gtest.h>

// definitions for the fixture "TokensstreamTesta"
parser_test::TokensStreamTest::TokensStreamTest() :
    m_valid_tokens {
			{
                {"0", "Node_1"},
                    {"1", "Node_1_1" },
			    	{"1", "Node_1_2" },
			    	{"1", "Node_1_3" },
			    	    {"2", "Node_1_3_1"},
					    {"2", "Node_1_3_2"},
				    {"1", "Node_1_4"},
                {"0", "Node_2"}
			}
	} { }

// definitions for the fixture "ListTest"
parser_test::ListTest::ListTest() {

    // set tokens stream
    m_tokens_stream.set_buffer(m_source_data);

    // set valid Nodes
    m_valid_nodes = m_valid_tokens;
}

Lib_parser::Node* parser_test::ListTest::get_next_node( Lib_parser::List const& list_nodes ) {

        // iterator
        static bool is_first {true};

        static Lib_parser::Node* ptr_node { list_nodes.get_head()  };

        if( is_first) { is_first = false; return ptr_node; }

        Lib_parser::Node* ptr_res { nullptr };

        if( ptr_node->m_ptr_right )
        
            ptr_node = ptr_node->m_ptr_right;

        else if ( ptr_node->m_ptr_down)

            ptr_node = ptr_node->m_ptr_down;

        else 
            return nullptr;

return ptr_node;
}

// definitions for the fixture "Number_enumerator"
parser_test::NumberEnumeratorTest::NumberEnumeratorTest() :

    // set valid enum Nodes
    m_valid_enum_nodes{
        { 
                {"1", "Node_1"},
                    {"1.1", "Node_1_1" },
			    	{"1.2", "Node_1_2" },
			    	{"1.3", "Node_1_3" },
			    	    {"1.3.1", "Node_1_3_1"},
					    {"1.3.2", "Node_1_3_2"},
				    {"1.4", "Node_1_4"},
                {"2", "Node_2"}
        }
    } {
    // set list of Nodes for enumerate
    while(m_tokens_stream)
        ls_nodes.add( m_tokens_stream.get() );
}
