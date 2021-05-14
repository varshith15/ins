#include "sdk/ins_sdk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <unistd.h>
using namespace std;

using namespace galaxy::ins::sdk;

string gen_random(int len) {
    string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    srand( (unsigned) time(NULL) * getpid());
    for (int j = 0; j < len; ++j)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;
}

void my_watch_cb(const WatchParam& param, SDKError error) {
    InsSDK* sdk = static_cast<InsSDK*>(param.context);
    printf("key: %s\n", param.key.c_str());
    printf("value: %s\n", param.value.c_str());
    printf("deleted: %s\n", param.deleted ?"true":"false");
    printf("error code: %d\n", static_cast<int>(error));
    if (sdk) {
        printf("watch again\n");
        SDKError er;
        sdk->Watch(param.key, my_watch_cb, (void*)sdk, &er);
    }
}

void on_session_timeout(void* context) {
    (void)context;
    fprintf(stderr, "in session timeout\n");
    exit(1);
}

inline double get_time(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double) tv.tv_usec / 1000000;
}

inline double get_time_accurate() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec + (double) ts.tv_nsec / 1000000000;
}

void filewrite(vector<double> v, string file_name){
    ofstream file;
    file.open(file_name);
    for(int i=0;i<v.size();++i){
        file<<v[i]<<endl;
    }
    file.close();
}


int main(int argc, char* argv[]) {
    std::vector<std::string> members;
    if (argc < 3) {
        fprintf(stderr, "./bench [read|write] op file_output\n");
        return 1;
    }
    if (strcmp("write", argv[1]) == 0) {
        int op = atoi(argv[2]);
        fprintf(stderr,"write test\n");
        InsSDK::ParseFlagFromArgs(argc, argv, &members);
        InsSDK sdk(members);
        char key_buf[1024] = {'\0'};
        SDKError err;
        double tt = 0.0;
        bool flag = true;
        double start = get_time();
        for (auto i=0; i<op; i++) {
            snprintf(key_buf, sizeof(key_buf), "key_%d", i);
            string val = gen_random(128);
            if (flag == true)
                start = get_time();
            sdk.Put(key_buf, val.c_str(), &err);
            double end = get_time();
            if (err == kClusterDown) {
                i--;
                fprintf(stderr,"try put again: %s", key_buf);
                flag = false;
//                sleep(2);
                continue;
            }
            cout<<fixed<<end-start<<" "<<start<<endl;
            flag = true;
            tt+=end-start;
            val.clear();
            fflush(stdout);
        }
        fprintf(stderr,"total time taken: %lf\n",tt);
    } else if(strcmp("read", argv[1]) == 0) {
        int op = atoi(argv[2]);
        fprintf(stderr, "read test\n");
        InsSDK::ParseFlagFromArgs(argc, argv, &members);
        InsSDK sdk(members);
        char key_buf[1024] = {'\0'};
        SDKError err;
        double tt = get_time();
        int tru = 0;
        bool flag = true;
        double start = get_time();
        for (int i=0; i<op; i++) {
            snprintf(key_buf, sizeof(key_buf), "key_%d", i);
            std::string value;
            if(flag == true)
                start = get_time();
            sdk.Get(key_buf, &value, &err);
            double end = get_time();
            value.clear();
            if (err == kClusterDown) {
                i--;
                fprintf(stderr,"try get again: %s", key_buf);
                flag = false;
//                sleep(2);
                continue;
            }
            cout<<fixed<<end-start<<" "<<start<<endl;
            flag = true;
            if (err == kOK) {
                tru+=1;
            }
            fflush(stdout);
        }
        fprintf(stderr, "total time taken: %lf\n",get_time()-tt);
        fprintf(stderr, "keys found: %d\n",tru);
    } else if(strcmp("watch", argv[1]) == 0) {
        fprintf(stderr, "watch test\n");
        InsSDK::ParseFlagFromArgs(argc, argv, &members);
        InsSDK sdk(members);
        sdk.RegisterSessionTimeout(on_session_timeout, NULL);
        char key_buf[1024] = {'\0'};
        SDKError err;
        for (int i=1; i<=1000; i++) {
            snprintf(key_buf, sizeof(key_buf), "key_%d", i);
            sdk.Watch(key_buf, my_watch_cb, &sdk, &err);
        }
        while (true) {
            sleep(1);
        }
    }
    return 0;
}


//class Benchmark {
//public:
//    Benchmark();
//    ~Benchmark();
//    double start_time;
//    double run_time;
//    double ops;
//    double gap;
//
//    void start() {driver_write_machine(); }
//    void start_loading(); //loading key value pairs
//
//private:
//    enum write_state_enum {
//        INIT_WRITE,
//        ISSUING,
//        WAITING_FOR_TIME,
//        WAITING_FOR_OPQ,
//        MAX_WRITE_STATE,
//    };
//    write_state_enum write_state;
//    void drive_write_machine(double now = 0.0);
//};
//
//void Benchmark::drive_write_machine(double now) {
//    if (now == 0.0) now = get_time();
//
//    double delay;
//    struct timeval tv;
//
//    while (1) {
//        switch (write_state) {
//            case INIT_WRITE:
//                delay = gap;
//                next_time = now + delay;
//                double_to_tv(delay, &tv);
//                write_state = WAITING_FOR_TIME;
//                break;
//
//            case ISSUING:
//                if (now < next_time) {
//                    write_state = WAITING_FOR_TIME;
//                    break; // We want to run through the state machine one more time
//                    // to make sure the timer is armed.
//                }
//
//                issue_something(now);
//                last_tx = now;
//                next_time += gap;
//                break;
//
//            case WAITING_FOR_TIME:
//                if (now < next_time) {
//                    if (!event_pending(timer, EV_TIMEOUT, NULL)) {
//                        delay = next_time - now;
//                        double_to_tv(delay, &tv);
//                        evtimer_add(timer, &tv);
//                    }
//                    return;
//                }
//                write_state = ISSUING;
//                break;
//        }
//    }
//}
//
//int main(int argc, char* argv[]) {
//    std::vector <std::string> members;
//    if (argc < 2) {
//        fprintf(stderr, "./sample [read|write]\n");
//        return 1;
//    }
//    now = get_time();
//    double delay;
//    struct timeval tv;
//
//    if (check_exit_condition(now)) return;
//
//}