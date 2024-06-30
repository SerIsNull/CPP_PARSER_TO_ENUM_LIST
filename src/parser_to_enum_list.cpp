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

void Lib_parser::List::print() {

    Node* ptr_node = get_head();

    while( ptr_node ) {

        std::cout << ptr_node->m_number << ':' << ptr_node->m_data << '\n';

        ptr_node = ptr_node->m_ptr_right ? ptr_node->m_ptr_right : ptr_node->m_ptr_down ? ptr_node->m_ptr_down : nullptr;
    }
}

Lib_parser::List::~List() {

    if( m_ptr_root ) {
        // go to the Last Node
        while( m_ptr_root ) {
            m_ptr_root = m_ptr_root->m_ptr_right ? m_ptr_root->m_ptr_right : m_ptr_root->m_ptr_down ? m_ptr_root->m_ptr_down : m_ptr_root;
            if( !m_ptr_root->m_ptr_right and !m_ptr_root->m_ptr_down ) break;
        }

        // remove all Nodes started from end
        while( m_ptr_root ) {
            Node* ptr_delete { m_ptr_root };
            m_ptr_root = m_ptr_root->m_ptr_up;
            delete ptr_delete;
        }
      }
}

// definitions for the type "Number_enumerator"
void Lib_parser::Number_enumerator::inc_number(Lib_parser::Node* ptr_node) {

    nested_lvl_t nested_lvl { ptr_node->m_number };

    // try to get old_number form previous Node.
    number_t old_number { nested_lvl_number.find(nested_lvl) != nested_lvl_number.end() ? nested_lvl_number[nested_lvl] : nested_lvl };
    
    number_t new_number {""};

    // try to get lasp part of number Node for increment it.
    if( std::size_t pos_last_part = old_number.find_last_of('.'); pos_last_part != decltype(old_number)::npos ) {

        Lib_parser::number_t new_last_part { old_number.begin() + pos_last_part + 1, old_number.end() };
        
        // increment it
        new_last_part = std::to_string(std::stoi(new_last_part)+ 1 );

        // add increment last part into new number
        new_number = old_number.replace( pos_last_part + 1, new_last_part.size(), new_last_part );
    }
    else
        // I just increment it because it's a number without few parts
        new_number  = std::to_string(std::stoi(old_number) + 1);

    // write new number into the table of associative nested level and number
    // It's necessary for next enumerations
    nested_lvl_number[nested_lvl] = new_number;

    // write new number into Node
    ptr_node->m_number = new_number;
}

void Lib_parser::Number_enumerator::add_number(Lib_parser::Node* ptr_node) {

    nested_lvl_t nested_lvl { ptr_node->m_number };

    // get old_number form previous Node.
    number_t old_number { ptr_node->m_ptr_up->m_number };

    old_number.append(".1");

    number_t new_number = old_number;

    // write new number into the table of associative nested level and number.
    // It's necessary for next enumerations
    nested_lvl_number[nested_lvl] = new_number;

    // write new number into Node
    ptr_node->m_number = new_number;
}


