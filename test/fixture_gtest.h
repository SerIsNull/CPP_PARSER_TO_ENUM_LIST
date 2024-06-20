// This file for declarations all the necessary things for the testing
# pragma once
	# include <gtest/gtest.h>
	# include <parser_to_enum_list.h>
	# include <array>

	namespace parser_test {
		
		// 1. Fixture for TokensStream testing
		class TokensStreamTest : public ::testing::Test {
			
			protected:

				TokensStreamTest();

				// Valid tokens
				std::array<Lib_parser::token_t, 8 > m_valid_tokens;

				// Source data for parsing
				const Lib_parser::data_t m_source_data {"\tNode_1\t\tNode_1_1\t\tNode_1_2\t\tNode_1_3\t\t\tNode_1_3_1\t\t\tNode_1_3_2\t\tNode_1_4\tNode_2"};

		}; // end fixture TekensStreamTest

	} // end namespace parser_test
