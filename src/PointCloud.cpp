#include "PointCloud.h"

namespace SkeletonViewerApplication
{
    void PointCloud::set_viewport(const rect& r)
    {
        glViewport((int)r.x, (int)r.y, (int)r.w, (int)r.h);
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glOrtho(0, r.w, r.h, 0, -1, +1);
    }

    void PointCloud::draw_floor()
    {
        glBegin(GL_LINES);
        glColor4f(0.4f, 0.4f, 0.4f, 1.f);
        // Render "floor" grid
        for (int i = 0; i <= 8; i++)
        {
            glVertex3i(i - 4, 0, -4);
            glVertex3i(i - 4, 0, 4);
            glVertex3i(-4, 0, i - 4);
            glVertex3i(4, 0, i - 4);
        }
        glEnd();
    }

    void PointCloud::draw_axes()
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        // Draw x, y, z axes
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);  glVertex3f(-1, 0, 0);
        glColor3f(0, 1, 0); glVertex3f(0, 0, 0);  glVertex3f(0, -1, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0, 0);  glVertex3f(0, 0, 1);
        glEnd();
        glLineWidth(1);
    }

    void PointCloud::draw_pts(const std::vector<float3>& vec_pt_3d)
    {
        glPointSize(3);
        glBegin(GL_POINTS);
        for (int id = 0; id < vec_pt_3d.size(); ++id)
        {
            glColor3f(0, 0.5, 0.5);
            glVertex3f(vec_pt_3d[id].x, vec_pt_3d[id].y, vec_pt_3d[id].z);
        }
        glEnd();
        glPointSize(1);
    }
    void PointCloud::draw_pts(const float3& pt_3d, const float3& color)
    {
        glPointSize(2);
        glBegin(GL_POINTS);
        glColor3f(color.x, color.y,color.z);
        glVertex3f(pt_3d.x, pt_3d.y, pt_3d.z);    
        glEnd();
        glPointSize(1);
    }

    void PointCloud::draw_lines(const float3& start_pt, const float3& end_pt, const float3& color)
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        // Draw x, y, z axes
        glColor3f(color.x, color.y, color.z);
        glVertex3f(start_pt.x, start_pt.y, start_pt.z);
        glVertex3f(end_pt.x, end_pt.y, end_pt.z);
        glEnd();
        glLineWidth(1);
    }

	void PointCloud::render(const std::vector<std::vector<float3>>& vec_vec_pts, const std::vector<float3>& color, const std::string& type,  glfw_state& app_state, const rect& rect)
	{
        set_viewport(rect);

        //render_scene(app_state);
        // OpenGL commands that prep screen for the pointcloud
        glLoadIdentity();
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        glClearColor(153.f / 255, 153.f / 255, 153.f / 255, 1);
        glClear(GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        gluPerspective(60, rect.w / rect.h, 0.01f, 10.0f);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        gluLookAt(0, 0, 0, 0, 0, 1, 0, -1, 0);

        glTranslatef(0, 0, +0.5f + app_state.offset_y * 0.05f);
        glRotated(app_state.pitch, 1, 0, 0);
        glRotated(app_state.yaw, 0, 1, 0);
        glTranslatef(0, 0, -0.5f);

        draw_axes();
        draw_floor();

        if (!_gl_handle)
            glGenTextures(1, &_gl_handle);
        GLenum err = glGetError();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _gl_handle);
        float tex_border_color[] = { 0.8f, 0.8f, 0.8f, 0.8f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, tex_border_color);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F); // GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F); // GL_CLAMP_TO_EDGE

        /* this segment actually prints the pointcloud */
        for (int person_id = 0; person_id < vec_vec_pts.size(); person_id++)
        {
            for (int id = 0; id < map_drawType[type].size(); ++id)
            {
                std::vector<int> cur_id_pair = map_drawType[type][id];
                float3 start_pt = vec_vec_pts[person_id][cur_id_pair[0]];
                float3 end_pt = vec_vec_pts[person_id][cur_id_pair[1]];
                draw_lines(start_pt, end_pt, color[person_id]);
            }

            draw_pts(vec_vec_pts[person_id]);

        }
        // OpenGL cleanup
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glPopAttrib();
	}
}
