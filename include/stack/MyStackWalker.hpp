#ifndef MY_STACK_WALKER_HPP
#define MY_STACK_WALKER_HPP

#include "stack-walker/StackWalker.h"

class MyStackWalker : public StackWalker
{

public:
	MyStackWalker() : StackWalker() {}

protected:
	void OnOutput(LPCSTR szText) override;

};

#endif // MY_STACK_WALKER_HPP