
// This file describes all the fixtures for testing the Lib_parser
# pragma once
    # include <gtest/gtest.h>
    # include <parser_to_enum_list.h>
    # include <array>

    namespace parser_test {

		// 1. Fixture for testing the type Tokens_stream
        class TokensStreamTest : public ::testing::Test {

            protected:
                TokensStreamTest();

                // valid tokens
                std::array<Lib_parser::token_t, 8 > m_valid_tokens;

                // Source data for parsing
                const Lib_parser::data_t m_source_data {"\tNode_1\t\tNode_1_1\t\tNode_1_2\t\tNode_1_3\t\t\tNode_1_3_1\t\t\tNode_1_3_2\t\tNode_1_4\tNode_2"};

		};// end fixture TekensStreamTest

        // 2. Fixture for testing the type List
        class ListTest : public TokensStreamTest {

            protected:
                ListTest();

                std::array<Lib_parser::token_t,8 >  m_valid_nodes;

                Lib_parser::Tokens_stream           m_tokens_stream;

                Lib_parser::Node* get_next_node( Lib_parser::List const& );

            private:
                using TokensStreamTest::m_source_data;
        };

	} // end namespace parser_test
