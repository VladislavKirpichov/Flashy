FROM gcc:latest
WORKDIR /server

# Install all libs
RUN apt update -y && \
    apt install -y cppcheck clang-tidy libc6-dbg cmake

RUN apt-get -y install python3-pip && \
    pip install cpplint

# instsall conan
RUN pip install conan

# copy files from project
COPY . .
COPY CMakeLists.txt .
COPY conanfile.py .

# create cmake-build-debug folder
RUN cmake -B cmake-build-debug -S . -DCMAKE_BUILD_TYPE=Debug; exit 0

# install all nedeed libs (boost, gtest, nlohhman)
RUN cd cmake-build-debug && \
    conan install .. -s compiler.libcxx=libstdc++11

# ---------------

# ERROR: CMake Error at src/CMakeLists.txt:5 (find_package):
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

# build src
RUN cmake . && \
    cd cmake-build-debug/src

EXPOSE 8080

# run src
CMD ["./src"]
