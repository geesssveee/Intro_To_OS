#include"oslabs.h"
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
struct RCB NULLRCB={
        .request_id=0,
        .arrival_timestamp=0,
        .cylinder=0,
        .address=0,
        .process_id=0
};
struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX], int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
    if(current_request.process_id==NULLRCB.process_id){
        return new_request;
    }
    request_queue[*queue_cnt]=new_request;
    *queue_cnt+=1;
    return current_request;
}
struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],int *queue_cnt){
    if ( *queue_cnt==0)
    return NULLRCB;
    int lowestAT= request_queue[0].arrival_timestamp;
    int i=0;
    int test=0;  
    struct RCB copy;      
    for(i=1;i<*queue_cnt;i++){
        if(request_queue[i].arrival_timestamp<lowestAT){
            lowestAT=request_queue[i].arrival_timestamp;
            test=i;
        }
    }
    copy=request_queue[test];
    for(i=test;i<*queue_cnt-1;i++){
        request_queue[i]=request_queue[i+1];
    }
    *queue_cnt-=1;
    return copy;
}
struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
    if(current_request.process_id==NULLRCB.process_id){
        return new_request;
    }
    request_queue[*queue_cnt]=new_request;
    *queue_cnt+=1;
    return current_request;  
}
struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],int *queue_cnt,int current_cylinder){
    if ( *queue_cnt==0)
    return NULLRCB;   
    int closest = abs(request_queue[0].cylinder-current_cylinder);
    int closesttime=request_queue[0].arrival_timestamp;
    int i=0;
    int test=0;
    int pos=0;
    struct RCB copy; 
    for(i=1;i<*queue_cnt;i++){
        test=abs(current_cylinder-request_queue[i].cylinder);
        if(test<=closest){
            if(test<closest){
                closest=test;
                closesttime=request_queue[i].arrival_timestamp;
                pos=i;
            }
            if(test==closest){
                if(request_queue[i].arrival_timestamp<closesttime)
                pos=i;
            }
        }
    }
    copy=request_queue[pos];
    for(i=pos;i<*queue_cnt-1;i++){
        request_queue[i]=request_queue[i+1];
    }
    *queue_cnt-=1;
    return copy;
}
struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, struct RCB current_request, struct RCB new_request, int timestamp){
        if(current_request.process_id==NULLRCB.process_id){
        return new_request;
    }
    request_queue[*queue_cnt]=new_request;
    *queue_cnt+=1;
    return current_request;  
}
struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],int *queue_cnt, int current_cylinder, int scan_direction){
struct RCB next_request = NULLRCB; // Initialize with NULLRCB
    int i;
    int min_distance = -1; // Minimum distance to current cylinder
    int found_same_cylinder = 0; // Flag to check if requests with same cylinder are found
    int found_larger_cylinder = 0; // Flag to check if requests with larger cylinder are found
    int found_smaller_cylinder = 0; // Flag to check if requests with smaller cylinder are found
    if(*queue_cnt==0){
        return NULLRCB;
    }
    // Iterate through the request queue
    for (i = 0; i < *queue_cnt; i++) {
        struct RCB request = request_queue[i];

        // If request has same cylinder as current cylinder
        if (request.cylinder == current_cylinder) {
            // If found_same_cylinder flag is not set or request's arrival time is earlier, update next_request
            if (!found_same_cylinder || request.arrival_timestamp < next_request.arrival_timestamp) {
                next_request = request;
                found_same_cylinder = 1;
            }
        }

        // If scan_direction is 1 and request's cylinder is larger than current cylinder
        if (scan_direction == 1 && request.cylinder > current_cylinder) {
            // If found_larger_cylinder flag is not set or request's cylinder is closer to current cylinder, update next_request
            if (!found_larger_cylinder || request.cylinder - current_cylinder < min_distance) {
                next_request = request;
                min_distance = request.cylinder - current_cylinder;
                found_larger_cylinder = 1;
            }
        }

        // If scan_direction is 0 and request's cylinder is smaller than current cylinder
        if (scan_direction == 0 && request.cylinder < current_cylinder) {
            // If found_smaller_cylinder flag is not set or request's cylinder is closer to current cylinder, update next_request
            if (!found_smaller_cylinder || current_cylinder - request.cylinder < min_distance) {
                next_request = request;
                min_distance = current_cylinder - request.cylinder;
                found_smaller_cylinder = 1;
            }
        }
    }

    // If no requests found with same cylinder or in scan direction, pick the request with closest cylinder
    if (!found_same_cylinder && !found_larger_cylinder && !found_smaller_cylinder) {
        next_request = request_queue[0];
        min_distance = abs(current_cylinder - request_queue[0].cylinder);
        for (i = 1; i < *queue_cnt; i++) {
            int distance = abs(current_cylinder - request_queue[i].cylinder);
            if (distance < min_distance) {
                next_request = request_queue[i];
                min_distance = distance;
            }
        }
    }

    // If a request is found, remove it from the request queue
    if (next_request.request_id != -1) {
        for (i = 0; i < *queue_cnt; i++) {
            if(next_request.request_id==request_queue[i].request_id){
                break;
            }
        }
        for(i;i<*queue_cnt-1;i++){
            request_queue[i]=request_queue[i+1];
        }
    }
    *queue_cnt-=1; 
    return next_request;
}


