#pragma once

#include <memory>

class	IController;

using	IControllerSPtr = std::shared_ptr<IController>;
using	IControllerWPtr = std::weak_ptr<IController>;