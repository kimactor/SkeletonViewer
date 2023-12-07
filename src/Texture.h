#pragma once
#include "dataStructure.h"
#include <opencv2/opencv.hpp>

namespace SkeletonViewerApplication
{
	class Texture
	{
	public:
		void upload(const unsigned char* image_data, const int cols, const int rows);
		void show(const rect& r, float alpha = 1.f) const;
		void render(const cv::Mat& frame, const rect& rect, float alpha = 1.f);
		GLuint get_gl_handle() { return _gl_handle; }

	private:
		GLuint _gl_handle = 0;
		int _stream_index{};


	};
}

