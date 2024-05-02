/**
 * @file maze.c
 * @author Igor Kaminski
 * @brief Code for the maze game for COMP1921 Assignment 2
 * NOTE - You can remove or edit this file however you like - this is just a provided skeleton code
 * which may be useful to anyone who did not complete assignment 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// defines for max and min permitted dimensions
#define MAX_DIM 100
#define MIN_DIM 5

// defines for the required autograder exit codes
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

typedef struct Coord
{
    int x;
    int y;
} coord;

typedef struct Maze
{
    char **map;
    int height;
    int width;

} maze;

/**
 * @brief Initialise a maze object - allocate memory and set attributes
 *
 * @param this pointer to the maze to be initialised
 * @param height height to allocate
 * @param width width to allocate
 * @return int 0 on success, 1 on fail
 */

int create_maze(maze *this, int height, int width) {
    this->height = height;
    this->width = width;

    this->map = malloc(sizeof(char*) * height);
    if (this->map == NULL) return 1;

    for (int i = 0; i < height; i++) {
        this->map[i] = malloc(sizeof(char) * (width + 1));
        if (this->map[i] == NULL) {
            while (--i >= 0) free(this->map[i]);
            free(this->map);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Free the memory allocated to the maze struct
 *
 * @param this the pointer to the struct to free
 */

void free_maze(maze *this) {
    if (this == NULL) return;
    for (int i = 0; i < this->height; i++) {
        free(this->map[i]);
    }
    free(this->map);
}

/**
 * @brief Validate and return the width of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid width (5-100)
 */

int get_width(FILE *file) {
    char buffer[MAX_DIM + 2];
    if (fgets(buffer, sizeof(buffer), file) == NULL) return 0;

    if (strchr(buffer, '\n') == NULL) {
        return 0;
    }

    int width = strlen(buffer) - 1;
    if (width < MIN_DIM || width > MAX_DIM) return 0;
    rewind(file);

    return width;
}

/**
 * @brief Validate and return the height of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid height (5-100)
 */
int get_height(FILE *file) {
    int lines = 0;
    char buffer[MAX_DIM + 2];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strchr(buffer, '\n') == NULL) {
            return 0;
        }
        lines++;
    }

    if (lines < MIN_DIM || lines > MAX_DIM) {
        return 0;
    }
    rewind(file);
    return lines;
}


/**
 * @brief Read in a maze file into a struct, validate single 'S' and 'E', and ensure only valid characters are used.
 *
 * @param this Maze struct to be used
 * @param file Maze file pointer
 * @return int 0 on success, 1 on fail
 */

int read_maze(maze *this, FILE *file) {
    char buffer[MAX_DIM + 2];
    int startCount = 0, exitCount = 0;
    char validChars[] = "# SE\n";

    for (int i = 0; i < this->height; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) return 1;

        for (int j = 0; buffer[j] != '\0' && j < this->width; j++) {
            if (strchr(validChars, buffer[j]) == NULL) {
                printf("Invalid character '%c' found in the maze.\n", buffer[j]);
                return 1;
            }
            if (buffer[j] == 'S') startCount++;
            if (buffer[j] == 'E') exitCount++;
        }

        strncpy(this->map[i], buffer, this->width);
        this->map[i][this->width] = '\0';
    }

    if (startCount != 1 || exitCount != 1) {
        printf("Error: Maze must contain exactly one start ('S') and one exit ('E').\n");
        return 1;
    }

    return 0;
}


/**
 * @brief Prints the maze out
 *
 * @param this pointer to maze to print
 * @param player the current player location
 */
void print_maze(maze *this, coord *player)
{
    printf("\n");
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (player->x == j && player->y == i)
            {
                printf("X");
            }
            else
            {
                printf("%c", this->map[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Validates and performs a movement in a given direction
 *
 * @param this Maze struct
 * @param player The player's current position
 * @param direction The desired direction to move in
 */
void move(maze *this, coord *player, char direction) {
    int newX = player->x;
    int newY = player->y;

    switch (direction) {
        case 'W': case 'w':
            newY--; break;
        case 'A': case 'a':
            newX--; break;
        case 'S': case 's':
            newY++; break;
        case 'D': case 'd':
            newX++; break;
    }

    if (newX >= 0 && newX < this->width && newY >= 0 && newY < this->height) {
        if (this->map[newY][newX] != '#') {
            player->x = newX;
            player->y = newY;
            if (this->map[newY][newX] == 'E') {
                printf("Congratulations, you reached the exit!\n");
                exit(EXIT_SUCCESS);
            }
        } else {
            printf("Move not allowed.\n");
        }
    } else {
        printf("Move not allowed.\n");
    }
}


/**
 * @brief Find the starting position 'S' in the maze and initialise the player's coordinates.
 *
 * @param this Pointer to the maze structure.
 * @param player Pointer to the player's coordinates.
 */
void find_start_position(maze *this, coord *player) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->map[i][j] == 'S') {
                player->x = j;
                player->y = i;
                return;
            }
        }
    }
}

/**
 * @brief The main game loop which handles user inputs and updates the game state accordingly.
 *
 * @param this Pointer to the initialised maze structure.
 */
void game_loop(maze *this) {
    coord player;
    find_start_position(this, &player);
    char input;

    do {
        print_maze(this, &player);
        printf("Enter command (WASD to move, M to view map, Q to quit): ");
        scanf(" %c", &input);

        switch (input) {
            case 'M': case 'm':
                print_maze(this, &player);
                break;
            case 'Q': case 'q':
                return;
            default:
                move(this, &player, input);
                break;
        }
    } while (true);
}

/**
 * @brief Main function which initialises everything, processes the command line arguments and handles file operations
 *
 * @param argc Argument count
 * @param argv Argument values
 * @return int EXIT_SUCCESS on normal exit, various EXIT_* codes on errors.
 */

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./maze <mazefile name>\n");
        return EXIT_ARG_ERROR;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Error: Unable to open maze file '%s'.\n", argv[1]);
        return EXIT_FILE_ERROR;
    }

    int width = get_width(f);
    int height = get_height(f);
    if (width == 0 || height == 0) {
        fclose(f);
        return EXIT_MAZE_ERROR;
    }

    maze *this_maze = malloc(sizeof(maze));
    if (!create_maze(this_maze, height, width)) {
        if (read_maze(this_maze, f) != 0) {
            printf("Error: Failed to load the maze from file.\n");
            free_maze(this_maze);
            fclose(f);
            return EXIT_MAZE_ERROR;
        }
    } else {
        printf("Error: Failed to initialise maze structure.\n");
        fclose(f);
        return EXIT_MAZE_ERROR;
    }
    fclose(f);
    game_loop(this_maze);

    free_maze(this_maze);
    free(this_maze);

    return EXIT_SUCCESS;


}