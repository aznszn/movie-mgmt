#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int ynmenu(char[]);
void adminmenu();
void addmovie();
void login();
void sugg();
void moviesuggest();
void ratemovie();
void usermenu();
void showratings();
void SearchByDirector();
void SearchYear();
int logout=0;
char CurrentUser[50];

int main()
{
    while(1){
    	logout=0;
    	login();
    }
    return 0;
}

void login()
{
	system("cls");
	int i=0,j=1,flag=0,c,unum=0;
	char dir[100];
	char pass[100];
	char chkpass[100];
	FILE *unames;
	FILE *ratings;
	FILE *passwords;
	unames=fopen("users.txt","r");
	fflush(stdin);
	printf("\n\n\n\t\t\t\t    Welcome to the movie database\n\n\n\n\t\t\t\t\tUsername: ");
	gets(CurrentUser);


	while(i!=EOF){
		i=getc(unames);
		for(j=0;*(CurrentUser+j)!='\0' && (char)i==*(CurrentUser+j);j++, i=getc(unames))
			;
		if(j>0&&CurrentUser[j]=='\0'&&i==';'){
			flag=1;
			break;
		}
		else{
			unum++;
			while(1){
				if((char)i==';'||i==EOF)
					break;
				i=getc(unames);
				}
			i=getc(unames);
		}
	}

	if(!flag){
		printf("\n\t\t\tuser not found\n");
		if(ynmenu("\n\n\n\t\t\tUser not found!\n\n\n\t\t\tWould you like to create a new user account?")){
			fclose(unames);
			unames=fopen("users.txt","a");
			
			fprintf(unames,"\n%s;",CurrentUser);
			sprintf(dir,"%s.txt",CurrentUser);
			ratings=fopen(dir,"w");
			
			printf("\n\t\t\tSet a password: ");
			fflush(stdin);
			gets(pass);
			
			passwords=fopen("passwords.txt","a");
			fprintf(passwords,"\n%s;",pass);
			
			fclose(passwords);
			fclose(unames);
			fclose(ratings);
		}
		else
			fclose(unames);
	}

	else{
		printf("\n\t\t\t\t\tPassword: ");

		fflush(stdin);
		gets(pass);
		fflush(stdin);
		passwords=fopen("passwords.txt","r");

		fflush(stdin);
		for(i=0,j=1;i!=unum;i++){
			while(j!=';')
				j=getc(passwords);
			j=getc(passwords);
		}
		
		j=0;
		i=0;
		while(j!=';'){
			j=getc(passwords);
			if(j!=';')
				chkpass[i++]=j;
		}
		chkpass[i]='\0';

		if(strcmp(pass,chkpass))
			flag=-1;

		if(flag==1){
			if(!strcmp("admin",CurrentUser))
				while(!logout){
					fclose(unames);
					adminmenu();
				}
			else
				while(!logout){
					fclose(unames);
					usermenu();
				}
		}
	}

	if(flag==-1){
		printf("\n\n\t\t\t\t\aIncorrect password\n\t\t\t\tPress any key to continue...");
		getch();
		flag=0;
		fflush(stdin);
		fclose(unames);
		rewind(passwords);
		fclose(passwords);
	}
}

void adminmenu()
{
    char x[4]={"    "},y='>';
    int opt=0;
    int cpos=0,c;
    x[0]=y;

    while (opt!=13){
        system("cls");
        printf("\n\n\n\n");
        printf("\t\t\t\t\t%c%c ",x[0],x[0]);
        printf("ADD a Movie\n\n");
        printf("\t\t\t\t\t%c%c ",x[1],x[1]);
        printf("VIEW Suggestions by users\n\n");
        printf("\t\t\t\t\t%c%c ",x[2],x[2]);
        printf("LOGOUT\n\n");
       
	    opt=_getch();
        if (opt== 0 || opt==224){
        	opt=_getch();
         	if (opt==72){
            	if (cpos==0)
                	cpos=3;
            	cpos--;
            	for (c=0;c<3;c++)
                	x[c]=' ';
            	x[cpos]=y;
            	printf("%c",opt);
        	}
        	else if (opt==80){
            	if (cpos==2)
                	cpos=-1;
            	cpos++;
            	for (c=0;c<3;c++)
                	x[c]=' ';
           		x[cpos]=y;
        	}
        }
    }
        switch (cpos){
            case 0:
                addmovie();
                break;
            case 1:
                sugg();
                break;
            case 2:
                logout=1;
                system("cls");
                printf("\n\n\n\n\t\t\t\t\tYou have been successfully logged out!\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tPress any key");
                getchar();
                break;
        }
}

void usermenu()
{

	char x[6]={"      "},y='>';
    int opt;
    int cpos=0,c;
    x[0]=y;

    while (1){
        system("cls");
        printf("\n\n\n\n");
        printf("\t\t\t\t\t%c%c ",x[0],x[0]);
        printf("See your movie ratings\n\n");
        printf("\t\t\t\t\t%c%c ",x[1],x[1]);
        printf("Search Director\n\n");
        printf("\t\t\t\t\t%c%c ",x[2],x[2]);
        printf("Search movie\n\n");
        printf("\t\t\t\t\t%c%c ",x[3],x[3]);
        printf("Suggest adding movie\n\n");
        printf("\t\t\t\t\t%c%c ",x[4],x[4]);
        printf("Search movie by year\n\n");
        printf("\t\t\t\t\t%c%c ",x[5],x[5]);
        printf("Logout\n\n");

        opt=_getch();

        if (opt== 0 || opt==224){
        	opt=_getch();
         	if (opt==72){
            	if (cpos==0)
               		cpos=6;
            	cpos--;
            	for (c=0;c<6;c++)
                	x[c]=' ';
            	x[cpos]=y;
        	}
        	else if (opt==80){
            	if (cpos==5)
                	cpos=-1;
            	cpos=cpos+1;
            	for (c=0;c<6;c++)
                	x[c]=' ';
            	x[cpos]=y;
        	}
        }
        else if (opt==13)
            break;
    }
    
    switch (cpos){
        case 0:
            system("cls");
            showratings();
            break;
        case 1:
            SearchByDirector();
            break;
        case 2:
            ratemovie();
            break;
        case 3:
            moviesuggest();
            break;
        case 4:
        	SearchYear();
        	break;
            case 5:
            logout=1;
            system("cls");
            printf("\n\n\n\n\t\t\t\t\tYou have been successfully logged out!\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tPress any key");
            getchar();
    }
}

void addmovie()
{
    FILE *moviedetailsptr;
    FILE *movfptr;

    char name[50],rtime[50],director[50],cast[150];
    char filename[30];
    int year,irating,rtrating;

    system("cls");

    fflush(stdin);

    printf("\n\n\nMovie Name: ");
    gets(name);

    printf("\n\nYear: ");
    scanf("%d",&year);
    getchar();

    printf("\n\nRuntime: ");
    scanf("%[^\n]",rtime);
    getchar();

    printf("\n\nDirector: ");
    scanf("%[^\n]",director);
    getchar();

    printf("\n\nCast: ");
    scanf("%[^\n]",cast);

    printf("\n\nIMDb Rating: ");
    scanf("%d",&irating);
    while ((irating <0) || (irating>10)){
        printf("\nERROR! Please enter a valid value between 1 and 10\n");
        scanf("%d",&irating);
    }
	fflush(stdin);
    printf("\n\nRotten Tomatoes Rating: ");
    scanf("%d",&rtrating);

    while ((rtrating <0) || (rtrating>100)){
        printf("\nERROR! Please enter a valid value between 1 and 100\n");
        scanf("%d",&rtrating);
    }

    movfptr=fopen("movies.txt","a");
    fprintf(movfptr,"%s;\n",name);
    fclose(movfptr);

    moviedetailsptr=fopen("MovieDetails.txt","a");
    fprintf(moviedetailsptr,"Year: %d\n",year);
    fprintf(moviedetailsptr,"Runtime: %s\n",rtime);
    fprintf(moviedetailsptr,"Director: %s\n",director);
    fprintf(moviedetailsptr,"Cast: %s\n",cast);
    fprintf(moviedetailsptr,"IMDb Rating: %d/10\n",irating);
    fprintf(moviedetailsptr,"Rotten Tomatoes Rating: %d",rtrating);
    fprintf(moviedetailsptr,"\%");
    fprintf(moviedetailsptr,"\n\\");
    fprintf(moviedetailsptr,"\n");
    fclose(moviedetailsptr);
}

void sugg()
{
	FILE *suggesstionfptr;
	int c;
	char line[250];
	suggesstionfptr=fopen("suggessions.txt","r");
	system("cls");
    printf("\n\nMovies suggessted by users are:\n");
	while (c!=EOF){
		c=getc(suggesstionfptr);
		printf("%c",c);
	}
	getchar();
	fclose(suggesstionfptr);
}



void moviesuggest()
{
	FILE *fptr;
	char suggesstionname[50];
	system("cls");
	printf("\n\nEnter the name of a movie to suggest: ");
	fflush(stdin);
	gets(suggesstionname);
	printf("\n\n    Thankyou for your suggession");
	getchar();
	fptr=fopen("suggessions.txt","a");

    fputs(suggesstionname,fptr);
    fputs("\n",fptr);
    fclose(fptr);
}

void ratemovie()
{
	system("cls");
	int c,i=0,j=0,fnum=0,flag=0,aflag,num=0,rating,PriorRating;
	float avg;
	float new_avg;
	char movie[50];
	char dir[100];
	char c_rating[3];
	char c_avg[4];
	FILE *movies;
	FILE *UserFile;
	FILE *MovieDetails;
	FILE *averages;
	sprintf(dir,"%s.txt",CurrentUser);
	UserFile=fopen(dir,"r+");
	movies=fopen("movies.txt","r");
	MovieDetails=fopen("MovieDetails.txt","r");

	printf("Enter movie name to search: ");
	fflush(stdin);
	gets(movie);

	fflush(stdin);

	//matches entered movie name with the movies in the list

	while(i!=EOF){
		i=getc(movies);
		for(j=0;*(movie+j)!='\0' && (char)i==*(movie+j);j++, i=getc(movies))
			;

		if(j>0&&((*(movie+j))=='\0')&&(i==';')){
			flag=1;
			break;
		}

		else{
			fnum++;
			while(1){
				i=getc(movies);
				if((char)i==';'||i==EOF)
					break;
				}
			i=getc(movies);
		}
	}

	i=0;

	if(flag==1){
		printf("\nMovie found in database\n");

		for(i=0;i!=fnum;i++,j=getc(MovieDetails))
			while(j!='\\')
				j=getc(MovieDetails);

		i=getc(MovieDetails);
		printf("\nTitle: %s\n",movie);
		while(i!=EOF){
			printf("%c",i);
			i=getc(MovieDetails);
			if(i=='\\')
				break;
		}

		i=0;
		flag=0;
		fnum=0;
		
		averages=fopen("averages.txt","r+");
		while(i!=EOF){
			i=getc(averages);
			for(j=0;*(movie+j)!='\0' && (char)i==*(movie+j);j++, i=getc(averages))
				;

			if(j>0&&((*(movie+j))=='\0')&&(i==':')){
				aflag=1;
				break;
			}

			else{
				while(1){
					i=getc(averages);
					if((char)i=='/'||i==EOF)
						break;
					}
				i=getc(averages);
			}
		}

		if(aflag==1){
			for(i=0,j=0;i<4;i++){
				j=getc(averages);
				c_avg[i]=j;
				}
			j=getc(averages);
			j=getc(averages);
			while(isdigit(j)){
				num=num*10+(j-'0');
				j=getc(averages);
			}
			fseek(averages,-1,SEEK_CUR);
			avg=atof(c_avg);
			printf("Average Rating by users on this database: %.1f, based on %d rating(s)\n",avg,num);
		}


		//Movie found in database now check if its in already rated by user
		while(i!=EOF){
			i=getc(UserFile);
			for(j=0;*(movie+j)!='\0' && (char)i == *(movie+j);j++, i=getc(UserFile))
				;

			if(j>0&&((*(movie+j))=='\0')&&(i==':')){
				flag=1;
				break;
			}

			else{
				fnum++;
				while(1){
					i=getc(UserFile);
					if((char)i=='\n'||i==EOF)
						break;
					}
			}
		}
		
		if(flag==1){
			//if movie was found in user file

			for(i=0;i<=fnum;i++)
				fscanf(UserFile,"%d",&PriorRating);
				//gets movie ratings from user file till it gets to where the movie was found in the user ratings

			printf("Your rating: %d\n",PriorRating);	//display previous rating
            getchar();
			if(ynmenu("\n\n\t\t\tDo you wish to update your rating?")){
				printf("\nEnter Rating in intgers between 1 and 10: ");
				while(1){
					scanf("%d",&rating);
					
					if(rating<0||rating>10)
						printf("\nPlease enter only integers between 1 and 10\nEnter again: ");
					
					else{
						itoa(rating,c_rating,10);
						fseek(UserFile,-2,SEEK_CUR);
						i=0;
						if(rating<10)
							fputc('0',UserFile);
						fputs(c_rating,UserFile);

						if(aflag==1){
							new_avg=((avg*num)-PriorRating+rating)/num;
							j=getc(averages);
							fseek(averages,-7,SEEK_CUR);
							if(new_avg<10)
								fputc('0',averages);
							fprintf(averages,"%.1f;%d",new_avg,num);
						}
						fclose(averages);
						fclose(UserFile);
						fclose(movies);
						fclose(MovieDetails);
						fflush(stdin);
						break;
					}
				}
			}
			else{
				fclose(averages);
				fclose(UserFile);
				fclose(movies);
				fclose(MovieDetails);
				fflush(stdin);
			}
		}

		else{
			getchar();
			//printf("\n\nYou have not rated this movie, Do you wish to do so?");
			if(ynmenu("\n\n\t\t\tYou have not rated this movie, Do you wish to do so?")){
				while(1){
					printf("\nEnter rating: ");
					scanf("%d",&rating);
					if(rating<0||rating>10)
						printf("\nPlease enter rating between 1 and 10\nEnter rating again: ");
					else{
						fclose(UserFile);
						sprintf(dir,"%s.txt",CurrentUser);
						UserFile=fopen(dir,"a");
						fprintf(UserFile,"%s:%02d;\n",movie,rating);
						if(aflag==1){
							new_avg=((avg*num)+rating)/(num+1);
							j=getc(averages);
							//printf("%f\t%c",new_avg,j);
							fseek(averages,-7,SEEK_CUR);
							if(new_avg<10)
								fputc('0',averages);
							printf("%.1f;%d",new_avg,num+1);
							fprintf(averages,"%.1f;%d",new_avg,num+1);
						}
						else{
							fclose(averages);
							averages=fopen("averages.txt","a");
							if(rating<10)
								fprintf(averages,"%s:0%d.0;1/\n",movie,rating);
							else
								fprintf(averages,"%s:%d.0;1/\n",movie,rating);
						}
						fclose(averages);
						fclose(UserFile);
						fclose(movies);
						fclose(MovieDetails);
						fflush(stdin);
						break;
						}
					}
				}

				else{
					fclose(averages);
					fclose(UserFile);
					fclose(movies);
					fclose(MovieDetails);
					fflush(stdin);
				}
		}
	}

	else{
		printf("\n\t\t\t\aCould not find \"%s\" in database\n\t\t\tPress any key to exit search....",movie);
		getch();
		fclose(UserFile);
		fclose(movies);
		fclose(MovieDetails);
		fflush(stdin);
	}
}

void showratings()
{
	int i;
	char dir[100];
	FILE *ratings;
	sprintf(dir,"%s.txt",CurrentUser);
	ratings=fopen(dir,"r");
	printf("All ratings of user %s:\n\n",CurrentUser);
	while((i=getc(ratings))!=EOF){
		if(i==';')
			i=getc(ratings);
		printf("%c",i);
		if(i==':')
			printf(" ",i);
	}

	printf("__________________________________________________\nEnd of record");
	fclose(ratings);
	printf("\n\nEnter any button to stop viewing");
	getch();
}




void SearchYear()
{
	int year,i=0,j=0,k=0,c=0,fnum=0,num=0,found=0;
	FILE *movies;
	FILE *MovieDetails;
	char movie[100];
	movies=fopen("movies.txt","r");
	MovieDetails=fopen("MovieDetails.txt","r");
	system("cls");
	printf("Enter year: ");
	scanf("%d",&year);

	printf("\n\nList of movies released in %d in the database\n\n",year);

	while(i!=EOF){
		i=getc(MovieDetails);

		while(i!=':')
			i=getc(MovieDetails);

		i=getc(MovieDetails);
		i=getc(MovieDetails);

		while(isdigit(i)){
			num=num*10+(i-'0');
			i=getc(MovieDetails);
		}
		if(year==num){
			found++;
			c=getc(movies);
			for(j=0;j!=fnum;j++){
				while(c!=';')
					c=getc(movies);
				c=getc(movies);
			}
			while(1){
				movie[k++]=c;
				c=getc(movies);
				if(c==';')
					break;
			}
			movie[k]='\0';
			printf("%s",movie);
		}
		fnum++;
		rewind(movies);
		k=0;

		while(i!='\\')
			i=getc(MovieDetails);

		i=getc(MovieDetails);
		i=getc(MovieDetails);
		num=0;
	}
	if(found ==0)
		printf("\nNo movies found\n\nPress any key to exit search");
	else
		printf("\n\n\nEnd of record\nPress any key to exit");
	fclose(MovieDetails);
	fclose(movies);
	fflush(stdin);
	getchar();
}

void SearchByDirector()
{
	int year,i=0,j=0,k=0,c=0,fnum=0,num=0,found=0;
	FILE *movies;
	FILE *MovieDetails;
	char movie[100];
	char dirInDetails[100];
	char director[100];
	movies=fopen("movies.txt","r");
	MovieDetails=fopen("MovieDetails.txt","r");
	system("cls");
	printf("Enter director name: ");
	gets(director);

	printf("\n\nList of movies directed by %s in the database\n\n",director);

	while(i!=EOF){
		for(j=0;j<3;j++){
			i=getc(MovieDetails);
			while(i!=':')
				i=getc(MovieDetails);
			i=getc(MovieDetails);
			i=getc(MovieDetails);
		}
	
		j=0;
		while(i!='\n'){
			dirInDetails[j++]=i;
			i=getc(MovieDetails);
		}
		
		dirInDetails[j] = '\0';
		
		if(!strcmp(director,dirInDetails)){
			found++;
			c=getc(movies);
			for(j=0;j!=fnum;j++){
				while(c!=';')
					c=getc(movies);
				c=getc(movies);
			}
			while(1){
				movie[k++]=c;
				c=getc(movies);
				if(c==';')
					break;
			}
			movie[k]='\0';
			printf("%s",movie);
		}
		fnum++;
		rewind(movies);
		k=0;

		while(i!='\\')
			i=getc(MovieDetails);

		i=getc(MovieDetails);
		i=getc(MovieDetails);
	}
	if(found ==0)
		printf("\nNo movies found\n\nPress any key to exit search");
	else
		printf("\n\n\nEnd of record\nPress any key to exit");
	fclose(MovieDetails);
	fclose(movies);
	fflush(stdin);
	getchar();
}

int ynmenu(char instructions[])
{
    char x[4]={"   "},y='>';
    int opt,c,i;
    int cpos=0;
    x[0]=y;

    while (1){
        system("cls");
    	printf("%s",instructions);
        printf("\n\n");
        printf("\t\t\t%c%c",x[0],x[0]);
        printf("YES\n\n");
        printf("\t\t\t%c%c",x[1],x[1]);
        printf("NO\n\n");

        opt=_getch();

        if (opt==0 || opt==224){
        	opt=_getch();
         	
			 if (opt==72){
        		if (cpos==0)
                	cpos=2;
            	
				cpos--;
            	
				for (c=0;c<2;c++)
                	x[c]=' ';
            	x[cpos]=y;
        	}

        	else if (opt==80){
        		if (cpos==1)
                	cpos=-1;
				cpos++;
            
				for (c=0;c<2;c++)
                	x[c]=' ';
            
				x[cpos]=y;
        	}
        }

        else if (opt==13)
            break;
        
		system("cls");
    }
    switch (cpos){
        case 0:
            return 1;
            break;
        case 1:
            return 0;
            break;
     }
}
