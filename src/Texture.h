#pragma once
#include "dataStructure.h"

namespace SkeletonViewerApplication
{
	class Texture
	{
	public:
		void upload(const unsigned char* image_data, const int cols, const int rows);
		void show(const rect& r, float alpha = 1.f) const;


	};
}

