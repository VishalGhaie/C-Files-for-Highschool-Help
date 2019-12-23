/***
fileScan

This program reads car data and store the information.

Author: Ashley Ghaie
Date: December, 16, 2019

Version: Final Version
***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

//A car is one node so to make add another car to the chain, we need to make a "next"
typedef struct node{
    char make[20];
    char model[20];
    char ownerf[20];
    char ownerl[20];
    char year[20];
    char initialPrice[20];
    char mileage[20];
    struct node* next;
} node;

node* head = NULL;

//Function Declerations
node* carAddFront(node* head1, char make[], char model[], char ownerf[], char ownerl[], char year[], char initialPrice[], char mileage[]);
node* createCar(char make[], char model[], char ownerf[], char ownerl[], char year[], char initialPrice[], char mileage[], node* next);

int main(void){
    int userChoice;
    int quitCondition = 0;

    while(quitCondition == 0){
        //Start the Main Menu
        userChoice = startUp();

        //User Choices
        switch(userChoice){
            case 1:
                fileRead();
            break;
            case 2:
                displayContents(head);
            break;
            case 3:
                free(head);//Clean up the memory before exiting
                quitCondition = 1;
            break;
            default:
            break;
        }
    }
    return 0;
}

/**
startUp

Main menu for the code.

Input: N/a
Output: userSelect: Whatever the user selects is returned back to main for further processing.

**/
int startUp(){
    int userSelect; //User options

    //User Enters a option
    printf("Welcome to File Edit Assignment 2:\n\n");
    printf("Here are the currently functioning items, what would you like to do: ");
    printf("\nEnter 1 to read a file\n");
    printf("Enter 2 to display list\n");
    printf("Enter 3 to Quit\n");
    printf("\nPress Enter After Selection...\n");
    scanf("%i", &userSelect);

    system("cls");
    return userSelect;
}


/**
fileRead

Reads the user selected file.

Input: N/a
Output: N/a

**/
void fileRead(){
    FILE *fp; //Pointer to the txt file
    char fileName[20]; //File name

    printf("Please enter a file location to read the file: ");
    scanf("%s", &fileName);

    system("cls");
    printf ("Reading file please wait...");

    //Open the file to read or write
    fp = fopen(fileName,"r+");

    //Test if file read was unsucessful
    if(fp == NULL) {
        printf("\n\nError opening file.");
    }
    //The file read was successful
    else {
        printf("\nFile %s successfully opened.\n\n", fileName);
        int addType = 0;
        char make[20];
        char model[20];
        char ownerf[20];
        char ownerl[20];
        char year[20];
        char initialPrice[20];
        char mileage[20];

        /*Input data from the file, and echo to the console*/
        while(!feof(fp)) {               /*A fancy line to stop at the end of file*/

          //retrieve data from the file and added into specific variable
            switch(addType){
                case 0:
                    fscanf(fp,"%s",&make);
                    printf("%s\n", make);
                break;
                case 1:
                    fscanf(fp,"%s",&model);
                    printf("%s\n", model);
                break;
                case 2:
                    fscanf(fp,"%s",&ownerf);
                    printf("%s\n", ownerf);
                break;
                case 3:
                    fscanf(fp,"%s",&ownerl);
                    printf("%s\n", ownerl);
                break;
                case 4:
                    fscanf(fp,"%s",&year);
                    printf("%s\n", year);
                break;
                case 5:
                    fscanf(fp,"%s",&initialPrice);
                    printf("%s\n", initialPrice);
                break;
                case 6:
                    fscanf(fp,"%s",&mileage);
                    printf("%s\n\n", mileage);
                    //add new car to list and make the head point to the most currently added car in the list
                    head = carAddFront(head, make, model, ownerf, ownerl, year, initialPrice, mileage);
                    addType = -1;
                break;
            }
          addType++;
        }
        printf("\nFile Read Complete...\n");
    }
    fclose(fp); /*Close the file access*/
    system("pause");
    system("cls");
    return 0;
}

/**
carAddFront

Adds a new car to the front of the chain.

Input:
node* head1: This is the pointer where the new car will be added to.
char make[]: The make of the car.
char model[]: The model of the car.
char ownerf[]: The Owners first name.
char ownerl[]: The Owners last name.
char year[]: The year the car was made.
char initialPrice[]: The initial price of the car.
char mileage[]: The mileage of the car.

Output:
node* : This will return a pointer back (dealer giving the car to the customer(head in this case))

**/
node* carAddFront(node* head1, char make[], char model[], char ownerf[], char ownerl[], char year[], char initialPrice[], char mileage[])
{
    //Dealer creates the new car from the recipe
    node* dealer = createCar(make, model, ownerf, ownerl, year, initialPrice, mileage, head1);
    //Head now points to the new car made by the dealer
    head1 = dealer;
    //Return this transaction
    return head1;
}

/**
createCar

Creates a new car.

Input:
char make[]: The make of the car.
char model[]: The model of the car.
char ownerf[]: The Owners first name.
char ownerl[]: The Owners last name.
char year[]: The year the car was made.
char initialPrice[]: The initial price of the car.
char mileage[]: The mileage of the car.
node* next: This is the pointer where the new car will be pointing to in relation to the other cars.

Output:
node* : This will return a pointer back (dealer will be recieving the manufactured car)

**/
node* createCar(char make[], char model[], char ownerf[], char ownerl[], char year[], char initialPrice[], char mileage[], node* next)
{
    //Create a temperary car
    node* tempCarVar = (node*)malloc(sizeof(node));

    //Just in case car cannot be made
    if(tempCarVar == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    //add items into the car (Had to use memcpy because it copies the array directly from memory)
    memcpy(tempCarVar->make, make, sizeof(tempCarVar->make));
    memcpy(tempCarVar->model, model, sizeof(tempCarVar->model));
    memcpy(tempCarVar->ownerf, ownerf, sizeof(tempCarVar->ownerf));
    memcpy(tempCarVar->ownerl, ownerl, sizeof(tempCarVar->ownerl));
    memcpy(tempCarVar->year, year, sizeof(tempCarVar->year));
    memcpy(tempCarVar->initialPrice, initialPrice, sizeof(tempCarVar->initialPrice));
    memcpy(tempCarVar->mileage, mileage, sizeof(tempCarVar->mileage));
    tempCarVar->next = next;

    //give car back to main code
    return tempCarVar;
}

/**
displayContents

Displays the entire linked list into a nice display.

Input:
node* head1: This is the pointer for the list that is going to be displayed.

Output:
Prints out the list details to the screen.

**/
void displayContents(node* head1){
    printf("Displaying Contents of List:\n");
    printf("_______________________________________");
    printf("\n\n");
    //Temperary node pointer so our main head pointer is not effected
    node* cursor = head1;
    int carId = 0;
    //Go through the list until the list is complete
    while(cursor != NULL)
    {
        //This prints the contents of 1 car
        printf("Car ID: %i\n", carId);
        printf("Make: %s\n", cursor->make);
        printf("Model: %s\n", cursor->model);
        printf("Owner: %s %s\n", cursor->ownerf, cursor->ownerl);
        printf("Year Made: %s\n", cursor->year);
        printf("Initial Price: %s\n", cursor->initialPrice);
        printf("Current Mileage: %s\n", cursor->mileage);
        printf("_______________________________________");
        printf("\n\n");

        //This moves the cursor along in the list and updates the car ID
        cursor = cursor->next;
        carId++;
    }
    printf("Done Searching...\n");
    system("pause");
    system("cls");
    return 0;
}
