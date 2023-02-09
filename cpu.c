#include"oslabs.h"
#include<stdio.h>

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp){
    if(current_process.process_id==0){
        new_process.execution_starttime=timestamp;
        new_process.execution_endtime=timestamp+new_process.total_bursttime;
        new_process.remaining_bursttime=new_process.total_bursttime;
        return new_process;
    }
    else{
        if(current_process.process_priority < new_process.process_priority ){
            new_process.execution_starttime=0;
            new_process.execution_endtime=0;
            new_process.remaining_bursttime=new_process.total_bursttime;
            ready_queue[*queue_cnt]=new_process;
            *queue_cnt+=1;
            return current_process;
        }
        else{

            new_process.execution_starttime=timestamp;
            new_process.execution_endtime=timestamp+new_process.total_bursttime;
            new_process.remaining_bursttime=new_process.total_bursttime;
            current_process.execution_endtime=0;
            current_process.remaining_bursttime=current_process.total_bursttime-current_process.execution_starttime;
            ready_queue[*queue_cnt]=current_process;
            *queue_cnt+=1;
            return new_process;
        }
    }
    
}
