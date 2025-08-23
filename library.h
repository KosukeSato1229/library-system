// gcc -o library-system main.c library.c

#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100
#define TITLE_LEN 100
#define AUTHOR_LEN 100

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int year;
    int is_borrowed;
} Book;

// ライブラリ管理
void init_library();
int add_book(const char *title, const char *author, int year);
void list_books();
Book* search_book_by_title(const char *title);
Book* search_book_by_author(const char *author);
Book* search_book_by_id(int id);
int borrow_book(int id);
int return_book(int id);
int remove_book(int id);

#endif
