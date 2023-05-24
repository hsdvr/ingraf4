#include <iostream>
#include "texture.h"
#include "Include/stb_image.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    // m_pImage = NULL;
}




bool Texture::Load()
{
    //#ifdef USE_IMAGE_MAGIC
    //    try {
    //       // m_pImage = new Magick::Image;
    //        m_pImage.read(m_fileName);
    //       // m_pImage = new Magick::Image(m_fileName);
    //        m_pImage.write(&m_blob, "RGBA");
    //    }
    //    catch (Magick::Error& Error) {
    //        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
    //        return false;
    //    }
    //
    //#else
    stbi_set_flip_vertically_on_load(1);
    int width = 0, height = 0, bpp = 0;
    unsigned char* image_data = stbi_load(m_fileName.c_str(), &width, &height, &bpp, 0);

    if (!image_data) {
        printf("Can't load texture from '%s' - '%s\n'", m_fileName.c_str(), stbi_failure_reason());
        exit(0);
    }
    printf("Width %d, height %d, bpp %d\n", width, height, bpp);

    //#endif
    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);
    if (m_textureTarget == GL_TEXTURE_2D) {
        glTexImage2D(m_textureTarget, 0, GL_RGB, width, height, -0.5, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    }
    else {
        printf("Support for texture target %x is not implemented\n", m_textureTarget);
        exit(1);
    }

    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //  glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
 //   glBindTexture(m_textureTarget, 0);

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}