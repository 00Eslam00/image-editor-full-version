#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

void ConvertBlackAndWhite() {
    long avg=0;

    // get the average pixels of the image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
        avg+= image[i][j];
        }
    }

    avg /= (SIZE*SIZE);

    // convert to black and white
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (image[i][j] > avg){
                image[i][j] = 255;
            }
            else{
                image[i][j] = 0;
            }
        }
    }
}

void flipImageHorizontally(){

    // flip horizontally
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            int tempSave = image[i][j];
            image[i][j] = image[i][SIZE-1-j];
            image[i][SIZE-1-j] = tempSave;
        }
    }
}

void flipImageVertically(){
    //flip vertically
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j < SIZE; j++) {
            int tempSave = image[i][j];
            image[i][j]=image[SIZE-1-i][j];
            image[SIZE-1-i][j]=tempSave;
        }
    }
}

void mirrorDown(){
    //mirror the down side
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=image[255-i][j];
        }
    }
}

void mirrorUp(){
    // mirror the upper side
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[255-i][j]=image[i][j];
        }
    }
}

void mirrorLeft(){
    // mirror the left side
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][255-j]=image[i][j];
        }
    }
}

void mirrorRight(){
    //mirror the right side
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=image[i][255-j];
        }
    }
}

void detectImageEdges(){
    //convert black and white
    ConvertBlackAndWhite();

    // detect the edges
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if(image[i][j] == image[i][j+1]){
                image[i][j]=255;
            }
            else{
                image[i][j]=0;
            }
        }
    }
}

int main()
{

string choice , flipDetect , mirordetect;
bool isVAlid =true , contin = true;

loadImage();

while (isVAlid || contin){
    cout<<"\n\n";
    cout<<"Enter The Number of the operation \n";
    cout<<"1- Black & White Filter \n";
    cout<<"4- Flip Image \n";
    cout<<"7- Detect Image Edges \n";
    cout<<"a- Mirror 1/2 Image \n";
    cout<<"s- Save the image to a file \n";
    cout<<"0- Exit \n\n";
    cout<<">>>> ";
    cin>>choice;

if (choice == "1"){
   ConvertBlackAndWhite();
   isVAlid = false;
}

else if(choice =="4"){
    cout<<"Flip (h)orizontally or (v)ertically ? \n";
    cin>>flipDetect;

    if(flipDetect == "h" || flipDetect == "horizontally"){
        flipImageHorizontally();
        isVAlid = false;
    }

    else if(flipDetect == "v" || flipDetect == "vertically"){
        flipImageVertically();
        isVAlid = false;
    }
}

else if(choice =="7"){
    detectImageEdges();
    isVAlid = false;
}

else if (choice == "a"){
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
    cin>>mirordetect;

    if(mirordetect=="d" || mirordetect == "down"){
        mirrorDown();
        isVAlid = false;
    }

    else if(mirordetect == "u" || mirordetect == "up"){
        mirrorUp();
        isVAlid = false;
    }

    else if(mirordetect == "l" || mirordetect == "left"){
        mirrorLeft();
        isVAlid = false;
    }

    else if(mirordetect == "r" || mirordetect == "right"){
        mirrorRight();
        isVAlid = false;
    }
}

else if (choice == "s"){
    saveImage();
    isVAlid = false;
    contin = false;
}
else if (choice == "0") {
    cout<<"HAVE A NICE DAY !! \n";
    isVAlid = false;
    contin = false;
}
else {
    cout<<"Please enter a VALID number ";
}
}

    return 0;
}
