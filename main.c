#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <string.h>

static void menu(void) {

    printf("\n====== 図書館管理システム ======\n");
    printf("1. 本を追加\n");
    printf("2. 本の一覧\n");
    printf("3. タイトルで検索\n");
    printf("4. 著者で検索\n");
    printf("5. 本を借りる\n");
    printf("6. 本を返す\n");
    printf("7. 本を削除\n");
    printf("0. 終了\n");
    printf("選択してください: ");
}

int main(void) {

    int choice;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int year;
    int id;
    init_library(void);

    while (1) {

        menu(void);
        scanf("%d", &choice);
        getchar(void);

        switch (choice) {

            case 1:
                printf("タイトル: ");
                fgets(title, TITLE_LEN, stdin);
                title[strcspn(title, "\n")] = 0;

                printf("著者: ");
                fgets(author, AUTHOR_LEN, stdin);
                author[strcspn(author, "\n")] = 0;

                printf("出版年: ");
                scanf("%d", &year);
                getchar();

                add_book(title, author, year);
                break;
                
            case 2:
                list_books();
                break;

            case 3:
                printf("検索するタイトル: ");
                fgets(title, TITLE_LEN, stdin);
                title[strcspn(title, "\n")] = 0;
                {
                    Book *b = search_book_by_title(title);

                    if (b) {

                        printf("見つかりました -> ID:%d タイトル:%s 著者:%s\n", b->id, b->title, b->author);

                    } else {

                        printf("本が見つかりませんでした。\n");
                    }
                }
                break;

            case 4:
                printf("検索する著者: ");
                fgets(author, AUTHOR_LEN, stdin);
                author[strcspn(author, "\n")] = 0;
                {
                    Book *b = search_book_by_author(author);

                    if (b) {

                        printf("見つかりました -> ID:%d タイトル:%s 著者:%s\n", b->id, b->title, b->author);

                    } else {

                        printf("本が見つかりませんでした。\n");
                    }
                }
                break;

            case 5:
                printf("借りたい本のID: ");
                scanf("%d", &id);
                getchar();
                borrow_book(id);
                break;
                
            case 6:
                printf("返す本のID: ");
                scanf("%d", &id);
                getchar();
                return_book(id);
                break;

            case 7:
                printf("削除する本のID: ");
                scanf("%d", &id);
                getchar();
                remove_book(id);
                break;

            case 0:
                printf("終了します。\n");
                exit(0);
                
            default:
                printf("無効な選択です。\n");
                break;
        }
    }
    return 0;
}
