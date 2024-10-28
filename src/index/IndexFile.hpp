#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../record_manage/RecordSlot.hpp"
#include "../table/Schema.hpp"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../defines.h"
#include "InternalPage.hpp"
#include "LeafPage.hpp"
#include "IndexSchema.hpp"


/* OPSchema负责最后的读写, data方便收取key */
class IndexFile{
    /* Schemas */
public:
    IndexPageSchema internal_schema;
    IndexPageSchema leaf_schema;
    SlotSchema internal_slot_schema;
    SlotSchema leaf_slot_schema;

    std::vector<int> key_ids;

    /* 管理内存的工具, 我们总是让IndexManager负责所有IndexFile的打开和关闭 */
    int file_id;
    BufPageManager * bpm;

    int tot_num;
    PageID page_num;
    PageID root;
    PageID data_head;

    /* Functions */
    std::vector<int> generate_keys(std::vector<FieldData> data);
    void handle_internal_split(PageID);
    void handle_leaf_split(PageID);
    void handle_leaf_update(PageID);
    void handle_internal_update(PageID);

    // void handle_leaf_merge();
    // void handle_internal_merge();

    /* File Operations */
    std::shared_ptr<InternalPage> get_inpage(PageID page_id);
    std::shared_ptr<LeafPage> get_leafpage(PageID page_id);
    
    std::shared_ptr<InternalPage> create_inpage();
    std::shared_ptr<LeafPage> create_leafpage();

    // 怎么删除一个page?

public:
    IndexFile(int fid, BufPageManager * bm, IndexSchema shcm, IndexInfo info){
        file_id = fid; bpm = bm;
        Logger::logError("IndexFile init " + std::to_string(fid));
        internal_schema = shcm.internal_schema;
        leaf_schema = shcm.leaf_schema;
        internal_slot_schema = shcm.internal_slot_schema;
        leaf_slot_schema = shcm.leaf_slot_schema;
        key_ids = shcm.key_ids;

        tot_num = info.tot_num; page_num = info.page_num ; root = info.root; data_head = info.data_head;
    }
    IndexFile(const IndexFile & other){
        file_id = other.file_id;
        bpm = other.bpm;
        internal_schema = other.internal_schema;
        leaf_schema = other.leaf_schema;
        internal_slot_schema = other.internal_slot_schema;
        leaf_slot_schema = other.leaf_slot_schema;
        key_ids = other.key_ids;

        tot_num = other.tot_num; page_num = other.page_num; root = other.root; data_head = other.data_head;
    }

    bool is_leaf(PageID);

    int get_file_id() const { return file_id;};

    void insert_data(std::vector<FieldData> data, RID rid);

    // void naive_traverse(TARGET op, QuerySchema query, OPSchema judge, OPSchema change);

    void leaf_traverse(TARGET op, QuerySchema query, OPSchema& opschm);

    void inter_traverse(TARGET op, QuerySchema query, OPSchema& opschm);

    void internal_delete_data(PageID , SlotID);

    void leaf_delete_data(PageID id, SlotID);

    bool find_primary_key(std::vector<int> pks);

};