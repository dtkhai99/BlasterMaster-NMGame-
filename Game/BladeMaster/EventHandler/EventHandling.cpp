#include "EventHandling.h"
#include "EventBase.h"
/*
  After receiving a generic event of type Event it determines its actual type and then calls the
  proper handler method with valid event as a parameter.
*/
void EventHandling::handleEvent(const Event * event) {
  std::map<std::type_index , HandlerFunctionBase *>::iterator actualEventType = mHandlers.find(std::type_index(typeid(event)));
  if(actualEventType != mHandlers.end()) {
    actualEventType->second->exec(event);
  }
}
