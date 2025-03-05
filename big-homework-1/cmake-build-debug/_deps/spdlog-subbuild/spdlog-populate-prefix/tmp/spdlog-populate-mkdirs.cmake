# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-src"
  "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-build"
  "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-subbuild/spdlog-populate-prefix"
  "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-subbuild/spdlog-populate-prefix/tmp"
  "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
  "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src"
  "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/big-homework-1/cmake-build-debug/_deps/spdlog-subbuild/spdlog-populate-prefix/src/spdlog-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
