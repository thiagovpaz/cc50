#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            float average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = (average);
            image[i][j].rgbtGreen = (average);
            image[i][j].rgbtBlue = (average);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        sumRed += image[ni][nj].rgbtRed;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            temp[i][j].rgbtRed = (int)round((float)sumRed / count);
            temp[i][j].rgbtGreen = (int)round((float)sumGreen / count);
            temp[i][j].rgbtBlue = (int)round((float)sumBlue / count);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

int computeGradientMagnitude(int gx, int gy) {
    return (int)round(sqrt(gx * gx + gy * gy));
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int kernelX[3][3] = {{-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1}};
    int kernelY[3][3] = {{-1, -2, -1},
                         {0, 0, 0},
                         {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sumRedX = 0, sumGreenX = 0, sumBlueX = 0;
            int sumRedY = 0, sumGreenY = 0, sumBlueY = 0;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        int pixelX = kernelX[di + 1][dj + 1];
                        int pixelY = kernelY[di + 1][dj + 1];

                        sumRedX += pixelX * image[ni][nj].rgbtRed;
                        sumGreenX += pixelX * image[ni][nj].rgbtGreen;
                        sumBlueX += pixelX * image[ni][nj].rgbtBlue;

                        sumRedY += pixelY * image[ni][nj].rgbtRed;
                        sumGreenY += pixelY * image[ni][nj].rgbtGreen;
                        sumBlueY += pixelY * image[ni][nj].rgbtBlue;

                    }
                }
            }

            int magnitudeRed = computeGradientMagnitude(sumRedX, sumRedY);
            int magnitudeGreen = computeGradientMagnitude(sumGreenX, sumGreenY);
            int magnitudeBlue = computeGradientMagnitude(sumBlueX, sumBlueY);

            magnitudeRed = fmin(255, fmax(0, magnitudeRed));
            magnitudeGreen = fmin(255, fmax(0, magnitudeGreen));
            magnitudeBlue = fmin(255, fmax(0, magnitudeBlue));

            temp[i][j].rgbtRed = magnitudeRed;
            temp[i][j].rgbtGreen = magnitudeGreen;
            temp[i][j].rgbtBlue = magnitudeBlue;


        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
