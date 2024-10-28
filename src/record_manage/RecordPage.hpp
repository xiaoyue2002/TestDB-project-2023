#pragma once
#include <vector>
#include <fstream>
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../table/SlotPage.hpp"
#include "RecordSchema.hpp"
#include "../query/constrains.hpp"
#include "../index/IndexSchema.hpp"

class RecordPage{
private:
    SlotPage slot_manager;

    /* buffer */
    PageID page_id;
    int file_id;
    BufPageManager * bpm;

    /* Schemas */
    RecordPageSchema& page_schema;
    RecordSchema& data_schema;

    PageID prev_page;
    PageID next_page;
    PageID prev_empty;
    PageID next_empty;

public:
    RecordPage(PageID id, int fid, BufPageManager * bp,  RecordSchema&  rs, RecordPageSchema& ps): data_schema(rs), page_schema(ps){
        page_id = id; file_id = fid; bpm = bp;
        slot_manager = SlotPage(ps.max_slot, ps.slot_size, ps.header_size);   
    }
    RecordPage(const RecordPage & other): page_schema(other.page_schema), data_schema(other.data_schema){
        slot_manager = other.slot_manager;
        page_id = other.page_id;
        file_id = other.file_id;
        bpm = other.bpm;
        prev_page = other.prev_page;
        next_page = other.next_page;
        prev_empty = other.prev_empty;
        next_empty = other.next_empty;
    }
    
    // TODO
    OPResult delete_data(SlotID slot);

    // data
    std::vector<RID> insert_batch_data(std::vector<std::vector<FieldData>> data);
    void insert_data(std::vector<FieldData> data);
    void select(std::vector<int> select_ids, std::vector<int> compare_ids, std::vector<Constrain> cons); 
    int delete_data(std::vector<int> compare_ids, std::vector<Constrain> cons); 
    int update_data(std::vector<int> set_ids, std::vector<FieldData> new_data,  std::vector<int> compare_ids, std::vector<Constrain> cons);
    void get_rows(std::vector<int> sel_ids, std::vector<int> comp_ids, std::vector<std::vector<FieldData>>& temp_get, std::vector<std::vector<FieldData>>& temp_comp, std::vector<Constrain> bench, std::vector<int> bench_index);

    void load_bitmap();

    void save();

    bool empty();

    void set_pn(PageID p, PageID n);
    void set_p(PageID p);
    void set_n(PageID n);

    void set_empn(PageID p, PageID n);
    void set_emp(PageID p);
    void set_emn(PageID n);

    PageID get_prev();
    PageID get_next();
    PageID get_empprev();
    PageID get_empnext();

    BytePtr get_page(int&);

    void print();

    bool dup_pk_check(std::vector<int> pk_data, std::vector<int> pids);
    std::vector<std::vector<int>> check_unique(std::vector<int> kids);
};