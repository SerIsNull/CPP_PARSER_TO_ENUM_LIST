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

  // definitions for the type "List"
  void Lib_parser::List::add( Lib_parser::token_t token ) noexcept {

     auto const& [nested_level, data] = token;

      Node* ptr_prev = m_ptr_root;

      // go to last Node
      while( ptr_prev ) {

          while( ptr_prev->m_ptr_right ) ptr_prev = ptr_prev->m_ptr_right;

          while( ptr_prev->m_ptr_down  ) ptr_prev = ptr_prev->m_ptr_down;

          if( ptr_prev->m_ptr_right == nullptr and ptr_prev->m_ptr_down == nullptr ) break;

      }
      // allocate new Node
      Node *ptr_next { new Node {.m_ptr_down  = nullptr,
                                 .m_ptr_up    = ptr_prev,
                                 .m_ptr_right = nullptr,
                                 .m_data      = data,
                                 .m_number    = nested_level }

      };
      // link alloacated Node into the Lists
    if( !m_ptr_root ) [[unlikely]]
              m_ptr_root = ptr_next;

      else if (ptr_next->m_number > ptr_prev->m_number )
          ptr_prev->m_ptr_right = ptr_next;

      else
          ptr_prev->m_ptr_down = ptr_next;

  }

  Lib_parser::List::~List() {
  
      if( m_ptr_root ) {
          // go to the Last Node
          while( m_ptr_root ) {
              while( m_ptr_root->m_ptr_right ) m_ptr_root = m_ptr_root->m_ptr_right;
              while( m_ptr_root->m_ptr_down ) m_ptr_root = m_ptr_root->m_ptr_down;

              if( m_ptr_root->m_ptr_right == nullptr and m_ptr_root->m_ptr_down == nullptr ) break;
          }
          // remove all from end
          while( m_ptr_root ) {
              Node* ptr_delete { m_ptr_root };
              m_ptr_root = m_ptr_root->m_ptr_up;
              delete ptr_delete;
          }
      }
  }

