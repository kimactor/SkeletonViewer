#pragma once
#include "dataStructure.h"
#include <vector>
#include <map>
namespace SkeletonViewerApplication
{
	class PointCloud
	{
	public:
		
		void render(const std::vector<std::vector<float3>>& vec_vec_pts, const std::vector<float3>& color, const std::string& type, glfw_state& app_state, const rect& rect);

	private:
		void draw_floor();
		void draw_axes();
		void draw_pts(const std::vector<float3>& vec_pt_3d);
		void draw_pts(const float3& pt_3d, const float3& color);
		void draw_lines(const float3& start_pt, const float3& end_pt, const float3& color);
		void set_viewport(const rect& rect);

		const std::vector<std::vector<int>> BODY_25_KPT_IDS =
		{ {0, 1}, {0, 15}, {15, 17}, {0, 16}, {16, 18}, {1, 2}, {1, 5}, {2, 3}, {3, 4}, {5, 6}, {6, 7}, {1, 8}, {8, 9}, {9, 10}, {10, 11},
					  {8, 12}, {12, 13}, {13, 14} };

		const std::vector<std::vector<int>> BODY_33_KPT_IDS =
		{
			{0, 1}, {0, 4}, {1, 2}, {2, 3}, {3, 7}, {4, 5}, {5, 6}, {6, 8}, {1, 2}, {9, 10},
			{11, 12}, {11, 13}, {11, 23}, {12, 14}, {12, 24}, {13, 15}, {14, 16}, {15, 17}, {15, 19}, {15, 21},
			{16, 18}, {16, 20}, {16, 22}, {17, 19}, {18, 20}, {23, 24}, {23, 25}, {24, 26}, {25, 27}, {26, 28},
			{27, 29}, {27, 31}, {28, 30}, {28, 32}, {29, 31}, {30, 32} };

		const std::vector<std::vector<int>> HAND_21_KPT_IDS =
		{
			{0, 1}, {1, 2}, {2, 3}, {3, 4},
			{0, 5}, {5, 6}, {6, 7}, {7, 8},
			{5, 9}, {9, 10}, {10, 11}, {11, 12},
			{9, 13}, {13, 14}, {14, 15}, {15, 16},
			{0, 17}, {13, 17}, {17, 18}, {18, 19}, {19, 20},
		};

		GLuint _gl_handle = 0;
		std::map < std::string, std::vector<std::vector<int>>> map_drawType = { 
			{"Body_25", BODY_25_KPT_IDS}, {"Body_33", BODY_33_KPT_IDS}, {"Hand", HAND_21_KPT_IDS}};
	};
}

