#include"oslabs.h"
#include<stdio.h>
#include<stdlib.h>

int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    int i;
    int newframe;
    int index=-1;
    int smallest=current_timestamp;
    if(page_table[page_number].is_valid==1){
        page_table[page_number].reference_count+=1;
        page_table[page_number].last_access_timestamp= current_timestamp;
        newframe = page_table[page_number].frame_number;
        return newframe;
    }
    else{
        if(*frame_cnt>0){
        newframe=frame_pool[*frame_cnt-1];
        page_table[page_number].arrival_timestamp=current_timestamp;
        page_table[page_number].frame_number=newframe;
        page_table[page_number].is_valid=1;
        page_table[page_number].reference_count=1;
        page_table[page_number].last_access_timestamp=current_timestamp;
        *frame_cnt-=1;
        return newframe;
        }
        else{
            for(i=0;i<*table_cnt;i++){
                if(page_table[i].is_valid==1 && page_table[i].arrival_timestamp<smallest){
                    smallest=page_table[i].arrival_timestamp;
                    index=i;
                }
            }
            newframe=page_table[index].frame_number;
            page_table[index].arrival_timestamp=-1;
            page_table[index].reference_count=-1;
            page_table[index].last_access_timestamp=-1;
            page_table[index].frame_number=-1;
            page_table[index].is_valid=0;
            page_table[page_number].arrival_timestamp=current_timestamp;
            page_table[page_number].frame_number=newframe;
            page_table[page_number].is_valid=1;
            page_table[page_number].reference_count=1;
            page_table[page_number].last_access_timestamp=current_timestamp;
            return newframe;
        }
    }
}
int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){}
int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    int i;
    int newframe;
    int index=-1;
    int smallest=current_timestamp;
    if(page_table[page_number].is_valid==1){
        page_table[page_number].reference_count+=1;
        page_table[page_number].last_access_timestamp= current_timestamp;
        newframe = page_table[page_number].frame_number;
        return newframe;
    }
    else{
        if(*frame_cnt>0){
        newframe=frame_pool[*frame_cnt-1];
        page_table[page_number].arrival_timestamp=current_timestamp;
        page_table[page_number].frame_number=newframe;
        page_table[page_number].is_valid=1;
        page_table[page_number].reference_count=1;
        page_table[page_number].last_access_timestamp=current_timestamp;
        *frame_cnt-=1;
        return newframe;
        }
        else{
            for(i=0;i<*table_cnt;i++){
                if(page_table[i].is_valid==1 && page_table[i].last_access_timestamp<smallest){
                    smallest=page_table[i].last_access_timestamp;
                    index=i;
                }
            }
            newframe=page_table[index].frame_number;
            page_table[index].arrival_timestamp=-1;
            page_table[index].reference_count=-1;
            page_table[index].last_access_timestamp=-1;
            page_table[index].frame_number=-1;
            page_table[index].is_valid=0;
            page_table[page_number].arrival_timestamp=current_timestamp;
            page_table[page_number].frame_number=newframe;
            page_table[page_number].is_valid=1;
            page_table[page_number].reference_count=1;
            page_table[page_number].last_access_timestamp=current_timestamp;
            return newframe;
        }
    }
}
int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){}
int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    int i;
    int newframe;
    int index=-1;
    int smallest=current_timestamp;
    int small=REFERENCEMAX;
    if(page_table[page_number].is_valid==1){
        page_table[page_number].reference_count+=1;
        page_table[page_number].last_access_timestamp= current_timestamp;
        newframe = page_table[page_number].frame_number;
        return newframe;
    }
    else{
        if(*frame_cnt>0){
        newframe=frame_pool[*frame_cnt-1];
        page_table[page_number].arrival_timestamp=current_timestamp;
        page_table[page_number].frame_number=newframe;
        page_table[page_number].is_valid=1;
        page_table[page_number].reference_count=1;
        page_table[page_number].last_access_timestamp=current_timestamp;
        *frame_cnt-=1;
        return newframe;
        }
        else{
            for(i=0;i<*table_cnt;i++){
                if(page_table[i].is_valid==1 && page_table[i].reference_count<=small){
                    if(page_table[i].arrival_timestamp<smallest){
                    small=page_table[i].reference_count;
                    index=i;
                    smallest=page_table[i].arrival_timestamp;
                    }
                }
            }
            newframe=page_table[index].frame_number;
            page_table[index].arrival_timestamp=-1;
            page_table[index].reference_count=-1;
            page_table[index].last_access_timestamp=-1;
            page_table[index].frame_number=-1;
            page_table[index].is_valid=0;
            page_table[page_number].arrival_timestamp=current_timestamp;
            page_table[page_number].frame_number=newframe;
            page_table[page_number].is_valid=1;
            page_table[page_number].reference_count=1;
            page_table[page_number].last_access_timestamp=current_timestamp;
            return newframe;
        }
    }
}
int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    
}