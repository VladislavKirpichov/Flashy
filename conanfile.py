from conans import ConanFile, CMake

class Server(ConanFile):
    name = "Server"
    version = "1.0"
    settigns = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package"
    requires = [("boost/1.78.0"), ("gtest/cci.20210126")]