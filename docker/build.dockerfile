FROM nexus.engageska-portugal.pt/ska-docker/tango-cpp:9.3.4-rc4

USER root

RUN apt-get update && apt-get install -y build-essential pkg-config cmake nodejs npm

RUN npm install -g cmake-js

