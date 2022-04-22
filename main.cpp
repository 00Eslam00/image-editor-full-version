// FCI – Programming 1 – 2022 - Assignment 3
// Program Name:    main.cpp
// Last Modification Date: 20/04/2022
// Author1 and ID and Group: Saead Mohamed Mohamed 20210159 S15
// Author2 and ID and Group: Eslam Amin Mostafa 20210064 S15
// Author3 and ID and Group: Karim Mohamed Shebl 20210300 S15
// Teaching Assistant:  Nesma Mohamed & Yousra Ayman
// Purpose: 12 filters to make edits on bmp images

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE]; //necessary for merge

void loadImage()
{
	//char imageFileName[100];
	char imageFileName[100];
	// Get gray scale image file name
	cout << "Enter the source image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");

	// check if file exist or not
	ifstream image_exist;
	image_exist.open(imageFileName);
	if (image_exist)
	{
		readGSBMP(imageFileName, image);
	}
	else
	{
		cout << "\n invalid name \n";
		cout << " try again: \n ";
		loadImage();
	}
}

//necessary for merge
void loadSecondImage()
{
	char imageFileName[100];

	// Get gray scale image file name
	cout << "Enter the second image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");

	// check if file exist or not
	ifstream image_exist;
	image_exist.open(imageFileName);
	if (image_exist)
	{
		readGSBMP(imageFileName, image2);
	}
	else
	{
		cout << "\n invalid name \n";
		cout << " try again: \n ";
        loadSecondImage();
	}
}

void saveImage()
{
	char imageFileName[100];

	// Get gray scale image target file name
	cout << "Enter the target image file name: ";
	cin >> imageFileName;

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	writeGSBMP(imageFileName, image);
}

void ConvertBlackAndWhite()
{
	long avg = 0;

	// get the average pixels of the image
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			avg += image[i][j];
		}
	}

	avg /= (SIZE * SIZE);

	// convert to black and white
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (image[i][j] > avg)
			{
				image[i][j] = 255;
			}
			else
			{
				image[i][j] = 0;
			}
		}
	}
}

//invert the image color
void invert()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//invert every pixal in photo
			image[i][j] = SIZE - image[i][j];
		}
	}
}

void flipImageHorizontally()
{
	// flip horizontally
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			int tempSave = image[i][j];
			image[i][j] = image[i][SIZE - 1 - j];
			image[i][SIZE - 1 - j] = tempSave;
		}
	}
}

void flipImageVertically()
{
	//flip vertically
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int tempSave = image[i][j];
			image[i][j] = image[SIZE - 1 - i][j];
			image[SIZE - 1 - i][j] = tempSave;
		}
	}
}

void mirrorDown()
{
	//mirror the down side
	for (int i = 0; i < SIZE/2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = image[255 - i][j];
		}
	}
}

void mirrorUp()
{
	// mirror the upper side
	for (int i = 0; i < SIZE/2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[255 - i][j] = image[i][j];
		}
	}
}

void mirrorLeft()
{
	// mirror the left side
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE/2; j++)
		{
			image[i][255 - j] = image[i][j];
		}
	}
}

void mirrorRight()
{
	//mirror the right side
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE/2; j++)
		{
			image[i][j] = image[i][255 - j];
		}
	}
}

void detectImageEdges()
{
    int arr1[SIZE][SIZE],arr2[SIZE][SIZE];
	//convert black and white
	ConvertBlackAndWhite();

	// detect the edges
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (image[i][j] == image[i][j + 1])
			{
				arr1[i][j] = 255;
			}
			else
			{
				arr1[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (image[i][j] == image[i+1][j])
			{
				arr2[i][j] = 255;
			}
			else
			{
				arr2[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
		 image[i][j]=arr1[i][j] & arr2[i][j];
        }
	}
}

void mergeTwoPictures()
{
	// Load the second image to merge
	loadSecondImage();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = (image[i][j] + image2[i][j]) / 2;
		}
	}
}

void enlarge()
{
	int choice, x, y, z;
	cout << "Enter section you wanna take : ";
	cin >> choice;

	// if else statements to decide which part of photo will be taken

	if (choice == 1)
		x = 0, y = 0, z = 0;

	else if (choice == 2)
		x = 0, y = 128, z = 0;

	else if (choice == 3)
		x = 128, y = 0, z = 128;

	else if (choice == 4)
		x = 128, y = 128, z = 128;

	// array to carry pixels of one part in this photo
	int carry[SIZE][SIZE] = {{0}, {0}};

	// for loop to put one skip the other pixel in this array
	for (int i = 0; i < SIZE; i += 2)
	{
		x = z;
		for (int j = 0; j < SIZE; j += 2)
		{
			carry[i][j] = image[x][y];
			x++;
		}
		y++;
	}

	//this for loop to fill the empty pixels with the average of surrounded pixels around it
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (j == 0 && carry[i][j] == 0)
				carry[i][j] = ceil((carry[i - 1][j] + carry[i + 1][j] + carry[i][j + 1]) / 3.0);

			else if (j == 255 && carry[i][j] == 0)
				carry[i][j] = ceil((carry[i - 1][j] + carry[i + 1][j] + carry[i][j - 1]) / 3.0);

			else if (i == 0 && carry[i][j] == 0)
				carry[i][j] = ceil((carry[i][j - 1] + carry[i + 1][j] + carry[i][j + 1]) / 3.0);

			else if (i == 255 && carry[i][j] == 0)
				carry[i][j] = ceil((carry[i - 1][j] + carry[i][j - 1] + carry[i][j + 1]) / 3.0);

			else if (carry[i][j] == 0)
				carry[i][j] = ceil((carry[i - 1][j] + carry[i + 1][j] + carry[i][j + 1] + carry[i][j - 1]) / 4.0);
		}
	}

	// to fill the main array with pixels of sub array "carry"
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = carry[i][j];
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			swap(image[i][j], image[j][i]);
		}
	}
	cin.ignore();
}

void darken_Lighten()
{
	string s;
	cout << " To darken an image press (d) \n To lighten an image press (l) \n";
	cin >> s;
	if (s == "d")
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] *= 0.5;
			}
		}
	}
	else if (s == "l")
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (image[i][j] < 170)
				{
					image[i][j] *= 1.5;
				}
				else
				{
					image[i][j] = 255;
				}
			}
		}
	}
}

//rotate image as user want
void rotate()
{
	int all = ceil(SIZE / 2.0), ch;
	cout << "choose \n [ 1 ] rotate 90 \n [ 2 ] rotate 180 \n [ 3 ] rotate 270 \n choice : ";
	cin >> ch;
	if (ch == 1)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(image[i][j], image[j][i]);
			}
		}

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < all; j++)
			{
				swap(image[i][j], image[i][SIZE - j]);
			}
		}
	}

	else if (ch == 2)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < all; j++)
			{
				swap(image[j][i], image[SIZE - j][i]);
			}
		}

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < all; j++)
			{
				swap(image[i][j], image[i][SIZE - j]);
			}
		}
	}

	else if (ch == 2)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < all; j++)
			{
				swap(image[i][j], image[i][SIZE - j]);
			}
		}

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(image[i][j], image[j][i]);
			}
		}
	}
	cin.ignore();
}

void shrinkImage()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image2[i][j] = image[i][j];
		}
	}
	int index_i, index_j, value, new_size;
	cout << "enter a shrink value : ";
	cin >> value;
	new_size = SIZE / value;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i < new_size && j < new_size)
			{
				image[i][j] = image2[index_i][index_j];
				index_j += value;
			}
			else
			{
				image[i][j] = 255;
			}
		}
		index_j = 1;
		index_i += value;
	}
}

//shuffel image parts
void shuffle_image()
{
	int ch[4];

	cout << "Enter all order of photos separeted by spaces : ";
	for (int i = 0; i < 4; i++)
		cin >> ch[i];

	int x = 0, y = 0;

	//to store new image parts
	int imaget[SIZE][SIZE] = {{0}, {0}};

	// first quarter
	int image1[SIZE / 2][SIZE / 2];

	// second quarter
	int image2[SIZE / 2][SIZE / 2];

	// third quarter
	int image3[SIZE / 2][SIZE / 2];

	// fourth quarter
	int image4[SIZE / 2][SIZE / 2];

	// fill first part of image
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			image1[i][j] = image[i][j];
		}
	}

	// fill second part of image
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = SIZE / 2; j < SIZE; j++)
		{
			image2[x][y] = image[i][j];
			y++;
		}
		y = 0;
		x++;
	}

	// fill third part of image
	x = 0, y = 0;
	for (int i = SIZE / 2; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			image3[x][y] = image[i][j];
			y++;
		}
		y = 0;
		x++;
	}

	// fill third part of image
	x = 0, y = 0;
	for (int i = SIZE / 2; i < SIZE; i++)
	{
		for (int j = SIZE / 2; j < SIZE; j++)
		{
			image4[x][y] = image[i][j];
			y++;
		}
		y = 0;
		x++;
	}

	int count = 0;
	for (int k : ch)
	{
		x = 0, y = 0;
		if (count == 0)
		{
			for (int i = 0; i < SIZE / 2; i++)
			{
				for (int j = 0; j < SIZE / 2; j++)
				{
					if (k == 1)
						imaget[i][j] = image1[i][j];
					else if (k == 2)
						imaget[i][j] = image2[i][j];
					else if (k == 3)
						imaget[i][j] = image3[i][j];
					else if (k == 4)
						imaget[i][j] = image4[i][j];
				}
			}
		}

		else if (count == 1)
		{
			for (int i = 0; i < SIZE / 2; i++)
			{
				for (int j = SIZE / 2; j < SIZE; j++)
				{
					if (k == 1)
						imaget[i][j] = image1[x][y];
					else if (k == 2)
						imaget[i][j] = image2[x][y];
					else if (k == 3)
						imaget[i][j] = image3[x][y];
					else if (k == 4)
						imaget[i][j] = image4[x][y];
					y++;
				}
				y = 0;
				x++;
			}
		}

		else if (count == 2)
		{
			for (int i = SIZE / 2; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE / 2; j++)
				{
					if (k == 1)
						imaget[i][j] = image1[x][y];
					else if (k == 2)
						imaget[i][j] = image2[x][y];
					else if (k == 3)
						imaget[i][j] = image3[x][y];
					else if (k == 4)
						imaget[i][j] = image4[x][y];
					y++;
				}
				y = 0;
				x++;
			}
		}

		else if (count == 3)
		{
			for (int i = SIZE / 2; i < SIZE; i++)
			{
				for (int j = SIZE / 2; j < SIZE; j++)
				{
					if (k == 1)
						imaget[i][j] = image1[x][y];
					else if (k == 2)
						imaget[i][j] = image2[x][y];
					else if (k == 3)
						imaget[i][j] = image3[x][y];
					else if (k == 4)
						imaget[i][j] = image4[x][y];
					y++;
				}
				y = 0;
				x++;
			}
		}

		count++;
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = imaget[i][j];
		}
	}
	cin.ignore();
}

void blurImage()
{
	//Gaussian blur algorithm
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image2[i + 1][j + 1] = image[i][j];
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = (image2[i][j] + image2[i][j + 1] + image2[i][j + 2] + image2[i + 1][j] + image2[i + 1][j + 2] + image2[i + 2][j] + image2[i + 2][j + 1] + image2[i + 2][j + 2]) / 9;
		}
	}
}

int main()
{
	string choice, flipDetect, mirordetect;
	bool contin = true, load = true;

	while (contin)
	{
		if (load)
		{
			loadImage();
			load = false;
		}
		cout << "\n\n";
		cout << "Enter The Number of the operation \n";
		cout << "1- Black & White Filter \n";
		cout << "2- Invert Image\n";
		cout << "3- Merge Images \n";
		cout << "4- Flip Image \n";
		cout << "5- Rotate Image\n";
		cout << "6- Darken & Lighten an image \n";
		cout << "7- Detect Image Edges \n";
		cout << "8- Enlarge Image\n";
		cout << "9- Shrink an Image \n";
		cout << "a- Mirror 1/2 Image \n";
		cout << "b- Shuffle Image\n";
		cout << "c- Blur an Image \n";
		cout << "s- Save the image to a file \n";
		cout << "n- Make new edit \n";
		cout << "0- Exit \n\n";
		cout << ">>>> ";
		cin >> choice;

		if (choice == "1")
		{
			ConvertBlackAndWhite();
		}

		else if (choice == "2")
		{
			invert();
		}

		else if (choice == "3")
		{
			mergeTwoPictures();
		}
		else if (choice == "4")
		{
			cout << "Flip (h)orizontally or (v)ertically ? \n";
			cin >> flipDetect;

			if (flipDetect == "h" || flipDetect == "horizontally")
			{
				flipImageHorizontally();
			}

			else if (flipDetect == "v" || flipDetect == "vertically")
			{
				flipImageVertically();
			}
		}

		else if (choice == "5")
		{
			rotate();
		}

		else if (choice == "6")
		{
			darken_Lighten();
		}
		else if (choice == "7")
		{
			detectImageEdges();
		}

		else if (choice == "8")
		{
			enlarge();
		}

		else if (choice == "9")
		{
			shrinkImage();
		}
		else if (choice == "a")
		{
			cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
			cin >> mirordetect;

			if (mirordetect == "d")
			{
				mirrorDown();
			}

			else if (mirordetect == "u")
			{
				mirrorUp();
			}

			else if (mirordetect == "l")
			{
				mirrorLeft();
			}

			else if (mirordetect == "r")
			{
				mirrorRight();
			}
		}

		else if (choice == "b")
		{
			shuffle_image();
		}

		else if (choice == "c")
		{
			blurImage();
		}

		else if (choice == "s")
		{
			saveImage();
		}

		else if (choice == "n")
		{
			load = true;
		}

		else if (choice == "0")
		{
			cout << "HAVE A NICE DAY !! \n";
			contin = false;
		}
		else
		{
			cout << "Please enter a VALID number ";
		}
	}

	return 0;
}
