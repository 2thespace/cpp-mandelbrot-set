

#include <iostream>
#include <mondelbort_set.hpp>
#include <vector>
// clang-format off

#include <jerror.h>
#include <jpeglib.h>
// clang-format on

#define cimg_display 0
#define cimg_plugin "plugins/jpeg_buffer.h"

#include <CImg.h>
#include <bmp_image.h>
#include <img_lib.h>
#include <jpeg_image.h>
#include <ppm_image.h>

img_lib::Image VectorToImage(std::vector<std::vector<unsigned char>> const& raster) {
    // Размеры изображения
    int width  = raster[0].size() / 3;
    int height = raster.size();
    img_lib::Image image(width, height, {});
    for (auto y = 0; y < height; ++y) {
        auto color = image.GetLine(y);
        for (auto x = 0; x < width; ++x) {
            auto& pixel = color[x];
            pixel.r     = (std::byte)raster[y][3 * x + 0];
            pixel.g     = (std::byte)raster[y][3 * x + 0];
            pixel.b     = (std::byte)raster[y][3 * x + 0];
            pixel.a     = (std::byte)255;
        }
    }

    return image;
}

enum Format {
    JPEG,
    PPM,
    BMP,
    UNKNOWN,
};

class ImageFormatInterface {
public:
    virtual bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const = 0;
    virtual img_lib::Image LoadImage(const img_lib::Path& file) const                    = 0;
};

namespace FormatInterfaces {

class PPM: public ImageFormatInterface {
public:
    bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const override {
        return img_lib::SavePPM(file, image);
    }

    img_lib::Image LoadImage(const img_lib::Path& file) const override { return img_lib::LoadPPM(file); }
};

class JPEG: public ImageFormatInterface {
public:
    bool SaveImage(const img_lib::Path& file, const img_lib::Image& image) const override {
        return img_lib::SaveJPEG(file, image);
    }

    img_lib::Image LoadImage(const img_lib::Path& file) const override { return img_lib::LoadJPEG(file); }
};
}  // namespace FormatInterfaces

int main(int argc, char** argv) {
    const double x_min      = -2;
    const double x_max      = 2;
    const double y_min      = -1.5;
    const double y_max      = 1.5;
    const int raster_width  = 2048;
    const int raster_height = 2048;
    std::cout << "H" << std::endl;
    std::vector<std::vector<unsigned char>> raster;
    raster.resize(raster_height);
    mondelbort::Calculater mondel;
    using namespace std::complex_literals;
    for (auto k = 0; k < raster_height; ++k) {
        double y = y_min + double(k) / raster_height * (y_max - y_min);
        raster[k].resize(3 * raster_width);
        for (auto j = 0; j < raster_width; ++j) {
            double x = x_min + double(j) / raster_width * (x_max - x_min);

            std::complex<double> point{x, y};
            unsigned char pixel  = mondel.IsSet(point).second;
            raster[k][3 * j]     = pixel;
            raster[k][3 * j + 1] = 0;
            raster[k][3 * j + 2] = 0;
        }
    }

    // Размеры изображения
    int width  = raster[0].size() / 3;
    int height = raster.size();

    // Преобразование в массив unsigned char
    std::vector<unsigned char> image_data(width * height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            image_data[y * width + x + 0] = raster[y][3 * x + 0];
        }
    }

    cimg_library::CImg<unsigned char> image(image_data.data(), width, height, 1, 1);
    // Преобразование в монохромное изображение
    // cimg_library::CImg<unsigned char> monochrome_image = image.get_RGBtoYCbCr().channel(0);
    // Сохранение изображения в формате JPEG
    image.save_png("output.png");
    auto image2 = VectorToImage(raster);
    FormatInterfaces::JPEG jpeg_image;

    jpeg_image.SaveImage("output.jpeg", image2);
    std::cout << "End of drawing" << std::endl;
    return 0;
}
