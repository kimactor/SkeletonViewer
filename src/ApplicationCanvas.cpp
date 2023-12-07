#include "ApplicationCanvas.h"

namespace SkeletonViewerApplication
{
    ApplicationCanvas::ApplicationCanvas(int width, int height, const char* title)
    : _width(width), _height(height), _canvas_left_top_x(0), _canvas_left_top_y(0), _canvas_width(width), _canvas_height(height)
    {
        glfwInit();
        win = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!win)
            throw std::runtime_error("Could not open OpenGL window, please check your graphic drivers or use the textual SDK tools");
        glfwMakeContextCurrent(win);

        glfwSetWindowUserPointer(win, this);
        glfwSetMouseButtonCallback(win, [](GLFWwindow* w, int button, int action, int mods)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                if (button == 0) s->on_left_mouse(action == GLFW_PRESS);
            });

        glfwSetScrollCallback(win, [](GLFWwindow* w, double xoffset, double yoffset)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                s->on_mouse_scroll(xoffset, yoffset);
            });

        glfwSetCursorPosCallback(win, [](GLFWwindow* w, double x, double y)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                s->on_mouse_move(x, y);
            });

        glfwSetKeyCallback(win, [](GLFWwindow* w, int key, int scancode, int action, int mods)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                if (0 == action) // on key release
                {
                    s->on_key_release(key);
                }
            });

        register_OPRS_glfw_callbacks();
    }

    //another c'tor for adjusting specific frames in specific tiles, this window is NOT resizeable
    ApplicationCanvas::ApplicationCanvas(unsigned width, unsigned height, const char* title, unsigned tiles_in_row, unsigned tiles_in_col, float canvas_width,
        float canvas_height, float canvas_left_top_x, float canvas_left_top_y)
        : _width(width), _height(height), _tiles_in_row(tiles_in_row), _tiles_in_col(tiles_in_col)

    {
        //user input verification for mosaic size, if invalid values were given - set to default
        if (canvas_width < 0 || canvas_width > 1 || canvas_height < 0 || canvas_height > 1 ||
            canvas_left_top_x < 0 || canvas_left_top_x > 1 || canvas_left_top_y < 0 || canvas_left_top_y > 1)
        {
            std::cout << "Invalid window's size parameter entered, setting to default values" << std::endl;
            canvas_width = 0.8f;
            canvas_height = 0.6f;
            canvas_left_top_x = 0.15f;
            canvas_left_top_y = 0.075f;
        }

        //user input verification for number of tiles in row and column
        if (_tiles_in_row <= 0) {
            _tiles_in_row = 4;
        }
        if (_tiles_in_col <= 0) {
            _tiles_in_col = 2;
        }

        //calculate canvas size
        _canvas_width = int(_width * canvas_width);
        _canvas_height = int(_height * canvas_height);
        _canvas_left_top_x = _width * canvas_left_top_x;
        _canvas_left_top_y = _height * canvas_left_top_y;

        //calculate tile size
        _tile_width_pixels = float(std::floor(_canvas_width / _tiles_in_row));
        _tile_height_pixels = float(std::floor(_canvas_height / _tiles_in_col));

        glfwInit();
        // we don't want to enable resizing the window
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        win = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!win)
            throw std::runtime_error("Could not open OpenGL window, please check your graphic drivers or use the textual SDK tools");
        glfwMakeContextCurrent(win);

        glfwSetWindowUserPointer(win, this);
        glfwSetMouseButtonCallback(win, [](GLFWwindow* w, int button, int action, int mods)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                if (button == 0) s->on_left_mouse(action == GLFW_PRESS);
            });

        glfwSetScrollCallback(win, [](GLFWwindow* w, double xoffset, double yoffset)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                s->on_mouse_scroll(xoffset, yoffset);
            });

        glfwSetCursorPosCallback(win, [](GLFWwindow* w, double x, double y)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                s->on_mouse_move(x, y);
            });

        glfwSetKeyCallback(win, [](GLFWwindow* w, int key, int scancode, int action, int mods)
            {
                auto s = (ApplicationCanvas*)glfwGetWindowUserPointer(w);
                if (0 == action) // on key release
                {
                    s->on_key_release(key);
                }
            });

        register_OPRS_glfw_callbacks();
    }

    ApplicationCanvas::~ApplicationCanvas()
    {
        glfwDestroyWindow(win);
        glfwTerminate();
    }

    void ApplicationCanvas::close()
    {
        glfwSetWindowShouldClose(win, 1);
    }

    ApplicationCanvas::operator bool()
    {
        glPopMatrix();
        glfwSwapBuffers(win);

        auto res = !glfwWindowShouldClose(win);

        glfwPollEvents();
        glfwGetFramebufferSize(win, &_width, &_height);

        // Clear the framebuffer
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, _width, _height);

        // Draw the images
        glPushMatrix();
        glfwGetWindowSize(win, &_width, &_height);
        glOrtho(0, _width, _height, 0, -1, +1);

        return res;
    }


    void ApplicationCanvas::register_OPRS_glfw_callbacks()
    {
        on_left_mouse = [&](bool pressed)
        {
            app_state.ml = pressed;
        };

        on_mouse_scroll = [&](double xoffset, double yoffset)
        {
            app_state.offset_x -= static_cast<float>(xoffset);
            app_state.offset_y -= static_cast<float>(yoffset);
        };

        on_mouse_move = [&](double x, double y)
        {
            if (app_state.ml)
            {
                app_state.yaw -= (x - app_state.last_x);
                app_state.yaw = (std::max)(app_state.yaw, -120.0);
                app_state.yaw = (std::min)(app_state.yaw, +120.0);
                app_state.pitch += (y - app_state.last_y);
                app_state.pitch = (std::max)(app_state.pitch, -80.0);
                app_state.pitch = (std::min)(app_state.pitch, +80.0);
            }
            app_state.last_x = x;
            app_state.last_y = y;
        };

        on_key_release = [&](int key)
        {
            if (key == 32) // Escape
            {
                app_state.yaw = app_state.pitch = 0; app_state.offset_x = app_state.offset_y = 0.0;
            }
        };
    }

    void ApplicationCanvas::show(const cv::Mat& frame, const int id, const rect& rect)
    {
        render_frame_mat(frame, 0, rect);
    }

    void ApplicationCanvas::show(const std::vector<std::vector<float3>>& vec_vec_pts, const std::vector<float3>& vec_color, const int id, const rect& rect, const std::string& type )
    {
        render_point_cloud(vec_vec_pts, vec_color, type, id, rect);
    }

    void ApplicationCanvas::render_frame_mat(const cv::Mat& frame, const int id, const rect& r)
    {
        auto& t = _textures[id];
        t.render(frame, r);
    }

    void ApplicationCanvas::render_point_cloud(const std::vector<std::vector<float3>>& vec_vec_pts, const std::vector<float3>& vec_color, const std::string& type, const int id, const rect& rect)
    {
        auto& t = _ptds[id];
        t.render(vec_vec_pts, vec_color, type, app_state, rect);
    }

}   
