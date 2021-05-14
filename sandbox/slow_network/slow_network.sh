#!/bin/bash
#service docker restart
echo "--cluster_members=172.20.0.2:8868,172.20.0.3:8869,172.20.0.4:8870" > nexus.flag
./docker_start_slow.sh 1.5 1.5 1.5 5s
txt="normal_network_write.log"
./../../output/bin/bench write $1 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 ./percentile_gen.py $txt
sleep 5s
txt="normal_network_read.log"
./../../output/bin/bench read $2 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 ./percentile_gen.py $txt
docker logs three > 3_n.log
docker logs two > 2_n.log
docker logs one > 1_n.log
./kill_dockers.sh
sleep 30s
sudo tc qdisc add dev br-a42e4d19a0b0 root netem delay 200us 50us 25%
./docker_start_slow.sh 1.5 1.5 1.5 5s
txt="slow_network_write.log"
./../../output/bin/bench write $1 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 ./percentile_gen.py $txt
sleep 5s
txt="slow_network_read.log"
./../../output/bin/bench read $2 --flagfile=./nexus.flag > $txt
sleep 2s
./show_cluster.sh
python3 ./percentile_gen.py $txt
docker logs three > 3_n.log
docker logs two > 2_n.log
docker logs one > 1_n.log
./kill_dockers.sh
sudo tc qdisc del dev br-a42e4d19a0b0 root