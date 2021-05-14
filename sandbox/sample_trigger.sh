#!/bin/bash

#./start_all.sh
#sleep 2s
#./show_cluster.sh
#./test_put.sh ppl kpl
#sleep 2s
#./test_get.sh ppl
#./clean_all.sh

./docker_start.sh 1 1 1 10
./test_put.sh ppl kpl
sleep 2s
./test_get.sh ppl
docker logs one > 1.log
docker logs two > 2.log
docker logs three > 3.log
./kill_dockers.sh