#pragma once
#include <vector>

namespace Engine{

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer);

	};

}