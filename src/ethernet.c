#include "ethernet.h"

// UNUSED - long parameter list but I still kinda like it more than the new way
// creates new frame
frame_t* createFrame(time_t timestamp, int microsecs, int cap_len, int real_len,
                       unsigned char* src_addr, unsigned char* dst_addr, int type,
                       unsigned char* data, int data_size){
    frame_t* frame = malloc(sizeof(frame_t));
    frame->timestamp = timestamp;
    frame->microsecs = microsecs;
    frame->captured_len = cap_len;
    frame->real_len = real_len;

    frame->src_addr = src_addr;
    frame->dst_addr = dst_addr;
    frame->type = type;
    frame->data = data;
    frame->data_size = data_size;

    frame->next = NULL;

    return frame;
}

// adds frame to list
frame_t* addFrame(frame_t** frame_list_p, frame_t* new_frame){
    if(!frame_list_p){
        return NULL;    //should not happen
    }

    //if empty list, initialize
    if(!(*frame_list_p)){
        *frame_list_p = new_frame;
        return new_frame;
    }

    //if not empty, find the last frame and add the new one
    frame_t* current_frame = *frame_list_p;
    while(current_frame->next != NULL){
        current_frame = current_frame->next;
    }
    current_frame->next = new_frame;

    return new_frame;
}

// releases memory held by frame
void clearFrame(frame_t* frame){
    freePtr((void**)&frame->dst_addr);
    freePtr((void**)&frame->src_addr);
    freePtr((void**)&frame->data);
}

// releases all memory
void clearFrames(frame_t** frame_list_p){
    frame_t* cur_frame = (*frame_list_p);

    while(cur_frame){
        clearFrame(cur_frame);
        frame_t* prev_frame = cur_frame;
        cur_frame = cur_frame->next;
        freePtr((void**)&prev_frame);
    }

    *frame_list_p = NULL;
}
