#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>  

#define MAX_ID_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_FILENAME_LENGTH 256
#define MAX_LINE_LENGTH 1024
#define MAX_LENGTH 100



int is_term_in_file(const char *filename, const char *search_term);
void displayAnimation();
void end_screen();
char x[30];

typedef struct {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;
void write_current_time_to_file(const char *str11,int uht);

// Function to check password restrictions
int checkPasswordRestrictions(char *password) {

    if (strlen(password) < 8) {
        printf("Password must be at least 8 characters long.\n");
        //system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        return 0;
    }

    int upperCount = 0, lowerCount = 0, digitCount = 0, specialCount = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) upperCount++;
        if (islower(password[i])) lowerCount++;
        if (isdigit(password[i])) digitCount++;
        if (ispunct(password[i])) specialCount++;
    }

    if (upperCount == 0) { 
			//system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
             //system("taskkill /IM wmplayer.exe /F");  
			 printf("Password must contain at least one uppercase letter.\n");
			}
    if (lowerCount == 0) {
    		//system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
		//	system("taskkill /IM wmplayer.exe /F");  
			printf("Password must contain at least one lowercase letter.\n");
		}
	if (digitCount == 0) {
    	//system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
			// system("taskkill /IM wmplayer.exe /F");  
	 		 printf("Password must contain at least one digit.\n");
			 }
    if (specialCount == 0){
    //	system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
 		//	 system("taskkill /IM wmplayer.exe /F");  
			 printf("Password must contain at least one special character.\n");
	}
    		 

    return upperCount > 0 && lowerCount > 0 && digitCount > 0 && specialCount > 0;
}


// Function to check if a user exists
int userExists(char *id) {
    FILE *file = fopen("users.txt", "r");
    if (!file) return 0;

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.id, id) == 0) {
            fclose(file);
            return 1;
        }
    }
fclose(file);
/*system("start wmplayer \"D:\\c\\error.wav.mp3\"");
sleep(2);
system("start wmplayer \"D:\\c\\error.wav.mp3\"");

printf("\n\n\n\t\t \033[38;5;208m	u kiddin' :( \n\n\n\t\t first SIGN UP  to LOGIN ");
system("start wmplayer \"D:\\c\\error.wav.mp3\"");
sleep(5);
system("taskkill /IM wmplayer.exe /F");  
system("cls");
exit (0);*/

    return 0;
}
/*int userExists(char *id) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        perror("Error opening users file");
        return 0; // Return 0 if file cannot be opened
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.id, id) == 0) {
            fclose(file);
            return 1; // User exists
        }
    }

    fclose(file);
    //return 0; // User does not exist
    printf("\n \033[31mUser does not exist.\n");
    sleep(3);
    exit(0);
}*/

//------------------------------------------------------------------------------------------------------------------------------------------------
// Function prototypes
int is_term_in_file(const char *filename, const char *search_term);
void print_file_content(const char *filename);

void search_and_display_files(const char *list_filename, const char *search_term) {
   // printf("Searching for '%s' in files listed in %s\n", search_term, list_filename);
  

    FILE *list_file = fopen(list_filename, "r");
    if (list_file == NULL) {
  //  	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        perror("Error opening list file");
        exit(EXIT_FAILURE);
    }
char filename[MAX_FILENAME_LENGTH];
    int found_any = 0;
// Read filenames from the list file
    while (fgets(filename, sizeof(filename), list_file)) {
        // Remove the newline character from the filename
        filename[strcspn(filename, "\n")] = '\0';

        // Check if the term is in the file
        if (is_term_in_file(filename, search_term)) {
            // If found, print the file content
            print_file_content(filename);
            found_any = 1;
        }
    }
 if (!found_any) {
 //	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
 	  printf("\033[96m'%s'\033[0m not found in any file\n\033[96m", search_term);
 	 
    }

    fclose(list_file);
}
void print_file_content(const char *filename) {
    // Debug message: consider removing or replacing with proper logging
  
FILE *file = fopen(filename, "r");
    if (file == NULL) {
  //  	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
    	
        perror("Error opening file");
        return;
    }
char line[MAX_LINE_LENGTH];
// Optionally use color codes for terminal output; ensure terminal compatibility
    printf("Contents of file '%s':\n", filename);
    while (fgets(line, sizeof(line), file)) {
        printf("\t%s", line);
        sleep(2);
    }
    printf("\n");

    fclose(file);
}
int is_term_in_file(const char *filename, const char *search_term) {
	
    // Debug message: consider removing or replacing with proper logging
   // printf("Checking if term is in file: %s\n", filename);
FILE *file = fopen(filename, "r");
    if (file == NULL) {
  //   system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        perror("Error opening file");
        return 0;
    }
char line[MAX_LINE_LENGTH];
    int found = 0;
// Read each line and search for the term
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_term)) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}
//-------------------------------------------------------------------------------------
// Function to create a new user and associated file
void createUser(char *id) {
    char password[MAX_PASSWORD_LENGTH];
    do {
printf("\033[33mPassword can't be Changed !!\n  ");
        printf("\033[38;5;208mEnter password : \033[38;5;226m");
        scanf("%99s", password);
    } while (!checkPasswordRestrictions(password));

    User newUser;
    strcpy(newUser.id, id);
    strcpy(newUser.password, password);

    FILE *file = fopen("users.txt", "ab");
  /*  if (file == NULL) {
    
        printf("\033[38;5;208mEnter password : \033[38;5;226m");
        printf("Error opening file!\n");
        return;
    }*/
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);
    //system("cls");
    //system("start wmplayer \"D:\\c\\login.wav.mp3\"");
 
    
    printf("\n Profile created successfully.\n\033[34mU Logged in !!\n\n");
    
           // printf("\t\t\t\t Profile created successfully.\n\033[34mU Logged in !!\n\n");
    //printf("\t\033[34mLogin successful.\n\n");
	printf("\t \033[97m*          *****           *   \n");
    printf("\t *         *******          *\n");
    printf("\t *        *********         *\n");
    printf("\t *         *******          * \n");
    printf("\t *          *****           *\n");
    printf("\t *\033[38;5;226m           ***            \033[35m* \n");
    printf("\t *\033[38;5;226m       ***********        \033[35m* \n");
    printf("\t *\033[38;5;226m     ***************      \033[35m*   \n");
    printf("\t *\033[38;5;226m    *****************     \033[35m*   \n");
    printf("\t *\033[38;5;226m    *****************     \033[35m*\n");
    printf("\t *\033[38;5;226m    *****************     \033[35m*\n");
    printf("\t *\033[38;5;226m    *  %s        *       \033[35m*   \n", id);
    sleep(2);
    printf("\n\n\t \033[38;5;129mYo\033[93m %s,\n \t\033[38;5;129m this ur diary - ditch everythin' and have fun!",id);
    sleep(3);
    system("cls");//-------------------------------------
    
    
    char str11[10] = "UH";
strcat(str11, id);
// printf("user history filename [sign up]: %s\n",str11);
write_current_time_to_file(str11,1);//write_current_time_to_file(str11);  // 1: SIGNED UP
    // Function to check if a search term is in a file
}
// Function to print the content of a file
// WRITE TIME -FILEV--------------------------------------------------------
void write_current_time_to_file(const char *str11,int uht) {
//	
	//	printf(" [at write to file fun ]  %s",str11 );

    // Open the file in append mode ("a")
    FILE *file = fopen(str11, "a");
    if (file == NULL) {
    	
        perror("\033[91mError opening file");
        return;
    }
	//printf("\n str11,id passed in side fun  : %s %d",str11,uht);
    // Get the current time
    time_t now;
    time(&now);
    char *time_str = ctime(&now); // Convert time to a string
    
    // Check if ctime returns NULL
    if (time_str == NULL) {
    
        perror("\033[91mError getting time");
        fclose(file);
        return;
    }

    // Write the current time to the file
    //fprintf(file, "time: %s", time_str);
    if (uht==1){
    	//printf("signed up worked");
    fprintf(file, "SIGNED UP ON : %s", time_str);	
	}
	if (uht==2){
	//printf("login  worked");
    fprintf(file, "LOGGED IN : %s", time_str);	
	}
	if(uht==3){
	 //printf("access worked");
		fprintf(file, "ACCESSED FILES : %s", time_str);
			}
	if(uht==4){
	//printf("data deleted worked");
	fprintf(file, "DATA DELETED : %s", time_str);	
	}
	if(uht==5){
	//printf("search  worked");
 fprintf(file, "SEARCHED DATA : %s", time_str);	
	}
	if(uht==6){
				//printf("login  worked");

	fprintf(file, "LOGIN ERROR : %s", time_str);	
	}
	if(uht==7){
		//printf("user checked history :");
	fprintf(file, "CHECKED HISTORY : %s", time_str);	
	}
	 // Close the file
    fclose(file);
//printf("Current time has been written to %s\n", str11);
}// enc file decrypt and enc rypt
void charToInvertedBinary(char c, char *binary) {
    for (int i = 7; i >= 0; --i) {
        binary[7-i] = ((c >> i) & 1) ? '0' : '1'; // Invert bits
    }
    binary[8] = '\0'; // Null-terminate the string
}

// Function to convert inverted binary representation back to a character
char invertedBinaryToChar(char *binary) {
    char c = 0;
    for (int i = 0; i < 8; ++i) {
        c = (c << 1) | ((binary[i] == '0') ? 1 : 0); // Invert bits
    }
    return c;
}

// Function to write encrypted binary data to a file
void writeEncryptedDataToFile(const char *spfilename, const char *data) {
    FILE *file = fopen(spfilename, "w");
    if (file == NULL) {
  //  	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        fprintf(stderr, "Unable to open file for writing\n");
        exit(1);
    }

    size_t len = strlen(data);
    char binary[9]; // 8 bits + 1 null terminator

    for (size_t i = 0; i < len; ++i) {
        charToInvertedBinary(data[i], binary);
        fprintf(file, "%s", binary);
    }

    fclose(file);
    printf("Data encrypted and written to '%s'.\n", spfilename);
}

// Function to read and decrypt binary data from a file
void readDecryptedDataFromFile(const char *spfilename, char *output, size_t len) {
    FILE *file = fopen(spfilename, "r");
    if (file == NULL) {
  //  	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        fprintf(stderr, "Unable to open file for reading\n");
        exit(1);
    }

    char *binary_data = (char *)malloc(len * 8 + 1);
    if (binary_data == NULL) {
  //  	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        fprintf(stderr, "Memory error\n");
        fclose(file);
        exit(2);
    }

    fread(binary_data, 1, len * 8, file);
    binary_data[len * 8] = '\0'; // Null-terminate the binary data
    fclose(file);

    for (size_t i = 0; i < len; ++i) {
        char binary_char[9];
        strncpy(binary_char, &binary_data[i * 8], 8);
        binary_char[8] = '\0'; // Null-terminate the binary_char
        output[i] = invertedBinaryToChar(binary_char);
    }
    output[len] = '\0'; // Null-terminate the output string

    free(binary_data);
}

//----------------------------------------------------------------------------
// Function to search term in files and display content if term is found
// Function to log in a user
void loginUser(char *id) {
    char password[MAX_PASSWORD_LENGTH];
    
    // Print prompt for password
    printf("\t\033[38;5;226mEnter password: \033[30m");
    scanf("%99s", password);

    // Open the file
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        //system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        sleep(2);
        //system("taskkill /IM wmplayer.exe /F");
        perror("\033[31mError opening users file");
        return;
    }

    User user;
    int userFound = 0;

    // Read the file and search for the user
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.id, id) == 0) {
            userFound = 1;
            if (strcmp(user.password, password) == 0) {
                int count = 0;
           
              // system("start wmplayer \"D:\\c\\login.wav.mp3\"");
                while (count <= 1) {
                    system("cls");
                    usleep(500000);
                    printf("\t\033[34mLogin successful.\n\n");
                    printf("\t \033[97m*          *****           *   \n");
                    printf("\t *         *******          *\n");
                    printf("\t *        *********         *\n");
                    printf("\t *         *******          * \n");
                    printf("\t *          *****           *\n");
                    printf("\t *\033[38;5;226m           ***            \033[35m* \n");
                    printf("\t *\033[38;5;226m       ***********        \033[35m* \n");
                    printf("\t *\033[38;5;226m     ***************      \033[35m*   \n");
                    printf("\t *\033[38;5;226m    *****************     \033[35m*   \n");
                    printf("\t *\033[38;5;226m    *****************     \033[35m*\n");
                    printf("\t *\033[38;5;226m    *****************     \033[35m*\n");
                    printf("\t *\033[38;5;226m    *  %s        *       \033[35m*   \n", id);
                    
                    count++;
                    usleep(1000000);
                    printf("\n\t \033[38;5;129mYo!  \033[38;5;129m%s \n \033[38;5;129m \tGreat to see you again!", id);
                    sleep(count);
                }
            //    system("taskkill /IM wmplayer.exe /F");
                system("cls");

                char str11[20] = "UH";
                strcat(str11, id);
                write_current_time_to_file(str11, 2); // 1: LOG
                
                fclose(file);
                return;
            } else {
          //      system("start wmplayer \"D:\\c\\error.wav.mp3\"");
                sleep(2);
        //        system("taskkill /IM wmplayer.exe /F");
                printf("\033[31mInvalid password.\n");
                
                fclose(file);
                exit(0);
            }
        }
    }

    if (!userFound) {
    //    system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        sleep(2);
      //  system("taskkill /IM wmplayer.exe /F");
        printf("\n \033[31mUser does not exist.\n");
        fclose(file);
        exit(0);
    }

    fclose(file);
}
//--------------------------------------------------------------------
int fileExists(const char *filename) {
			//	printf(" at file exists   %s",filename );
			
	
    FILE *fcheck = fopen(filename, "r");

    if (fcheck != NULL) {
        fclose(fcheck);
        return 1; // File exists
    }
    return 0; // File does not exist
}

// Function to get a valid filename that doesn't already exist
void getValidFilename(char *filename) {
			//	printf(" at get valid filename 1   %s",filename );

    while (1) {
    	char str[30];
   
        printf("\033[38;5;226mEnter a NEW FILE NAME : \033[96m");
        scanf("%49s", filename);
        //sleep(2);
        //system("cls");
         str[strcspn(str, "\n")] = '\0';// Append ".txt" to the string
    strcat(filename,"");//removed .txt-----------------------------------------------
    		//	printf(" at getvalid filename 2   %s",filename);

  if (fileExists(filename)) {
  //	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
            printf("\n \033[31mFile Already Exists \n");
            sleep(2);
           // printf("\033[31mFile Already Exists \n");
           // sleep(2);
            //system("cls");
            
            } else {
            break; // Exit the loop if file does not exist
                        //system("cls");

        }
    }}
// Function to write to the user's file
int writeToFile(const char *userfile) {

			//	printf(" at write to file   %s",userfile  );

    
//FILE *fcheck = fopen(filename, "r");
char filename[50];
    getValidFilename(filename);
    	//		printf(" after getvalid filename in wrt to file   %s",filename );
char str11[20] = "UH";
strcat(str11,userfile);  // 'filename' is the name of the file being written to
		//	printf(" in write to file ater strcat  %s",userfile  );
		//	printf(" in write to file after remvoe extension   %s",str11  );

//printf("\n user history file name [write to file ]:%s\n ",str11);
char filePath[60];
snprintf(filePath, sizeof(filePath), "%s", filename);// rmeoved .txt 
		//	printf(" in write to file after snprintf  %s",filename  );


    FILE *fp = fopen(userfile, "a");
    if (!fp) {
    	 //system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        perror("\n \033[31mError opening user file");
        return EXIT_FAILURE;
    }
    fprintf(fp, "%s\n", filePath);
    fclose(fp);

    FILE *diaryFile = fopen(filePath, "a");
    if (!diaryFile) {
    	//	printf("\n\n\n\n");
        //	printf("\n\n\n");
            //printf("\t\t\t\t\t"); 
            // system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        perror("\n \033[31mError opening diary file");
        return EXIT_FAILURE;
    //----------------------------------
	}
// ----------------------------------------------------------------------------------------------------- enc

    time_t currentTime;
    time(&currentTime);
    //char str11[20]="UH" ;  


    fprintf(diaryFile, "Time : %s", ctime(&currentTime));
    fprintf(diaryFile, "D I A R Y\n");
    int masking=0;
    printf("Wanna write diary in mask mode ?\n");
    printf("1 : yes !\n");
    printf("2 : NO  !\n");
    printf(">>>> ");
    scanf("%d",&masking);
    
    char buffer[256];
    printf("\033[35mTime : %s",ctime(&currentTime));
    printf("\033[36mD I A R Y \033[33m");
    printf("Enter lines of text (TO end press $$ in new line):\n");
    if(masking==1){
    	printf("\n masking turned on ! ");
    	printf("\033[30m");
    	}
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (strncmp(buffer, "$$", 2) == 0) {
            break;
        }
        fputs(buffer, diaryFile);
    }

    fclose(diaryFile);
    printf("\033[34mData written to file successfully.\n");
    return 0;

}  // Function to display entries from user's file
int display(const char *filename) {
	char ch1,ch2;
	printf(" in display 1  %s",filename  );

    char line[256];
    char str11[20] = "UH";
strcat(str11,filename);  // Here, 'line' should be the filename from the user's entries
//remove_extension(str11);
//printf(" display -> remove extension 2  %s",str11  );

//printf("user history in display [access ,delete search] : %s\n",str11);
//system("cls");
//printf("\n\n\n\n");
        	printf("\n\n\n");
            //printf("\t\t\t\t\t"); 
            system("cls");
printf("\033[38;5;208mYOUR ENTRIES \n");
printf("|--------------------|\n");
printf("  FILE NO : FILE NAME  \n");

    //printf("\n  %s",x);
FILE *file = fopen(filename, "r");
    if (!file) {
    	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
system("taskkill /IM wmplayer.exe /F");  
        perror("\n \033[91mError opening file");
        return EXIT_FAILURE;
    }
int index = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("\033[96m     %d \033[0m:\033[38;5;226m %s", index++, line);
    }
    fclose(file);
int b=0;//char str11[20]="UH" ;  
printf("\n \033[0m1 :\033[93m ACCESS FILES \n \033[0m2 :\033[93m DELETE DATA FROM FILE ,yo! ? \n \033[0m3 :\033[93m wanna search something ? \n \033[0m4 :\033[93m check history\n \033[0m5 : \033[93mencryption mode\033[0m \n 6 : \033[93mExit \n>>>> \033[91m");
scanf("%d",&b);
//system("cls");
if(b==1 ){
write_current_time_to_file(str11, 3);  // 3: ACCESSED FILES
  int choice;
   printf("\n\033[35mENTER  FILE NO : \033[91m");
    scanf("%d", &choice);
if (choice < 1 ) {
	// system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        printf("\n \033[91mINVALID CHOICE\n");
        return EXIT_FAILURE;
    }
file = fopen(filename, "r");
    if (!file) {
    	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
system("taskkill /IM wmplayer.exe /F");  
        perror("\n \033[91mError opening file");
        return EXIT_FAILURE;
    }
    index = 1;
    //printf("here 1\n ---");
    while (fgets(line, sizeof(line), file) && index < choice) {
        index++;
    }
//strcat(str11,line);

//write_current_time_to_file(str11,3);
    if (index != choice) {
    	// system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        printf("\n \033[91mChoice out of range\n");
        fclose(file); 
        return EXIT_FAILURE;
    }
fclose(file);
// Remove newline character from the line buffer----------------------------------------------
   line[strcspn(line,"\n")] = 0;
char buffer[1024];
    FILE *fl = fopen(line, "r");
    if (fl == NULL) {
    	 //system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        perror("\n \033[91mError opening selected file ER-5");
        return EXIT_FAILURE;
    }
//printf("here it reads 2");
    while (fgets(buffer, sizeof(buffer), fl)) {
        printf("%s", buffer);
    }
fclose(fl);
printf("\nPress any key to continue...\n");
    scanf(" %c", &ch1);
     return EXIT_SUCCESS;
     }
if (b==2) {
	char filename[100];
	
printf("\033[35mEnter file name to delete data : \033[35m");
    scanf("%s", filename);
// Attempt to delete the file
    FILE *fd=fopen(filename,"w");
    if (fd==NULL){
    //	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
    	printf("\n \033[91merror in file opening ");
	}
	//printf("\n str11 : %s",str11);
write_current_time_to_file(str11,4);
	char text[40]=" YOU DELETED DATA FROM THIS FILE  :( ";
	fprintf(fd, "%s", text);
	printf("\033[34mDATA DELETED SUCCESSFULLY");
	sleep(3);
	fclose(fd);
}
	if (b == 3) {
    char search_term[50];
    
      printf("\033[36myo! what you wanna search ? : \033[38;5;226m");
    scanf("%49s",search_term);
//	printf("fileanme in search  : %s ",filename);// Limit input to prevent buffer overflow
  search_and_display_files(filename, search_term);
    	//printf("\n str11 : %s",str11);
write_current_time_to_file(str11,5);
char ch;
printf("\nPress any key to continue...\n");
    scanf(" %c", &ch);
    //system("cls");
    }
    if (b==4){
    	write_current_time_to_file(str11,7);
	}
    if(b==4){
    	FILE *uhfile;
    char uhl[100]; // Adjust buffer size as needed
   uhfile = fopen(str11,"r"); // Replace "data.txt" with your file name
    if (uhfile == NULL) {
    //	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        printf("\n \033[91mError opening file!\n");
        return 1;
    }
    while (fgets(uhl, sizeof(uhl),uhfile) != NULL) {
    	
        printf("%s",uhl); // Remove newline if needed: printf("%s", line);
    }
   fclose(uhfile);
   printf("\nPress any key to continue...\n");
    scanf(" %c", &ch2);
    return 0;
    	}
    if (b == 5) {
    char encuf[256];
    char line[256]; 
    snprintf(encuf, sizeof(encuf), "%s_enc", filename);
    FILE *encFile = fopen(encuf, "a+");
    int fn=1;
    printf(" \nNO   | Encrypted files\n");
    while (fgets(line, sizeof(line),encFile )) {
        printf("  %d | %s", fn,line);
        fn++;
    }
     if (encFile == NULL) {
     //	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
        perror("\n Error opening file for appending");
        return EXIT_FAILURE;
    }

    char filename[50];
    char filepath[40];
    int encc;
    printf("\n1: Write data to encrypt?");
    printf("\n2: Decrypt?\n");
    printf(">>>> : ");
    scanf("%d", &encc);
    getchar(); // Consume the newline character left by scanf
    
    char output[4096];
    char spfenc[40];
    char input[256];
    char fullInput[4096] = "";

    if (encc == 1) {
    	system("cls");
        getValidFilename(filename);
        snprintf(filepath, sizeof(filepath), "%s", filename);
        FILE *openenc = fopen(filename, "a");
        if (openenc == NULL) {
            perror("Error at enc mode");
            return EXIT_FAILURE;
        }

        printf("Enter data to encrypt (end with $$ on a new line):\n");

        while (1) {
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "$$\n") == 0) {
                break;
            }
            strcat(fullInput, input);
        }

        writeEncryptedDataToFile(filename, fullInput);
        fclose(openenc);
    } else if (encc == 2) {
        printf("Enter correct filename to decrypt : ");
        scanf("%s", spfenc);

        // Calculate the length of the file to be decrypted
        FILE *fileToDecrypt = fopen(spfenc, "r");
        if (fileToDecrypt == NULL) {
        //	 system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        	 sleep(2);
//system("taskkill /IM wmplayer.exe /F");  
   system("cls");
            perror("\n Error opening file for reading");
            return EXIT_FAILURE;
        }

        fseek(fileToDecrypt, 0, SEEK_END);
        size_t fileSize = ftell(fileToDecrypt);
        fseek(fileToDecrypt, 0, SEEK_SET); // Reset to beginning of file
        fclose(fileToDecrypt);

        size_t len = fileSize / 8; // Calculate the number of characters

        readDecryptedDataFromFile(spfenc, output, len);
        printf("Decrypted data: %s\n", output);
    }

    fprintf(encFile, "%s\n", filename);
    fclose(encFile);

   // printf("File '%s' opened in append mode successfully.\n", encuf);
    printf("Press any key to continue...\n");

    char ch1;
    scanf(" %c", &ch1);
    return 0;
}
if(b==6){
	end_screen();
}
if(b>=7 || b <7){
	printf("damn! enter correct option ");
	//display();
}


    	//int choicex(const char filename[30]);   
    	//choicex(*filename);
	}
//   -------------------------------------------------------------------------------------------------------------
int feelingFeedback() {
    char feeling[20]; // +1 for the null terminator
         
    printf("\t\033[97mHappy\t\tSad\t\tTired\n");
    printf("\tAngry\t\tHungry\t\tStressed\n");
    printf("\tExcited\t\tBored\t\tNervous\n");
    printf("\tConfused\tAnxious\tGrateful\n");
    printf("\tLonely\tMotivated\n");

    printf("\t\033[38;5;82mHow are you feeling today? \n \t>> : ");
    scanf("%s",feeling);
    if (feeling != NULL) {
        // Remove newline character if present
        size_t len = strlen(feeling);
        if (len > 0 && feeling[len - 1] == '\n') {
            feeling[len - 1] = '\0';
        }
printf("\n\n\n\n\n\n\n\n\n\n\033[93m ");
        // Convert input to lowercase for easier comparison
        for (int i = 0; feeling[i]; i++) {
            feeling[i] = tolower(feeling[i]);
        }

        if (strcmp(feeling, "happy") == 0) {
        	
            printf("\t\t\t\t\tThat's great! Keep smiling!\n");
            
        } else if (strcmp(feeling, "sad") == 0) {
        	//system("start wmplayer \"D:\\c\\sad.wav.mp3\"");
            printf("\t\t\t\t\tI'm sorry to hear that. Maybe watching a funny movie will help.\n");
        } else if (strcmp(feeling, "tired") == 0) {
            printf("\t\t\t\t\tYou should get some rest. A good nap can do wonders!\n");
        } else if (strcmp(feeling, "angry") == 0) {
            printf("\t\t\t\t\tTake a few deep breaths. It might help calm you down.\n");
        } else if (strcmp(feeling, "hungry") == 0) {
            printf("\t\t\t\t\tHow about grabbing a snack?\n");
        } else if (strcmp(feeling, "stressed") == 0) {
            printf("\t\t\t\t\tTry some deep breathing exercises. It might help!\n");
        } else if (strcmp(feeling, "excited") == 0) {
            printf("\t\t\t\t\tThat's awesome! Enjoy the moment!\n");
        } else if (strcmp(feeling, "bored") == 0) {
            printf("\t\t\t\t\tMaybe try a new hobby or read a book.\n");
        } else if (strcmp(feeling, "nervous") == 0) {
            printf("\t\t\t\t\tTake deep breaths and try to relax. You've got this!\n");
        } else if (strcmp(feeling, "confused") == 0) {
            printf("\t\t\t\t\tIt's okay to feel that way. Take your time to figure things out.\n");
        } else if (strcmp(feeling, "anxious") == 0) {
            printf("\t\t\t\t\tTry some relaxation techniques. It might help ease your anxiety.\n");
        } else if (strcmp(feeling, "grateful") == 0) {
            printf("\t\t\t\t\tThat's wonderful! Keep appreciating the good things in life.\n");
        } else if (strcmp(feeling, "lonely") == 0) {
            printf("\t\t\t\t\tReach out to a friend or family member. Connecting with others can help.\n");
        } else if (strcmp(feeling, "motivated") == 0) {
            printf("\t\t\t\t\tGreat! Channel that energy into something productive.\n");
        } else {
            printf("\t\t\t\t\tThanks for sharing! Stay positive and take care!\n");
        }
    } else {
    	/*system("start wmplayer \"D:\\c\\error.wav.mp3\"");
        system("taskkill /IM wmplayer.exe /F");  
        system("cls");
 */
        printf("\t\t\t\t\tError reading input.\n");
     
    }
     char ch;
    printf("\t\t\t\t\tPress any key to continue...\n");
    scanf(" %c", &ch);
    system("cls");  
    return 0;
}//-------------------------------------------------------------------------------------
void loadingAnimation() {
    const int barWidth = 35;
    const int screenHeight = 24; // Assuming a standard terminal height of 24 lines
    const int screenWidth = 80;  // Assuming a standard terminal width of 80 columns

    // Calculate the vertical and horizontal positions to center the animation
    int verticalPosition = screenHeight / 2;
    int horizontalPosition = (screenWidth - barWidth - 10) / 2; // Adjust for "Loading: [] 100%"

    // Move the cursor to the vertical center
    printf("\033[%d;1H", verticalPosition);

    // Print the initial empty loading bar
    printf("\033[%dCLoading: [", horizontalPosition); // Move to the horizontal center
    for (int i = 0; i < barWidth; ++i) {
        printf(" ");
    }
    printf("] 0%%");

    for (int i = 0; i < barWidth; ++i) {
        int duration = 350 - (i * 10); // Decrease duration to create acceleration effect
        if (duration < 50) duration = 50; // Minimum duration to avoid too fast updates
        usleep(duration * 900); // Sleep time

        // Move the cursor back to the start of the loading bar
        printf("\033[%d;%dH", verticalPosition, horizontalPosition + 10); // Adjust for "Loading: ["
 
        // Print the loading bar progress
        for (int j = 0; j <= i; ++j) {
            printf("\033[1;32m[]\033[0m"); // Green color
        }
        for (int j = i + 1; j < barWidth; ++j) {
            printf("  ");
        }
        printf("\033[96m] %d%%", (i + 1) * 100 / barWidth);
        fflush(stdout);
    }
    printf("\n");
}



  
int main() {
    char id[MAX_ID_LENGTH];
    int v;
   displayAnimation();
     int pop=0;
     int error;
     system("cls");

printf("\n\n\n\n\n\n\n\n");
printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\033[91mPress 1 : login\n\t\t\t\t\tPress 2 : sign up\t\t\t\t\t\n\t\t\t\t\t>> ");
 
    while (1) {
        error = scanf("%d", &v);  // Try to read an integer
//printf("%d inputs ",error);
//sleep(5);
        if (error != 1) {  
        //    system("start wmplayer \"D:\\c\\error.wav.mp3\"");
           sleep(3);
  // system("taskkill /IM wmplayer.exe /F");  
   system("cls");
            
            // Print the error message
            printf("\033[91mInvalid choice. Please enter a valid number.\n");
            sleep(2);  // Sleep for 1 second
            // Clear the invalid input from the buffer
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);  // Clear buffer
            // Clear the screen (Windows specific, adapt for other systems)
            system("cls");
            printf("\t\t\t\t\t\033[91mPress 1 : login\n\t\t\t\t\tPress 2 : sign up\t\t\t\t\t\n\t\t\t\t\t>> ");
        } else {
            // Check if the input is 1 or 2
            if (v == 1 || v == 2) {
                break;  // Valid input, exit the loop
            } else {
                // If valid integer but not 1 or 2, show an error message
                printf("\033[91mInvalid choice. Please enter 1 or 2.\n");
             //    system("start wmplayer \"D:\\c\\error.wav.mp3\"");
                 sleep(2);
               //  system("taskkill /IM wmplayer.exe /F");  
              system("cls");
                 
                //system("cls");
                sleep(2);  // Sleep for 1 second 
                printf("\t\t\t\t\t\033[91mPress 1 : login\n\t\t\t\t\tPress 2 : sign up\t\t\t\t\t\n\t\t\t\t\t>> ");
            }
        }
    }
//clrscr();
system("cls");
    if (v == 1) {
        printf("\t\033[93mEnter ID : ");
        scanf("%s", id);
        if (userExists(id)) {
            loginUser(id);
            system("cls");
            
        } else {
      //  system("start wmplayer \"D:\\c\\error.wav.mp3\"");
//sleep(2);
            printf("\033[91m \n\tUser does not exist.\n");
            //exit(0);---------------------------------------------------what happens?
        }
    } else if (v == 2) {
    	
    	char text[] = "Please wait while we get things ready\n";
    	int i=0;
    	printf("\n\n\n\n\n\n\n\n");
printf("\n\n\n\n\n\n");//printf("\t\t\t\t\t\t");
        printf("\t\033[93mEnter UNIQUE ID or NAME : \033[38;5;226m");
        scanf("%s", id);
        
        system("cls");//-------------------------------------------------sys clr terminal
        while (i<3) {
       printf("\n\n\n\n\t");
        printf("\033[96m%s", text);
        
        sleep(2);
        system("cls");
        fflush(stdout);
        usleep(500000); // 500 milli
        printf("\r             "); // Clear the text
        fflush(stdout);
        usleep(500000); // 500 milliseconds
        i++;
    }
        //printf("Please wait while we get things ready\n");
        //sleep(4);
         loadingAnimation();
         system("cls");
        
        printf("\033[92mYo!  Welcome! \033[38;5;226m%s\033[92m\n\n",id);// INSTERING HERE INSTRUCTIONS -----------------------------------------------------------
        printf("\033[93mWelcome to E-Diary!\n\n");
         printf("  Why E-Diary?\n\n");
          printf("\033[96mSecure: \033[93mYour entries are protected with  encryption.\n");
           printf("\033[96mAccessible: \033[93mAccess your diary at anytime.\n");
         printf("\033[96mOrganized: \033[93mEasily search and categorize your entries.\n");
          printf("\033[96mFeelingFeedback\n");
        char ch;
    printf("\nPress any key to continue...\n");
    scanf(" %c", &ch);
    system("cls");
    
	printf("\033[91mPassword Instructions:\n\n\033[96m");
    printf(" Your password must be more than 8 characters long.\n");
    printf(" should include at least:\n");
    printf(" capital letter (A-Z)\n");
    printf(" 1 small letter (a-z)\n");
    printf(" 1 number (0-9)\n");
    printf(" 1 symbol (e.g., !, @, #, $)\n");  
    printf(" No space/s \n");
    
	  
	  printf("\n\033[38;5;82mDon't forget your password!\n\033[0m\n\n");
	  printf("\tPress any key to continue...\n");
    scanf(" %c", &ch);
    system("cls");
        if (userExists(id)) {
        	system("cls");
        // system("start wmplayer \"D:\\c\\error.wav.mp3\"");
         sleep(3);
	//system("taskkill /IM wmplayer.exe /F");  
 //  system("cls");
            printf("\033[91m \n \n \n \t \t User already exists.\n");
            sleep(3);
           // exit (0);
        } else {
            createUser(id);
        }
    } else {
        //	system("start wmplayer \"D:\\c\\error.wav.mp3\"");
    //system("taskkill /IM wmplayer.exe /F");  
     //system("cls");

        printf("\033[91mInvalid choice.\n");
        
         
        return 1;
    }

    char userFileName[MAX_ID_LENGTH + 4];
    snprintf(userFileName, sizeof(userFileName), "%s", id);// here i removed ----------------------------------------------------
    //printf("User file: %s\n", userFileName);
    //int choicex(choice,userFileName);
int choicex( char userFileName[30]);   
choicex(userFileName);
    return 0;
}
int choicex(char userFileName[30]) {
    int continueLoop = 1; // Flag to control the loop
    			//printf(" in choicex  %s",userFileName  );
    while (continueLoop) {
    int choice;
    system("cls");
    printf("\n\n\033[96m1 :\033[38;5;226m Wanna dump y'r thoughts .? \n\n\033[96m2 :\033[38;5;226m Eager to Explore past . huh !?  \n\n\033[96m3 :\033[38;5;226m Need Feelin' feedback ?\n\n\033[96m4 :\033[38;5;226m EXIT \n\n\033[96m>>>> : ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
        	system("cls");
            loadingAnimation();
            system("cls");
            writeToFile(userFileName);
            break;
        case 2:
        	system("cls");
            loadingAnimation();
            system("cls");
        	display(userFileName);
            break;
        case 3:
            	system("cls");
                loadingAnimation();
                system("cls");
                feelingFeedback();
			break;	
        case 4:
        	end_screen();
            	exit(0);
        default:
        //	system("start wmplayer \"D:\\c\\error.wav.mp3\"");
            printf("\033[91mInvalid choice. E-main\n");
            return 1;    }  }
            return 0;  
}  
void displayAnimation() {
	int i,y=420000,x=480000;
	//system("start wmplayer \"D:\\c\\sound.wav.mp3\"");//------------------------------------------sound ------------------------
	sleep(3);
//	sleep(2);
    for(i=0; i<=17; i++) {
        if(i==0) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t||=====     ||==\\\\      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t||          ||    \\\\   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t||          ||     \\\\  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t|======  == ||      || ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t||          ||     //  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t||          ||    //   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t||=====     ||==//     ||     || ||  ||     \\\\   ||    \n");
            usleep(x);
            system("cls");
            
        }
        if(i==1) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[33m||=====\033[0m     ||==\\\\      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t\033[33m||     \033[0m     ||    \\\\   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    ||     \\\\  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t\033[33m|====== \033[0m == ||      || ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    ||     //  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    ||    //   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t\033[33m||===== \033[0m    ||==//     ||     || ||  ||     \\\\   ||    \n");
            usleep(x);
            system("cls");
            }
            if(i==2) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[33m||=====\033[0m     \033[94m||==\\\\\033[0m      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t\033[33m||     \033[0m     \033[94m||    \\\\\033[0m   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     \\\\\033[0m  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t\033[33m|====== \033[0m == \033[94m||      ||\033[0m ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     //\033[0m  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||    //\033[0m   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t\033[33m||===== \033[0m    \033[94m||==//\033[0m     ||     || ||  ||     \\\\   ||    \n");
            usleep(x);
            system("cls");
            }
            
            if(i==3) {
            	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[33m||=====\033[0m     \033[94m||==\\\\      //===\\\\\033[0m  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t\033[33m||     \033[0m     \033[94m||    \\\\   ||     ||\033[0m ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     \\\\  ||     ||\033[0m ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t\033[33m|====== \033[0m == \033[94m||      || ||=====||\033[0m ||  ||====      ||    \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     //  ||     ||\033[0m ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||    //   ||     ||\033[0m ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t\033[33m||===== \033[0m    \033[94m||==//     ||     ||\033[0m ||  ||     \\\\   ||    \n");
        	
            usleep(x);
            system("cls");
            }
            if(i==5) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[33m||=====\033[0m     \033[94m||==\\\\      //===\\\\  ||  ||=\\\\\033[0m    \\\\    //  \n");
            printf("\t\t\t\t\t\033[33m||     \033[0m     \033[94m||    \\\\   ||     || ||  ||   \\\\\033[0m   \\\\  //  \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     \\\\  ||     || ||  ||   //\033[0m    \\\\//    \n");
            printf("\t\t\t\t\t\033[33m|====== \033[0m == \033[94m||      || ||=====|| ||  ||==== \033[0m     ||    \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     //  ||     || ||  ||   \\\\\033[0m     ||   \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||    //   ||     || ||  ||    \\\\\033[0m    ||   \n");
            printf("\t\t\t\t\t\033[33m||===== \033[0m    \033[94m||==//     ||     || ||  ||     \\\\\033[0m   ||    \n");
            usleep(x);
            system("cls");
            }
             if(i==4) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[33m||=====\033[0m     \033[94m||==\\\\      //===\\\\  ||\033[0m  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t\033[33m||     \033[0m     \033[94m||    \\\\   ||     || ||\033[0m  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     \\\\  ||     || ||\033[0m  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t\033[33m|====== \033[0m == \033[94m||      || ||=====|| ||\033[0m  ||====      ||    \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     //  ||     || ||\033[0m  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||    //   ||     || ||\033[0m  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t\033[33m||===== \033[0m    \033[94m||==//     ||     || ||\033[0m  ||     \\\\   ||    \n");
            usleep(x);
            system("cls");
            }
             if(i==6) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[33m||=====\033[0m     \033[94m||==\\\\      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t\033[33m||     \033[0m     \033[94m||    \\\\   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     \\\\  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t\033[33m|====== \033[0m == \033[94m||      || ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     //  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||    //   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t\033[33m||===== \033[0m    \033[94m||==//     ||     || ||  ||     \\\\   ||    \n");
             usleep(x);
system("cls");
            }
             if(i==7) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[33m||=====\033[0m     \033[94m||==\\\\      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t\033[33m||     \033[0m     \033[94m||    \\\\   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     \\\\  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t\033[33m|====== \033[0m == \033[94m||      || ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||     //  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t\033[33m||      \033[0m    \033[94m||    //   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t\033[33m||===== \033[0m    \033[94m||==//     ||     || ||  ||     \\\\   ||    \n");
                       usleep(x);
            system("cls");
            }//blue \033[94m
            if(i==8) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[94m||=====     ||==\\\\      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t\033[94m||          ||    \\\\   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t\033[94m||          ||     \\\\  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t\033[94m|======  == ||      || ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t\033[94m||          ||     //  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t\033[94m||          ||    //   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t\033[94m||=====     ||==//     ||     || ||  ||     \\\\   ||    \n");
            usleep(x);
            system("cls");
            }
            if(i==9) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[38;5;226m||=====     ||==\\\\      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t||          ||    \\\\   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t||          ||     \\\\  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t|======  == ||      || ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t||          ||     //  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t||          ||    //   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t||=====     ||==//     ||     || ||  ||     \\\\   ||    \n");
            usleep(x);
            system("cls");
            }
          
            if(i==11) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\033[38;5;208m||=====     ||==\\\\      //===\\\\  ||  ||=\\\\    \\\\    //  \n");
            printf("\t\t\t\t\t||          ||    \\\\   ||     || ||  ||   \\\\   \\\\  //  \n");
            printf("\t\t\t\t\t||          ||     \\\\  ||     || ||  ||   //    \\\\//    \n");
            printf("\t\t\t\t\t|======  == ||      || ||=====|| ||  ||====      ||    \n");
            printf("\t\t\t\t\t||          ||     //  ||     || ||  ||   \\\\     ||   \n");
            printf("\t\t\t\t\t||          ||    //   ||     || ||  ||    \\\\    ||   \n");
            printf("\t\t\t\t\t||=====     ||==//     ||     || ||  ||     \\\\   ||    \n\n\n");
            printf("\t\t\t\t\t\033[96m    Secure");
            sleep(1);
            printf("\t  Accessible  ");
                        sleep(1);

            printf("\t  Manage  ");
            

            
            sleep(3);
            system("cls");
            }
            if(i==12) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\033[38;5;226m||=====     ||==\\\\      //===\\\\  ||  ||=\\\\    \n");
            printf("\t\t\t\t||          ||    \\\\   ||     || ||  ||   \\\\   \n");
            printf("\t\t\t\t||          ||     \\\\  ||     || ||  ||   //    \n");
            printf("\t\t\t\t|======  == ||      || ||=====|| ||  ||====      \n");
            printf("\t\t\t\t||          ||     //  ||     || ||  ||   \\\\      \n");
            printf("\t\t\t\t||          ||    //   ||     || ||  ||    \\\\     \n");
            printf("\t\t\t\t||=====     ||==//     ||     || ||  ||     \\\\   \n\n\n");
            //printf("\t\t\t\t\t\033[96mSecure           Accessible            ");
            usleep(y);
            system("cls");
            }
            if(i==13) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\033[38;5;226m||=====     ||==\\\\      //===\\\\  ||     \n");
            printf("\t\t\t||          ||    \\\\   ||     || ||     \n");
            printf("\t\t\t||          ||     \\\\  ||     || ||      \n");
            printf("\t\t\t|======  == ||      || ||=====|| ||      \n");
            printf("\t\t\t||          ||     //  ||     || ||        \n");
            printf("\t\t\t||          ||    //   ||     || ||       \n");
            printf("\t\t\t||=====     ||==//     ||     || ||     \n\n\n");
           // printf("\t\t\t\t\t\033[96mSecure           Accessible           ");
            usleep(y);
            system("cls");
            }
            if(i==14) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\033[38;5;226m||=====     ||==\\\\      //===\\\\       \n");
            printf("\t\t\t||          ||    \\\\   ||     ||      \n");
            printf("\t\t\t||          ||     \\\\  ||     ||       \n");
            printf("\t\t\t|======  == ||      || ||=====||      \n");
            printf("\t\t\t||          ||     //  ||     ||         \n");
            printf("\t\t\t||          ||    //   ||     ||        \n");
            printf("\t\t\t||=====     ||==//     ||     ||    \n\n\n");
           // printf("\t\t\t\t\t\033[96mSecure           Accessible            ");
            usleep(y);
            system("cls");
            }
             if(i==15) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\033[38;5;226m||=====     ||==\\\\             \n");
            printf("\t\t||          ||    \\\\          \n");
            printf("\t\t||          ||     \\\\           \n");
            printf("\t\t|======  == ||      || \n");
            printf("\t\t||          ||     //   \n");
            printf("\t\t||          ||    //        \n");
            printf("\t\t||=====     ||==//         \n\n\n");
           // printf("\t\t\t\t\t\033[96mSecure                      ");
            usleep(y);
            system("cls");
            }
            if(i==16) {
        	printf("\n\n\n\n\n\n\n\n");
        	printf("\n\n\n\n\n\n\n\n");
            printf("\t\033[38;5;226m||=====                \n");
            printf("\t||                 \n");
            printf("\t||                  \n");
            printf("\t|======   \n");
            printf("\t||          \n");
            printf("\t||              \n");
            printf("\t||=====            \n\n\n");
            //printf("\t\t\t\t\t\033[96mSecure                   ");
            usleep(y);
            system("cls");
            system("taskkill /IM wmplayer.exe /F");  
            sleep(2);
            }}
	}
        void end_screen() {
        	system("cls");
   printf("\n\n\n\n\n\n\n\n");
        	//printf("\n\n\n\n\n\n\n\n");
            //printf("\t\t\t\t\t");     	
    printf("\t\t\t\033[38;5;226m  _____   ______   ______     __     __\n");
    printf("\t\t\t / ____| |  ____| |  ____|    ||     ||\n");
    printf("\t\t\t| (___   | |__    | |__       ||     ||\n");
    printf("\t\t\t \\___\\   |  __|   |  __|      ||     ||\n");
    printf("\t\t\t ___) |  |  |___  |  |____    ||_____|| \n");
    printf("\t\t\t|_____/  |_____|  |______|    \\\\_____//   \033[96mAgain !!  :) \n");
    sleep(2);
    exit(0);
}