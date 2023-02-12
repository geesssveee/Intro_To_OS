#include"oslabs.h"
#include<stdio.h>
struct PCB NULLPCB={
        .process_id=0,
        .arrival_timestamp=0,
        .total_bursttime=0,
        .execution_starttime=0,
        .execution_endtime=0,
        .remaining_bursttime=0,
        .process_priority=0};

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
struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp){
    int i=0;
    int minimum=0;
    int pointer=0;
    int j=0;
    struct PCB Copy;
    if(*queue_cnt==0){
        return NULLPCB;
    }
    else{
        minimum=ready_queue[0].process_priority;
        for(i=0;i<*queue_cnt;i++){
            if(ready_queue[i].process_priority<minimum)
            pointer=i;
        }
        ready_queue[pointer].execution_starttime=timestamp;
        ready_queue[pointer].execution_endtime=timestamp+ready_queue[pointer].remaining_bursttime;
        Copy=ready_queue[pointer];
        for(i=pointer;i<*queue_cnt-1;i++){
            ready_queue[i]=ready_queue[i+1];
        }
        *queue_cnt-=1;
        return Copy;
    }
}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{
    if(current_process.process_id==0){
        new_process.execution_starttime=time_stamp;
        new_process.execution_endtime=time_stamp+new_process.total_bursttime;
        new_process.remaining_bursttime=new_process.total_bursttime;
        return new_process;
    }
    else{
        if(current_process.remaining_bursttime < new_process.total_bursttime ){
            new_process.execution_starttime=0;
            new_process.execution_endtime=0;
            new_process.remaining_bursttime=new_process.total_bursttime;
            ready_queue[*queue_cnt]=new_process;
            *queue_cnt+=1;
            return current_process;
        }
        else{
            new_process.execution_starttime=time_stamp;
            new_process.execution_endtime=time_stamp+new_process.total_bursttime;
            new_process.remaining_bursttime=new_process.total_bursttime;
            current_process.remaining_bursttime=current_process.total_bursttime-current_process.execution_starttime;
            current_process.execution_endtime=0;
            current_process.execution_starttime=0;
            ready_queue[*queue_cnt]=current_process;
            *queue_cnt+=1;
            return new_process;
        }    
}
}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp){
    int minimum;
    int i=0;
    int pointer=0;
    struct PCB Copy;
    
    if(*queue_cnt==0)
    return NULLPCB;
    else{
        minimum=ready_queue[0].remaining_bursttime;
        for(i=0;i<*queue_cnt;i++){
            if(ready_queue[i].remaining_bursttime<minimum){
            pointer=i;
            }
        }
        ready_queue[pointer].execution_starttime=timestamp;
        ready_queue[pointer].execution_endtime=timestamp+ready_queue[pointer].remaining_bursttime;
        Copy=ready_queue[pointer];
        for(i=pointer;i<*queue_cnt-1;i++){
            ready_queue[i]=ready_queue[i+1];
        }
        *queue_cnt-=1;
        return Copy;
    }
}
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum){
    if(current_process.process_id==0){
    new_process.execution_starttime=timestamp;
    new_process.execution_endtime=timestamp+MIN(new_process.total_bursttime,time_quantum);
    new_process.remaining_bursttime=new_process.total_bursttime;
    return new_process;
    } 
    else{
        new_process.execution_endtime=0;
        new_process.execution_starttime=0;
        new_process.remaining_bursttime=new_process.total_bursttime;
        ready_queue[*queue_cnt]=new_process;
        *queue_cnt+=1;
        return current_process;
    }
}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum){
    int minimum=0;
    int i=0;
    int pointer=0;
    struct PCB Copy;
    if(*queue_cnt==0){
    return NULLPCB;
    }
    else{
        minimum=ready_queue[0].arrival_timestamp;
        for(i=0;i<*queue_cnt;i++){
            if(ready_queue[i].arrival_timestamp<minimum){
            pointer=i;
            }
        }
        ready_queue[pointer].execution_starttime=timestamp;
        ready_queue[pointer].execution_endtime=timestamp+MIN(ready_queue[pointer].remaining_bursttime,time_quantum);
        Copy=ready_queue[pointer];
        for(i=pointer;i<*queue_cnt-1;i++){
            ready_queue[i]=ready_queue[i+1];
        }
        *queue_cnt-=1;
        return Copy;
    }
}
