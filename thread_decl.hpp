#pragma once

#include <string>
#include <unordered_map>
#include <thread>
#include <functional>

namespace DI {


class ThreadData{
public: 
  enum Type{
    JOINED,
    DETACHED,
  };
  enum JoinPoint{
    NONE,
    END_APP,
    END_FRAME_CYCLE,
    END_EVENT_CYCLE
  };
  std::unordered_map<std::string,std::thread> pool;
  std::unordered_map<std::string,Type> type;
  std::unordered_map<std::string,JoinPoint> joinPoint;
};
  namespace ThreadHandler{
    void Init();
    void Kill();
    template <typename T>
    void Set(const std::string name, ThreadData::Type type, ThreadData::JoinPoint jPoint, std::function<T> callback);
    void UnSet(const std::string name);
    void JoinCall(ThreadData::JoinPoint jPoint);
  }
}
