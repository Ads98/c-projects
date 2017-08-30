#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct play
    {
        int user_id;
        int artist_id;
        int playcount;
        struct play *next;
    };

struct artist
    {
        int artist_id;
        int artist_count;
        int alt_id;
        char artist_name[64];
        struct artist *next;
    };

struct list
{
    void *val;
    struct list *next;
};


struct artist* search(int artistId, struct artist** index,int size)
{
    int first=0;
    int last=size-1;
    int middle =(first+last)/2;
    int i;

    while (first<=last)
    {
        if (size==0)
        {
            printf("NULL\n");
            return NULL;
        }
        else if (artistId==index[middle]->artist_id)
        {
            printf("artist name: %s artist ID: (%d) count: %d\n",  index[middle]->artist_name, index[middle]->artist_id,index[middle]->artist_count);
            return index[middle];
        }
        else if ( index[middle]->artist_id<artistId)
        {
            first=middle+1;
        }
        else
        {
            last=middle -1;
        }
        middle=(first+last)/2;
    }
        if (first>last)
        {
                printf("cannot be found\n");
            return NULL;
        }
}


struct artist **create_index(struct artist *head, int n) {
  int i = 0;
  struct artist **index = NULL;
  index = (struct artist **)malloc(n*sizeof(struct artist_index *));

  if( index != NULL )
    for(i=0; i<n && head != NULL; i++, head=head->next)
    {
        index[i] = head;

      }
  return index;
}

void print_play(struct play *p)
{
  struct play *head;
  head=p;
  if (head==NULL)
  {
    printf("NULL\n");
  }
   else

    printf("user: %d artist: %d count: %d\n", head->user_id, head->artist_id, head->playcount);

}


void print_plays(struct play*p)
{
     struct play *head;
     for( head = p; head != NULL; head=head->next )
     {
        print_play(head);
     }


}

int count_plays(struct play *head)
{
    int total=0;
    struct play *p;
     for( p = head; p != NULL; p=p->next )
        {
             total=total+p->playcount;
        }
    return total;
}


struct play *create_play(int user_id, int artist_id, int count)
{
    struct play *head=
    (struct play *)malloc(sizeof(struct play));
    if( head == NULL )
    {
        printf(" error memoar allocation was unsuccessful\n");
        head = NULL;
    }
    else
        head->user_id = user_id;
        head->artist_id = artist_id;
        head->playcount = count;
        head->next=NULL;
        return head;
    }



void free_play(struct play *p)
 {
    struct play *tmp;
        tmp = p;
        free(tmp);
}

void free_plays(struct play *p)
 {
    struct play *tmp;
    while( p != NULL )
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
}

struct play *add_play(struct play *head, struct play *newp)
{
    if (newp != NULL)
    {
        if (head != NULL)
        {
            newp->next=head;
        }
        else
        {
            head=newp;
        }
        return newp;
    }
    else
    return head;

}


struct play *read_plays(char *file_name)
{
    FILE *artist;
    char str[1000];
    int a,b,c;
    struct play *start=NULL;

    artist=fopen(file_name,"r");
    if (artist ==NULL)
    {
        printf("error cannot open file");
    }
    else
    {
       while(fgets(str,1000, artist) != NULL)
       {
            sscanf(str,"%d %d %d",&a,&b,&c);
            start=add_play(start,create_play(a,b,c));
       }
    }
    fclose(artist);
    return start;
}


struct play *filter_artist(int artist_id, struct play *head)
{
     struct play *p;
     struct play *user=NULL;
     while( head != NULL )
     {
        p=head;
        head=head->next;
        if (p->artist_id !=artist_id)
        {
            free(p);
        }
        else
        {
            user=add_play(user,create_play(p->user_id,p->artist_id,p->playcount));
        }

     }
     return user;
}

struct play *filter_user(int user_id, struct play *head)
{
     struct play *p;
     struct play *user=NULL;
     while( head != NULL )
     {
        p=head;
        head=head->next;
        if (p->user_id !=user_id)
        {
            free(p);
        }
        else
        {
            user=add_play(user,create_play(p->user_id,p->artist_id,p->playcount));
        }

     }
     return user;
}





struct artist *create_artist(int artist_id, char *artistName)
{
    struct artist *head=
    (struct artist *)malloc(sizeof(struct artist));
    if( head == NULL )
    {
        printf(" error memoary allocation was unsuccessful\n");
        head = NULL;
    }
    else
        head->artist_id = artist_id;
        strcpy(head->artist_name,artistName);
        //head->artist_name=(char*)artistName;
        head->artist_count=0;
        head->next=NULL;
        return head;
    }




struct artist *add_artist(struct artist *head, struct artist *newp)
{
    if (newp != NULL)
    {
        if (head != NULL)
        {
            newp->next=head;
        }
        else
        {
            head=newp;
        }
        return newp;
    }
    else
    return head;


}

void write_playCount(struct artist *cur,int playerId,char*file_name)
{
    FILE *artist;
    char str[1000];
    int count, valid,a,b;
    struct play *start=NULL;
    artist=fopen(file_name,"r");
    if (artist ==NULL)
    {
        printf("error cannot open file") ;
    }
    else
    {
      do
       {
            valid=0;
            if (fgets(str,1000, artist) != NULL)
            {
                valid=1;
                sscanf(str,"%d %d %d",&a,&b,&count);
                if (a==cur->artist_id)
                cur->artist_count=count;
            }

        }
         while( a!=playerId || valid!=0);

    }
}

struct artist *read_artists(char *fname,int *number)

{
    FILE *users;
    char str[1000];
    int a;
    int size;
    char b[64];
    struct artist *start=NULL;
    struct artist *person=NULL;

    users=fopen(fname,"r");
    if (users ==NULL)
    {
        printf("error cannot open file");
    }
    else
    {
        size=*number;
       while(fgets(str,1000, users) != NULL)
       {
            sscanf(str,"%d\t%65[^\t\n]\n",&a,b);
            person=create_artist(a,b);
            start=add_artist(start,person);
            size++;
       }
       *number=size;
    }
    fclose(users);
    return start;


}




void print_artist(struct artist *a)
{
  struct artist *head= NULL;
  head=a;
  if (head==NULL)
  {
    printf("NULL artist\n");
  }
   else
    printf("artist name: %s artist ID: (%d) count: %d\n",  head->artist_name, head->artist_id,head->artist_count);


}

void print_artists(struct artist *a,int k)
{
     struct artist *head;
     int count=0;
     count=0;
     for( head = a; count==k; count++ )
     {
        print_artist(head);
        head=head->next;
     }


}

/*void print_generic(struct list *a)
{
  struct list *head;
  struct artist *artist_head;
  head=a;
  if (head==NULL)
  {
    printf("NULL\n");
  }
    else
    artist_head=((struct artist*)head->val);
    printf("artist name: %s artist ID: (%d) count: [%d]\n",  artist_head->artist_id, artist_head->artist_name,artist_head->artist_count);

}*/


/*void print_list (struct list*a,int k)
{
    struct list *head;
    int count=0;


    for( head = a; count=k; count++ )
     {
        print_generic(head);
        head=head->next;
     }
}*/

void free_artists(struct artist *a)
 {
    struct artist *tmp;
    while( a != NULL )
    {
        tmp = a;
        a = a->next;
        free(tmp);
    }
}





int compare_decplaycount (struct artist *a, struct artist *b)
{
   return  ( a->artist_count <  b->artist_count);

}

int compare_incplaycount (struct artist *a, struct artist *b)
{
   return  ( a->artist_count >  b->artist_count);

}

int compare_decartist (struct artist *a, struct artist *b)
{
    //printf("dec artist\n");
    //scanf("%c");
    return  ( a->artist_id <  b->artist_id);

}

int compare_incartist (struct artist*a, struct artist *b)
{
    //printf("test inc id\n");
    //printf("id 1 = %d, id2= %d\n",a->artist_id,b->artist_id);
   //return  ((struct artst *) a)-> artist_id > ((struct artist *) b)-> artist_id;
   return  (a->artist_id > b->artist_id);

}



struct artist *merge_artistId(struct artist  *x, struct artist *y,int (*comp)(struct artist *a,struct artist *b))
{
    struct artist *tmp  = NULL;
    struct artist *head = NULL;
    struct artist*curr = NULL;
    if( x == NULL )
    return y;
    else
    if( y == NULL )
    return x;
    while
    ( x != NULL && y != NULL)
    {
       // printf("sorting\n");
        //printf("x = %d, y = %d\n",x->artist_id,y->artist_id);
         if( comp(x, y))
         {
            //printf("comp\n");
            tmp = y;
            y   = x;
            x   = tmp;
         }
        if( head == NULL)
        {
            //printf("head\n");
            head = x;
            curr = x;
        }
        else
        {
      //  printf("curr= \n");
            curr->next = x;
            curr = curr->next;
        }
        x = x->next;
    }
    if( x != NULL)
    curr->next = x;
    else
    if (y !=NULL)
    curr->next = y;
   // printf("sorted\n");
    return head;
}

struct artist *merge_artist_count(struct artist  *x, struct artist *y,int (*comp)(struct artist *a,struct artist *b))
{
    struct artist *tmp  = NULL;
    struct artist *head = NULL;
    struct artist*curr = NULL;
    if( x == NULL )
    return y;
    else
    if( y == NULL )
    return x;
    while
    ( x != NULL && y != NULL)
    {
        if( comp(x, y))
         {
            tmp = y;
            y   = x;
            x   = tmp;
         }
        if( head == NULL)
        {
            head = x;
            curr = x;
        }
        else
        {
            curr->next = x;
            curr = curr->next;
        }
        x = x->next;
    }
    if( x == NULL)
    curr->next = y;
    else
    curr->next = x;
    return head;
}


struct artist* find_middle_art(struct artist *x)
{
    struct artist *slow = x;
    struct artist* fast = x;
    while( fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


struct artist* merge_count_sort(struct artist *head, char* sortType)
        {
            struct artist *m = NULL;
            struct artist *x = NULL;
            struct artist *y =NULL;
            int comparison;
            if ( head == NULL || head->next == NULL )
            return head;
            x = head;
            m = find_middle_art(head);
            y = m->next;
            m->next = NULL;
            if (strcmp(sortType,"inc_pc")==0)
            return  merge_artist_count( merge_count_sort(x,sortType), merge_count_sort(y,sortType),compare_incplaycount);
            if (strcmp(sortType,"dec_pc")==0)
            return  merge_artist_count( merge_count_sort(x,sortType), merge_count_sort(y,sortType),compare_decplaycount);
            }



        struct artist* merge_artist_sort(struct artist *head, int (*comp)(struct artist *a, struct artist *b))
        {
            struct artist *m = NULL;
            struct artist *x = NULL;
            struct artist *y =NULL;
            int comparison;
            //printf("here\n");
            if ( head == NULL || head->next == NULL )
            return head;
            x = head;
            m = find_middle_art(head);
            y = m->next;
            m->next = NULL;
            //printf("testing\n");
            //printf("a= %d ,b=%d\n",x->artist_id,y->artist_id);
            return  merge_artistId( merge_artist_sort(x,comp), merge_artist_sort(y,comp),comp);


        }



struct play *merge(struct play *x, struct play *y)
{
    struct play *tmp  = NULL;
    struct play *head = NULL;
    struct play*curr = NULL;
    if( x == NULL )
    return y;
    else
    if( y == NULL )
    return x;
    while
    ( x != NULL && y != NULL)
    {
        if( x->artist_id > y->artist_id)
         {
            tmp = y;
            y   = x;
            x   = tmp;
         }
        if( head == NULL)
        {
            head = x;
            curr = x;
        }
        else
        {
            curr->next = x;
            curr = curr->next;
        }
        x = x->next;
    }
    if( x == NULL)
    curr->next = y;
    else
    curr->next = x;
    return head;
}




/*struct list *merge_generic(struct list *x, struct list *y,int comp)
{
    struct list *tmp  = NULL;
    struct list *head = NULL;
    struct list*curr = NULL;
    if( x == NULL )
    return y;
    else
    if( y == NULL )
    return x;
    while( x != NULL && y != NULL)
    {
        if( comp !=0)
         {
            tmp = y;
            y   = x;
            x   = tmp;
         }
        if( head == NULL)
        {
            head = x;
            curr = x;
        }
        else
        {
            curr->next = x;
            curr = curr->next;
        }
        x = x->next;
    }
    if( x == NULL)
    curr->next = y;
    else
    curr->next = x;
    if (head==NULL)
        printf("generic=NULL");

    return head;
}*/


struct play* find_middle(struct play *x)
{
    struct play *slow = x;
    struct play* fast = x;
    while( fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct list* find_centre(struct list *x)
{
    struct list *slow = x;
    struct list* fast = x;
    while( fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}



struct play* merge_sort(struct play *head)
        {
            struct play *m = NULL;
            struct play *x = NULL;
            struct play *y =NULL;
            if ( head == NULL || head->next == NULL )
            return head;
            x = head;
            m = find_middle(head);
            y = m->next;
            m->next = NULL;
            return  merge( merge_sort(x), merge_sort(y));
        }

/*struct list *sort_list(struct list *head,int crteria)

{
    struct list *m = NULL;
    struct list *x = NULL;
    struct list *y =NULL;
    int *funcP;
    int comparison;
    if ( head == NULL || head->next == NULL )
    {
        if (head==NULL)
        printf("head=null\n");
        else
        printf("next=null\n");
        return head;
    }
    printf ("sorting\n");
    x = head;
    m = find_centre(head);
    y = m->next;
    m->next = NULL;
    if (crteria==0)
    {

    comparison =compare_playcount(sort_list(x,crteria),sort_list(y,crteria));
    return merge_generic(sort_list(x,crteria),sort_list(y, crteria),crteria);
    }
    if (crteria==1)
    {

    comparison =compare_artist(sort_list(x,crteria),sort_list(y,crteria));
    return merge_generic(sort_list(x,crteria),sort_list(y, crteria),comparison);
    }

 //return  merge_generic( sort_list(x), sort_list(y), compare_playcount ((void *)x, (void *)y),compare_playcount( (void *)x, (void *)y),compare_playcount( (void *)x, (void *)y));

}*/


void exit_usage() {
  printf("USAGE: query_plays file command\n"
         "\n"
         "where command is one of\n"
         "\n"
         "   p <userid>  prints plays, optionally limited to user.\n"
         "   c <userid>  counts plays, optionally limited to user.\n");
   exit(1);
}

void Test_task1()
{
    struct play *test_play = NULL;
    print_play(test_play);
    test_play = create_play(1,2,3);
    print_play(test_play);
    free_play(test_play);

}

void Test_task2()
{
    printf("task 2 \n");
    struct play *a = create_play(1,2,3);
    struct play *b = create_play(4,5,6);
    a = add_play(a, NULL);
    a = add_play(a, b);
    print_plays(a);
    printf("There are %d plays in a.\n", count_plays(a));
}









struct list *create_generic()
{
    struct play *plays=NULL;
    struct artist* artists=NULL;
    struct list*newE=NULL;
    //sort play  file
    struct list *head=
    (struct list *)malloc(sizeof(struct list));
    if( head == NULL )
    {
        printf(" error memoary allocation was unsuccessful\n");
        head = NULL;
    }
    else
    {
        head->val=NULL;
        head->next=NULL;
    }
    return head;
}







struct list *add_list (struct list *head, struct artist *a,char *file_name)
{
    struct list *newp=NULL;
    struct artist *artist_head=NULL;
    for( artist_head = a; artist_head != NULL; artist_head=artist_head->next)
    {
        newp=create_generic();
        if (newp != NULL)
        {
            if (head != NULL)
            {
                //newp=create_generic();
                newp->next=head;
                newp->val=artist_head;

            }

            else
            {
                head=newp;
            }
            return newp;
        }
        else
        if (head==NULL)
        {
            printf("null add\n");

            return head;
        }
    }
}



struct artists *update_counts (struct artist* artists ,struct play *plays)

{
    struct artist *preserve=NULL;
    preserve=artists;
    while (artists != NULL && plays != NULL)
    {
        if(plays->artist_id > artists->artist_id)
        {
            artists=artists->next;
        }
        else
        if (plays->artist_id < artists->artist_id)
        {
            plays=plays->next;
        }
        else
        if (artists->artist_id == plays->artist_id)
        {
            artists->artist_count= artists->artist_count+ plays->playcount;
            plays=plays->next;
        }
    }
    return preserve;
}

struct artist * sort_all(char *fileA, char *fileP,int (*comp)(struct artist *a, struct artist *b))
{
    struct play *plays=NULL;
    struct artist *a =NULL;
    struct artist* artists=NULL;
    struct artist*head=NULL;
    struct plays *p=NULL;
    struct artist *pres=NULL;
    struct list *returnval;
    int option, PID,count;
    int number;
    char choice;
    printf("over here\n");
    //get play list
    //sort play  file
    plays= merge_sort(read_plays(fileP));

    //sort artist file
    printf("hi\n");
    artists= merge_artist_sort(read_artists(fileA,&number),compare_incartist);
    printf ("adam\n");
    head=update_counts(artists, plays);
    print_artist(head);
    printf("now here\n");

    head=merge_artist_sort(head,comp);
    count=0;
    a=head;
    do
    //for (a=head; count==k;count++)
    {
        print_artist(a);
        a=a->next;
    }
    while(a !=NULL);
    //updating palys count

    return head;
     //
}

find_artist(struct artist* head,int num,int ID)
{
    struct artist** I;
    head= merge_artist_sort(head,compare_incartist);
    I=create_index(head,num);
    if (I==NULL)
        printf("NULL\n");
    search(ID,create_index(head,num),num);

}



int main(int argc, char **argv)
   {
    int user;
    int artist;
    int count;
    int *p;
    int sortType;
    struct artist *head;
    char con;
    struct play *begin=NULL;
        switch(argc)
          {print_plays(read_plays(argv[1]));
            case 1:
                Test_task1();
                Test_task2();
                break;
            case 3:
                printf("arg 2\n");
                if (strcmp(argv[2],"c")==0)
                {
                    printf("%d\n",count_plays(read_plays(argv[1])));
                    break;
                }
                if (strcmp(argv[2],"p")==0)
                    {

                        print_plays(read_plays(argv[1]));

                    }
                    else
                    {

                       count=0;
                       sortType=(int) strtol(argv[1], (char **)NULL, 10);
                        head=read_artists(argv[2],&count);
                        //p=&count;
                       find_artist(head,count,sortType);
                    }

                break;
            case 4:
                sscanf(argv[3],"%d",&artist);
                //begin=filter_user(user, read_plays(argv[1]));
                if (strcmp(argv[2],"c")==0)
                {
                    printf("%d\n",count_plays(filter_artist(artist,read_plays(argv[1]))));
                }
                if (strcmp(argv[2],"p")==0)
                {
                     print_plays(filter_artist(artist,read_plays(argv[1])));
                }

                //if (strcmp(argv[2],"k")==0)
                else
                    {
                        //sortType=(int) strtol(argv[1], (char **)NULL, 10);
                        if (strcmp(argv[3],"inc_id")==0)

                        sort_all(argv[1],argv[2],compare_incartist);

                        if (strcmp(argv[3],"dec_id")==0)

                        sort_all(argv[1],argv[2],compare_decartist);

                        if (strcmp(argv[3],"inc_pc")==0)

                        sort_all(argv[1],argv[2],compare_incplaycount);

                        if (strcmp(argv[3],"dec_pc")==0)

                        sort_all(argv[1],argv[2],compare_decplaycount);

                    }
                break;

    }

        if (argc==2||argc>4)
                {
                    printf("error invalid number of argumnets");
                }
        return 0;
}
