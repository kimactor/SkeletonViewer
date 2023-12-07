#include "Texture.h"

namespace SkeletonViewerApplication
{

    void Texture::upload(const unsigned char* image_data, const int cols, const int rows)
    {
        if (!_gl_handle)
            glGenTextures(1, &_gl_handle);
        GLenum err = glGetError();

        glBindTexture(GL_TEXTURE_2D, _gl_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cols, rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::show(const rect& r, float alpha) const
    {
        if (!_gl_handle)
            return;

        //set_viewport(r);

        glBindTexture(GL_TEXTURE_2D, _gl_handle);
        glColor4f(1.0f, 1.0f, 1.0f, alpha);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(0, 1); glVertex2f(0, r.h);
        glTexCoord2f(1, 1); glVertex2f(r.w, r.h);
        glTexCoord2f(1, 0); glVertex2f(r.w, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        //draw_text(int(0.05f * r.w), int(0.05f * r.h), "color");
    }

    void Texture::render(const cv::Mat& frame, const rect& rect, float alpha)
    {
        if (!frame.empty())
            return;
        upload(frame.data, frame.cols, frame.rows);
        show(rect.adjust_ratio({ (float)frame.cols, (float)frame.rows }), alpha);
    }
}