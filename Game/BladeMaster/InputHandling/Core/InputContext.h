#pragma once
#include <memory>
#include <list>
//This is second layer in Input Handling System
/*
  The second layer examines what game contexts are active, and maps the raw inputs into high-level actions, states, and ranges.


  More information:
  https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/designing-a-robust-input-handling-system-for-games-r2975/
*/
class Context;
typedef struct MappedInput;
class InputContext {
public:
  InputContext();
  void Dispatch(MappedInput &);

private:
  /*
    a simple ordered list: each context in the list is given the raw input for the frame. If the context can validly map that raw input
    to an action, state, or range, it does so; otherwise, it passes on to the next context in the list.

    This is similar to Chain of Responsibility

    More information about CoR:
    https://refactoring.guru/design-patterns/chain-of-responsibility
  */
  std::list<std::unique_ptr<Context>> mListContexts;
};
