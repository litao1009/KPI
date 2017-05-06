#pragma once

#include <memory>

class	ExtensionUtil
{
	class	Imp;
	std::unique_ptr<Imp>	ImpUPtr_;

public:

	static ExtensionUtil&	GetInstance();

public:

	ExtensionUtil();

	~ExtensionUtil();

public:

	void	Init();

	void	UnInit();
};