#include "InputContext.h"
#include "MappedInput.h"
#include "Context.h"
void InputContext::Dispatch(MappedInput & mappedInput)
{
    for(std::list<std::unique_ptr<Context>>::iterator it = mListContext.begin(); it != mListContext.end() ; it++) {
      if(it->get()->Handle(mappedInput) == true) {
        return;
      }
    }

}
