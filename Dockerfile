FROM ubuntu:latest
WORKDIR /server

# Install all libs
RUN apt update -y && \
    apt install -y cppcheck clang-tidy libc6-dbg cmake

RUN apt-get update -y && \
    apt-get -y install python3-pip && \
    pip install cpplint

# instsall conan
RUN pip install conan

# install boost
RUN apt-get update -y && \
    apt-get -y install libboost-all-dev

# copy files from project
COPY . .
COPY CMakeLists.txt .
COPY conanfile.py .

# create cmake-build-debug folder
RUN cmake -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug; exit 0

# install all nedeed libs (boost, gtest, nlohhman)
RUN cd cmake-build-debug && \
    conan install ..

# ---------------

# ERROR: CMake Error at server/CMakeLists.txt:5 (find_package):
# By not providing "Findnlohmann_json.cmake" in CMAKE_MODULE_PATH this
#  project has asked CMake to find a package configuration file provided by
#  "nlohmann_json", but CMake did not find one.
#
#  Could not find a package configuration file provided by "nlohmann_json"
#  with any of the following names:
#
#    nlohmann_jsonConfig.cmake
#    nlohmann_json-config.cmake

# ---------------

# build server
RUN cmake . && \
    cd cmake-build-debug/server

EXPOSE 8080

# run server
CMD ["./src"]
