cmake_minimum_required(VERSION 3.5)
project(DIThreads VERSION 0.1 DESCRIPTION "Thread module" LANGUAGES CXX)


file( GLOB SOURCES **.cpp )

SetFlags()
SetLibraries( DIDebuger )
CreateLibrary( ${PROJECT_NAME} )