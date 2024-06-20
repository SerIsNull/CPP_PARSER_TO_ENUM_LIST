# include <fixture_gtest.h>

// definitions for the fixture "TokensstreamTesta"


parser_test::TokensStreamTest::TokensStreamTest() :
	m_valid_tokens{ 
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
