#include <vector>
#include <string>
#include <unordered_map>
#include "IndexFile.hpp"
#include <stdexcept>
#include <memory>
#include "../record_manage/RecordSlot.hpp"
#include "../Logger.hpp"

typedef std::shared_ptr<InternalPage> InternaPtr;
typedef std::shared_ptr<LeafPage> LeafPtr;

// get keys
std::vector<int> IndexFile::generate_keys(std::vector<FieldData> data){
    std::vector<int> keys;
    for (auto const & id : key_ids){
        keys.push_back(data[id].intValue);
    }
    return keys;
}

/* File Operetions */

std::shared_ptr<InternalPage> IndexFile::get_inpage(PageID page_id){
    std::shared_ptr<InternalPage> page = std::make_shared<InternalPage>(file_id, page_id, bpm, &internal_schema, &internal_slot_schema);
    page->load();
    return page;
}

std::shared_ptr<LeafPage> IndexFile::get_leafpage(PageID page_id){
    Logger::logError("get-leaf-page" + std::to_string(page_id));
    std::shared_ptr<LeafPage> page = std::make_shared<LeafPage>(file_id, page_id, bpm, &leaf_schema, &leaf_slot_schema);
    page->load();
    return page;
}


bool IndexFile::is_leaf(PageID page_id){
    int index;
    // Logger::logError("is_leaf (" + std::to_string(page_id) + ")");
    BufType buff_ptr = bpm->getPage(file_id, page_id, index);
    bool res = internal_schema.get_is_leaf(reinterpret_cast<BytePtr>(buff_ptr));
    // Logger::logError(std::to_string(res));
    return res;
}

std::shared_ptr<InternalPage> IndexFile::create_inpage(){
    Logger::logError("create-in-page " + std::to_string(page_num));
    std::shared_ptr<InternalPage> page = std::make_shared<InternalPage>(file_id, page_num, bpm, &internal_schema, &internal_slot_schema);
    page->write();
    page_num += 1;
    Logger::logError("success.");
    return page;
}

std::shared_ptr<LeafPage> IndexFile::create_leafpage(){
    Logger::logError("create_leaf-page " + std::to_string(page_num));
    std::shared_ptr<LeafPage> page = std::make_shared<LeafPage>(file_id, page_num, bpm, &leaf_schema, &leaf_slot_schema);
    page->write();
    page_num += 1;
    return page;
}

// 这两个函数实现是一样的
// 传入的是本节点，更新的是父亲
void IndexFile::handle_internal_update(PageID this_id){
     Logger::logError("handle-internal-update");
    std::shared_ptr<InternalPage> this_page = get_inpage(this_id);
    if (this_page->parent != -1){
        if (this_page->slot_head == -1){
            std::runtime_error("No slot head!");
        }
        std::vector<int> min_keys = this_page->get_first_keys();
        SlotID parent_slot = this_page->parent_slot;
        std::shared_ptr<InternalPage> father_page = get_inpage(this_page->parent);
        OPResult res = father_page->update_slot_keys(parent_slot, min_keys);
        father_page->print();
        if (res == OPResult::UPDATE){
            handle_internal_update(this_page->parent);
        }
    } 
}

void IndexFile::handle_leaf_update(PageID this_id){
    Logger::logError("handle-leaf-update");
    std::shared_ptr<LeafPage> this_page = get_leafpage(this_id);
    // if has father
    if (this_page->parent != -1){
        if (this_page->slot_head == -1){
            std::runtime_error("No slot head!");
        }
        std::vector<int> min_keys = this_page->get_first_keys();
        SlotID parent_slot = this_page->parent_slot;
        std::shared_ptr<InternalPage> father_page = get_inpage(this_page->parent);
        
        OPResult res = father_page->update_slot_keys(parent_slot, min_keys);
        father_page->print();
        if (res == OPResult::UPDATE){
            handle_internal_update(this_page->parent);
        }
    }
}

void IndexFile::handle_internal_split(PageID this_id){
    Logger::logError("handle_internal_split");

    std::shared_ptr<InternalPage> this_page = get_inpage(this_id);
    // TODO
    std::vector<MemoryBlock> mem_block = this_page->get_half_out();
    std::shared_ptr<InternalPage> brother = create_inpage();

    brother->insert_blocks(mem_block);

    for (auto const & child : brother->get_all_child()){
        if (is_leaf(child)){
            std::shared_ptr<LeafPage> child_page = get_leafpage(child);
            child_page->parent = brother->page_id;
            child_page->write();
        }else{
            std::shared_ptr<InternalPage> child_page = get_inpage(child);
            child_page->parent = brother->page_id;
            child_page->write();
        }
    }

    OPResult res;
    // this | brother

    std::shared_ptr<InternalPage> father;
    // -- * 修改父亲 * --
    if (this_page->parent != -1){
        father = get_inpage(this_page->parent);
        SlotID brother_slot;

        res = father->insert_slot_keys(brother->get_first_keys(), brother->page_id,  brother_slot);
        
        brother->parent = father->page_id;
        brother->parent_slot = brother_slot;

        brother->write();
    }else { // 自己是root
        father = create_inpage();
        SlotID this_slot, brother_slot;
        
        // Logger::logError("1");
        father->insert_slot_keys(this_page->get_first_keys(), this_id, this_slot);
        father->insert_slot_keys(brother->get_first_keys(), brother->page_id, brother_slot);

        // Logger::logError("2");
        this_page->parent = father->page_id;
        this_page->parent_slot = this_slot;

        brother->parent = father->page_id;
        brother->parent_slot = brother_slot;

        this_page->write();
        brother->write();
        root = father->page_id; // 父亲是新的root

        res = OPResult::SUCCESS;
    }

    father->print();
    this_page->print();
    brother->print();

    if (father->check_full()){
        handle_internal_split(father->page_id); // TODO
    }

}

void IndexFile::handle_leaf_split(PageID this_id){
    Logger::logError("handle_leaf_split");

    std::shared_ptr<LeafPage> this_page = get_leafpage(this_id);
    std::vector<MemoryBlock> mem_block = this_page->get_half_out();
    std::shared_ptr<LeafPage> brother = create_leafpage();
    
    brother->insert_blocks(mem_block);

    // this | brother 

    // -- * 设置 prev, next * --
    PageID ori_next_page = this_page->next_page;
    this_page->next_page = brother->page_id;

    brother->prev_page = this_id; // this | brother | ori
    brother->next_page = ori_next_page;

    // -- * 也许有兄弟 * --
    if (ori_next_page != -1){ // brother | ori
        std::shared_ptr<LeafPage> ori_next = get_leafpage(ori_next_page);
        ori_next->prev_page = brother->page_id;
        ori_next->write();
    }
    
    this_page->write();
    brother->write();
    // -- * end * --

    OPResult res;

    std::shared_ptr<InternalPage> father;
    // -- * 修改父亲 * --
    if (this_page->parent != -1){
        father = get_inpage(this_page->parent);
        SlotID brother_slot;

        res = father->insert_slot_keys(brother->get_first_keys(), brother->page_id,  brother_slot);
        
        brother->parent = father->page_id;
        brother->parent_slot = brother_slot;

        brother->write();
    }else { // 自己是root
        father = create_inpage();
        SlotID this_slot, brother_slot;
        
        // Logger::logError("1");
        father->insert_slot_keys(this_page->get_first_keys(), this_id, this_slot);
        father->insert_slot_keys(brother->get_first_keys(), brother->page_id, brother_slot);

        // Logger::logError("2");
        this_page->parent = father->page_id;
        this_page->parent_slot = this_slot;

        brother->parent = father->page_id;
        brother->parent_slot = brother_slot;

        this_page->write();
        brother->write();
        root = father->page_id; // 父亲是新的root

        res = OPResult::SUCCESS;
    }

    father->print();

    // std::ofstream outFile1("show/" + std::to_string(brother->page_id) + "_split.txt");
    // brother->print(outFile1, opschm);
    // std::ofstream outFile2("show/" + std::to_string(this_id) + "_split.txt");
    // this_page->print(outFile2, opschm);
    // outFile1.close(); outFile2.close();

    if (father->check_full()){
        handle_internal_split(father->page_id); // TODO
    }
}

void IndexFile::insert_data(std::vector<FieldData> data, RID rid){
    std::vector<int> keys = generate_keys(data);

    // if there's no data, there's no page then
    if (root == -1){
        // If there's no page, create one
        std::shared_ptr<LeafPage> new_leaf = create_leafpage();
        
        new_leaf->set_parent(-1, -1);
        new_leaf->insert_data(keys, rid);
        new_leaf->write();

        root = new_leaf->page_id;
        data_head = new_leaf->page_id;
        tot_num += 1;
        return ;
    }
    
    PageID now = root;
    PageID child;
    int index;
    
    // first try to find the right leaf page
    while (!is_leaf(now)){
        Logger::logError("leaf?");
        if (get_inpage(now)->search_child(keys, child) == OPResult::SUCCESS){
            now = child;
        }else {
            throw std::runtime_error("Failed to find page.");
        }
    }


    // then we find a leaf page
    OPResult res = get_leafpage(now)->insert_data(keys, rid);
    if (res == OPResult::FAILED){
        throw std::runtime_error("Something wrong.");
    }else if (res == OPResult::UPDATE){
        handle_leaf_update(now);
    }

    tot_num += 1;

    if (get_leafpage(now)->check_full()){
        handle_leaf_split(now);
    }

    return;
}

void IndexFile::internal_delete_data(PageID id, SlotID slot_id){
    InternaPtr page = get_inpage(id);
    OPResult res = page->delete_slot(slot_id);

    if (page->parent != -1){
        if (res == OPResult::DELETE){
            internal_delete_data(page->parent, page->parent_slot);
        } else if (res == OPResult::UPDATE){
            handle_internal_update(id);
        }
    }
}

void IndexFile::leaf_delete_data(PageID id, SlotID slot_id){
    LeafPtr page = get_leafpage(id);
    OPResult res = page->delete_slot(slot_id);
    
    if (page->parent != -1){
        if (res == OPResult::DELETE){
            internal_delete_data(page->parent, page->parent_slot);
        } else if (res == OPResult::UPDATE){
            handle_leaf_update(id);
        }
    }
}

// void inter_traverse

// void IndexFile::naive_traverse(TARGET op, QuerySchema query, OPSchema judge, OPSchema change){
//     PageID now = data_head;
//     PageID next;

//     LeafPtr page;
//     int index;
//     int tot = 0;

//     while (now != -1){
//         page = get_leafpage(now);
//         SlotID this_slot = page->slot_head;
//         SlotID next_slot, prev_slot;
//         BytePtr slot_ptr;
//         BytePtr buff_ptr;

//         while (this_slot != -1){
//             tot += 1;
            // // 由于中途可能换页, 我们经常查找buff_ptr
            // buff_ptr = page->get_page(index);
            // page->slot_manager.load_bitmap_bool(buff_ptr);

            // slot_ptr = page->get_slot_ptr(this_slot, buff_ptr);
            // // page->slot_manager.get_by_index(this_slot, judge);

            // // 可能发生换页
            // if (query.compare_data(judge.result_data)){
            //     if (op == TARGET::DELETE){
            //         leaf_delete_data(now, this_slot);
            //     } else if (op == TARGET::SELECT){
            //         // page->slot_manager.get_by_index(this_slot, change);
            //         std::cout << change.tostring_data(change.result_data) << std::endl;
            //     } else if (op == TARGET::UPDATE){
                    // page->slot_manager.get_by_index(this_slot, change);
//                     leaf_delete_data(now, this_slot);
//                 }
//             }

//             // 查找
//             buff_ptr = page->get_page(index);
//             slot_ptr = page->get_slot_ptr(this_slot, buff_ptr);
//             page->read_slot(prev_slot, next_slot, slot_ptr);
//             this_slot = next_slot;
//         }

//         std::cout<< "travel tot" << tot << std::endl;
//         buff_ptr = page->get_page(index);
//         now = leaf_schema.get_next_page(buff_ptr);
//     }
// }

bool IndexFile::find_primary_key(std::vector<int> pkds){
    PageID now; 
    PageID child;

    if (now == -1){
        return false;
    }

    int index;
    while (!is_leaf(now)){
        child = get_inpage(now)->find(pkds);
        now = child;
    }

    SlotID slot_id;
    return get_leafpage(now)->find(pkds, slot_id);
}