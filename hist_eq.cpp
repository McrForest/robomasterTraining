#include "tests.h"

// 练习6，实现图像处理算法：直方图均衡化
void hist_eq(float *in, int h, int w) {
    /**
     * 将输入图片进行直方图均衡化处理。参数含义：
     * (1) float *in: 输入的灰度图片。
     * (2) int h:     height，即图片的高度。
     * (3) int w:      width，即图片的宽度。
     *
     * 参考资料：
     * https://blog.csdn.net/qq_15971883/article/details/88699218
     * 其它的博客也行。
     *
     * 提示：
     * (1) 输入图片是灰度图，每个像素值是[0, 255]内的小数
     * (2) 灰度级个数为256，也就是{0, 1, 2, 3, ..., 255}
     * (3) 使用数组来实现灰度级 => 灰度级的映射
     */

    // IMPLEMENT YOUR CODE HERE
    int N = h * w;
    if (N == 0) return;

    // 1. 统计直方图：计算每个灰度级出现的次数
    int hist[256] = {0};
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // 像素值为float，四舍五入取整得到灰度级索引
            int level = (int)(in[i * w + j] + 0.5);
            if (level < 0) level = 0;
            if (level > 255) level = 255;
            hist[level]++;
        }
    }

    // 2. 计算累积分布函数(CDF)
    int cdf[256] = {0};
    cdf[0] = hist[0];
    for (int k = 1; k < 256; k++) {
        cdf[k] = cdf[k - 1] + hist[k];
    }

    // 3. 构建灰度级 => 灰度级的映射表
    int mapping[256];
    for (int k = 0; k < 256; k++) {
        // 标准直方图均衡化公式：s_k = round( cdf[k] / N * (L-1) )
        // 其中 L = 256，所以 L-1 = 255
        mapping[k] = (int)(cdf[k] / (float)N * 255 + 0.5);
        if (mapping[k] < 0) mapping[k] = 0;
        if (mapping[k] > 255) mapping[k] = 255;
    }

    // 4. 应用映射：遍历每个像素，用映射表替换原值（原地修改）
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int level = (int)(in[i * w + j] + 0.5);
            if (level < 0) level = 0;
            if (level > 255) level = 255;
            in[i * w + j] = (float)mapping[level];
        }
    }
}
