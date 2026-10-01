// 练习5，实现图像处理算法 resize：缩小或放大图像
void resize(float *in, float *out, int h, int w, int c, float scale) {
    /**
     * 图像处理知识：
     *  1.单线性插值法
     *      假设有两个已知 点1(x1, y1) 和 点2(x2, y2)，
     *      点1 的值为v1，点2 的值为v2，
     *      待插值点 (x, y)处于 点1 和 点2 中间，值为 v，
     *      如下图所示(*表示点，/表示三个点在一条直线上)：
     *
     *                                * (x2, y2), v2
     *                               /
     *                              /
     *                             * (x, y), v
     *                            /
     *                           * (x1, y1), v1
     *
     *      则满足下面的条件：
     *                    x2 - x          x - x1
     *          v = v1 * ———————— + v2 * ————————
     *                   x2 - x1         x2 - x1
     *      也就是说，v的值是 点1 和 点2 的值的加权平均值，权重与到两点的距离相关
     *      (公式中的 x也可以是 y，因为是在一条直线上)。
     *
     *  2.双线性插值法
     *     2.1 由于图片是二维的，每个像素点有两个方向可以用来插值，所以可以使用双线性插值法。
     *     假设有四个已知 P1(x1, y2), P2(x2, y2), P3(x1, y1), P4(x2, y1)，
     *      如下图（看起来是在一条直线上就是在一条直线上）
     *
     *          P1(x1, y2)                      P2(x2, y2)
     *              *                               *
     *
     *                              * P(x, y)
     *
     *              *                               *
     *          P3(x1, y1)                      P4(x2, y1)
     *
     *      2.2 核心思想：
     *          双线性差值相当于三次差值，如下图所示：
     *
     *              P1(x1, y2)      Q1(x, y2)       P2(x2, y2)
     *                  *               *               *
     *
     *                                  * P(x, y)
     *
     *                  *               *               *
     *              P3(x1, y1)      Q2(x, y1)       P4(x2, y1)
     *
     *          先用单线性插值法计算出 Q1 和 Q2 的值，再用单线性插值法计算出 P 的值，即
     *                     x2 - x          x - x1
     *          Q1 = P1 * ———————— + P2 * ————————
     *                     x2 - x1         x2 - x1
     *
     *                     x2 - x          x - x1
     *          Q2 = P3 * ———————— + P4 * ————————
     *                     x2 - x1         x2 - x1
     *
     *                    y2 - y          y - y1
     *          Q = Q1 * ———————— + Q2 * ————————
     *                    y2 - y1         y2 - y1
     *
     *      2.3 化简：
     *          记 Dx = x2 - x1, Dy = y2 - y1, dx = x - x1, dy = y - y1，
     *
     *                     (Dx - dx)(Dy - dy)         dx(Dy - dy)
     *          Q = P1 * ———————————————————— + P2 * ————————————— +
     *                          Dx * Dy                 Dx * Dy
     *
     *                    (Dx - dx)dy           dxdy
     *              P3 * ————————————— + P4 * —————————
     *                      Dx * Dy            Dx * Dy
     *
     *  3. 双线性插值用于 resize 图片
     *      记 原图为 src，目标图为 dst，
     *         比例 dst宽高 = src宽高 * scale，
     *      设一个点 resize 后的坐标为 (x, y)，resize 前的坐标为 (x', y')，
     *      则有 x' = x / scale, y' = y / scale，
     *
     *      现在，对于每个目标图片中的像素点 (x, y)：
     *          1. 找到对应的源图片中的像素点 (x', y')
     *          2. 找到其在原图中的四个邻居点 (这四个邻居是相邻的四个点，组成一个正方形)
     *          3. 用双线性插值法计算出 该像素点 的值
     *
     *      不难发现，在这种情况下：Dx = Dy = 1（原图中相邻的四个像素横竖距离是1）
     *      所以，上面的公式可以化简为：
     *          Q = P1 * (1 - dx)(1 - dy) + P2 * dx(1 - dy)
     *            + P3 * (1 - dx)dy + P4 * dxdy
     * HINT:
     *     1. 对于每个 dst 中的像素点 (x, y)，先计算出其在 src 中的坐标 float(x0, y0)，
     *     2. 然后计算出其在 src 中的四个邻居点:
     *        x1 = static_cast<int>(x0), y1 = static_cast<int>(y0)
     *        上面这样可以直接将 float 通过下取整的方式转换为 int，
     *        剩下三个邻居就好找了
     *     3. 注意上面的方法中，四个邻居点的坐标可能会超出 src 的范围，
     *        所以需要对其进行边界检查
     */

    int new_h = h * scale, new_w = w * scale;
    // IMPLEMENT YOUR CODE HERE

    // 遍历目标图像的每个像素 (x, y)
    for (int y = 0; y < new_h; y++) {
        for (int x = 0; x < new_w; x++) {
            // 1. 计算对应源图像的坐标
            float x0 = (float)x / scale;
            float y0 = (float)y / scale;

            // 2. 计算四个邻居点的坐标
            int x1 = (int)x0;       // floor(x0)
            int y1 = (int)y0;       // floor(y0)
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            // 小数部分作为插值权重
            float dx = x0 - x1;
            float dy = y0 - y1;

            // 3. 边界检查：防止邻居坐标超出源图像范围
            if (x1 < 0) x1 = 0;
            if (x2 >= w) x2 = w - 1;
            if (y1 < 0) y1 = 0;
            if (y2 >= h) y2 = h - 1;

            // 4. 对每个通道分别进行双线性插值
            for (int ch = 0; ch < c; ch++) {
                // 获取四个邻居像素的值
                // P1 = (x1, y2) 左上角, P2 = (x2, y2) 右上角
                // P3 = (x1, y1) 左下角, P4 = (x2, y1) 右下角
                float P1 = in[(y2 * w + x1) * c + ch];
                float P2 = in[(y2 * w + x2) * c + ch];
                float P3 = in[(y1 * w + x1) * c + ch];
                float P4 = in[(y1 * w + x2) * c + ch];

                // 双线性插值公式
                float Q = P1 * (1 - dx) * (1 - dy)
                        + P2 * dx * (1 - dy)
                        + P3 * (1 - dx) * dy
                        + P4 * dx * dy;

                // 写入目标图像
                out[(y * new_w + x) * c + ch] = Q;
            }
        }
    }
}
