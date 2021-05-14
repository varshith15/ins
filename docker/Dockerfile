FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -y update && apt-get -y upgrade && apt-get -y install git
RUN apt-get -y install wget
RUN apt-get install -y libboost-dev libsnappy-dev && apt-get -y install zlib1g-dev && apt-get -y install cmake
RUN apt-get -y install g++
COPY ./ /ins/
WORKDIR /ins
RUN make clean
RUN make
RUN echo "--cluster_members=one:8868,two:8869,three:8870" >nexus.flag
