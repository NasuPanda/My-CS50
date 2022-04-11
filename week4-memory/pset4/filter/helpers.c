#include "helpers.h"

#include <stdio.h>
#include <cs50.h>
#include <math.h>

typedef struct
{
    float red;
    float green;
    float blue;
}
WEIGHTED_SUM;

// カーネル
int GX_KERNEL[][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
int GY_KERNEL[][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

// prototype
float get_rgbt_ave(int h, int w, RGBTRIPLE *image, int width);
void calculate_gx(WEIGHTED_SUM *sobel, RGBTRIPLE *image, int kernel_h, int kernel_w);
void calculate_gy(WEIGHTED_SUM *sobek, RGBTRIPLE *image, int kernel_h, int kernel_w);
void reset_weighted_sum(WEIGHTED_SUM *sum);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Average of pixel BGR values
    float pixel_ave = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Take the BGR value (image[h][w]), determine gray scale shading.
            pixel_ave = get_rgbt_ave(h, w, &image[0][0], width);
            pixel_ave = round(pixel_ave);

            image[h][w].rgbtBlue = pixel_ave;
            image[h][w].rgbtGreen = pixel_ave;
            image[h][w].rgbtRed = pixel_ave;
        }
    }
}

// Reflect image horizontal_posly
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    int center = width / 2; // 小数点以下は切り捨てられるため奇数の場合でも問題ない

    // バッファに一時格納、反対側と値をスワップする
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < center; w++)
        {
            buffer = image[h][w];
            image[h][w] = image[h][width - w];
            image[h][width - w] = buffer;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 画像の複製
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // 縦、横の移動方向
    int vertical_pos;
    int horizontal_pos;
    // 合計値の格納
    float blue;
    float green;
    float red;
    // カウント用(平均の算出に使う)
    int count;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w <= width; w++)
        {
            blue = 0.0;
            green = 0.0;
            red = 0.0;
            count = 0;

            // 周辺ピクセルの平均を取る
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    vertical_pos = h + i;
                    horizontal_pos = w + j;

                    // 縦方向がオーバーする時
                    if (vertical_pos < 0 || vertical_pos > height)
                    {
                        continue;
                    }
                    // 横方向がオーバーする時
                    else if (horizontal_pos < 0 || horizontal_pos > width)
                    {
                        continue;
                    }
                    blue += temp[vertical_pos][horizontal_pos].rgbtBlue;
                    green += temp[vertical_pos][horizontal_pos].rgbtGreen;
                    red += temp[vertical_pos][horizontal_pos].rgbtRed;
                    count++;
                }
            }
            image[h][w].rgbtBlue = round(blue/count);
            image[h][w].rgbtGreen = round(green/count);
            image[h][w].rgbtRed = round(red/count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // 画像の複製
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // 縦、横の移動方向
    int vertical_pos;
    int horizontal_pos;
    // 加重合計
    WEIGHTED_SUM gx;
    WEIGHTED_SUM gy;
    // 計算結果
    int result_red;
    int result_green;
    int result_blue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            reset_weighted_sum(&gx);
            reset_weighted_sum(&gy);
            result_red = result_green = result_blue = 0;

            // 周辺ピクセルの平均を取る
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    vertical_pos = h + i;
                    horizontal_pos = w + j;
                    // 縦方向がオーバーする時
                    if (vertical_pos < 0 || vertical_pos > height)
                    {
                        continue;
                    }
                    // 横方向がオーバーする時
                    else if (horizontal_pos < 0 || horizontal_pos > width)
                    {
                        continue;
                    }
                    calculate_gx(&gx, &temp[vertical_pos][horizontal_pos], i+1, j+1);
                    calculate_gy(&gy, &temp[vertical_pos][horizontal_pos], i+1, j+1);
                }
            }

            result_red = round(sqrt(pow(gx.red, 2.0) + pow(gy.red, 2.0)));
            result_green = round(sqrt(pow(gx.green, 2.0) + pow(gy.green, 2.0)));
            result_blue = round(sqrt(pow(gx.blue, 2.0) + pow(gy.blue, 2.0)));

            if (result_blue > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = result_blue;
            }

            if (result_green > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = result_green;
            }

            if (result_red > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = result_red;
            }
        }
    }
}

// - - - - - - - - - -
// 自分で実装
// - - - - - - - - - -

// 指定した位置(ピクセル)のRGB値平均を取得。
float get_rgbt_ave(int h, int w, RGBTRIPLE *image, int width)
{
    // h*width で↓方向、 wで→方向の移動。
    int red = image[h * width + w].rgbtRed;
    int green = image[h * width + w].rgbtGreen;
    int blue = image[h * width + w].rgbtBlue;

    return (red + green + blue) / 3.0;
}
// gx, gyのリセット
void reset_weighted_sum(WEIGHTED_SUM *sum)
{
    sum->blue = 0.0;
    sum->green = 0.0;
    sum->red = 0.0;
}
// gx, gyの計算
// -> : ポインタ経由で構造体のメンバにアクセス出来る
void calculate_gx(WEIGHTED_SUM *gx, RGBTRIPLE *image, int kernel_h, int kernel_w)
{
    gx->blue += image->rgbtBlue * GX_KERNEL[kernel_h][kernel_w];
    gx->green += image->rgbtGreen * GX_KERNEL[kernel_h][kernel_w];
    gx->red += image->rgbtRed * GX_KERNEL[kernel_h][kernel_w];
}
void calculate_gy(WEIGHTED_SUM *gy, RGBTRIPLE *image, int kernel_h, int kernel_w)
{
    gy->blue += image->rgbtBlue * GY_KERNEL[kernel_h][kernel_w];
    gy->green += image->rgbtGreen * GY_KERNEL[kernel_h][kernel_w];
    gy->red += image->rgbtRed * GY_KERNEL[kernel_h][kernel_w];
}