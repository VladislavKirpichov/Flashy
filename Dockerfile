FROM ubuntu:bionic AS build

# Install tools required for the project
RUN apt-get update \
    && apt-get install gcc -y \
    && apt-get install g++ -y \
    && apt-get install cmake -y \
    && apt-get install wget -y \

# Copy the entire project and build it
WORKDIR /app/
COPY . .

RUN cmake build -B cmake-build-debug \
    && cd cmake-build-debug \
    && conan install .. \
    && cmake --build

RUN cd ../ \


ENTRYPOINT ["/app/websocket-chat-server", "0.0.0.0", "8080", "/app/wwwroot"]

EXPOSE 8080