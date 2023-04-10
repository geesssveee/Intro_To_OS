#include"oslabs.h"
#include<stdio.h>
#include<stdlib.h>

struct MEMORY_BLOCK NULLBLOCK={
        .start_address=0,
        .end_address=0,
        .segment_size=0,
        .process_id=0
};
struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
    int i=0;
    int j=0;
    int temp=1023;
    int test=-1;
    if(*map_cnt==0){
        return NULLBLOCK;
    }
    else{
        for(i=0;i<*map_cnt;i++){
            if(request_size==memory_map[i].segment_size && memory_map[i].process_id==0){
                memory_map[i].process_id=process_id;
                return memory_map[i];
            }
        }
        for(i=0;i<*map_cnt;i++){
            if(request_size<memory_map[i].segment_size && memory_map[i].process_id==0){
                if(abs(memory_map[i].segment_size-request_size)<temp){
                    temp=abs(memory_map[i].segment_size-request_size);
                    test=i;
                }
            }
        }
        if(test>=0){
        for(j=*map_cnt;j!=test;--j){
                memory_map[j]=memory_map[j-1];
                }
                memory_map[test+1].process_id=memory_map[test].process_id;
                memory_map[test+1].end_address=memory_map[test].end_address;
                memory_map[test+1].segment_size=memory_map[test].segment_size - request_size;
                memory_map[test+1].start_address=memory_map[test].start_address+request_size;
                memory_map[test].process_id=process_id;
                memory_map[test].end_address=memory_map[test].start_address+request_size-1;
                memory_map[test].segment_size=request_size;
                *map_cnt+=1;
                return memory_map[test];
        }
        
        return NULLBLOCK;
    }
}
// struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
//  int i=0;
//  int j =0;
//  int test=0;
//  if(*map_cnt==0){
//     return NULLBLOCK;
//  }
//  else{
//     for(i=0;i<*map_cnt;i++){
//         if(request_size == memory_map[i].segment_size){
//             memory_map[i].process_id=process_id;
//             return memory_map[i];
//         }
//     }
//     for(i=0;i<*map_cnt;i++){
//         if(memory_map[i].segment_size>request_size && memory_map[i].process_id==0){
//             test=i;
//             for(j=*map_cnt;j>test;--j){
//                 memory_map[j]=memory_map[j-1];
//             }
//             memory_map[test+1].process_id=memory_map[test].process_id;
//             memory_map[test+1].end_address=memory_map[test].end_address;
//             memory_map[test+1].segment_size = memory_map[test].segment_size - request_size;
//             memory_map[test+1].start_address = memory_map[test].start_address+ request_size;
//             memory_map[test].end_address=memory_map[test].start_address + request_size -1;
//             memory_map[test].segment_size = request_size;
//             memory_map[test].process_id = process_id;
//             *map_cnt+=1;
//             return memory_map[test];
//         }
//     }
//     return NULLBLOCK;
//     }
// } 
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    int i;
    struct MEMORY_BLOCK allocated_block = NULLBLOCK;

    for (i = 0; i < *map_cnt; i++) {
        if (memory_map[i].process_id == 0 && memory_map[i].segment_size >= request_size) {
            if (memory_map[i].segment_size == request_size) {
                // Allocate the entire block to the process
                memory_map[i].process_id = process_id;
                allocated_block = memory_map[i];
            } else {
                // Split the block into allocated and free blocks
                struct MEMORY_BLOCK free_block;
                free_block.start_address = memory_map[i].start_address + request_size;
                free_block.end_address = memory_map[i].end_address;
                free_block.segment_size = memory_map[i].segment_size - request_size;
                free_block.process_id = 0;

                memory_map[i].end_address = memory_map[i].start_address + request_size - 1;
                memory_map[i].segment_size = request_size;
                memory_map[i].process_id = process_id;

                // Add the free block to the memory map
                if (*map_cnt < MAPMAX) {
                    memory_map[*map_cnt] = free_block;
                    *map_cnt += 1;
                }

                allocated_block = memory_map[i];
            }

            break;
        }
    }

    return allocated_block;
} 
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id){
    int i=0;
    int j=0;
    int maxi=0;
    int test=-1;
    if(*map_cnt==0){
        return NULLBLOCK;
    }
    else{
        for(i=0;i<*map_cnt;i++){
            if(request_size==memory_map[i].segment_size && memory_map[i].process_id==0){
                memory_map[i].process_id=process_id;
                return memory_map[i];
            }
        }
        for(i=0;i<*map_cnt;i++){
            if(request_size<memory_map[i].segment_size && memory_map[i].process_id==0){
                if(memory_map[i].segment_size>maxi){
                    maxi=memory_map[i].segment_size;
                    test=i;
                }
            }
        }
        if(test>=0){
            for(j=*map_cnt;j>test;--j){
                memory_map[j]=memory_map[j-1];
            }
            memory_map[test+1].process_id=memory_map[test].process_id;
            memory_map[test+1].end_address=memory_map[test].end_address;
            memory_map[test+1].segment_size = memory_map[test].segment_size - request_size;
            memory_map[test+1].start_address = memory_map[test].start_address+ request_size;
            memory_map[test].end_address=memory_map[test].start_address + request_size -1;
            memory_map[test].segment_size = request_size;
            memory_map[test].process_id = process_id;
            *map_cnt+=1;
            return memory_map[test];
        }
        else
        return NULLBLOCK;
    }
}
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address){
    int i=0;
    int j=0;
    int maxi=0;
    int test=-1;
    if(*map_cnt==0){
        return NULLBLOCK;
    }
    else{
        for(i=0;i<*map_cnt;i++){
            if(request_size==memory_map[i].segment_size && memory_map[i].process_id==0){
                memory_map[i].process_id=process_id;
                return memory_map[i];
            }
        }
        for(i=0;i<*map_cnt;i++){
            if(request_size<memory_map[i].segment_size && memory_map[i].process_id==0 && memory_map[i].start_address>=last_address){
                for(j=*map_cnt;j>i;--j)
                memory_map[j]=memory_map[j-1];

                memory_map[i+1].process_id=memory_map[i].process_id;
                memory_map[i+1].end_address=memory_map[i].end_address;
                memory_map[i+1].segment_size = memory_map[i].segment_size - request_size;
                memory_map[i+1].start_address = memory_map[i].start_address+ request_size;
                memory_map[i].end_address=memory_map[i].start_address + request_size -1;
                memory_map[i].segment_size = request_size;
                memory_map[i].process_id = process_id;
                *map_cnt+=1;
                return memory_map[i];
            }
        }
        for(i=0;i<*map_cnt;i++){
            if(request_size<memory_map[i].segment_size && memory_map[i].process_id==0){
                for(j=*map_cnt;j>i;--j)
                memory_map[j]=memory_map[j-1];

                memory_map[i+1].process_id=memory_map[i].process_id;
                memory_map[i+1].end_address=memory_map[i].end_address;
                memory_map[i+1].segment_size = memory_map[i].segment_size - request_size;
                memory_map[i+1].start_address = memory_map[i].start_address+ request_size;
                memory_map[i].end_address=memory_map[i].start_address + request_size -1;
                memory_map[i].segment_size = request_size;
                memory_map[i].process_id = process_id;
                *map_cnt+=1;
                return memory_map[i];
            }
        return NULLBLOCK;
        }
    } 
} 
void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt){
    int i,j;
    for(i=0;i<*map_cnt;i++){
    if(freed_block.process_id==memory_map[i].process_id){
    memory_map[i].process_id=0;
    break;
    }
    }
    for(i=0;i<*map_cnt;i++){
        if(memory_map[i].process_id==0 && memory_map[i+1].process_id==0 && memory_map[i+1].start_address==(memory_map[i].end_address+1)){
            memory_map[i].end_address=memory_map[i+1].end_address;
            memory_map[i].segment_size+=memory_map[i+1].segment_size;
            for(j=i+1;j<*map_cnt;j++){
                memory_map[j]=memory_map[j+1];
            }
            *map_cnt-=1;
            i-=1;
        }
        else
        continue;
    }
}
