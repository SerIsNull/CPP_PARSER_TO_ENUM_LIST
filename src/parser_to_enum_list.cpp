# include <parser_to_enum_list.h>

// definitions for the type "Token_stream"
Lib_parser::token_t Lib_parser::Tokens_stream::get() noexcept {

	data_t::value_type ch {' '};

	// find nested level for token
	int nested_lvl{-1};
	while( m_ss.get(ch) and ch == '\t' )
		nested_lvl++;

	if( !m_ss.eof() )
		m_ss.putback(ch);

	// find data for token
	data_t data {""};
	while( m_ss.get(ch) and ch != '\t')
		data+=ch;

	if( !m_ss.eof() )
		m_ss.putback(ch);

return std::move(std::make_pair( std::to_string(nested_lvl), data ));
}
