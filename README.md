# This is my job task ror parsing some data to enumeration data.
I can change the format of enumerating using Ienumerator interface.
In this case I use Number_enumerator for it.
## 1. Node
This type is a part of the result.
## 2. Tokens_stream
This type for preparing data for the next parsing.
## 3. List
This type creates the tree depending on the nested level of the token.
## 3. IEnumerator
This interface for enumeration each Node into the List
## 4. Number_enumerator
This type defines interface Enumeration.
It means that this type enumerates some nodes like before 1 after 2 or befor 1.1 after 1.2 and so on.
## 5. parser
This type is a manager for the types such as Node, Tokens_stream, List and Number_enumerator which define IEnumerator interface.
