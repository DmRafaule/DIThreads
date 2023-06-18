#include "thread.hpp"

namespace DI{
  ThreadData* eg_thrData;

  void ThreadHandler::Init(){
    DI_LOG_TRACE("ThreadHandler say: Init Threads");
    eg_thrData = new ThreadData(); 
  }
  void ThreadHandler::Kill(){
    DI_LOG_TRACE("ThreadHandler say: Kill Threads");
    delete eg_thrData; 
  }
  void ThreadHandler::UnSet(const std::string name){
    DI_LOG_TRACE("ThreadHandler say: UnSet thread {0}",name);
    eg_thrData->pool.erase(name);
    eg_thrData->type.erase(name);
    eg_thrData->joinPoint.erase(name);
  }
  void ThreadHandler::JoinCall(ThreadData::JoinPoint jPoint){
    // Iterator for cycling throu all setted up threads
    std::unordered_map<std::string,ThreadData::JoinPoint>::iterator it;
    // Threads to be deleted
    std::vector<std::string> thrToDel;
    // Join all joinable thread if specific code location was reached
    for (it = eg_thrData->joinPoint.begin(); it != eg_thrData->joinPoint.end(); it++){
      switch(it->second){
      // For those who was detached
      case ThreadData::JoinPoint::NONE:{
        // Skip 
        break;
      }
      case ThreadData::JoinPoint::END_APP:{
        eg_thrData->pool.find(it->first)->second.join(); 
        thrToDel.push_back(it->first);
        break;
      }
      case ThreadData::JoinPoint::END_FRAME_CYCLE:{
        eg_thrData->pool.find(it->first)->second.join(); 
        thrToDel.push_back(it->first);
        break;
      }
      case ThreadData::JoinPoint::END_EVENT_CYCLE:{
        eg_thrData->pool.find(it->first)->second.join(); 
        thrToDel.push_back(it->first);
        break;
      }
      }
    }
    // Actual remove
    for (int i = 0; i < thrToDel.size(); i++)
      UnSet(thrToDel[i]);
  }
}
