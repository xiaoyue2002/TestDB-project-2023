
// #ifndef LIST_FUNCTION_HPP
// #define LIST_FUNCTION_HPP

// /*
//     Used to iterate over an ordered list.
// */
// template <typename DMType, typename DStruct, typename IndexType, typename KeyType>
// class ListFunction{
//     /**
//      * Iterate over the linked list, getting elements greater than or equal to the specified key.
//      * @param dm : Data management object used to access a linked list element.
//      * @param start : Start index
//      * @param target : Reference to target index found, set to -1 if not fount
//      * @param value : Key value to find
//     */
//     static void get_ge_key(const DMType dm, IndexType start, IndexType &target, const KeyType value){
//         IndexType current = start;
//         while (current != -1){
//             DStruct entry = dm.get_from_index(start);
//             KeyType currentKey = entry.key;
//             if (currentKey >= value){
//                 target = current;
//                 return;
//             }
//             current = entry.next;
//         }
//         target = -1;
//     }
// }

// #endif