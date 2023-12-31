// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: CS213-2023–SectionNumber-20220099-20220352-20220389-A1-FULL.cpp
// Last Modification Date: 7/10/2023
// Author1 and ID and Email: Joseph Sameh   20220099  jojo.1922005@gmail.com
// Author2 and ID and Email: Miguel Reda    20220352  megooreda2005@gmail.com
// Author3 and ID and Email: Youssef Joseph 20220389  Youssefjoseph35@gmail.com
// Purpose: The program downloads a grayscale image,
//          performs some operations and stores it in another file

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image1[SIZE][SIZE]; // Define a 2D array for the first image
unsigned char image2[SIZE][SIZE]; // Define a 2D array for the second image
int EXIT = 1;                     // Initialize a variable for program exit control
//__________________________________________________________
void loadImage(unsigned char image[SIZE][SIZE]); // Function to load an image

void saveImage(unsigned char image[SIZE][SIZE]); // Function to save an image
//__________________________________________________________
// Filter functions for image processing
void Black_and_White_Filter();
void Invert_Filter();
void Merge_Filter();
void Flip_Filter();
void Rotate_Filter();
void Darken_and_Lighten_Filter();
void Detect_Image_Edges();
void Enlarge_Image();
void Shrink_Image();
void Mirror_Image();
void Shuffle_Image();
void Blur_Image();
void Crop_Image();
void Skew_Image_Right();
void Skew_Image_Up();
void Save_the_image_to_a_file();
void copy_image_to_image1(unsigned char image[SIZE][SIZE]);
void Exit();
//__________________________________________________________________________
void doSomethingForImage() // Function to handle user input and apply filters
{
  // Display menu options
  cout << "\nPlease select a filter to apply or 0 to exit: \n"
       << "1- Black & White Filter\n"
       << "2- Invert Filter \n"
       << "3- Merge Filter \n"
       << "4- Flip Image \n"
       << "5- Rotate Image\n"
       << "6- Darken and Lighten Image\n"
       << "7- Detect Image Edges\n"
       << "8- Enlarge Image\n"
       << "9- Shrink Image\n"
       << "a- Mirror 1/2 Image\n"
       << "b- Shuffle Image\n"
       << "c- Blur Image\n"
       << "d- Crop Image\n"
       << "e- Skew Image Right\n"
       << "f- Skew Image Up\n"
       << "s- Save the image to a file\n"
       << "0- Exit\n";

  char choose_op;
  cin >> choose_op; // Get user's choice

  switch (choose_op)
  {
    // Apply corresponding filter based on user's choice
  case '1':
    Black_and_White_Filter();
    break;
  case '2':
    Invert_Filter();
    break;
  case '3':
    Merge_Filter();
    break;
  case '4':
    Flip_Filter();
    break;
  case '5':
    Rotate_Filter();
    break;
  case '6':
    Darken_and_Lighten_Filter();
    break;
  case '7':
    Detect_Image_Edges();
    break;
  case '8':
    Enlarge_Image();
    break;
  case '9':
    Shrink_Image();
    break;
  case 'a':
  case 'A':
    Mirror_Image();
    break;
  case 'b':
  case 'B':
    Shuffle_Image();
    break;
  case 'c':
  case 'C':
    Blur_Image();
    break;
  case 'd':
  case 'D':
    Crop_Image();
    break;
  case 'e':
  case 'E':
    Skew_Image_Right();
    break;
  case 'f':
  case 'F':
    Skew_Image_Up();
    break;
  case 's':
  case 'S':
    Save_the_image_to_a_file();
    break;
  case '0':
    Exit();
    break;
  default:
    cout << "\nplease, select a valid operation"; // Prompt for valid choice
    doSomethingForImage();
    break;
  }
}

//_________________________________________________________________

int main()
{
  cout << "Please enter file name of the image to process: ";

  loadImage(image1);     // Load the initial image
  doSomethingForImage(); // Apply filter and display result

  while (EXIT)
  {
    cout << "Do you want to do another operation on the image? (y) (n)\n";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
      doSomethingForImage(); // Continue applying filters until user chooses to exit
    }
    else if (choice == 'n' || choice == 'N')
    {
      cout << "s- Save the image to a file\n"
           << "0- Exit\n"
           << "else- back\n";
      cin >> choice;
      switch (choice)
      {
      case 's':
      case 'S':
        Save_the_image_to_a_file();
        break;
      case '0':
        EXIT = 0;
        break;
      }
    }
    else
    {
      cout << "please, select a valid operation\n"; // Prompt for valid choice
    }
  }

  return 0;
}
// _____________________________________________________________________
// Function to load an image
void loadImage(unsigned char image[SIZE][SIZE])
{
  char imageFileName[100]; // Define a character array for image file name

  // Get gray scale image file name from user
  cin >> imageFileName;

  // Add .bmp extension to the file name and load image
  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, image);

  // Check if the file exists
  if (!(fopen(imageFileName, "rb")))
  {
    cout << "Please enter a valid file name of the image to process: ";
    loadImage(image); // Prompt user for a valid file name
  }
}
// _____________________________________________________________________
// Function to save an image
void saveImage(unsigned char image[SIZE][SIZE])
{
  char imageFileName[100]; // Define a character array for target image file name

  // Get target image file name from user
  cout << "Enter the target image file name: ";
  cin >> imageFileName;

  // Add .bmp extension to the file name and save image
  strcat(imageFileName, ".bmp");
  writeGSBMP(imageFileName, image);
}
// _____________________________________________________________________
// Function for Black & White Filter
void Black_and_White_Filter()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (image1[i][j] > 127)
        image1[i][j] = 255; // Convert pixel with value > 127 to white
      else
        image1[i][j] = 0; // Convert pixel with value <= 127 to black
    }
  }
}
// _____________________________________________________________________
// Function for Invert Filter
void Invert_Filter()
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // Invert color by subtracting current value from 255
      image1[i][j] = 255 - image1[i][j];
    }
  }
}
// _____________________________________________________________________
// Function for Merge Filter
void Merge_Filter()
{
  cout << "Enter the 2nd source image file name: ";
  loadImage(image2); // Load the second image

  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // Merge images by averaging pixel values
      image1[i][j] = (image1[i][j] + image2[i][j]) / 2;
    }
  }
}
// _____________________________________________________________________
// Function for Flip Filter
void Flip_Filter()
{
  cout << "Flip (h)orizontally or (v)ertically ?: ";
  char a;
  cin >> a;
  if (a == 'h' || a == 'H')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image2[i][j] = image1[i][255 - j]; // Flip horizontally
      }
    }
  }
  else if (a == 'v' || a == 'V')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image2[i][j] = image1[255 - i][j]; // Flip vertically
      }
    }
  }
  else
  {
    cout << "\nplease, select a valid operation (v) or (h)\n"; // Prompt for valid choice
    Flip_Filter();
  }
  copy_image_to_image1(image2); // Copy the result back to the original image // copy image2 to image1
}
// _____________________________________________________________________
// Function for Rotate Filter
void Rotate_Filter()
{
  cout << "Rotate (90), (180) or (270) degrees?: ";
  int b;
  cin >> b;
  b %= 360; // Ensure b is within 0-359 range
  if (b == 0)
  {
    // No rotation required
  }
  else if (b == 90)
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image2[j][255 - i] = image1[i][j]; // Rotate 90 degrees
      }
    }
    copy_image_to_image1(image2); // Copy the result back to the original image
  }
  else if (b == 180)
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image2[255 - i][255 - j] = image1[i][j]; // Rotate 180 degrees
      }
    }
    copy_image_to_image1(image2); // Copy the result back to the original image
  }
  else if (b == 270)
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image2[i][j] = image1[j][255 - i]; // Rotate 270 degrees
      }
    }
    copy_image_to_image1(image2); // Copy the result back to the original image // copy image2 to image1
  }
  else
  {
    cout << "\nPlease choose a number that is divisible by 90\n"; // Prompt for valid choice
    Rotate_Filter();
  }
}
// _____________________________________________________________________
// Function for Darken & Lighten Filter
void Darken_and_Lighten_Filter()
{
  cout << "Do you want to (d)arken or (l)ighten ?: \n";
  char c;
  cin >> c;
  if (c == 'd' || c == 'D')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image1[i][j] = image1[i][j] / 2; // Darken image by 50%
      }
    }
  }
  else if (c == 'l' || c == 'L')
  {
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image1[i][j] = (image1[i][j] + 255) / 2; // Lighten image by 50%
      }
    }
  }
  else
  {
    cout << "\nPlease choose a valid operation (d) or (l) \n"; // Prompt for valid choice
    Darken_and_Lighten_Filter();
  }
}
// _____________________________________________________________________
// Function to detect edges in the image
void Detect_Image_Edges()
{
  // for (int i = 0; i < SIZE; i++)
  // {
  //   for (int j = 0; j < SIZE; j++)
  //   {
  //     if (image1[i][j] > 127)
  //       image1[i][j] = 255;
  //     else
  //       image1[i][j] = 0;
  //   }
  // }

  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // Check if the difference between adjacent pixels is greater than 32
      if (abs(image1[i][j] - image1[i + 1][j]) > 32 || abs(image1[i][j] - image1[i][j + 1]) > 32)
      {
        image2[i][j] = 0; // Set edge pixels to black
      }
      else
      {
        image2[i][j] = 255; // Set non-edge pixels to white
      }
    }
  }

  // Delete single points
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (image2[i][j - 1] == 255 && image2[i][j + 1] == 255 && image2[i - 1][j] == 255 && image2[i + 1][j] == 255 && image2[i - 1][j - 1] == 255 && image2[i + 1][j + 1] == 255 && image2[i - 1][j + 1] == 255 && image2[i + 1][j - 1] == 255)
      {
        image2[i][j] = 255;
      }
    }
  }
  copy_image_to_image1(image2); // Copy the result back to the original image
}
// _____________________________________________________________________
// Function to enlarge a quarter of the image
void Enlarge_Image()
{
  cout << "Which quarter to enlarge 1, 2, 3 or 4?\n";
  int choose;
  cin >> choose;
  if (choose == 1)
  {
    // Extract the top-left quarter and enlarge it
    unsigned char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE / 2; i++)
    {
      for (int j = 0; j < SIZE / 2; j++)
      {
        temp[i][j] = image1[i][j];
      }
    }
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image1[i][j] = temp[i / 2][j / 2];
      }
    }
  }
  else if (choose == 2)
  {
    // Extract the top-right quarter and enlarge it
    unsigned char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE / 2; i++)
    {
      for (int j = SIZE / 2; j < SIZE; j++)
      {
        temp[i][j] = image1[i][j];
      }
    }
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image1[i][j] = temp[i / 2][(j + SIZE) / 2];
      }
    }
  }
  else if (choose == 3)
  {
    // Extract the down-left quarter and enlarge it
    unsigned char temp[SIZE][SIZE];
    for (int i = SIZE / 2; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE / 2; j++)
      {
        temp[i][j] = image1[i][j];
      }
    }
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image1[i][j] = temp[(i + SIZE) / 2][j / 2];
      }
    }
  }
  else if (choose == 4)
  {
    // Extract the down-right quarter and enlarge it
    unsigned char temp[SIZE][SIZE];
    for (int i = SIZE / 2; i < SIZE; i++)
    {
      for (int j = SIZE / 2; j < SIZE; j++)
      {
        temp[i][j] = image1[i][j];
      }
    }
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE; j++)
      {
        image1[i][j] = temp[(i + SIZE) / 2][(j + SIZE) / 2];
      }
    }
  }
  else
  {
    cout << "input a valid number 1, 2, 3 or 4\n";
    Enlarge_Image(); // Prompt for valid input
  }
}
// _____________________________________________________________________
// Function to shrink the image
void Shrink_Image()
{
  cout << "Shrink to (1/2), (1/3) or (1/4)?\n";
  string shrink;
  cin >> shrink;
  if (shrink == "1/2")
  {
    // Shrink the image by half
    for (int i = 0; i < SIZE / 2; i++)
    {
      for (int j = 0; j < SIZE / 2; j++)
      {
        image2[i][j] = image1[(2 * i)][(2 * j)];
      }
    }
  }
  else if (shrink == "1/3")
  {
    // Shrink the image by one-third
    for (int i = 0; i < SIZE / 3; i++)
    {
      for (int j = 0; j < SIZE / 3; j++)
      {
        image2[i][j] = image1[(3 * i)][(3 * j)];
      }
    }
  }
  else if (shrink == "1/4")
  {
    // Shrink the image by one-fourth
    for (int i = 0; i < SIZE / 4; i++)
    {
      for (int j = 0; j < SIZE / 4; j++)
      {
        image2[i][j] = image1[(4 * i)][(4 * j)];
      }
    }
  }
  else
  {
    cout << "input a valid value (1/2), (1/3) or (1/4)\n";
    Shrink_Image(); // Prompt for valid input
  }

  copy_image_to_image1(image2); // Copy the result back to the original image
}
// _____________________________________________________________________
// Function to mirror the image
void Mirror_Image()
{
  cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
  char mirror;
  cin >> mirror;
  if (mirror == 'l' || mirror == 'L')
  {
    // Mirror the image horizontally (left to right)
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = SIZE / 2; j < SIZE; j++)
      {
        image1[i][j] = image1[i][SIZE - j];
      }
    }
  }
  else if (mirror == 'r' || mirror == 'R')
  {
    // Mirror the image horizontally (right to left)
    for (int i = 0; i < SIZE; i++)
    {
      for (int j = 0; j < SIZE / 2; j++)
      {
        image1[i][j] = image1[i][SIZE - j];
      }
    }
  }
  else if (mirror == 'u' || mirror == 'U')
  {
    // Mirror the image vertically (upper to lower)
    for (int i = SIZE / 2; i < SIZE; ++i)
    {
      for (int j = 0; j < SIZE; ++j)
      {
        image1[i][j] = image1[SIZE - i][j];
      }
    }
  }
  else if (mirror == 'd' || mirror == 'D')
  {
    // Mirror the image vertically (lower to upper)
    for (int i = 0; i < SIZE / 2; ++i)
    {
      for (int j = 0; j < SIZE; ++j)
      {
        image1[i][j] = image1[SIZE - i][j];
      }
    }
  }
  else
  {
    cout << "input a valid character l, r, u or d \n";
    Mirror_Image(); // Prompt for valid input
  }
}
// _____________________________________________________________________
// Function to shuffle the quarters of the image
void Shuffle_Image()
{
  cout << "New order of quarters ?: ";
  int order[4];
  for (int i = 0; i < 4; ++i)
  {
    cin >> order[i];
    if (order[i] < 1 || order[i] > 4)
    {
      cout << "Invalid input Please enter numbers between 1 and 4.\n";
      cin.ignore();
      Shuffle_Image();
      return;
    }
  }
  if (order[0] == 1 && order[1] == 2 && order[2] == 3 && order[3] == 4)
  {
    return;
  }
  else
  {
    int curr = 1;
    for (auto u : order)
    {
      if (u == 1)
      {
        // Copy the top-left quarter to the top-left quarter in result image
        if (curr == 1)
        {
          for (int i = 0; i < 128; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i][j] = image1[i][j];
            }
          }
        }
        else if (curr == 2)
        {
          // Copy the top-right quarter to the top-left quarter in result image
          for (int i = 0; i < 128; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i][j + 128] = image1[i][j];
            }
          }
        }
        else if (curr == 3)
        {
          // Copy the down-left quarter to the top-left quarter in result image
          for (int i = 0; i < 128; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i + 128][j] = image1[i][j];
            }
          }
        }
        else if (curr == 4)
        {
          // Copy the down-right quarter to the top-left quarter in result image
          for (int i = 0; i < 128; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i + 128][j + 128] = image1[i][j];
            }
          }
        }
      }
      else if (u == 2)
      {
        if (curr == 1)
        {
          // Copy the top-left quarter to the top-right quarter in result image
          for (int i = 0; i < 128; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i][j - 128] = image1[i][j];
            }
          }
        }
        else if (curr == 2)
        {
          // Copy the top-right quarter to the top-right quarter in result image
          for (int i = 0; i < 128; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i][j] = image1[i][j];
            }
          }
        }
        else if (curr == 3)
        {
          // Copy the down-left quarter to the top-right quarter in result image
          for (int i = 0; i < 128; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i + 128][j - 128] = image1[i][j];
            }
          }
        }
        else if (curr == 4)
        {
          // Copy the down-right quarter to the top-right quarter in result image
          for (int i = 0; i < 128; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i + 128][j] = image1[i][j];
            }
          }
        }
      }
      else if (u == 3)
      {
        if (curr == 1)
        {
          // Copy the top-left quarter to the down-left quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i - 128][j] = image1[i][j];
            }
          }
        }
        else if (curr == 2)
        {
          // Copy the top-right quarter to the down-left quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i - 128][j + 128] = image1[i][j];
            }
          }
        }
        else if (curr == 3)
        {
          // Copy the down-left quarter to the down-left quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i][j] = image1[i][j];
            }
          }
        }
        else if (curr == 4)
        {
          // Copy the down-right quarter to the down-left quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 0; j < 128; j++)
            {
              image2[i][j + 128] = image1[i][j];
            }
          }
        }
      }
      else if (u == 4)
      {
        if (curr == 1)
        {
          // Copy the top-left quarter to the down-right quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i - 128][j - 128] = image1[i][j];
            }
          }
        }
        else if (curr == 2)
        {
          // Copy the top-right quarter to the down-right quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i - 128][j] = image1[i][j];
            }
          }
        }
        else if (curr == 3)
        {
          // Copy the down-left quarter to the down-right quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i][j - 128] = image1[i][j];
            }
          }
        }
        else if (curr == 4)
        {
          // Copy the down-right quarter to the down-right quarter in result image
          for (int i = 128; i < 256; i++)
          {
            for (int j = 128; j < 256; j++)
            {
              image2[i][j] = image1[i][j];
            }
          }
        }
      }
      curr++;
    }
  }
  copy_image_to_image1(image2); // Copy the result back to the original image
}
// _____________________________________________________________________
// Function to apply a blur filter to the image
void Blur_Image()
{
  // Apply a blur filter to the image using a weighted average of neighboring pixels
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image1[i][j] = (image1[i][j] + image1[i][j + 1] + image1[i][j - 1] + image1[i + 1][j] + image1[i - 1][j] + image1[i + 1][j + 1] + image1[i - 1][j - 1] + image1[i - 1][j + 1] + image1[i + 1][j - 1]) / 9;
    }
  }
  // Repeat the process again to get better
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image1[i][j] = (image1[i][j] + image1[i][j + 1] + image1[i][j - 1] + image1[i + 1][j] + image1[i - 1][j] + image1[i + 1][j + 1] + image1[i - 1][j - 1] + image1[i - 1][j + 1] + image1[i + 1][j - 1]) / 9;
    }
  }
}
// _____________________________________________________________________
// Function to crop a region of interest from the image
void Crop_Image()
{
  cout << "Please enter the starting point coordinates x and y and the end point coordinates l and w: ";
  int x, y, l, w;
  cin >> x >> y >> l >> w;
  // Copy the specified region to the result image
  for (int i = y; i < y + w; ++i)
  {
    for (int j = x; j < x + l; ++j)
    {
      image2[i][j] = image1[i][j];
    }
  }
  copy_image_to_image1(image2); // Copy the result back to the original image
}
// _____________________________________________________________________
// Function to skew the image to the right
void Skew_Image_Right()
{
  cout << "Please enter degree to skew right less than 89: ";
  double degree;
  cin >> degree;
  double mov = tan((degree * 22) / (180 * 7)) * 256;
  double step = mov / SIZE; // Number of steps
  unsigned char temp[SIZE][SIZE + (int)mov];

  // Initialize the temporary image with white pixels
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE + (int)mov; j++)
    {
      temp[i][j] = 255;
    }
  }

  // Shift the pixels to the right according to the degree of skew
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      temp[i][j + (int)mov] = image1[i][j];
    }
    mov -= step;
  }

  // Copy the result back to the original image
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image1[i][j] = temp[i][int((1 + step) * j)];
    }
  }
}
// _____________________________________________________________________
// Function to skew the image upwards
void Skew_Image_Up()
{
  cout << "Please enter degree to skew up less than 89: ";
  double degree;
  cin >> degree;
  double mov = tan((degree * 22) / (180 * 7)) * 256;
  double step = mov / SIZE; // Number of steps
  unsigned char temp[SIZE + (int)mov][SIZE];

  // Initialize the temporary image with white pixels
  for (int i = 0; i < SIZE + (int)mov; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      temp[i][j] = 255;
    }
  }

  // Shift the pixels upwards according to the degree of skew
  for (int j = 0; j < SIZE; j++)
  {
    for (int i = 0; i < SIZE; i++)
    {
      temp[i + (int)mov][j] = image1[i][j];
    }
    mov -= step;
  }

  // Copy the result back to the original image
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image1[i][j] = temp[int((1 + step) * i)][j];
    }
  }
}
// _____________________________________________________________________
// Function to save the image to a file
void Save_the_image_to_a_file()
{
  saveImage(image1); // Save the image
  EXIT = 0;          // Set EXIT flag to exit the program
}
// _____________________________________________________________________
// Function to copy one image to another
void copy_image_to_image1(unsigned char image[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image1[i][j] = image[i][j];
    }
  }
}
// _____________________________________________________________________
// Function to exit
void Exit()
{
  cout << "Do you want to save the image before exiting? (y) or (n) \n";
  char ch;
  cin >> ch;
  if (ch == 'Y' || ch == 'y')
  {
    saveImage(image1);
    EXIT = 0; // Set EXIT flag to exit the program
  }
  else if (ch == 'N' || ch == 'n')
  {
    EXIT = 0; // Set EXIT flag to exit the program
  }
  else
  {
    cout << "input a valid character (y) or (n) \n";
    Exit();
  }
}
