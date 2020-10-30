#pragma once
#include "HandlerFunctionBase.h"
#include<typeinfo>
#include<typeindex>
#include<map>
/*
     the main message handling function determines the actual message type using dynamic_cast<>
     The idea is to derive concrete event types from the base class Event and register member functions to handle that
     event in EventHandler class instance. EventHandler is responsible for mapping from the type of event to the proper
     method that handles that event

     The only one thing that the event handling class is aware of is a stable (never changing)
     base event class and concrete message classes that it has interest in.

     More information: https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/effective-event-handling-in-c-r2459/
*/

class Event; //Forward declaration
class EventHandling
{
public:
  void handleEvent(const Event *);

  // T -> HandlerFunctionBase derived class
  // EventT -> kinda like message. this class derive from Event base class
  template<typename T, typename EventT>
  void registerEventFunction(T* obj, void (T::*memFunction)(EventT *) ) {
      mHandlers.emplace(std::type_index(typeid(EventT)), nullptr);
      mHandlers[typeid(EventT)] = new MemberFunctionHandler<T, EventT>(obj, memFunction);
  }

private:
  std::map<std::type_index , HandlerFunctionBase *> mHandlers;
};
