// FCAI – OOP Programming – 2023 - Assignment 1
// Last Modification Date:	19/10/2023
// Author1 :	Osama Moheb Shafik.
// Author2 :	Yousef Tarek Bahr.
// Purpose: Demonstrate use of bmplip for handling bmp colored and grayscale images
// Program load a gray image and store in another file

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <algorithm>
#include <string>
#include<bits/stdc++.h>


using namespace std;
// number of filters
const int num_filters = 15;
unsigned char image[SIZE][SIZE];
unsigned char img_gs2[SIZE][SIZE];
string menu_items[num_filters] = {"Black & White", "Invert", "Merge",
                                 "Flip","Darken & lighten","Rotate Image","Detect Image Edges",
                                "Enlarge Image", "Shrink Image","Mirror half image",
                                "Shuffle Image", "Blur Image",
                                "Crop Image", "Skew Image Right", "Skew Image Up"};

void loadImage (string word, unsigned char the_image[SIZE][SIZE]);
void saveImage ();
int menu();
void mirrorImage();
void flipImage();
void rotateImage();
void dark_lightenImage();
void edge_detectionImage();
void bw_filter();
void invert_filter();
void merge_filter();
void cropImage();
void blur_image();
void enlargeImage();
void shrinkImage();
void shuffleImage();
void skewImage(string variation);

int main()
{
  loadImage("source image file name", image);
  bool CONTINUE = true;
  // get specified filter
  while(CONTINUE)
  {
  int filter = menu();
  switch (filter) {
  case 0:
      CONTINUE = false;
    case 1:
        bw_filter();
        break;
    case 2:
        invert_filter();
        break;
    case 3:
        merge_filter();
        break;
    case 4:
        flipImage();
        break;
    case 5:
        dark_lightenImage();
        break;
    case 6:
        rotateImage();
        break;
    case 7:
        edge_detectionImage();
        break;
    case 8:
        enlargeImage();
        break;
    case 9:
        shrinkImage();
        break;
    case 10:
        mirrorImage();
        break;
    case 11:
        shuffleImage();
        break;
    case 12:
        blur_image();
        break;
    case 13:
        cropImage();
        break;
    case 14:
        skewImage("right");
        break;
    case 15:
        skewImage("up");
        break;
    case 16:
          saveImage();
          CONTINUE = false;
          break;
    }
  }
  return 0;
}

//_________________________________________
void loadImage (string word, unsigned char the_image[SIZE][SIZE]) {
   char imageFileName[100];
   // Get gray scale image file name
   // Continue in loop until entered a valid image file name
   while(true) {
       cout << "Enter a valid "<< word <<": ";
       cin >> imageFileName;

       // Add to it .bmp extension and load image
       strcat(imageFileName, ".bmp");
       if (!readGSBMP(imageFileName, the_image))
           break;

   }

}


//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}


//_________________________________________
int menu()
{
    // Get specified filter number
    int answer;
    cout << "Please insert a number representing a filter to apply or 0 to exit:" << endl;
    for(int i = 0; i < num_filters; i++)
        cout << i + 1 << "- " << menu_items[i] << endl;
    cout << "16- Save the image" << endl << "0- Exit" << endl << "Ans: ";
    cin >> answer;
    return answer;

}
//_________________________________________

void mirrorImage(){
    char variation;
    cout << "Mirror (l)eft, (r)ight, (u)pper, or (d)own?" << endl;
    cin >> variation;
    if (variation == 'l')
    {
        for(int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 1; j >= SIZE/2 ; j--) {
                image[i][j] = image[i][SIZE - 1 - j];
            }
        }
    }
    else if(variation == 'u')
    {
        for (int i = SIZE - 1; i >= SIZE/2; i--) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[SIZE - 1 - i][j];

            }
        }
    }
    else if (variation == 'd')
    {
        for (int i = SIZE - 1; i >= SIZE/2; i--) {
            for (int j = 0; j < SIZE; j++) {
                image[SIZE - 1 - i][j] = image[i][j];

            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 1; j >= SIZE/2; j--) {
                image[i][SIZE - 1 - j] = image[i][j];

            }
        }
    }
}
//_________________________________________

void flipImage(){
    char variation;
    cout << "FLip (h)orizontally or (v)ertically" << endl;
    cin >> variation;
    //Take a copy
    unsigned char image_copy[SIZE][SIZE];
    copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);
    if(variation == 'v')
    {
        for (int i = SIZE - 1; i >= 0; i--) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image_copy[SIZE - 1 - i][j];

            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 1; j >= 0; j--) {
                image[i][j] = image_copy[i][SIZE - 1 - j];

            }
        }
    }
}
//_________________________________________

void rotateImage(){
    int deg;
    cout << "Rotate (90), (180) , (270), or (360) degrees?" << endl;
    cin >> deg;
    unsigned char image_copy[SIZE][SIZE];
    copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);
    // keep rotating image until deg is less than 0
    while(deg > 0)
    {
        for (int i = 0 ; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image_copy[j][SIZE - 1 -i];

            }
        }
        copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);
        deg -= 90;
    }
}
//_________________________________________

void dark_lightenImage(){
    // add a number to every pixel's intensity to darken or lighten an image
    char variation;
    cout << "Do you want to (d)arken or (l)ighten?" << endl;
    cin >>variation;
    int num;
    if( variation == 'd')
    {
        for (int i = 0 ; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                num = round( image[i][j] / 4);
                // pixel's intensity must be between 0 and 255
                if (num < 0)
                    num = 0;

                image[i][j] = num;
            }
        }
    }
    else
    {
        for (int i = 0 ; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                num = round( image[i][j] + 70);
                // pixel's intensity must be between 0 and 255
                if (num > 255)
                    num = 255;

                image[i][j] = num;
            }
        }
    }
}
//_________________________________________

void edge_detectionImage()
{
    // detect if surrounding pixels of a pixel are of different intensity, if that turn the pixel into black
    // else turn it to white
    unsigned char image_copy[SIZE][SIZE];
    copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);
    for (int i = 0 ; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if((i == 0 && j == 0) || (i == SIZE - 1 && j == SIZE - 1) || (i == SIZE - 1 && j == 0) || (j == SIZE - 1 && i == 0) )
                continue;

            if(abs(image_copy[i][j] - image_copy[i + 1][j]) >= 40
               ||abs(image_copy[i][j] - image_copy[i][j + 1]) >= 40
               ||abs(image_copy[i][j] - image_copy[i - 1][j]) >= 40
               ||abs(image_copy[i][j] - image_copy[i][j - 1]) >= 40)
                image[i][j] = 0;
            else
                image[i][j] = 255;
        }
    }
}
//_________________________________________

void bw_filter()
{
    // if pixel's intensity greater than 127 turn it into white(255)
    // else turn it to white(0)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j]>127) image[i][j]=255;
            else image[i][j]=0;
        }
    }
}
//_________________________________________

void invert_filter()
{
    // invert each pixel's intensity by subtracting from 255(white color)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=255-image[i][j];
        }
    }
}
//_________________________________________

void merge_filter()
{
    // change each pixel's intensity of the original image into the average of the original and second image
    loadImage("image file to be merged with", img_gs2);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j]=(image[i][j]+img_gs2[i][j])/2;
        }
    }
}

void cropImage()
{
    int x, y, l, w;
    cout << "Please enter x, y, l, and w: ";
    cin >> x >> y >> l >> w;
    // turn all pixels to white
    // except the pixels inside the specified rectangle with corners of (x,y) and  (x + w, y) and (x,y) and (x, y + l)
    for(int i =0; i < SIZE; i++)
    {
        for(int j =0; j < SIZE; j++)
        {
            if( (x<= i && i <= x + w) && (y <= j && j <= y + l) )
                continue;
            else
                image[i][j] = 255;
        }
    }

}

void blur_image(){
    unsigned char image_copy[SIZE][SIZE];
    copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // The more pixels you take in average the higher blur you get
            image[i][j]=(image_copy[i][j]+image_copy[i+1][j]+image_copy[i][j+1]+image_copy[i+1][j+1]+image_copy[i-1][j]+image_copy[i][j-1]+image_copy[i-1][j-1]+image_copy[i-1][j+1]+image_copy[i+1][j-1])/9;

        }
    }
}

void enlargeImage()
{
    int num;
    unsigned char image_copy[SIZE][SIZE];
    copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);
    cout << "Which quarter to enlarge 1 , 2, 3, 4?";
    cin >> num;
    switch (num) {
        case 1:
            {
                // x and y are the same as i and j but in the new image
                //in the new image each pixel from original is in 4 pixels
                // so x and y increment by 2
                for(int i = 0, x = 0; i < SIZE / 2; i++, x+=2)
                {
                    for(int j = 0, y = 0; j < SIZE / 2; j++, y+=2)
                    { // every first 4 pixels from enlarged image are the same as one pixel from original image
                        image[x][y] = image_copy[i][j];
                        image[x][y + 1] = image_copy[i][j];
                        image[x + 1][y] = image_copy[i][j];
                        image[x + 1][y + 1] = image_copy[i][j];
                    }
                }
            }
            break;
        case 2:
            for(int i = 0, x = 0; i < SIZE / 2; i++, x+=2)
            {
                for(int j = SIZE / 2, y = 0; j < SIZE; j++, y+=2)
                {
                    image[x][y] = image_copy[i][j];
                    image[x][y + 1] = image_copy[i][j];
                    image[x + 1][y] = image_copy[i][j];
                    image[x + 1][y + 1] = image_copy[i][j];
                }
            }
            break;
        case 3:
            for(int i = SIZE / 2, x = 0; i < SIZE; i++, x+=2)
            {
                for(int j = 0 , y = 0; j < SIZE / 2; j++, y+=2)
                {
                    image[x][y] = image_copy[i][j];
                    image[x][y + 1] = image_copy[i][j];
                    image[x + 1][y] = image_copy[i][j];
                    image[x + 1][y + 1] = image_copy[i][j];
                }
            }
            break;
        case 4:
            for(int i = SIZE / 2, x = 0; i < SIZE; i++, x+=2)
            {
                for(int j = SIZE / 2, y = 0; j < SIZE; j++, y+=2)
                {
                    image[x][y] = image_copy[i][j];
                    image[x][y + 1] = image_copy[i][j];
                    image[x + 1][y] = image_copy[i][j];
                    image[x + 1][y + 1] = image_copy[i][j];
                }
            }
            break;
    }
}


void shrinkImage() {
    string num;
    unsigned char image_copy[SIZE][SIZE];
    copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);
    // Clear image (make it all white)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }
    cout << "shrink to (1/2), (1/3), or (1/4)?";
    cin >> num;
    if (num == "1/2") {   // the opposite of 'enlargeimage' function
        // every 4 pixels from original image are averaged into one pixel in new image
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) {
            for (int j = 0, y = 0; j < SIZE; j += 2, y++) {
                image[x][y] = (image_copy[i][j] + image_copy[i][j + 1] + image_copy[i + 1][j] + image_copy[i + 1][j + 1]) / 4;
            }
        }
    }
    if (num == "1/4")
    { // the only difference is the value to increment i and j
        for (int i = 0, x = 0; i < SIZE; i += 4, x++)
        {
            for (int j = 0, y = 0; j < SIZE; j += 4, y++)
            {
                image[x][y] = (image_copy[i][j] + image_copy[i][j + 1] + image_copy[i + 1][j] + image_copy[i + 1][j + 1]) / 4;
            }

        }
    }
    else if(num == "1/3")
    { // the only difference is the value to increment i and j
        for (int i = 0, x = 0; i < SIZE; i += 3, x++)
        {
            for (int j = 0, y = 0; j < SIZE; j += 3, y++)
            {
                image[x][y] = (image_copy[i][j] + image_copy[i][j + 1] + image_copy[i + 1][j] + image_copy[i + 1][j + 1]) / 4;
            }

        }
    }
}

void shuffleImage()
{
    int order1, order2, order3, order4;
    unsigned char q1[SIZE / 2][SIZE / 2], q2[SIZE / 2][SIZE / 2],
    q3[SIZE / 2][SIZE / 2], q4[SIZE / 2][SIZE / 2];
    // reject wrong integer inputs
    while(true)
    {
        cout << "New order of quarters: " << endl;
        cin >> order1 >> order2 >> order3 >> order4;
        if( (1<= order1 && order1 <= 4) &&
            (1<= order2 && order2 <= 4) &&
            (1<= order3 && order3 <= 4) &&
            (1<= order4 && order4 <= 4) &&
            order1 + order2 + order3 + order4 == 10)
            break;
    }

    // fill up q1, q2, q3, q4
    // every quarter (q1, q2, q3, q4) is filled from 0 to 127 2D matrix
    for (int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++)
        {
            if( (0<=i &&i < SIZE / 2) && (0 <=j && j < SIZE / 2)) // quarter 1
                q1[i][j] = image[i][j];

            else if( (0<=i &&i < SIZE / 2) && ( SIZE / 2 <= j && j < SIZE)) // quarter 2
                q2[i][j - (SIZE / 2)] = image[i][j];

            else if( (SIZE / 2 <= i && i < SIZE) && (0 <= j && j < SIZE / 2))// quarter 3
                q3[i - (SIZE / 2)][j] = image[i][j];

            else if((SIZE / 2 <= i && i < SIZE) && (SIZE / 2 <= j && j < SIZE)) // quarter 4
                q4[i - (SIZE / 2)][j - (SIZE / 2)] = image[i][j];
        }
    }
    // shuffle the new image
    for (int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++)
        {
            if( (0<=i &&i < SIZE / 2) && (0 <=j && j < SIZE / 2)) // first quarter
            {
                if (order1 == 4)
                    image[i][j] = q4[i][j];
                else if (order1 == 3)
                    image[i][j] = q3[i][j];
                else if (order1 == 2)
                    image[i][j] = q2[i][j];
                else if (order1 == 1)
                    image[i][j] = q1[i][j];
            }
            else if( (0<=i &&i < SIZE / 2) && ( SIZE / 2 <= j && j < SIZE)) // second quarter
            {
                if (order2 == 4)
                    image[i][j] = q4[i][j - (SIZE / 2)];
                else if (order2 == 3)
                    image[i][j] = q3[i][j - (SIZE / 2)];
                else if (order2 == 2)
                    image[i][j] = q2[i][j - (SIZE / 2)];
                else if (order2 == 1)
                    image[i][j] = q1[i][j - (SIZE / 2)];
            }

            else if( ( SIZE / 2 <= i && i < SIZE ) && (0 <= j && j < SIZE / 2))// third quarter
            {
                if (order3 == 4)
                    image[i][j] = q4[i - (SIZE / 2)][j];
                else if (order3 == 3)
                    image[i][j] = q3[i - (SIZE / 2)][j];
                else if (order3 == 2)
                    image[i][j] = q2[i - (SIZE / 2)][j];
                else if (order3 == 1)
                    image[i][j] = q1[i - (SIZE / 2)][j];
            }
            else  // fourth quarter
            {
                if (order4 == 4)
                    image[i][j] = q4[i -(SIZE / 2)][j - (SIZE / 2)];
                else if (order4 == 3)
                    image[i][j] = q3[i -(SIZE / 2)][j - (SIZE / 2)];
                else if(order4 == 2)
                    image[i][j] = q2[i -(SIZE / 2)][j - (SIZE / 2)];
                else if (order4 == 1)
                    image[i][j] = q1[i -(SIZE / 2)][j - (SIZE / 2)];
            }

        }

    }

}

void skewImage(string variation)
{
    int deg;
    unsigned char image_copy[SIZE][SIZE];
    copy(&image[0][0], &image[0][0] + SIZE * SIZE, &image_copy[0][0]);

    // clear image
    for (int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }

    if(variation == "right")
    {
        cout << "Please enter degree to skew image right: ";
        cin >> deg;

        // number of pixels turning white from the left
        double steps_left = SIZE * tan(deg * (M_PI / 180));
        // number of pixels turning white from the right
        double steps_right = SIZE;

        int z;
        double scale_factor = 1 / (1 - tan(deg * (M_PI / 180)  ) );
        // shrink the image
        for(int i =0; i < SIZE; i++)
        {
            for(int j = 0, y = 0; j < SIZE; j+=scale_factor,  y++)
            {
                z = round(y + steps_left);
                if(z < steps_right)
                    image[i][z] = (image_copy[i][j] + image_copy[i][j + 1])  / 2;

            }
            steps_left -= tan(deg * (M_PI / 180));
            steps_right -= tan(deg * (M_PI / 180));

        }
    }
    else
    {
        cout << "Please enter degree to skew image up: ";
        cin >> deg;

        int z;
        double scale_factor = 1 / (1 - tan(deg * (M_PI / 180)  ) );

        double steps_up = SIZE * tan(deg * (M_PI / 180));
        double steps_down = SIZE;
        // shrink the image
        for(int i =0; i < SIZE; i++)
        {
            for(int j = 0, y = 0; j < SIZE; j+=scale_factor,  y++)
            {
                z = round(y + steps_up);
                if(z < steps_down)
                    image[z][i] = (image_copy[j][i] + image_copy[j][i + 1])  / 2;

            }
            steps_up -= tan(deg * (M_PI / 180));
            steps_down -= tan(deg * (M_PI / 180));

        }
    }
}




