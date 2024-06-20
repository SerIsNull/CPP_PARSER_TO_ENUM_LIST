 # include <fixture_gtest.h>

// Name: test case #1. Test Tokens_stream
// Desc: this test for tesing methods such as bool() and get()
// good result: false if eof for bool()  and valid token for get()
// bad result : true if eof for bool()   and invalid token for get()
using TokensStreamTest = parser_test::TokensStreamTest;

	TEST_F( TokensStreamTest, methodCheckEofReturnTrue ) {

		Lib_parser::Tokens_stream tokens_stream;

		tokens_stream.set_buffer(m_source_data);
		
		decltype(m_valid_tokens)::size_type cnt_tokens {};
		while( tokens_stream ) {
			tokens_stream.get();
			cnt_tokens++;
		}

		ASSERT_EQ( cnt_tokens, m_valid_tokens.size() );
	}

	TEST_F( TokensStreamTest, methodGetreturnValidToken ) {
	
		Lib_parser::Tokens_stream tokens_stream;

		tokens_stream.set_buffer(m_source_data);

		for( auto const& valid_token : m_valid_tokens )
			ASSERT_EQ( tokens_stream.get(), valid_token );
	}


int main( int argc, char **argv ) {
	
	::testing::InitGoogleTest(&argc, argv );
		
return RUN_ALL_TESTS();
}
