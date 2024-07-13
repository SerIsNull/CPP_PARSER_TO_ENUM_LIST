# pragma once
# include <iostream>
# include <sstream>
# include <string>
# include <unordered_map>

// begin main namespace
namespace Lib_parser
{
// common types
using data_t   = std::basic_string<char>;
using number_t = data_t;
using token_t  = std::pair<number_t, data_t>;

// ---------------------------------------------------------------------------------
// This type is part of result
class Node
{
	public:
	Node     *m_ptr_down  { nullptr },
			     *m_ptr_up    { nullptr },
			     *m_ptr_right { nullptr };
    data_t   m_data      {""};
    number_t m_number    {""};
};
// ---------------------------------------------------------------------------------
// This type for preparing data for next parsing
class Tokens_stream
{
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
// ---------------------------------------------------------------------------------
// This type creates the tree depending on the nested level of the token.
class List
{
    public:
    List() = default;
    List( List const& other ) = delete;
    List( List&& other );
    List& operator=( List const& other ) = delete;
    List& operator=( List && other );
    // add node into the tree
    void add( token_t token ) noexcept;
    // getter for the head pointer
    Node* get_head() const noexcept { return m_ptr_root; }
    // print all nodes
    void print();
    // delete all the Nodes
    ~List();
    private:
    Node* m_ptr_root {nullptr};
};
// ---------------------------------------------------------------------------------
// This interface for enumeration each Node into the List
class IEnumerator
{
    public:
    // for incremente each Node from List.
    // For example: before 1, after 2 or before 1.1 after 1.2
    virtual void inc_number(Node* ptr_root) = 0;
    // for adding new part into the number of Node from List.
    // For example: before 1, after 1.1 or before 1.1 after 1.1.1
    virtual void add_number(Node* ptr_root) = 0;
    protected:
    using nested_lvl_t = number_t;
    std::unordered_map<nested_lvl_t, number_t> nested_lvl_number;
};
// ---------------------------------------------------------------------------------
// This type defines interface Enumeration.
// It means that this type enumerates some nodes like before 1 after 2 or befor 1.1 after 1.2 and so on.
class Number_enumerator : public IEnumerator
{
    public:
    void inc_number(Node* ptr_root) override;
    void add_number(Node* ptr_root) override;
};
// ---------------------------------------------------------------------------------
// This type is a manager
class parser
{
    public:
    List parse_from(data_t data);
    private:
    Number_enumerator m_enumerator;
    List m_result;
    Tokens_stream m_tstream;
};
} // end main namespace
