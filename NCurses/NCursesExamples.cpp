#include <iostream>
    #if(_LINUXANSI_)
#include <locale>
    #else
#include <windows.h>
    #endif
#include <ncurses.h>

#define EXAMPLE_NRO 4

    #if(EXAMPLE_NRO == 1 || EXAMPLE_NRO == 2 || EXAMPLE_NRO == 4)
int main() {
    #elif(EXAMPLE_NRO == 3)
int main(int argc, char *argv[]) {
    #endif

    // Output functions example
    #if(EXAMPLE_NRO == 1)
    char mesg[]="Just a string";        /* message to be appeared on the screen */
    int row,col;                        /* to store the number of rows and *
                                         * the number of colums of the screen */
    initscr();                          /* start the curses mode */
    getmaxyx(stdscr,row,col);           /* get the number of rows and columns */
    mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
                                        /* print the message at the center of the screen */
    mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
    printw("Try resizing your window(if possible) and then run this program again");
    refresh();
    getch();
    endwin();

    #elif(EXAMPLE_NRO == 2)
    // Input functions example
    char mesg[]="Enter a string: ";     /* message to be appeared on the screen */
    char str[80];
    int row,col;                        /* to store the number of rows and *
                                         * the number of colums of the screen */
    initscr();                          /* start the curses mode */
    getmaxyx(stdscr,row,col);           /* get the number of rows and columns */
    mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
                                        /* print the message at the center of the screen */
    getstr(str);
    mvprintw(LINES - 2, 0, "You Entered: %s", str);
    getch();
    endwin();

    #elif(EXAMPLE_NRO == 3)
    // Attributes example (pager functionality by Joseph Spainhour" <spainhou@bellsouth.net>)
    int ch, prev, row, col;
    prev = EOF;
    FILE *fp;
    int y, x;

    if(argc != 2)
    {
        printf("Usage: %s <a c file name>\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        perror("Cannot open input file");
        exit(1);
    }
    initscr();                      /* Start curses mode */
    getmaxyx(stdscr, row, col);     /* find the boundaries of the screeen */
    while((ch = fgetc(fp)) != EOF)  /* read the file till we reach the end */
    {
        getyx(stdscr, y, x);        /* get the current curser position */
        if(y == (row - 1))          /* are we are at the end of the screen */
        {
            printw("<-Press Any Key->");    /* tell the user to press a key */
            getch();
            clear();                /* clear the screen */
            move(0, 0);             /* start at the beginning of the screen */
        }
        if(prev == '/' && ch == '*')        /* If it is / and * then only
                                             * switch bold on */    
        {
            attron(A_BOLD);         /* cut bold on */
            getyx(stdscr, y, x);    /* get the current curser position */
            move(y, x - 1);         /* back up one space */
            printw("%c%c", '/', ch);        /* The actual printing is done here */
        }
        else
            printw("%c", ch);
        refresh();
        if(prev == '*' && ch == '/')
            attroff(A_BOLD);        /* Switch it off once we got *
                                     * and then / */
        prev = ch;
    }
    endwin();                       /* End curses mode */
    fclose(fp);

    #elif(EXAMPLE_NRO == 4)
    // Chgat() example
    initscr();              /* Start curses mode 		*/
    start_color();          /* Start color functionality	*/
	
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    printw("A Big string which i didn't care to type fully ");
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);	
    /* 
     * First two parameters specify the position at which to start 
     * Third parameter number of characters to update. -1 means till 
     * end of line
     * Forth parameter is the normal attribute you wanted to give 
     * to the charcter
     * Fifth is the color index. It is the index given during init_pair()
     * use 0 if you didn't want color
     * Sixth one is always NULL 
     */
    refresh();
    getch();
    endwin();

    #endif

    return 0;
}
