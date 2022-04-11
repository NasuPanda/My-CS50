## 画像の全データを列挙

`image`は`RGBTRIPLE`(3バイト分のデータを持つ構造体)の2次元配列。
行数が画像の高さを、列数が画像の幅を、各列の値=各ピクセルの値。

```c
for (int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j++)
    {
        printf("%x", image[i][j].rgbtBlue);
        printf("%x", image[i][j].rgbtGreen);
        printf("%x ", image[i][j].rgbtRed);
    }
printf("\n");
}
```

## グレースケール

ピクセルの持つBGR値の平均を取り、濃淡を決定する。

```c
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Average of pixel BGR values
    int pixel_ave = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Take the BGR value (image[h][w]), determine gray scale shading.
            pixel_ave = (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3;
            image[h][w].rgbtBlue = pixel_ave;
            image[h][w].rgbtGreen = pixel_ave;
            image[h][w].rgbtRed = pixel_ave;
        }
    }
}

```

## `malloc`/`calloc`

![malloc/calloc](https://monozukuri-c.com/wp-content/uploads/2020/07/971757feb04a398f09eb5cfe7331fc42.png)