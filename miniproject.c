//The objectives of this program are as follows:

/*  Create a Music Playlist Using Circular Linked List:
	1.Implement a circular doubly linked list to store and manage a playlist of songs.
	2.Maintain connections between songs such that traversing the list in both forward and backward directions is possible.
	3.Add Songs to the Playlist:
	4.Allow the user to input details for new songs, including the song name, artist name, duration (in minutes and seconds), and lyrics.
	5.Dynamically allocate memory for new songs and add them to the playlist.
	6.Delete Songs from the Playlist:

	Use circular doubly linked lists as a data structure to showcase dynamic memory allocation, traversal, and manipulation of nodes.*/
	//First Project in C

// PROGRAM -------------------------------------------------MUSIC PLAYLIST USING LINKED LISTS-----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct cll {
    char name[50];
    char artist[20];
    int durationinmin;
    int durationinsec;
    char lyrics[10000];
    struct cll *lptr;
    struct cll *rptr;
};

typedef struct cll node;
node *dummy = NULL;
node *displaying = NULL;
char playlistname[20];

void insertsong() {
    node *newnode = (node *)malloc(sizeof(node));
    printf("Enter the name of song: ");
    scanf(" %[^\n]%*c", newnode->name);
    printf("Enter the artist name: ");
    scanf( " %[^\n]%*c", newnode->artist);
    printf("Enter the duration of the song (minutes): ");
    int min, sec;



    scanf("%d", &min);
    getchar();
    printf("Enter the duration of the song (seconds): ");
    scanf("%d", &sec);
    getchar();
    while (sec >= 60) {
    	sec -= 60;
    	min += 1;
 	}

    newnode->durationinmin = min;
    newnode->durationinsec = sec;
    newnode->lyrics[0] = '\0';

    printf("Enter the lyrics of the song and end it with a new line:\n");
    char singleline[1024];
    while (1) {
        fgets(singleline, 1024, stdin);
        if (strcmp(singleline, "\n") == 0) {
               break;
        }
        singleline[strcspn(singleline, "\n")] = '\0';
        strcat(newnode->lyrics, singleline);
        strcat(newnode->lyrics, "\n");
    }
    if (dummy->rptr == NULL) {
           dummy->rptr = newnode;
           newnode->lptr = dummy;
           newnode->rptr = dummy;
           dummy->lptr = newnode;
           dummy->durationinmin++;
           return;
       }
       node *last = dummy->lptr;
       last->rptr = newnode;
       newnode->lptr = last;
       newnode->rptr = dummy;
       dummy->lptr = newnode;
       dummy->durationinmin++;
   }



void deletesong() {
    if (dummy->rptr == NULL) {
        printf("No songs in the PlayList %s to delete\n", playlistname);
        return;
    }

    char songname[50];
    printf("Enter the name of the song to delete from %s: ", playlistname);
    getchar();
    fgets(songname, sizeof(songname), stdin);
    songname[strcspn(songname, "\n")] = '\0';

    if (dummy->durationinmin == 1 && strcmp(dummy->rptr->name, songname) == 0) {
        node *temp = dummy->rptr;
        printf("Deleted song: Artist: %s, Song: %s, Duration: %d:%d\n",
               temp->artist, temp->name, temp->durationinmin, temp->durationinsec);

        dummy->rptr = NULL;
        dummy->lptr = NULL;
        displaying = NULL;
        free(temp);
        dummy->durationinmin--;
        return;
    }

    node *temp = dummy->rptr;
    while (temp != dummy) {
        if (strcmp(temp->name, songname) == 0) {
            printf("Deleted song: Artist: %s, Song: %s, Duration: %d:%d\n",
                   temp->artist, temp->name, temp->durationinmin, temp->durationinsec);
            node *prev = temp->lptr;
            node *next = temp->rptr;
            prev->rptr = next;
            next->lptr = prev;
            if (displaying == temp) {
                if (next != dummy) {
                    displaying = next;
                } else if (prev != dummy) {
                    displaying = prev;
                } else {
                    displaying = NULL;
                }
            }

            free(temp);
            dummy->durationinmin--;
            return;
        }
        temp = temp->rptr;
    }

    printf("Song with the name '%s' not found in %s.\n", songname, playlistname);
}

void display() {
    if (dummy->rptr == NULL) {
        printf("No songs in the PlayList %s. Insert songs using option 1.\n",playlistname);
        return;
    }

    node *temp = dummy->rptr;
    do {
        printf("Artist: %s\nSong: %s\nDuration: %d:%d\n",
               temp->artist, temp->name, temp->durationinmin, temp->durationinsec);
        temp = temp->rptr;
    } while (temp != dummy);
}

int displaylyrics() {
    if (dummy->rptr == NULL) {
        printf("No songs in the PlayList.\n");
        return 100;
    }
    while (getchar() != '\n');
    char songname[50];
    printf("Enter the name of the song you want to listen:\n ");
    fgets(songname, sizeof(songname), stdin);
    songname[strcspn(songname, "\n")] = '\0';

    node *temp = dummy->rptr;
    while (temp != dummy) {
        if (strcmp(temp->name, songname) == 0) {
        	displaying = temp;
        	printf("Artist: %s, Song: %s, Duration: %d:%d\n",
        	               temp->artist, temp->name, temp->durationinmin, temp->durationinsec);
            printf("Lyrics for '%s':\n%s\n", temp->name, temp->lyrics);
            return 0;
        }
        temp = temp->rptr;
    }

    printf("Song with the name '%s' not found in %s.\n", songname,playlistname);
    return -1;
}
void displaylyrics2(int choice) {
    if (dummy->rptr == NULL || displaying == NULL) {
        printf("No songs in the PlayList %s to play next or previous\n",playlistname);
        return;
    }

    if(choice == 5){
    	if(displaying->rptr==dummy){
    		displaying = dummy->rptr;
    	}
    	else{
    		displaying = displaying->rptr;
    	}
    	printf("Artist: %s, Song: %s, Duration: %d:%d\n",
    	        	               displaying->artist, displaying->name, displaying->durationinmin, displaying->durationinsec);
    	printf("Lyrics for '%s':\n%s\n", displaying->name, displaying->lyrics);
    }
    if(choice==6){
    	if(displaying->lptr==dummy){
    	    	displaying = dummy->lptr;
    	    }
    	    else{
    	    	displaying = displaying->lptr;
    	    }
    	    printf("Artist: %s, Song: %s, Duration: %d:%d\n",
    	    	        	               displaying->artist, displaying->name, displaying->durationinmin, displaying->durationinsec);
    	    printf("Lyrics for '%s':\n%s\n", displaying->name, displaying->lyrics);
    }


}

int validate_and_play_song() {
	if(dummy->rptr==NULL) return 9;
    int output;
    do {
        output = displaylyrics();
        if (output == -1 && dummy->durationinmin != 0) {
            printf("WRONG TRY!! Enter a correct song to play now\n");
        }
    } while (output == -1 && dummy->durationinmin != 0);

    return output;
}

int main() {
    dummy = (node *)malloc(sizeof(node));
    dummy->rptr = NULL;
    dummy->lptr = NULL;
    dummy->durationinmin = 0;
    printf("Hello, This is a mini project to demonstrate the use of Linked Lists in a Music Playlist\n");
    printf("What do you want the name of your PlayList to be?\n");
    printf("-");

    fgets(playlistname, sizeof(playlistname), stdin);
    playlistname[strcspn(playlistname, "\n")] = '\0';
    printf("Enter the number of songs you want to add to %s:\n",playlistname);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        insertsong();
    }

    validate_and_play_song();

    while (1) {
    	if (dummy->rptr == NULL) {
    	    printf("The PlayList is now empty. Add new songs using option 1.\n");
    	    displaying = NULL;

    	}

        printf("\n*********************************************\n");
        printf("\nEnter:1. Insert a song into the PlayList"
               "\nEnter 2. Delete a song from the PlayList\n"
               "Enter 3. Display all songs\n"
               "Enter 4. Display lyrics of a specific song"
               "\nEnter 5. Play the next song\n"
               "Enter 6. Play the previous song\n"
               "Any other number to exit\n");
        if(dummy->rptr!=NULL){
        	node *temp = dummy->rptr;
        	        int found = -1;
        	        while (temp != dummy) {
        	            if (strcmp(temp->name, displaying->name) == 0) {
        	                found = 0;
        	                break;
        	            }
        	            temp = temp->rptr;
        	        }

        	        if (found != 0) {

        	            printf("The song playing was deleted.\n");
        	            int up = validate_and_play_song();
        	            if(up==9){
        	            	continue;
        	            }
        	        }


        	        printf("The current song playing is: %s\n", displaying->name);
        	        printf("*********************************************\n");

        }
        printf("\n");
        int flagg = 0;
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:

            	if(dummy->rptr==NULL){
            		flagg = 1;
            	}
            	insertsong();
            	if(flagg==1){
            		displaying = dummy->rptr;
            	}
                break;
            case 2:
                deletesong();
                break;
            case 3:
                printf("\nThe number of songs present in the %s are: %d\n", playlistname, dummy->durationinmin);
                display();
                break;
            case 4:
                displaylyrics();
                break;
            case 5:
                displaylyrics2(5);
                break;
            case 6:
                displaylyrics2(6);
                break;
            default:
                printf("PlayList %s deleted\n", playlistname);
                printf("Thank you for using our PlayList manager.\n");
                exit(0);
        }
    }

    return 0;
}
