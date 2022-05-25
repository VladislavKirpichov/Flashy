from conans import ConanFile, CMake

class Server(ConanFile):
    name = "src"
    version = "1.0"
    settigns = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package"
    requires = [("boost/1.78.0"), ("gtest/cci.20210126"), ("nlohmann_json/3.10.5"), ("mysql-connector-c/6.1.11")]
    
# conan install .. --build missing -s compiler=gcc -s compiler.version=6.3 -s compiler.libcxx=libstdc++11