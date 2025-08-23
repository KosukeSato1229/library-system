#include <stdio.h>
#include <string.h>
#include "library.h"

static Book library[MAX_BOOKS];
static int book_count = 0;

void init_library(void) {
    
    book_count = 0;

    for (int i = 0; i < MAX_BOOKS; i++) {

        library[i].id = -1;
    }
}

int add_book(const char *title, const char *author, int year) {
    
    if (book_count >= MAX_BOOKS) {

        printf("ライブラリが満杯です。\n");
        
        return 0;
    }
    
    library[book_count].id = book_count + 1;
    strncpy(library[book_count].title, title, TITLE_LEN - 1);
    strncpy(library[book_count].author, author, AUTHOR_LEN - 1);
    library[book_count].year = year;
    library[book_count].is_borrowed = 0;
    
    book_count++;

    return 1;
}

void list_books(void) {

    printf("\n--- 図書一覧 ---\n");

    if (book_count == 0) {

        printf("現在登録されている本はありません。\n");

        return;
    }

    for (int i = 0; i < book_count; i++) {

        printf("ID: %d | タイトル: %s | 著者: %s | 出版年: %d | 状態: %s\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].year,
                library[i].is_borrowed ? "貸出中" : "利用可");
    }
}

Book* search_book_by_title(const char *title) {

    for (int i = 0; i < book_count; i++) {

        if (strcmp(library[i].title, title) == 0) {

            return &library[i];
        }
    }
    return NULL;
}

Book* search_book_by_author(const char *author) {

    for (int i = 0; i < book_count; i++) {

        if (strcmp(library[i].author, author) == 0) {

            return &library[i];
        }
    }
    return NULL;
}

Book* search_book_by_id(int id) {

    for (int i = 0; i < book_count; i++) {

        if (library[i].id == id) {

            return &library[i];
        }
    }
    return NULL;
}

int borrow_book(int id) {

    Book *book = search_book_by_id(id);

    if (!book) {

        printf("ID %d の本は存在しません。\n", id);

        return 0;
    }

    if (book->is_borrowed) {

        printf("この本はすでに貸出中です。\n");

        return 0;
    }

    book->is_borrowed = 1;
    printf("「%s」を借りました。\n", book->title);

    return 1;
}

int return_book(int id) {

    Book *book = search_book_by_id(id);

    if (!book) {

        printf("ID %d の本は存在しません。\n", id);

        return 0;
    }

    if (!book->is_borrowed) {

        printf("この本は貸し出されていません。\n");

        return 0;
    }
    book->is_borrowed = 0;
    printf("「%s」を返却しました。\n", book->title);

    return 1;
}

int remove_book(int id) {

    int index = -1;

    for (int i = 0; i < book_count; i++) {

        if (library[i].id == id) {

            index = i;

            break;
        }
    }

    if (index == -1) {

        printf("指定されたIDの本は存在しません。\n");

        return 0;
    }

    for (int i = index; i < book_count - 1; i++) {

        library[i] = library[i + 1];
    }

    book_count--;
    printf("本を削除しました。\n");

    return 1;
}