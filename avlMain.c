#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

//#define NDEBUG
#include <assert.h>

#include "avlTree.h"

#define TEST_MODE

extern int isVerbose;
extern int nodeCount;
extern int rotationCount;

#define OPTIONS "hvt:"

#ifdef TEST_MODE
static void runTests(int);
#else // TEST_MODE

static int operationCount = 0;

static int getKey(void);
#endif // TEST_MODE

#ifdef TEST_MODE
static void
runTests(int testNumber)
{
    // Validate with
    //     https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

    int testsPassed = 0;

    if (testNumber == 0 || testNumber == 1) {
        node_t *root = NULL;

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        root = NULL;
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 2) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left == NULL);
        assert(root->right == NULL);

        assert(nodeCount == 1);
        assert(root->height == 1);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 3) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right == NULL);

        assert(root->left != NULL);
        assert(root->left->key == 5);
        assert(root->left->count == 1);

        assert(nodeCount == 2);
        assert(root->height == 2);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 4) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);
        root = insertNode(root, 5);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right == NULL);

        assert(root->left->key == 5);
        assert(root->left->count == 2);
        assert(root->left->left == NULL);
        assert(root->left->right == NULL);

        assert(nodeCount == 2);
        assert(root->height == 2);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 5) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);

        root = insertNode(root, 15);
        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 5);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 5);
        assert(root->left->count == 6);
        assert(root->left->left == NULL);
        assert(root->left->right == NULL);

        assert(root->right->key == 15);
        assert(root->right->count == 1);
        assert(root->right->left == NULL);
        assert(root->right->right == NULL);

        assert(nodeCount == 3);
        assert(root->height == 2);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 6) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);
        root = insertNode(root, 15);

        root = insertNode(root, 4);
        root = insertNode(root, 6);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 5);
        assert(root->left->count == 1);

        assert(root->right->key == 15);
        assert(root->right->count == 1);

        assert(root->left->right->key == 6);
        assert(root->left->right->count == 1);

        assert(root->left->left->key == 4);
        assert(root->left->left->count == 1);

        assert(nodeCount == 5);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 7) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);
        root = insertNode(root, 15);

        root = insertNode(root, 4);
        root = insertNode(root, 6);

        root = insertNode(root, 14);
        root = insertNode(root, 16);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 5);
        assert(root->left->count == 1);

        assert(root->right->key == 15);
        assert(root->right->count == 1);

        assert(root->left->right->key == 6);
        assert(root->left->right->count == 1);

        assert(root->left->left->key == 4);
        assert(root->left->left->count == 1);

        assert(root->right->right->key == 16);
        assert(root->right->right->count == 1);

        assert(root->right->left->key == 14);
        assert(root->right->left->count == 1);

        assert(nodeCount == 7);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 8) {
        node_t *root = NULL;

        root = insertNode(root, 1);
        root = insertNode(root, 2);
        root = insertNode(root, 2);
        root = insertNode(root, 2);
        root = insertNode(root, 3);
        root = insertNode(root, 3);

        assert(root != NULL);
        assert(root->key == 2);
        assert(root->count == 3);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->right->key == 3);
        assert(root->right->count == 2);
        assert(root->right->left == NULL);
        assert(root->right->right == NULL);

        assert(root->left->key == 1);
        assert(root->left->count == 1);
        assert(root->left->right == NULL);
        assert(root->left->left == NULL);

        assert(root->height == 2);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 9) {
        node_t *root = NULL;

        root = insertNode(root, 1);
        root = insertNode(root, 1);
        root = insertNode(root, 2);
        root = insertNode(root, 3);
        root = insertNode(root, 3);
        root = insertNode(root, 4);
        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 5);

        assert(root != NULL);
        assert(root->key == 2);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 1);
        assert(root->left->count == 2);
        assert(root->left->left == NULL);
        assert(root->left->right == NULL);

        assert(root->right->key == 4);
        assert(root->right->count == 1);
        assert(root->right->left != NULL);
        assert(root->right->right != NULL);

        assert(root->right->left->key == 3);
        assert(root->right->left->count == 2);
        assert(root->right->left->left == NULL);
        assert(root->right->left->right == NULL);

        assert(root->right->right->key == 5);
        assert(root->right->right->count == 3);
        assert(root->right->right->left == NULL);
        assert(root->right->right->right == NULL);

        assert(nodeCount == 5);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 10) {
        node_t *root = NULL;

        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 4);
        root = insertNode(root, 3);
        root = insertNode(root, 3);
        root = insertNode(root, 3);

        assert(root != NULL);
        assert(root->key == 4);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 3);
        assert(root->left->count == 3);
        assert(root->left->left == NULL);
        assert(root->left->right == NULL);

        assert(root->right->key == 5);
        assert(root->right->count == 2);
        assert(root->right->left == NULL);
        assert(root->right->right == NULL);

        assert(nodeCount == 3);
        assert(root->height == 2);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 11) {
        node_t *root = NULL;

        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 4);
        root = insertNode(root, 4);
        root = insertNode(root, 4);
        root = insertNode(root, 3);
        root = insertNode(root, 2);
        root = insertNode(root, 2);
        root = insertNode(root, 1);

        assert(root != NULL);
        assert(root->key == 4);
        assert(root->count == 3);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 2);
        assert(root->left->count == 2);
        assert(root->left->left != NULL);
        assert(root->left->right != NULL);

        assert(root->right->key == 5);
        assert(root->right->count == 2);
        assert(root->right->left == NULL);
        assert(root->right->right == NULL);

        assert(root->left->left->key == 1);
        assert(root->left->left->count == 1);
        assert(root->left->left->left == NULL);
        assert(root->left->left->right == NULL);

        assert(root->left->right->key == 3);
        assert(root->left->right->count == 1);
        assert(root->left->right->left == NULL);
        assert(root->left->right->right == NULL);

        assert(nodeCount == 5);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 12) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 15);

        root = insertNode(root, 4);
        root = insertNode(root, 6);

        root = insertNode(root, 14);
        root = insertNode(root, 16);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 5);
        assert(root->left->count == 2);

        assert(root->right->key == 15);
        assert(root->right->count == 1);

        assert(root->left->right->key == 6);
        assert(root->left->right->count == 1);

        assert(root->left->left->key == 4);
        assert(root->left->left->count == 1);

        assert(root->right->right->key == 16);
        assert(root->right->right->count == 1);

        assert(root->right->left->key == 14);
        assert(root->right->left->count == 1);

        assert(nodeCount == 7);

        root = deleteNode(root, 4);
        assert(root->left->left == NULL);
        assert(root->left->key == 5);
        assert(root->left->count == 2);

        assert(nodeCount == 6);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 13) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 5);

        root = insertNode(root, 15);

        root = insertNode(root, 4);
        root = insertNode(root, 4);

        root = insertNode(root, 14);
        root = insertNode(root, 16);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 5);
        assert(root->left->count == 3);

        assert(root->right->key == 15);
        assert(root->right->count == 1);

        assert(root->left->left->key == 4);
        assert(root->left->left->count == 2);

        assert(nodeCount == 6);

        root = deleteNode(root, 5);

        assert(root->left->left == NULL);
        assert(root->left->right == NULL);
        assert(root->left->key == 4);
        assert(root->left->count == 2);

        assert(nodeCount == 5);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 14) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);
        root = insertNode(root, 5);
        root = insertNode(root, 5);

        root = insertNode(root, 15);

        root = insertNode(root, 6);
        root = insertNode(root, 6);
        root = insertNode(root, 6);
        root = insertNode(root, 6);
        root = insertNode(root, 6);

        root = insertNode(root, 14);
        root = insertNode(root, 16);

        root = insertNode(root, 17);
        root = insertNode(root, 18);
        root = insertNode(root, 19);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 5);
        assert(root->left->count == 3);
        assert(root->left->left == NULL);

        assert(root->left->right->key == 6);
        assert(root->left->right->count == 5);

        assert(root->right->key == 17);
        assert(root->right->count == 1);

        assert(root->right->right->key == 18);
        assert(root->right->right->right->key == 19);

        assert(root->right->left->key == 15);
        assert(root->right->left->left->key == 14);
        assert(root->right->left->right->key == 16);

        assert(nodeCount == 9);
        assert(root->height == 4);

        root = deleteNode(root, 5);
        root = insertNode(root, 10);
        root = insertNode(root, 10);
        root = insertNode(root, 15);

        assert(nodeCount == 8);
        assert(root->height == 4);

        assert(root != NULL);
        assert(root->key == 17);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 10);
        assert(root->left->count == 3);
        assert(root->left->left != NULL);

        assert(root->left->left->key == 6);
        assert(root->left->left->count == 5);

        assert(root->left->right->key == 15);
        assert(root->left->right->count == 2);

        assert(root->left->right->left->key == 14);
        assert(root->left->right->right->key == 16);

        assert(root->right->key == 18);
        assert(root->right->right->key == 19);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 15) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);

        root = insertNode(root, 15);

        root = insertNode(root, 4);
        root = insertNode(root, 3);

        assert(root != NULL);
        assert(root->key == 10);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(root->left->key == 4);

        assert(root->right->key == 15);

        assert(root->left->left->key == 3);
        assert(root->left->right->key == 5);

        assert(nodeCount == 5);
        assert(root->height == 3);

        root = deleteNode(root, 15);

        assert(root->key == 4);
        assert(root->left->key == 3);
        assert(root->left->left == NULL);
        assert(root->left->right == NULL);

        assert(root->right->left->key == 5);
        assert(root->right->right == NULL);

        assert(nodeCount == 4);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 16) {
        node_t *root = NULL;

        root = insertNode(root, 10);

        root = insertNode(root, 5);

        root = insertNode(root, 15);

        root = insertNode(root, 2);
        root = insertNode(root, 6);

        root = insertNode(root, 12);
        root = insertNode(root, 16);

        assert(root->key == 10);

        assert(root->left->key == 5);
        assert(root->right->key == 15);

        assert(root->left->left->key == 2);
        assert(root->left->right->key == 6);

        assert(root->right->left->key == 12);
        assert(root->right->right->key == 16);

        assert(nodeCount == 7);
        assert(root->height == 3);

        //printf("Preorder 1 %2d: ", testNumber);
        //preOrder(root);
        //printf("\n");

        root = deleteNode(root, 10);

        //printf("Preorder 2 %2d: ", testNumber);
        //preOrder(root);
        //printf("\n");

        assert(root->key == 6);

        assert(root->left->key == 5);
        assert(root->left->right == NULL);

        assert(root->left->left->key == 2);

        assert(root->right->key == 15);
        assert(root->right->left->key == 12);
        assert(root->right->right->key == 16);

        assert(nodeCount == 6);
        assert(root->height == 3);

        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 17) {
        node_t *root = NULL;
        node_t *node = NULL;
        int i = 0;

        for (i = 1; i <= 12; i++) {
            root = insertNode(root, i);
        }

        assert(nodeCount == 12);
        assert(root->height == 4);

        assert(root->key == 8);
        assert(root->left->key == 4);
        assert(root->right->key == 10);

        assert(root->left->left->key == 2);
        assert(root->left->right->key == 6);

        assert(root->left->left->left->key == 1);
        assert(root->left->left->right->key == 3);

        assert(root->left->right->left->key == 5);
        assert(root->left->right->right->key == 7);

        assert(root->right->left->key == 9);
        assert(root->right->right->key == 11);

        assert(root->right->right->right->key == 12);


        node = findKey(root, 10);
        assert(node->key == 10);
        assert(node->count == 1);

        node = findKey(root, 5);
        assert(node->key == 5);
        assert(node->count == 1);

        node = findKey(root, 2);
        assert(node->key == 2);
        assert(node->count == 1);

        node = findKey(root, 8);
        assert(node->key == 8);
        assert(node->count == 1);

        node = findKey(root, 11);
        assert(node->key == 11);
        assert(node->count == 1);

        node = findKey(root, 18);
        assert(node == NULL);

        printf("root: %d  count: %d  height: %d\n", root->key, nodeCount, root->height);
        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 18) {
        node_t *root = NULL;
        int i = 0;

        for (i = 1; i <= 100; i++) {
            root = insertNode(root, i);
        }

        assert(root != NULL);
        assert(root->key == 64);
        assert(root->count == 1);
        assert(root->left != NULL);
        assert(root->right != NULL);

        assert(nodeCount == 100);
        assert(root->height == 7);

        printf("root: %d  count: %d  height: %d\n", root->key, nodeCount, root->height);
        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 19) {
        node_t *root = NULL;
        int i = 0;
        int j = 0;

        for (i = 50, j = i - 1; i <= 100; i++, j--) {
            root = insertNode(root, i);
            root = insertNode(root, j);
        }

        assert(root != NULL);
        assert(root->key == 50);

        assert(nodeCount == 102);
        assert(root->height == 7);
        
        printf("root: %d  count: %d  height: %d\n", root->key, nodeCount, root->height);
        printf("Preorder %2d: ", testNumber);
        preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 20) {
        node_t *root = NULL;
        int i = 0;

        srand(3);
        for (i = 1; i <= 100; i++) {
            root = insertNode(root, rand());
        }

        assert(root != NULL);
        assert(root->key == 844158168);

        assert(nodeCount == 100);
        assert(root->height == 8);
        
        printf("root: %d  count: %d  height: %d\n", root->key, nodeCount, root->height);
        printf("Preorder %2d: no tree printed", testNumber);
        //preOrder(root);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    if (testNumber == 0 || testNumber == 21) {
        node_t *root = NULL;
        int i = 0;

        srand(3);
        for (i = 1; i <= 10000; i++) {
            root = insertNode(root, rand());
        }

        assert(root != NULL);
        assert(root->key == 1119448937);

        assert(nodeCount == 10000);
        assert(root->height == 16);
        
        printf("root: %d  count: %d  height: %d\n", root->key, nodeCount, root->height);
        printf("Preorder %2d: no tree printed", testNumber);
        printf("\n");

        freeTree(root);
        testsPassed++;
    }

    printf("You passed %d tests\n", testsPassed);
}
#else // TEST_MODE

static int
getKey(void)
{
    char chkey[20] = {0};
    
    fgets(chkey, sizeof(chkey), stdin);
    return atoi(chkey);
}
#endif // TEST_MODE

int
main(int argc, char *argv[])
{
#ifdef TEST_MODE
    int testNumber = 0;
#endif // TEST_MODE

    {
        char opt;

        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
            case 'h':
                fprintf(stderr, "%s %s\n", argv[0], OPTIONS);
                exit(EXIT_SUCCESS);
                break;
            case 't':
#ifdef TEST_MODE
                testNumber = atoi(optarg);
#endif // TEST_MODE
                break;
            case 'v':
                isVerbose++;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s %s\n", argv[0], OPTIONS);
                exit(EXIT_FAILURE);
            }
        }
    }

#ifdef TEST_MODE

    runTests(testNumber);

#else // TEST_MODE
    {
        node_t *root = NULL; 
        int ch = '-';
        int key = 0;
        int done = FALSE;
        node_t *node = NULL;
        struct timeval tv0;
        struct timeval tv1;
        double elapse_time = 0.0D;
        char junk[10] = {0};

        // should switch to fgets to fetch the line and get rid of the newline
        while ((!done) && ((ch = fgetc(stdin)) != EOF)) {
            switch (ch) {
            case 'I':
                // insert key
                if (isVerbose) {
                    fprintf(stderr, "** insertNode key: %d\n", key);
                }
                key = getKey();
                root = insertNode(root, key);
                operationCount++;

                break;
            case 'D':
                // delete key
                if (isVerbose) {
                    fprintf(stderr, "** deleteNode key: %d\n", key);
                }

                key = getKey();
                root = deleteNode(root, key);
                operationCount++;

                break;
            case 'F':
                // search/find key
                if (isVerbose) {
                    fprintf(stderr, "** findKey key: %d\n", key);
                }
                key = getKey();
                node = findKey(root, key);
                if (node) {
                    fprintf(stdout, "key found: %d  height: %d\n", node->key, node->height);
                }
                else {
                    fprintf(stdout, "key not found: %d\n", key);
                }
                operationCount++;

                break;
            case 'B':
                // begin time
                gettimeofday (&tv0, NULL);
                operationCount = 0;
                rotationCount = 0;

                // this clears out the rest of the line (such as the newline character)
                fgets(junk, sizeof(junk), stdin);

                break;
            case 'E':
                // end time
                gettimeofday (&tv1, NULL);
                elapse_time = (((double) (tv1.tv_usec - tv0.tv_usec)) / MICROSECONDS_PER_SECOND)
                    + ((double) (tv1.tv_sec - tv0.tv_sec));
                fprintf(stdout, "Elapse time: %12.6lf seconds   Operations: %d\n"
                        , elapse_time, operationCount);

                // this clears out the rest of the line (such as the newline character)
                fgets(junk, sizeof(junk), stdin);

                break;
            case 'S':
                // stats
                fprintf(stdout, "Height: %d   Node Count: %d   Operations: %d   Rotations: %d\n"
                        , root->height, nodeCount, operationCount, rotationCount);

                // this clears out the rest of the line (such as the newline character)
                fgets(junk, sizeof(junk), stdin);

                break;
            case 'P':
                // print the avl tree
                // i may have more than one way to print the tree
                fprintf(stdout, "\nInorder traversal  (height: %d   node count: %d)\n"
                        , root->height, nodeCount); 
                inOrder(root);
                fprintf(stdout, "\n");

                fprintf(stdout, "\nPretty print\n"); 
                print2D(root, 0);
                fprintf(stdout, "\n");

                // this clears out the rest of the line (such as the newline character)
                fgets(junk, sizeof(junk), stdin);

                break;
            case 'C':
                // clean up everything, back to empty tree
                freeTree(root);
                root = NULL;
                nodeCount = 0;
                operationCount = 0;
                rotationCount = 0;

                // this clears out the rest of the line (such as the newline character)
                fgets(junk, sizeof(junk), stdin);

                break;
            case 'Q':
                // quit
                done = TRUE;

                // this clears out the rest of the line (such as the newline character)
                fgets(junk, sizeof(junk), stdin);

                break;
            case 'V':
                // emable verbose mode
                isVerbose = (isVerbose ? FALSE : TRUE);
                if (isVerbose) {
                    fprintf(stderr, ">> verbose enabled <<\n");
                }

                // this clears out the rest of the line (such as the newline character)
                fgets(junk, sizeof(junk), stdin);

                break;
            default:
                fprintf(stderr, "** unrecognized command: %c **\n", ch);
                break;
            }
        }
        freeTree(root);
        root = NULL;
    }
#endif // TEST_MODE

    return EXIT_SUCCESS;
} 
