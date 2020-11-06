#include "InputContext.h"
#include "MappedInput.h"
#include "Context.h"
#include "../ExteriorSideScrollingContext.h"
#include "../InteriorTopDownContext.h"
InputContext::InputContext() {
  mListContexts.push_front(std::make_unique<ExteriorSideScrollingContext>());
  mListContexts.push_front(std::make_unique<InteriorTopDOwnContext>());
}

void InputContext::Dispatch(MappedInput & mappedInput)
{
    for(std::list<std::unique_ptr<Context>>::iterator it = mListContexts.begin(); it != mListContexts.end() ; it++) {
      if(it->get()->Handle(mappedInput) == true) {
        return;
      }
    }

}
