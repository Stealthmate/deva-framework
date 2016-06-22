#include "InputFunction.hpp"

using namespace DevaEngine;

bool dummy() { return false; }

InputFunction::InputFunction()
{
	this->f = dummy;
}

InputFunction::InputFunction(rawfunc f)
{
	this->f = f;
}

InputFunction::InputFunction(lambdafunc &lambda)
{
	this->f = lambda.target<bool()>();
}

bool InputFunction::operator()()
{
	return f();
}