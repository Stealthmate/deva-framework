#include "InputFunction.hpp"

using namespace DevaEngine;

bool dummy() { return false; }

InputFunction::InputFunction()
{
	this->vk = dummy;
}

InputFunction::InputFunction(rawfunc vk)
{
	this->vk = vk;
}

InputFunction::InputFunction(lambdafunc &lambda)
{
	this->vk = lambda.target<bool()>();
}

bool InputFunction::operator()()
{
	return vk();
}