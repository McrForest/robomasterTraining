#include <iostream>
#include <cstring>
#include "include/utils.h"
#include "include/tests.h"
using namespace std;

// all below this line are from utils.cpp

#define STB_IMAGE_IMPLEMENTATION
#include "3rd/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "3rd/stb/stb_image_write.h"


float* fmalloc(int n) {
    return (float*)malloc(sizeof(float) * n);
}


void imread(const char *path, float **out_data, int *out_h, int *out_w, int *out_c) {
    // load image, memory order is HWC (RGB)
    // see stb_image.h: 170
    int h, w, c;
    unsigned char *buffer = stbi_load(path, &w, &h, &c, 0);

    // [修复1] 检查 stbi_load 是否成功加载图片
    if (buffer == NULL) {
        fprintf(stderr, "Error: 无法加载图片 %s\n", path);
        *out_data = NULL;
        *out_h = 0;
        *out_w = 0;
        *out_c = 0;
        return;
    }

    float *data = fmalloc(h * w * c);
    for (int i = 0; i < h * w * c; ++i)
        data[i] = (float)buffer[i];
    free(buffer);

    *out_data = data, *out_h = h, *out_w = w, *out_c = c;
}


void imwrite(const char *path, float *data, int h, int w, int c) {
    int n = h * w * c;
    unsigned char *buffer = (unsigned char*)malloc(n);
    
    for (int i = 0; i < n; i++) {
        if (data[i] < 0.f)
            buffer[i] = 0;
        else if (data[i] > 255.f)
            buffer[i] = 255;
        else
            buffer[i] = (unsigned char)data[i];
    }

    // [修复2] 灰度图(comp=1)先转为RGB三通道再写入JPEG，提高兼容性
    if (c == 1) {
        int rgb_n = h * w * 3;
        unsigned char *rgb_buffer = (unsigned char*)malloc(rgb_n);
        for (int i = 0, j = 0; i < rgb_n; i += 3, j++) {
            rgb_buffer[i]     = buffer[j];  // R
            rgb_buffer[i + 1] = buffer[j];  // G
            rgb_buffer[i + 2] = buffer[j];  // B
        }
        stbi_write_jpg(path, w, h, 3, rgb_buffer, 0);
        free(rgb_buffer);
    } else {
        stbi_write_jpg(path, w, h, c, buffer, 0);
    }
    free(buffer);
}

// all above this line are from utils.cpp 






void rgb2gray(float *in, float *out, int h, int w) {
    /**
     * 编写这个函数，将一张彩色图片转化为灰度图片。以下是各个参数的含义：
     * (1) float *in:  指向彩色图片对应的内存区域（或者说数组）首地址的指针。
     * (2) float *out: 指向灰度图片对应的内存区域（或者说数组）首地址的指针。
     * (3) int h:      height，即图片的高度。
     * (4) int w:      width，即图片的宽度。
     *
     * 提示：
     * (1) in数组只管读取就行了，别修改它的值。out数组只修改不读取。
     * (2) 利用公式 V = 0.1140 * B  + 0.5870 * G + 0.2989 * R 计算彩色图片每个
     *     像素对应的灰度值，写到灰度图片相同的位置中就行。
     * (3) 使用for循环来遍历每个位置。利用图片在内存中的存储顺序，计算出每个位置像素
     *     的地址。
     *
     * 考点：
     * (1) for循环的使用。
     * (2) 内存的访问。
     */

    // IMPLEMENT YOUR CODE HERE
    // ...

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // 彩色图片在内存中按 R G B R G B ... 存储
            // 像素 (i, j) 的 R 分量在索引 (i * w + j) * 3 处
            int idx = (i * w + j) * 3;
            float R = in[idx];
            float G = in[idx + 1];
            float B = in[idx + 2];
            // 利用公式 V = 0.1140 * B + 0.5870 * G + 0.2989 * R 计算灰度值
            float V = 0.1140 * B + 0.5870 * G + 0.2989 * R;
            // 写入灰度图片，灰度图每个像素只占一个位置
            out[i * w + j] = V;
        }
    }
}

void test_rgb2gray() {
    std::cout << "开始测试函数 << rgb2gray >> ..." << std::endl;
    const char *path = "./images/rgb2gray/input.jpg";
    float *img;
    int h, w, c;

    imread(path, &img, &h, &w, &c);

    // [修复3] 检查图片是否加载成功
    if (img == NULL) {
        std::cout << "错误：图片加载失败，请检查文件路径是否正确" << std::endl;
        return;
    }

    std::cout << "读取图片images/rgb2gray/input.jpg，高度为" << h << "，宽度为" << w
              << "，通道数为" << c
              << std::endl;

    float *gray = fmalloc(h * w);
    rgb2gray(img, gray, h, w);

    const char *out_path = "./images/rgb2gray/output.jpg";
    imwrite(out_path, gray, h, w, 1);
    std::cout << "使用你的代码产生的灰度图片已经保存为images/rgb2gray/output.jpg"
              << std::endl
              << "可以与images/rgb2gray/answer.jpg进行比较，看结果是否正确"
              << std::endl;

    free(gray), free(img);
    std::cout << std::endl << std::endl;
}

int main() {
    std::cout << "开始测试函数 << rgb2gray >> ..." << std::endl;
    test_rgb2gray();
}
