#pragma once
#include "thread.hpp"
#include <thread>
#include "DIDebuger/log.hpp"
#include <functional>



namespace DI{
  extern ThreadData* eg_thrData;
  // Set up thread and define wich type it is detached or joined
  template <typename T>
  void ThreadHandler::Set(const std::string name, ThreadData::Type type, ThreadData::JoinPoint jPoint, std::function<T> callback){
    DI_LOG_TRACE("ThreadHandler say: Set thread {0}",name);
    eg_thrData->pool.emplace(name,std::thread([&]{
      // Here is some addition logic
      callback();
    }));
    eg_thrData->type.emplace(name,type);
    eg_thrData->joinPoint.emplace(name,jPoint);
    if (type == ThreadData::Type::DETACHED){
      eg_thrData->joinPoint.emplace(name,ThreadData::JoinPoint::NONE);
      eg_thrData->pool.find(name)->second.detach();
    }
  }
}
