#pragma once
#include <iostream>
#include <functional>
#include <map>
#include "Texture.h"
#include "PointCloud.h"

namespace SkeletonViewerApplication
{
	class ApplicationCanvas
	{
	public:
        std::function<void(bool)>           on_left_mouse = [](bool) {};
        std::function<void(double, double)> on_mouse_scroll = [](double, double) {};
        std::function<void(double, double)> on_mouse_move = [](double, double) {};
        std::function<void(int)>            on_key_release = [](int) {};
        // Struct to get keys pressed on window
        struct window_key_listener {
            int last_key = GLFW_KEY_UNKNOWN;

            window_key_listener(ApplicationCanvas& win) {
                win.on_key_release = std::bind(&window_key_listener::on_key_release, this, std::placeholders::_1);
            }

            void on_key_release(int key) {
                last_key = key;
            }

            int get_key() {
                int key = last_key;
                last_key = GLFW_KEY_UNKNOWN;
                return key;
            }
        };
        ApplicationCanvas(int width, int height, const char* title);
        ApplicationCanvas(unsigned width, unsigned height, const char* title, unsigned tiles_in_row, unsigned tiles_in_col, float canvas_width = 0.8f,
            float canvas_height = 0.6f, float canvas_left_top_x = 0.1f, float canvas_left_top_y = 0.075f);
        ~ApplicationCanvas();
        void close();
        explicit operator bool();
        float width() const { return float(_width); }
        float height() const { return float(_height); }
        void register_OPRS_glfw_callbacks();
        void show(const cv::Mat& frame, const int id, const rect& rect);
        void show(const std::vector<std::vector<float3>>& vec_vec_pts, const std::vector<float3>& vec_color, const int id, const rect& rect, const std::string& type = "Body_25");

    private:
        void render_frame_mat(const cv::Mat& frame, const int id, const rect& r);
        void render_point_cloud(const std::vector<std::vector<float3>>& vec_vec_pts, const std::vector<float3>& vec_color, const std::string& type, const int id, const rect& rect);

        GLFWwindow* win;
        std::map<int, Texture> _textures;
        std::map<int, PointCloud> _ptds;
        glfw_state app_state;
        //text_renderer _main_win;
        int _width, _height;
        float _canvas_left_top_x, _canvas_left_top_y;
        int _canvas_width, _canvas_height;
        unsigned _tiles_in_row, _tiles_in_col;
        float _tile_width_pixels, _tile_height_pixels;
	};

}

