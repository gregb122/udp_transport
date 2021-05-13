//Grzegorz Bielecki 288388

#include <arpa/inet.h>

#include "record.h"

const int MAXWHENINF = 64;

int construct_record_from_str(char *str, record rec){
    //TODO string to record
    return 0;
}
int construct_record(int _conn_type, addr _via_router, addr _network_ip, int _mask_len, int _distance, int _reachable, record *rec_out){
    rec_out->conn_type = _conn_type;
    rec_out->via_router_addr = _via_router;
    rec_out->network_ip_with_mask.network_addr = _network_ip;
    rec_out->network_ip_with_mask.mask_len = _mask_len;
    rec_out->reachable = _reachable;

    if(_distance > MAXWHENINF){
        rec_out->distance = UINT32_MAX;
        rec_out->reachable = 0;
        return 0;
    }
    rec_out->distance = _distance;
    return 1;
}

int set_distance(record *rec, int _distance){
    if(_distance > MAXWHENINF){
        rec->distance = UINT32_MAX;
        rec->reachable = 0;
        return 0;
    }
    rec->distance = _distance;
    return 1;//when distance is INF
}

int display_record(record *rec){
    char network_str[16];
    char via_router_str[16];
    
    inet_ntop(AF_INET, 
              &(rec->network_ip_with_mask.network_addr.s_addr), 
              network_str, 16);
    inet_ntop(AF_INET, &(rec->via_router_addr.s_addr), via_router_str, 16);

    printf("%s/%d ", network_str, rec->network_ip_with_mask.mask_len);
    if(!rec->reachable){
        printf("unreachable ");
    } else{
        printf("distance %d ", rec->distance);
    }

    if(!rec->conn_type){
        printf("connected directly\n");
    } else{
        printf("via %s\n", via_router_str);
    }
    return 0;
}

u_int8_t prepare_and_broadcast(record *rec){
    u_int8_t buffer[9];
    uint distance = htonl(rec->distance);
    memset(buffer, 0, sizeof(buffer[0] * 9));
    memcpy(buffer, &rec->network_ip_with_mask.network_addr.s_addr, 4);
    memcpy(buffer + 4, &rec->network_ip_with_mask.mask_len, 1);
    memcpy(buffer + 5, &rec->distance, 4);
    return broadcast_record(buffer);
}

int decode_data_to_fields(record *rec, struct sockaddr_in sender, u_int8_t buffer[]){
    uint distance;
    rec->conn_type = 1;
    rec->via_router_addr = sender.sin_addr;
    memcpy(&rec->network_ip_with_mask.network_addr.s_addr, buffer, 4);
    rec->network_ip_with_mask.mask_len = buffer[4];
    memcpy(&distance, buffer + 5, 4);
    rec->distance = ntohl(distance);
    rec->reachable = 0;
}
        

int broadcast_record(u_int8_t buffer){
    if (broadcast(buffer) == EXIT_FAILURE){
        fprintf(stderr, "Broadcast record error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
