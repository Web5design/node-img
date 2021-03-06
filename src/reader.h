#ifndef NODE_IMG_SRC_READER_H
#define NODE_IMG_SRC_READER_H

#include <png.h>
#include <assert.h>

#include <string>
#include <queue>

class ImageReader {
public:
    inline unsigned long getWidth() { return width; }
    inline unsigned long getheight() { return height; }
    inline bool getAlpha() { return alpha; }
    virtual void decode(unsigned char* surface, bool alpha = true) = 0;
    ImageReader() : width(0), height(0), depth(0), color(-1), alpha(false),
                    source(NULL), length(0), pos(0) {}

    static ImageReader* create(const char* surface, size_t len);

    unsigned long width;
    unsigned long height;
    int depth;
    int color;
    bool alpha;
protected:
    const char* source;
    size_t length;
    size_t pos;
};

class PNGImageReader : public ImageReader {
public:
    PNGImageReader(const char* src, size_t len);
    ~PNGImageReader();
    void decode(unsigned char* surface, bool alpha);

protected:
    static void readCallback(png_structp png, png_bytep data, png_size_t length);
    static void writeCallback(png_structp png, png_bytep data, png_size_t length);

protected:
    png_structp png;
    png_infop info;
};

#endif
