# pragma once 

	# include <iostream>
	# include <sstream>
	# include <string>

// begin main namespace 
namespace Lib_parser {

	// common types
	using data_t   = std::basic_string<char>;
	using number_t = data_t;
	using token_t  = std::pair<number_t, data_t>;
	
	// This type is part of result
	class Node {
		public:
			Node *m_ptr_down  { nullptr },
			     *m_ptr_up    { nullptr },
			     *m_ptr_right { nullptr };
	};

	class Tokens_stream {
		public:
			Tokens_stream() = default;
			Tokens_stream( Tokens_stream const& ) = delete;
			Tokens_stream( Tokens_stream && )     = delete;
			Tokens_stream& operator=( Tokens_stream const&) = delete;
			Tokens_stream& operator=( Tokens_stream && )    = delete;

			// set new buffer
			void set_buffer( data_t buffer ) noexcept { m_ss.str( buffer ); }

			// get next token
			token_t get() noexcept;

			// check state of stream
			operator bool() { return m_ss.good(); }
		private:
			std::basic_stringstream< data_t::value_type> m_ss;

	}; // end type Token_stream

} // end main namespace 
