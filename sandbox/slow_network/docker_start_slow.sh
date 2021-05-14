#!/bin/bash
docker run --name one --cpus $1 --network slownet -p 8868 -it -d ins_slow sh -c "output/bin/nexus --flagfile=nexus.flag --server_id=1"
docker run --name two --cpus $2 --network slownet -it -p 8869 -d ins_slow sh -c "output/bin/nexus --flagfile=nexus.flag --server_id=2"
docker run --name three --cpus $3 --network slownet -it -p 8870 -d ins_slow sh -c "output/bin/nexus --flagfile=nexus.flag --server_id=3"
#docker run --name one --cpus $1 -p 8868 --network my-net -it -d ins sh -c "output/bin/nexus --flagfile=nexus.flag --server_id=1"
#docker run --name two --cpus $2 -p 8869 --network my-net -it -d ins sh -c "output/bin/nexus --flagfile=nexus.flag --server_id=2"
#docker run --name three --cpus $3 -p 8870 --network my-net -it -d ins sh -c "output/bin/nexus --flagfile=nexus.flag --server_id=3"
sleep $4
./show_cluster.sh

