#!/bin/bash
docker update --cpus $1 one
docker update --cpus $2 two
docker update --cpus $3 three