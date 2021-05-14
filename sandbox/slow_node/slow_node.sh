#!/bin/bash
echo "--cluster_members=varshith:8868,varshith:8869,varshith:8870" >nexus.flag
./docker_start.sh 1.5 1.5 1.5 10s
txt="normal_write.log"
./../../output/bin/bench write $1 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 percentile_gen.py $txt
sleep 10s
txt="normal_read.log"
./../../output/bin/bench read $2 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 percentile_gen.py $txt
docker logs three > 3_n.log
docker logs two > 2_n.log
docker logs one > 1_n.log
./kill_dockers.sh
sleep 5s
./docker_start.sh 1.5 1.5 0.02 10s
txt="slow_write.log"
./../../output/bin/bench write $1 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 percentile_gen.py $txt
sleep 10s
txt="slow_read.log"
./../../output/bin/bench read $2 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 percentile_gen.py $txt
docker logs three > 3_s.log
docker logs two > 2_s.log
docker logs one > 1_s.log
./kill_dockers.sh
